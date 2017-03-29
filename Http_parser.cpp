#include "Http_parser.h"

Http_parser::Http_parser(char *req_context,Request *req){
	this->req_context = req_context;
	if(req!=NULL)
		this->req = req;
	else
		this->req = new Request;
	this->is_complete = false;
}