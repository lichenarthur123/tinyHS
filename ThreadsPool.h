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
#include "Http_parser.h"

#define MAX_REQUEST 1000000
struct connection{
	int conn;
	int request_or_response;//0:req,1:res
}
class ThreadsPool
{
    private:
        int _thread_num;
        int _conn_max;
        std::vector<pthread_t> threads;
        std::queue<conncetion> conn_pool;
		std::map<int,Request*> req_pool;
		std::map<int,Response*> res_pool;
        Lock locker;
        Semaphore status_queue;
        bool is_work;

        static void* worker(void* arg);
        //void* worker(void* arg);   //if you use C++11 or higher worker doesn't need static.
				void run();
    public:
        ThreadsPool(int thread_num = 20,int request_max = MAX_REQUEST);
        virtual ~ThreadsPool();
        bool add(int conn,char *buff,int buff_size,int req_or_res);
    protected:
};

#endif // THREADSPOOL_H
