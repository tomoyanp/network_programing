#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

int http_client();
int compare_int(const void *a,const void *b);
//void add_list(list* head,int value);


typedef struct list list;

struct list{
	list* next;
	list* prev;
	int value;
};

int main(){


	FILE *fp;
	int *list = (int*)malloc(sizeof(int) * 1000000);
//	list* head = (list*)malloc(sizeof(list));
//	head->next = NULL;

	if(list == NULL) {
		printf("aaaaaaaaaaaaaaa\n");
		exit(0);
	}
	int fd = http_client();
	char string[256];
	char tmp[30];
	memset(tmp,0,sizeof(tmp));
	memset(string,0,sizeof(string));

	read(fd,string,256);
	printf("%s\n",string);

	unsigned long i = 0;
	unsigned long index = 0;
	int size = 0;
	

	while(recv(fd,string,256,0)){
		size = read(fd,string,256);
		if(size <= 0){
			break;
		}
		for ( i = 0; i< 256;i++){
			if(string[i] == '\n'){
				//add_list(head,atoi(tmp));
				list[index] = atoi(tmp);
				index++;
				printf("%ld\n",index);
				memset(tmp,0,sizeof(tmp));
			} else {
				sprintf(tmp,"%s%c",tmp,string[i]);
			}
		}
	}

	qsort(list,index,sizeof(int),compare_int);
	for ( i = 0; i < index;i++){
		printf("%d\n",list[i]);
	}

	free(list);
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
	printf("%s\n",first_request);
	write(fd,first_request,strlen(first_request));
//	char second_request[256];
//	sprintf(second_request,"Host: web.ht.sfc.keio.ac.jp:%d\r\n",port);
	char second_request[] = "Host: web.ht.sfc.keio.ac.jp\r\n";
	printf("%s\n",second_request);
	write(fd,second_request,strlen(second_request));
	char final_request[] = "\r\n";
	printf("%s\n",final_request);
	write(fd,final_request,strlen(final_request));

	printf("============= ok ================\n");


	return fd;
}

int compare_int(const void *a,const void *b){
	return *(int*)a - *(int*)b;
}

/*void add_list(list* head,int value){
	list* node = (list*)malloc(sizeof(list));
	while(
	*/


