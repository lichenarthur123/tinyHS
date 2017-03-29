#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H
#include<iostream>
#include<string.h>
enum Req_method{GET,POST};
enum Http_version{HTTP09,HTTP10,HTTP11,HTTP20};
enum Parser_status{COMPLETE,MORE_DATA};
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
	char *cache-control;
	char *connection;
	char *content-length;
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
	char *body;
	Request_line *req_line;
	Request_header *req_header;
	Request_body *req_body;
	bool is_finish;
	
};
void request_init(Request *r){
	
}
void request_clear(Request *r){
	
}
class Http_parser{
	public:
		Http_parser(char *req_context,Request *req = NULL);
		~Http_parser();
		bool is_complete;
		Parser_status parser();
	private:
		char *req_context;
		Request *req;
};


#endif