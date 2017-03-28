#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

enum Req_method{GET,POST};
enum Http_version{HTTP09,HTTP10,HTTP11,HTTP20}
struct Request_line{
	char *context;
	Req_method method;
	char *url;
	Http_version version;
	bool is_finish;
};
struct Request_header{
	char *context;
	map<string,string> rep_head_map;
	bool is_finish;
};
struct Request_body{
	char *context;
	bool is_over;
};
struct Request{
	char *body;
	Request_line req_line;
	Request_header req_header;
	Request_body req_body;
	bool is_finish;
	
};



#endif