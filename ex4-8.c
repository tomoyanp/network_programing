#include<stdio.h>
#include<stdlib.h>


int fanctionality(int i);
void adjust_answer(int i);

int main(){
	int i = 0;
	for(i = 1; i <= 1000;i++){
		if(fanctionality(i) == 0){
			printf("%d = %d\n",i,i);
		}else{
			adjust_answer(i);
		}
	}
	return 0;
}

int fanctionality(int i){
	int n = 2;
	int flag = 0;
	for(n = 2;n < i;n++){
		if(i % n == 0){
			flag = 1;
		}
	}
	return flag;
}


void adjust_answer(int i){
	int n = 2;
	printf("%d = ",i);
	while(1){
		if(i % n == 0){
			i = i/n;
			printf("%d * ",n);
			n = 2;
		}else{
			n++;
		}
		if(fanctionality(i) == 0){
			printf("%d \n",i);
			break;
		}
	}
}
