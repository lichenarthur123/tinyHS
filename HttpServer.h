#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include<iostream>
#include "ThreadsPool.h"
#include "Socket_process.h"
#include<sys/epoll.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

#define MAX_EVENTS 100000
class HttpServer
{
    public:
        HttpServer(int port = 8080);
        virtual ~HttpServer();
        void run();
    private:
        int _port;
        ThreadsPool *_pool;
        void add_event(int epollfd,int sock,bool one_shot);
};

#endif // HTTPSERVER_H
