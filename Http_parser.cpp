#include "Http_parser.h"
void request_line_init(Request_line **rl){
	*rl = new Request_line;
	(*rl)->url = new URI;
};
void request_header_init(Request_header **rh){
	*rh = new Request_header;
};
void request_body_init(Request_body **rb){
	*rb = new Request_body;
};
void request_init(Request **r){
	*r = new Request;
	(*r)->content = NULL;
	(*r)->content_size = 0;
	(*r)->is_finish = false;
	request_line_init(&((*r)->req_line));
	request_header_init(&((*r)->req_header));
	request_body_init(&((*r)->req_body));
};
void request_line_clear(Request_line **rl){};
void request_header_clear(Request_header **rh){};
void request_body_clear(Request_body **rb){};
void request_clear(Request **r){
	*r = NULL;
};
void Response_init(Response **r){
	*r = new Response;
};
void Response_line_init(Request_line **rl){};
void Response_header_init(Request_header **rh){};
void Response_body_init(Request_body **rb){};
void Response_line_clear(Request_line **rl){};
void Response_header_clear(Request_header **rh){};
void Response_body_clear(Request_body **rb){};
void Response_clear(Response **r){
	*r = NULL;
};
