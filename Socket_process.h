#ifndef SOCKET_PROCESS_H
#define SOCKET_PROCESS_H
#include<string>
#include<algorithm>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include "http_parser.h"

#define READ_BUF_SIZE 
class Socket_process
{
 public:
  Socket_process(int epollfd,int conn);
  virtual ~Socket_process();
  void process();
 private:
  void read_from_socket();
  int _epollfd;
  int _conn;
  char *read_buffer;
  char *write_buffer;
  http_request request;
};

#endif // SOCKET_PROCESS_H
