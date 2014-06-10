#include<stdio.h>
#include<stdlib.h>

typedef struct dictionary dictionary;

struct dictionary{
	dictionary *next;
	char word[100];
};

dictionary dict;

void Add(char* word);
void Display();

int main(){
	dict.next = NULL;
	char tmp[100];
	while(1){
		if(fgets(tmp,sizeof(tmp),stdin) != NULL){
			Add(tmp);
		}else{
			Display();
			break;
		}
	}
	return 0;
}

void Add(char* word){
	dictionary *p;
	dictionary *next;
	dictionary *prev;

	p = (dictionary*)malloc(sizeof(dictionary));
	sprintf(p->word,"%s",word);
	p->next = NULL;
	prev = &dict;

	for(next = dict.next; next != NULL; next = next->next){
		prev = next;
	}

	prev->next = p;
}

void Display(){
	printf("-------------------------------\n");
	dictionary *p;
	for(p = dict.next; p != NULL; p = p->next){
		printf("%s",p->word);
	}
}

