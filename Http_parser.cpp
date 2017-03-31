#include "Http_parser.h"

void request_init(Request *r){
	r = new Request;
};
void request_clear(Request *r){
	r = NULL;
};
void Response_init(Response *r){
	r = new Response;
};
void Response_clear(Response *r){
	r = NULL;
};