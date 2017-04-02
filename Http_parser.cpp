#include "Http_parser.h"

void request_init(Request **r){
	*r = new Request;
};
void request_line_init(Request_line **rl){};
void request_header_init(Request_header **rh){};
void request_body_init(Request_body **rb){};
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