#include <stdio.h>
#include <stdlib.h>
const char *file_name = "学生信息_data.txt";


typedef struct Student {
	char name[20];
	int age;
	int Class;
	double height;
} Student;

#define MAX_N 10000
Student stus[MAX_N + 5];
int scnt;

int read_from_file(Student *arr){
	int i = 0;
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		return 0;
	}
	while (fscanf(fp, "%s", arr[i].name) != EOF) {//读取文件
	fscanf(fp, "%d%d%lf",
		&arr[i].age,
		&arr[i].Class,
		&arr[i].height
	);
		i += 1;
	}
	fclose(fp);
	return i;
}

void output_to_file(Student *arr, int n) {
	FILE *fp = fopen(file_name, "a");//打开文件
	for (int i= 0; i < n; i++) {
		fprintf(fp, "%s %d %d %.2lf\n",
		 arr[i].name, arr[i].age, 
		 arr[i].Class, arr[i].height);//输入数据
	}
	fclose(fp);//关闭文件
	return ;
}

void clear_file() {
	FILE *fp = fopen(file_name, "w");
	fclose(fp);
	return ;
}

void restor_data_to_file(Student *arr, int n) {
	clear_file();
	output_to_file(arr, n);
	return ;
}


void list_students() {//学生列表
	int len = printf("%4s|%15s|%4s|%6s|%7s|",
		"序号", "姓名", "年龄", "班级", "身高"
	);
	printf("\n");
	for (int i = 0; i < len; i++) printf("=");
	printf("\n");
	for (int i = 0; i < scnt; i++) {
		printf("%4d|%15s|%4d|%6d|%7.2lf|\n",
		i, stus[i].name,
		stus[i].age, stus[i].Class,
		stus[i].height);
	}
	return ;
}

void add_a_student() {
	printf("添加一名学生 : (姓名, 年龄, 班级, 身高)\n");
	printf("在此输入 > ");
	scanf("%s%d%d%lf",
		stus[scnt].name,
		&stus[scnt].age,
		&stus[scnt].Class,
		&stus[scnt].height
	);
	output_to_file(stus+ scnt, 1);//（添加文件的首地址，几条数据）
	scnt += 1;
	printf("添加成功\n");
	return ;
}

void modify_a_student() {
	list_students();
	int id;
	do {
		printf("想要修改的序号 : ");
		scanf("%d", &id);
	} while (id < 0 || id >= scnt);
	printf("修改一名学生信息 : (姓名, 年龄, 班级, 身高)\n");
	printf("在此输入 > ");
	scanf("%s%d%d%lf",
		stus[id].name,
		&stus[id].age,
		&stus[id].Class,
		&stus[id].height
	);
	restor_data_to_file(stus, scnt);//先清空文件，再重新输入数据
	return ;
}

void delete_a_student() {
	if (scnt == 0) {
		printf("没有这个学生\n");
		return ;
	}
	list_students();
	int id;
	do {
		printf("删除的序号为 : ");
		scanf("%d", &id);
	} while (id < 0 || id >= scnt);
	char s[100];
	printf("请确认是否删除 (y / n) : ");
	fflush(stdin);//把读入缓冲区冲干净再读入
	scanf("%[^\n]", s);//[^\n]：读入一行字符串
	if (s[0] != 'y') return ;
	for (int i = id + 1; i < scnt; i++) {
		stus[i - 1] = stus[i];
	}//数据依次往前移动一位
	scnt -= 1;//学生数量减1
	restor_data_to_file(stus, scnt);//数据同步到文件中去
	
	return ;
}

enum NO_TYPE {
	LIST = 1,
	ADD,
	MODIFY,
	DELETE,
	QUIT,
};//枚举变量，为减少我们的记忆负担

int usage() {
	int no;
	do {
	printf("%d : 查看学生信息列表\n", LIST);
	printf("%d : 添加学生信息\n", ADD);
	printf("%d : 修改学生信息\n", MODIFY);
	printf("%d : 删除学生信息\n", DELETE);
	printf("%d : 退出系统\n", QUIT);
	printf("在此处输入 > ");
	scanf("%d", &no);
	} while (no < 1 || no > 5);//优化：直到输入了合法的数据才会退出usage循环
	return no;
}//交互界面设计

int main(){
	scnt = read_from_file(stus);
	while(1) {
		int no = usage();
		switch (no) {
			case LIST: {
				list_students();
			} break;
			case ADD: {
				add_a_student();
			} break;
			case MODIFY:{
				modify_a_student();
			} break;
			case DELETE: {
				delete_a_student();
			} break;
			case QUIT:	printf("已退出\n"); exit(0);//直接退出程序
		}
	}
	
	return 0;
}
