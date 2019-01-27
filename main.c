#include<stdlib.h>
#include<stdio.h>
#include"ctrl.h"
int main(){
	FILE *p = NULL;
	char link[100] = {0};
	open(&p, link);

	printf("menu\nchoices:\n");
	PW* content = NULL;
	if (link[0] == 0){
		return 0;
	}
	readinfo(&content,link);
	code(content);
	//init read stuff
	int a=0;
	
	while (a != 5){
		printf("1.input\n2.show\n3.find\n4.delete or change\n5.exit and change\n");

		
		scanf_s("%d", &a);
	
		if (getchar() != '\n'){
			system("cls");
			printf("wrong!\n\n");
			while (getchar() != '\n');
			continue;
		}
		
		switch (a){
		case 1:	putinfo(content);	system("cls"); break;
		case 2: show(content); 	system("cls"); break;
		case 3: search(content); system("cls"); break;

		case 4: alterDele(content);system("cls"); break;
		case 5:break;
		default: system("cls"); printf("wrong\n\n"); break;
		}


		

	} 
	code(content);
	save(content,link);
	free(content);

	return 0;
}