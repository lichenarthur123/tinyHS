#include "HttpServer.h"

HttpServer::HttpServer(int port)
{
    _port = port;
    _pool = new ThreadsPool();
}

HttpServer::~HttpServer()
{
    delete _pool;
}
void HttpServer::add_event(int epollfd,int sock,bool oneshot){
    epoll_event event;
    event.data.fd = sock;
    event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    if(oneshot){
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,sock,&event);
    int t = fcntl(sock, F_GETFL);
    fcntl(sock, F_SETFL, t | O_NONBLOCK);
}
void HttpServer::run()
{
    int sock = socket(AF_INET,SOCK_STREAM,0);
    int optval = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
    struct sockaddr_in server_sockaddr;
    memset(&server_sockaddr,0,sizeof(server_sockaddr));
    server_sockaddr.sin_port = htons(_port);
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock,(struct sockaddr*)&server_sockaddr,sizeof(server_sockaddr));

    listen(sock,SOMAXCONN-1);

    struct epoll_event ev[MAX_EVENTS];
    int epollfd = epoll_create(SOMAXCONN);
    add_event(epollfd, sock, false);

    while(true){
        int ready_num = epoll_wait(epollfd, ev, MAX_EVENTS, -1);
				std::cout<<ready_num<<std::endl;
        for(int i = 0; i < ready_num; i++){
            int fd = ev[i].data.fd;
            if(sock == fd){
                std::cout<<"old"<<std::endl;
								struct sockaddr_in clientaddr;
                socklen_t clientaddr_l = sizeof(clientaddr);
                int conn = accept(sock,(struct sockaddr*)&clientaddr,&clientaddr_l);

                add_event(epollfd,conn,true);
            }
            else if(fd & EPOLLIN){
							  std::cout<<"in"<<std::endl;
                _pool->add(new Http_request(epollfd,fd));
            }
            //else if(fd & EPOLLOUT){
            //    _pool->add(new Http_request(epollfd,sock));
            //}
            else{
                close(fd);
            }
        }

    }
    close(sock);
}
