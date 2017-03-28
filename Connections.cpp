#include "Connections.h"

Connections::Connections(){
	
}

Connections::~Connections(){
	Req_set.clear()
}

Request* Connections::get_connection(int fd){
	locker.lock();
	Request *ret = NULL;
	if(Req_set.find(fd)!=Req_set.end()){
		ret = Req_set[fd];
	}
	locker.unlock();
	return ret;
}

bool Connections::add_connection(int fd, Request req){
	locker.lock();
	Req_set.insert(make_pair<int,string>(fd,req));
	bool ret = true;
	if(Req_set.find(fd)==Req_set.end())
		ret = false;
	locker.unlock();
	return ret;
}