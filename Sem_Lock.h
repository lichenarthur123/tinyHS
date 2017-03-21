#ifndef SEM_LOCK_H
#define SEM_LOCK_H
#include<iostream>
#include<pthread.h>
#include<semaphore.h>

class Semaphore{
    public:
        Semaphore(){
						if(sem_init(&_sem,0,0)!=0){
							std::cout<<"semaphore init error."<<std::endl;
						}
				}
        virtual ~Semaphore(){sem_destroy(&_sem);}
        bool wait(){return sem_wait(&_sem)==0;}
        bool post(){return sem_post(&_sem)==0;}
    private:
        sem_t _sem;
};
class Lock{
    public:
        Lock(){
					if(pthread_mutex_init(&_mutex,NULL)!=0){
						std::cout<<"mutex init error."<<std::endl;
					}
				}
        virtual ~Lock(){pthread_mutex_destroy(&_mutex);}
        bool lock(){return pthread_mutex_lock(&_mutex)==0;}
        bool unlock(){return pthread_mutex_unlock(&_mutex)==0;}
    private:
        pthread_mutex_t _mutex;
};

#endif // SEM_LOCK_H
