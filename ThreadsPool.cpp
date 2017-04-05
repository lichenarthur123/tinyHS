#include "ThreadsPool.h"

ThreadsPool::ThreadsPool(int thread_num,int request_max):_thread_num(thread_num),_conn_max(request_max),is_work(true){
    threads.clear();
    threads.resize(_thread_num);
    for(int i=0; i< _thread_num; i++){
        std::cout<<"create thread "<<i<<"."<<std::endl;
        if(pthread_create(&threads[i],NULL,worker,this)!=0){
            threads.clear();
            break;
        }
        else if(pthread_detach(threads[i])){
            threads.clear();
            break;
        }
    }
    std::cout<<"threads create complete."<<std::endl;
    std::cout<<"is_work is true"<<std::endl;
}

ThreadsPool::~ThreadsPool(){
    threads.clear();
    while(!conn_pool.empty()){
        conn_pool.pop();
    }
    req_pool.clear();
    res_pool.clear();
    is_work = false;
}

bool ThreadsPool::add(int epollfd,int conn,char *read_buff,int buff_size,int req_or_res){
    locker.lock();
    if(conn_pool.size() >= _conn_max){
        locker.unlock();
        return false;
    }
    if(req_or_res == 0){//request
        connection con;
        con.conn = conn;
        con.request_or_response = 0;
        con.epollfd = epollfd;
        conn_pool.push(con);

        //add to request pool
        std::map<int,Request*>::iterator it;
        it = req_pool.find(conn);
        std::cout<<"inin"<<std::endl;
        if(it != req_pool.end()){//found
            int old_size = req_pool[conn]->content_size;
            char *old_buff = req_pool[conn]->content;
            char *new_buff = new char[old_size+buff_size];
            strncpy(new_buff,old_buff,old_size);
            strncpy(new_buff+old_size,read_buff,buff_size);
            delete[] old_buff;
            req_pool[conn]->content = new_buff;
            req_pool[conn]->content_size = old_size+buff_size;
            //return true;
        }
        else{
            Request *r;
            request_init(&r);
            std::cout<<"insert null"<<std::endl;
            r->content_size = buff_size;
            std::cout<<"insert null"<<std::endl;
            r->content = read_buff;
            req_pool.insert(std::make_pair<int,Request*>(conn,r));
            std::cout<<req_pool.size()<<std::endl;

            std::cout<<"insert null"<<std::endl;
            //return true;
	}
    }
    locker.unlock();
    std::cout<<conn_pool.size()<<std::endl;
    status_queue.post();
    return true;
}

void* ThreadsPool::worker(void* arg){
    ThreadsPool *tp = (ThreadsPool*)arg;
    tp->run();
    return tp;
}

void ThreadsPool::run(){
    while(is_work){
	//std::cout<<"1"<<std::endl;
        status_queue.wait();
        locker.lock();
        if(conn_pool.empty()){
            locker.unlock();
            continue;
        }
        std::cout<<conn_pool.size()<<std::endl;
        connection c = conn_pool.front();
        conn_pool.pop();
        if(c.request_or_response == 0){//request
            std::map<int,Request*>::iterator it;
            it = req_pool.find(c.conn);
            std::cout<<req_pool.size()<<std::endl;
            if(it!=req_pool.end()){//found
                Request *req = it->second;
                std::cout<<"parsering"<<std::endl;
                //parser request
                http_parser(req);
                std::cout<<req->req_line->content<<std::endl;
                std::cout<<req->req_line->method<<std::endl;
                std::cout<<req->req_line->version<<std::endl;
                if(req->req_line->url->abs_path)
                std::cout<<req->req_line->url->abs_path<<std::endl;
                if(req->req_line->url->query)
                std::cout<<req->req_line->url->query<<std::endl;
                if(req->req_line->url->fragment)
                std::cout<<req->req_line->url->fragment<<std::endl;
            }
            else{
                continue;
            }
        }
        locker.unlock();
    }
}

