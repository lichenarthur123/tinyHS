#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include<iostream>
#include<string.h>
#include<map>
#include<pthread.h>
#include "Sem_Lock.h"
#include "Http_parser.h"


class Connections{
	public:
		Connections();
		virtual ~Connections();
	private:
		Request *req;
		int fd;
		time_t alive_time;
}
#endif