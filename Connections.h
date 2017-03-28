#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include<iostream>
#include<string.h>
#include<map>
#include<pthread.h>
#include "Sem_Lock.h"
#include "Http_parser.h"


class Connections_unfinish{
	public:
		Connections_unfinish();
		virtual ~Connections_unfinish();
		Request* get_connection(int fd);
		bool add_connection(int fd,Request req);
	private:
		Lock locker;
		map<int,Request> Req_set;
}
#endif