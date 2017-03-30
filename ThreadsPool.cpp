#include "ThreadsPool.h"

ThreadsPool::ThreadsPool(int thread_num,int request_max):_thread_num(thread_num),_request_max(request_max),is_work(true){
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

bool ThreadsPool::add(int conn,char *read_buff,int buff_size,int req_or_res){
    locker.lock();
    if(r_queue.size() >= _request_max){
        locker.unlock();
        return false;
    }
	if(req_or_res == 0){//request
		connection con;
		con.conn = conn;
		con.request_or_response = 0;
		conn_pool.push(con);
		
		//add to request pool
		std::map<int,Request*>::iterator it;
		it = rep_pool.find(conn);
		if(it != rep_pool.end()){//found
			int old_size = rep_pool[conn]->content_size;
			char *old_buff = rep_pool[conn]->content;
			char *new_buff = new char[old_size+buff_size];
			strncpy(new_buff,old_buff,old_size);
			strncpy(new_buff+old_buff,read_buff,buff_size);
			delete[] old_buff;
			rep_pool[conn]->content = new_buff;
			req_pool[conn]->content_size = old_size+buff_size;
			return true;
		}
		else{
			Request *r;
			request_init(r);
			r->content_size = buff_size;
			r->content = read_buff;
			req_pool.insert(make_pair<int,Request*>(conn,r));
			return true;
		}
		
	}
    locker.unlock();
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
        status_queue.wait();
        locker.lock();
        if(r_queue.empty()){
            locker.unlock();
            continue;
        }
        Socket_process *r = r_queue.front();
        r_queue.pop();
        locker.unlock();
        if(r){
            std::cout<<"ok"<<std::endl;
            //r->process();
        }
    }
}

