#include<stdio.h>
#include<errno.h>
#include<string.h>


void all_read(int fp,char *buf,size_t size);

int main(){
	int fp;
	char buf[128];
	char file_name[256];

	scanf("%s",file_name);

	fp = fopen("test.txt","r");
	if(fp == NULL){
		printf("file open error\n");
	}

	all_read(fp,buf,sizeof(buf));

	return 0;
}


void all_read(int fp,char *buf,size_t size){
	size_t read_size;

	while(1){
		read_size = read(fp,buf,size);
		printf("%d\n",read_size);
		write(2,buf,strlen(buf));
	}
}
