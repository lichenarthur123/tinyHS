#include "Socket_process.h"
/*
Socket_process::Socket_process(int epollfd,int conn)
{
	_epollfd = epollfd;
	_conn = conn;
	t_buffer = new char[READ_BUF_SIZE];
	read_buffer = new char[READ_BUF_SIZE];
	read_size = 0;
	write_buffer = new char[READ_BUF_SIZE];
	write_size = 0;
	
	read_from_socket();
}

Socket_process::~Socket_process()
{
	close(conn);
	delete[] read_buffer;
	delete[] write_buffer;
	delete[] t_buffer;
}
Socket_process::conn_unfinish = new Connections_unfinish();
Socket_process::read_from_socket(){
	while(true){
		int res = recv(_conn,t_buffer,READ_BUF_SIZE,0);
		read_size += res;
		if(res == 0){
			close(_conn);
			break;
		}
		else if(res < 0){
			if(errno == EINTR || errno == EAGAIN){
				break;
			}
		}
		else{
			char *tt = new char[read_size];
			strncpy(tt,t_buffer,read_size-res);
			strncpy(tt+(read_size-res),t_buffer,res);
			delete[] read_buffer;
			read_buffer = tt;
		}
		
	}
}*/
char* read_from_socket(int conn,int &size){
	char *t_buffer = new char[READ_BUF_SIZE];
	char *read_buffer = new char[READ_BUF_SIZE];
	int read_size = 0;
	bool flag = true;
	while(true){
		int ret = recv(conn,t_buffer,READ_BUF_SIZE,0);
		read_size += ret;
		if(ret == 0){
			close(conn);
			flag = false;
			break;
		}
		else if(ret < 0){
			if(errno != EINTR && errno != EAGAIN){
				close(conn);
				flag = false;
			}
			break;
		}
		else{
			char *tt = new char[read_size];
			strncpy(tt,read_buffer,read_size-ret);
			strncpy(tt+(read_size-ret),t_buffer,ret);
			delete[] read_buffer;
			read_buffer = tt;
		}
	}
	if(flag){
		size = read_size;
		return read_buffer;
	}
	else{
		size = 0;
		return NULL;
	}
}