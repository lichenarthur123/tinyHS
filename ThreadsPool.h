#ifndef THREADSPOOL_H
#define THREADSPOOL_H

#include<queue>
#include<vector>
#include<map>
#include<iostream>
#include "Connections.h"
#include<pthread.h>
#include "Sem_Lock.h"
#include "Socket_process.h"

#define MAX_REQUEST 1000000

class ThreadsPool
{
    private:
        int _thread_num;
        int _request_max;
        std::vector<pthread_t> threads;
        std::queue<Socket_process*> r_queue;
		std::map<int,Connections> conn_pool;
        Lock locker;
        Semaphore status_queue;
        bool is_work;

        static void* worker(void* arg);
        //void* worker(void* arg);   //if you use C++11 or higher worker doesn't need static.
				void run();
    public:
        ThreadsPool(int thread_num = 20,int request_max = MAX_REQUEST);
        virtual ~ThreadsPool();
        bool add(Socket_process *request);
    protected:
};

#endif // THREADSPOOL_H
