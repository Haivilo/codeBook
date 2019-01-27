typedef struct password{
	char id[100];
	char pw[100];
	char web[100];
	char note[100];
}PW;
void readinfo(PW** a, char* link);
void putinfo(PW* content);
void show(PW* a);
void search(PW *a);
void alterDele(PW* a);
void save(PW* a, char* link);
void code(PW *a);
void open(void** v, char* a);