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
    is_work = false;
}

bool ThreadsPool::add(Socket_process *request){
    locker.lock();
    if(r_queue.size() >= _request_max){
        locker.unlock();
        return false;
    }
    r_queue.push(request);
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

