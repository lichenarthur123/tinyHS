#ifndef SOCKET_PROCESS_H
#define SOCKET_PROCESS_H
#include<string.h>
#include<algorithm>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<errno.h>
#include "http_parser.h"
//#include "Connections.h"


#define READ_BUF_SIZE 2048
#define WRITE_BUF_SIZE 2048
/*class Socket_process
{
 public:
  Socket_process(int epollfd,int conn);
  virtual ~Socket_process();
  void process();
  static Connections_unfinish *conn_unfinish;
 private:
  void read_from_socket();
  void process();
  int _epollfd;
  int _conn;
  int read_size;
  int write_size;
  char *t_buffer;
  char *read_buffer;
  char *write_buffer;
  http_request request;
};
*/
char* read_from_socket(int conn,int &size);

#endif // SOCKET_PROCESS_H
