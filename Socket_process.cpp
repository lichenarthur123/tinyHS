#include "Socket_process.h"

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
			strncpy(tt,read_buffer,read_size-res);
			strncpy(tt+(read_size-res),t_buffer,res);
			delete[] read_buffer;
			read_buffer = tt;
		}
		
	}
}