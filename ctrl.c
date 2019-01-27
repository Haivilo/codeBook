#include<stdlib.h>
#include<stdio.h>
#include"ctrl.h"
#include<string.h> 
#define size 100;
void open(FILE **p,char* a){
	//open file
	do{
		char root[100] = "0";
		printf("file name：\n");
		scanf_s("%s", root, 100);

		fopen_s(p, root, "r"); 
		if (*p == NULL){
			//check file existence
			printf("file doesn't exist, to create---input 1\nchange file name---input 2\npress other keys to exit\n");
			int out = 0;
			scanf_s("%d", &out);
			while (getchar() != '\n');
			if (out == 1){
				//create new
				fopen_s(p, root, "w");
				if (p == NULL){
					printf("unable to create, press any key to exit\n");
					_getch();
					return;
				}
				
				fclose(*p);
				strcpy_s(a, 100, root);
				system("cls");
				return;
			}
			else if (out == 2)
			{//restart

				system("cls");
				continue;
			}
			else
			{//exit
				
				return;
			}
		}
		else
		{ //if file exits
			fclose(*p);
			printf("file exits，input 1 to change or read，input other key to exit\n");
			int out = 0;
			scanf_s("%d", &out);
			while (getchar() != '\n');
			if (out==1)
				//run the program
			{
				strcpy_s(a, 100, root);

				system("cls");
				return;

			}
			else
			{//exit
				return;
			}

		}
		*p = NULL;
	} while (1);

}
void codeSingleChar(char a[]){
	//encrypt
	const int length = strlen(a);
	for (int i = 0; i < length; i++)
	{
		a[i] ^= 5;
	}
}
void code(PW *a){
	//encrypt struct
	int num = count(a);
	for (int i = 0; i < num; i++)
	{	
		codeSingleChar(a[i].id);
		codeSingleChar(a[i].note);
		codeSingleChar(a[i].pw);
		codeSingleChar(a[i].web);
	}
}

void readinfo(PW** a,char* link){
	
	FILE *p = NULL;
	fopen_s(&p, link, "rb");
	if (p == NULL){
		printf("readinfo failed");
		return;
	}
	//run code below if success
	*a = (PW*)malloc(sizeof(PW)*100);
	memset(*a, 0, sizeof(PW) * 100);

	fread_s(*a, sizeof(PW) * 100, sizeof(PW), 100, p);
	//read file to buffer
	fclose(p);
}
int count(PW* a){
	//count numbers of PW
	int i = 0;
	for (; (a + i)->id[0] != 0; i++);
	return i;

}
int find(PW* a, char id[100]){
	//find the index
	int num = count(a);

	int i = 0;
	for (; i < num; i++)
	{
		
		if (!strcmp(a[i].id, id))
		{
			return i+1;
			//0 means not success, so index could all plus 1 to get rid of 0 (which is used to return false input)
		}
		

	}
	return 0;
	//return false
}

void putinfo(PW* content){
	
	system("cls");
	PW a;

	printf("id:");

	scanf_s("%s", a.id,sizeof(a.id));
	//check if id exists
	while (getchar() != '\n');
	if (find(content,a.id)>0)
	{
		printf("all ready exist,press anykey to exit\n");
		_getch();
		return;
	}

	printf("password:");
	scanf_s("%s", a.pw, sizeof(a.pw));
	while (getchar() != '\n');

	printf("web:");
	scanf_s("%s", a.web, sizeof(a.web));
	while (getchar() != '\n');

	printf("note:");
	scanf_s("%s", a.note, sizeof(a.note));
	
	while (getchar() != '\n');
	
	int start = count(content);
	//get last index
	if (start > 99){
		printf("file is already full\n");
		_getch();
		return;
	}
\

	*(content + start) = a;

	printf("finished，press anykey to exit\n");
	_getch();
	return;
}
void show(PW* a){

	system("cls");
	int num = count(a);

	for (int i = 0; i < num; i++)
	{
		printf("id:%s\n", a[i].id);
		printf("web:%s\n", a[i].web);
		printf("note:%s\n", a[i].note);
		printf("password:%s\n", a[i].pw);
		printf("------------------------------------\n");
	}

	printf("press anykey to exit\n");
	_getch();
}
void search(PW *a){

	system("cls");
	printf("input id:");
	char id[100];
	scanf_s("%s", id,sizeof(id));
	while (getchar() != '\n');
	int i = find(a, id) - 1;
	//-1 
	if (find(a, id)){
		printf("web:%s\n", a[i].web);
		printf("note:%s\n", a[i].note);
		printf("password:%s\n", a[i].pw);
		printf("------------------------------------\npress anykey to exit");
		_getch();
		return;
	}//打印
	else
	{
		printf("It doesn't exist\npress anykey to exit\n");
		_getch();
		return;
	}
}
void alter(PW* a,PW* new,int index){
	//更改函数
	printf("password:");
	scanf_s("%s", new->pw, sizeof(new->pw));
	while (getchar() != '\n');

	printf("web:");
	scanf_s("%s", new->web, sizeof(new->web));
	while (getchar() != '\n');

	printf("note:");
	scanf_s("%s", new->note, sizeof(new->note));
	while (getchar() != '\n');
	strcpy_s(a[index].note, sizeof(a[index].note), new->note);
	strcpy_s(a[index].web, sizeof(a[index].web), new->web);
	strcpy_s(a[index].pw, sizeof(a[index].note), new->pw);
	printf("ok");
	_getch();
	return;
}
void dele(PW* a, int index){
	//delete
	int end = count(a);
	//move every thing forward from the index.
	while (index != end){
		a[index] = a[(index+1)];
		index++;
	}
	printf("deleted, press anykey to exit");
	_getch();
	return;

}
void alterDele(PW* a){
	//change or delete
	system("cls");

	printf("id:");
	PW input = { 0, 0, 0, 0 };
	PW *new = &input;
	scanf_s("%s",new->id , sizeof(new->id));

	while (getchar() != '\n');
	if (find(a, new->id) == 0){
		//if could not find
		printf("does not exist \npress anykey to exit");
		_getch();
		return;
	}
	int i = find(a, new->id) - 1;
	//if found
	printf("change:1，delete:2\n");
	char test = getchar();
	while (getchar() != '\n');
	//change is 1, delete is 2
	if (test == '1'){
		alter(a, new, i);
		return;
	}
	else if (test == '2'){
		dele(a, i);
		return;
	}
	else
	{
		printf("wrong input\nPress Anykey to exit");
		_getch();
		return;
	}
}
void save(PW* a,char* link){

	//save file 

	FILE *p = NULL;
	fopen_s(&p, link, "w");

	if (p == NULL){
		printf("readinfo failed");
		return;
	}

	fwrite(a, sizeof(PW), 100, p);

	fclose(p);

	
}