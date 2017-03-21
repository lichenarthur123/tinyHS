#ifndef THREADSPOOL_H
#define THREADSPOOL_H

#include<queue>
#include<vector>
#include<iostream>
#include<pthread.h>
#include "Sem_Lock.h"
#include "Http_request.h"

#define MAX_REQUEST 1000000

class ThreadsPool
{
    private:
        int _thread_num;
        int _request_max;
        std::vector<pthread_t> threads;
        std::queue<Http_request*> r_queue;
        Lock locker;
        Semaphore status_queue;
        bool is_work;

        static void* worker(void* arg);
        //void* worker(void* arg);   //if you use C++11 or higher worker doesn't need static.
				void run();
    public:
        ThreadsPool(int thread_num = 20,int request_max = MAX_REQUEST);
        virtual ~ThreadsPool();
        bool add(Http_request *request);
    protected:
};

#endif // THREADSPOOL_H
