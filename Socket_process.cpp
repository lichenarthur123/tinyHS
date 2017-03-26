#include "Socket_process.h"

Socket_process::Socket_process(int epollfd,int conn)
{
	_epollfd = epollfd;
	_conn = conn;
	read_buffer = new char[READ_BUF_SIZE];
	write_buffer = new char[WRITE_BUF_SIZE];
	
	read_from_socket();
}

Socket_process::~Socket_process()
{
	close(conn);
	delete[] read_buffer;
	delete[] write_buffer;
}
Socket_process::read_from_socket(){
	
}