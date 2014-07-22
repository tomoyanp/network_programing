#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

#include<pthread.h>
#include<unistd.h>

#define TRUE 1
#define FALSE 0

int http_client();
void *add_list();
void *sort();
void show_data();
int compare_int(const void *a, const void *b);

int list[1000000];
unsigned long list_index = 0;
int flag = FALSE;

int main(){

	int i = 0;
	pthread_t tid[2];
	void *thread_return;

	pthread_create(&tid[0],NULL,add_list,0);
	pthread_create(&tid[1],NULL,sort,0);
	pthread_join(tid[0],&thread_return);
	pthread_join(tid[1],&thread_return);


	show_data();
	return 0;

}

int http_client(){
	int fd;
	struct hostent *hostent;
	struct sockaddr_in server;

	int port;

	hostent = gethostbyname("web.sfc.keio.ac.jp");
	if (hostent == NULL){
		printf("cannot resulv host name\n");
	}
	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	port = server.sin_port = htons(80);
	bcopy(hostent->h_addr, &server.sin_addr, hostent->h_length);

	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("cannot make socket\n");
	}

	if(connect(fd,(struct sockaddr*)&server, sizeof(server)) == -1) {
		printf("cannot connect\n");
	}

	char first_request[] = "GET /~kusumoto/syspro/sortdata00 HTTP/1.1\r\n";
	write(fd,first_request,strlen(first_request));
	char second_request[] = "Host: web.ht.sfc.keio.ac.jp\r\n";
	write(fd,second_request,strlen(second_request));
	char final_request[] = "\r\n";
	write(fd,final_request,strlen(final_request));



	return fd;
}

void *add_list(){
	int fd = http_client();
	char initial_str[256];
	read(fd,initial_str,256);
	char string[256];
	char tmp[30];
	memset(tmp,0,sizeof(tmp));
	memset(string,0,sizeof(string));
	unsigned long i = 0;
	int size = 0;
	while(recv(fd,string,256,0)){
		size = read(fd,string,256);
		if(size <= 0){
			break;
		}
		for ( i = 0; i< 256;i++){
			if(string[i] == '\n'){
				list[list_index] = atoi(tmp);
				list_index++;
				memset(tmp,0,sizeof(tmp));
			} else {
				sprintf(tmp,"%s%c",tmp,string[i]);
			}
		}
	}
	flag = TRUE;
	pthread_exit(NULL);
}

void show_data(){
	int i;
	for ( i = 0; i < 5;i++){
		printf("%d\n",list[i]);
	}
	printf(" -------------------------------- \n");
	for(i = 5;i > 0;i--){
		printf("%d\n",list[list_index - i]);
	}
}


int compare_int(const void *a, const void *b){
	if(*(int*)a < *(int*)b){
		return -1;
	}
	else if(*(int*)a == *(int*)b){
		return 0;
	}
	return 1;
}

void *sort(){
	while(1){
		if(flag){
			qsort(list,list_index,sizeof(int),compare_int);
			break;
		}else{
			qsort(list,list_index,sizeof(int),compare_int);
		}
	}
	pthread_exit(NULL);
}


