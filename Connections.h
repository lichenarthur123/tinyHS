#include<iostream>
#include<map>
#include<pthread.h>
#include "Sem_Lock.h"
enum Req_method{GET,POST};
struct Request_line{
	
};
struct Request{
	char *body;
	bool is_finish;
	
};

class ConnectionPool{
	public:
		ConnectionPool();
		virtual ~ConnectionPool();
		
	private:
		Lock locker;
		map<>
}