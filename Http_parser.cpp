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

int msg_header_iscomplete(char *content,int size){
	int s_end = 0;
	for(int i = 0; i<=size-4;i++){
		if(content[i]=='\r' && content[i+1]=='\n' && content[i+2]=='\r' && content[i+3]=='\n')
			s_end = i-1;
	}
	if(s_end == 0)
		return -1;
	else
		return s_end;
};

int get_req_line_end(char *msg_header,int size){
	int s_end = 0;
	for(int i = 0; i <= size-2; i++){
		if(msg_header[i]=='\r' && msg_header[i+1] =='\n'){
			s_end = i-1;
			break;
		}
	}
	if(s_end == 0)
		return -1;
	else
		return s_end;
};
bool parser_url(Request *r,char *url,int size){
	int quote = 0;
	int sharp = 0;
	for(int i = 0; i<size; i++){
		if(url[i] == '?')
			quote = i;
		if(url[i] == '#')
			sharp = i;
	}
	//std::cout<<quote<<" "<<sharp<<" "<<size<<std::endl;
	if(quote == 0)
		quote = size;
	if(sharp == 0)
		sharp = size;
	if(quote > 0){
		r->req_line->url->abs_path = new char[quote+1];
		strncpy(r->req_line->url->abs_path,url,quote);
		r->req_line->url->abs_path[quote]='\0';
	}
	if(quote<size){
		r->req_line->url->query = new char[sharp-quote];
		strncpy(r->req_line->url->query,url+quote+1,sharp-quote);
		r->req_line->url->query[sharp-quote]='\0';

	}
	if(sharp<size){
		r->req_line->url->fragment = new char[size-sharp];
		strncpy(r->req_line->url->fragment,url+sharp+1,size-sharp);
		r->req_line->url->fragment[size-sharp]='\0';
	}
	return true;
};
bool parser_req_line(Request *r,int req_line_end){
	int first_b=0;
	int second_b=0;
	for(int i=0; i<=req_line_end; i++){
		if(r->req_line->content[i]==' '){
			if(first_b!=0)
				second_b = i;
			else
				first_b = i;
			if(first_b!=0 && second_b!=0)break;
		}
	}
	//std::cout<<first_b<<" "<<second_b<<std::endl;
	if(first_b==0 || second_b==0)
		return false;
	char *method = new char[first_b+1];
	strncpy(method,r->req_line->content,first_b+1);
	if(strstr(method,"GET"))
		r->req_line->method = GET;
	else if(strstr(method,"POST"))
		r->req_line->method = POST;
	else{
		//501
		delete[] method;
		method = NULL;
		return false;
	}
	delete[] method;
	method = NULL;
	char *version = new char[req_line_end-second_b];
	strncpy(version,r->req_line->content+second_b+1,req_line_end-second_b);
	if(strstr(version,"HTTP/0.9"))
		r->req_line->version = HTTP09;
	else if(strstr(version,"HTTP/1.0"))
		r->req_line->version = HTTP10;
	else if(strstr(version,"HTTP/1.1"))
		r->req_line->version = HTTP11;
	else if(strstr(version,"HTTP/2.0"))
		r->req_line->version = HTTP20;
	else
		r->req_line->version = HTTP09;
	delete[] version;
	version = NULL;
	char *url = new char[second_b-first_b-1];
	strncpy(url,r->req_line->content+first_b+1,second_b-first_b-1);
	if(!parser_url(r,url,second_b-first_b-1)){
		//
		delete[] url;
		url = NULL;
		return false;
	}
	delete[] url;
	url = NULL;
	return true;

};
void parser_req_header_line(Request *r,char *line,int line_size){
	char *ox = new char[line_size+1];
	strncpy(ox,line,line_size);
	ox[line_size]='\0';
	//std::cout<<line_size<<std::endl;
	if(strstr(ox,"Connection")){
		if(strstr(ox,"close")){
			r->req_header->connection = 0;
		}else{
			r->req_header->connection = 1;
		}
	}
	if(strstr(ox,"Content-Length")){
		int p_idx = 14;
		int sta = 0,endd = line_size;
		//std::cout<<"  xxx  "<<std::endl;
		while(p_idx<line_size){
			//std::cout<<(int)ox[p_idx]<<std::endl;
			if((int)ox[p_idx]>='0'&&(int)ox[p_idx]<='9'&&sta==0){
				sta = p_idx;
				std::cout<<ox[p_idx]<<std::endl;
			}
			if(((int)ox[p_idx]<'0'||(int)ox[p_idx]>'9')&&sta>0){
				endd = p_idx;
				std::cout<<ox[p_idx-1]<<std::endl;
				break;
			}
			p_idx++;
		}
		std::cout<<"num "<<sta<<" "<<endd<<std::endl; 
		char *num = new char[endd-sta+1];
		strncpy(num,ox+sta,endd-sta);
		num[endd-sta]='\0';
		int cl = atoi(num);
		r->req_header->content_length = cl;
		delete[] num;
		num = NULL;
	}
	std::cout<<"header lines"<<std::endl;
	std::cout<<ox<<std::endl;
	delete[] ox;
	ox = NULL;
};
bool parser_req_header(Request *r,int header_size){
	std::cout<<"this is a header"<<std::endl;
	//std::cout<<r->req_header->content<<std::endl;
	//std::cout<<r->req_header->content_size<<std::endl;
	//std::cout<<header_size<<std::endl;
	//std::cout<<header_size<<std::endl;
	int sta=0;
	int p_idx = 0;
	char *p = r->req_header->content;
	while(p_idx+1<header_size){
		if(p[p_idx]=='\r'&&p[p_idx+1]=='\n'){
			//std::cout<<p_idx<<std::endl;
			parser_req_header_line(r,p+sta,p_idx-sta);
			//std::cout<<r->req_header->content<<std::endl;
			sta = p_idx+2;
			p_idx = sta;
		}
		p_idx++;
	}
	std::cout<<"header end"<<std::endl;
	return true;
	
};
//bool parser_header()
void http_parser(Request *r){
	std::cout<<r->content<<std::endl;
	//char *p = r->content;
	std::cout<<msg_header_iscomplete(r->content,r->content_size)<<std::endl;
	//int header_end = 0;
	int msg_end = msg_header_iscomplete(r->content,r->content_size);
	if(msg_end == -1){//header is incomplete.
		return;
	}
	int http_req_line_end = get_req_line_end(r->content,msg_end+1);
	if(http_req_line_end == -1){//did not found request line.
		//500
		return;
	}
	//std::cout<<http_req_line_end<<std::endl;
	//std::cout<<r->content[18]<<std::endl;
	//std::cout<<r->content[21]<<std::endl;
	//if(r->content[19]=='\r')std::cout<<"y"<<std::endl;
	//if(r->content[20]=='\n')std::cout<<"y"<<std::endl;
	r->req_line->content = new char[http_req_line_end+3];
	//std::cout<<http_req_line_end<<std::endl;
	strncpy(r->req_line->content,r->content,http_req_line_end+3);
	//std::cout<<r->req_line->content<<std::endl;
	if(!parser_req_line(r,http_req_line_end)){
		//500
		return;
	}
	//std::cout<<r->content+http_req_line_end+3<<std::endl;
	r->req_header->content = new char[msg_end - http_req_line_end];
	strncpy(r->req_header->content,r->content+http_req_line_end+3,msg_end - http_req_line_end);
	//std::cout<<r->req_header->content<<std::endl;
	if(!parser_req_header(r,msg_end - http_req_line_end)){
		return;
	}
	std::cout<<r->req_header->connection<<std::endl;
	std::cout<<r->req_header->content_length<<std::endl;
	std::cout<<"cout body"<<std::endl;
	std::cout<<r->content+msg_end+5<<std::endl;
	//char *ppp = new char[5060];
	//std::cout<<"akkkkkk"<<std::endl;
	//strncpy(ppp,r->content+265,5060);
	//std::cout<<ppp<<std::endl;
	
};
