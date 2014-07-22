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
void sort(int left,int right);
void swap(int i, int j);
void show_data();

int list[1000000];
unsigned long list_index = 0;
int flag = FALSE;

int main(){

//	int *list = (int*)malloc(sizeof(int) * 1000000);
//	if(list == NULL) exit(0) ;


	int i = 0;
	pthread_t tid;
	void *thread_return;
//	pthread_create(&tid,NULL,add_list,&list);
	pthread_create(&tid,NULL,add_list,0);
	pthread_join(tid,&thread_return);

	while(1){
		if(flag){
			sort(0,list_index);
			break;
		}else{
			sort(0,list_index);
		}
	}


	show_data();


//	free(list);
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
	char second_request[] = "Host: web.ht.sfc.keio.ac.jp\r\n";
	printf("%s\n",second_request);
	write(fd,second_request,strlen(second_request));
	char final_request[] = "\r\n";
	printf("%s\n",final_request);
	write(fd,final_request,strlen(final_request));

	printf("============= ok ================\n");


	return fd;
}

void *add_list(){
//	int *list = (int*)ls;
	int fd = http_client();
	char initial_str[256];
	read(fd,initial_str,256);
	printf("%s\n",initial_str);
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
				printf("%ld\n",list_index);
				memset(tmp,0,sizeof(tmp));
			} else {
				sprintf(tmp,"%s%c",tmp,string[i]);
			}
		}
	}
	flag = TRUE;
	pthread_exit(NULL);
}


void sort(int left,int right){
	int i, j;
	int pivot;
	
	while(TRUE){
		printf("sort\n");
		i = left;
		j = right;
		pivot = list[(i + j)/2];
		while(list[i] < pivot){
			i++;
		}
		while(pivot < list[j]){
			j--;
		}

		if(i >= j){
			break;
		}

		swap(i,j);
		i++;
		j--;
	}

	if( left < i-1){
		sort(left,i-1);
	}
	if(j+1 < right){
		sort(j+1,right);
	}
}

void show_data(){
	int i;
	for ( i = 0; i < list_index;i++){
		printf("%d\n",list[i]);
	}
}



void swap(int i, int j){
	int tmp;

	tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}

