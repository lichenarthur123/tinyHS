#include <iostream>
#include<vector>
#include<pthread.h>
#include "HttpServer.h"
//#include "Http_request.h"

using namespace std;
void* worker(void* arg){
    cout<<"ok"<<endl;
}
int main()
{
	  /*
    int *a =new int[2];
    a[0]=1;
    a[1]=2;
    cout<<a<<endl;
    vector<pthread_t> s;
    s.resize(5);
    for(int i=0;i<s.size();i++){
				int x = 1;
        cout<<pthread_create( &s[i], NULL, worker, &x )<<endl;
        cout<<s[i]<<endl;
    }
    cout<<"xx"<<endl;
    cout << "Hello world!" << endl;*/
		HttpServer server(8080);
		server.run();
    return 0;
}
