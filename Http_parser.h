#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H
#include<iostream>
#include<string.h>
enum Req_method{GET,POST};
enum Http_version{HTTP09,HTTP10,HTTP11,HTTP20};
//enum Parser_status{COMPLETE,MORE_DATA};
struct URI{
	char *host;
	char *scheme;
	char *port;
	char *abs_path;
	char *extension;
	char *query;
};
struct Request_line{
	char *context;
	Req_method method;
	URI url;
	Http_version version;
	bool is_finish;
};
struct Request_header{
	char *context;
	char *accpet;
	char *accpet_charset;
	char *accpet_encoding;
	char *authorization;
	char *accpet_language;
	char *accpet_range;
	char *cache_control;
	char *connection;
	int  content-length;
	char *content-type;
	char *date;
	char *if_match;
	char *if_modified_since;
	char *if_none_match;
	char *if_range;
	char *if_unmodified-since;
	char *max_forward;
	char *pragma;
	char *proxy_authorization;
	char *range;
	char *referer;
	char *update;
	char *cookie;
	char *expect;
	char *from;
	char *host;
	char *te;
	char *user_agent;
	bool is_finish;
};
struct Request_body{
	char *context;
	bool is_finish;
};
struct Request{
	char *content;
	int content_size;
	Request_line *req_line;
	Request_header *req_header;
	Request_body *req_body;
	bool is_finish;
	
};
void request_init(Request *r);
void request_clear(Request *r);
struct Responses_line{
	Http_version　version;
	int status_code;
	char *status;
	bool is_finish;
};
struct Responses_header{
	char *accpet_range;
	char *age;
	char *allow;
	char *cache_control;
	char *content_encoding;
	char *content_language;
	int content_length;
	char *content_location;
	char *content_md5;
	char *content_range;
	char *content_type;
	char *date;
	char *etag;
	char *expires;
	char *last_modified;
	char *location;
	char *pragma;
	char *proxy_authorization;
	char *refresh;
	int retry_after;
	char *server;
	char *set_cookie;
	char *trailer;
	char *transfer_encoding;
	char *vary;
	char *via;
	char *warning;
	char *www_authenticate;
	bool is_finish;
};
struct Responses_body{
	char *context;
	bool is_finish;
};
struct Responses{
	char *content;
	int content_size;
	Responses_line *res_line;
	Responses_header *res_header;
	Responses_body *res_body;
	bool is_finish;
};
void Responses_init(Responses *r);
void Responses_clear(Responses *r);


#endif