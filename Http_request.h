#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H


class Http_request
{
 public:
  Http_request(int epollfd,int conn);
  virtual ~Http_request();
 protected:
 private:
};

#endif // HTTP_REQUEST_H
