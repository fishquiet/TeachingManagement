#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_S 200
#define MAX_C 100
#define MAX_SC 1000
#define EPSILON 0.01

struct Student {
	int sno;
	char sname[20];
	char gender[3];
	char nation[10];
	int age;
};

struct Course {
	int cno;
	char cname[20];
	float credit;
};

struct SC {
	int sno;
	int cno;
	int grade;
};

struct SR {
	Student stu;
	int allgrade;
	int ranking;
};


int checkSno(Student *, int, int varSno);
int checkCno(Course *, int, int varCno);

int inputAllS(Student *, int);
void inputC(Course *);
int inputAllC(Course *, int);
void inputSC( SC *, int);
int inputAllSC (Student *, int, Course *, int, SC *, int );

void outputSC (Student *, int, Course *, int, SC *, int );
int outputAllSC(Student *, int, Course *, int, SC *, int);
void outputS(Student *);
int outputAllS(Student *, int);
void outputC(Course *);
int outputAllC(Course *, int);

int countByGender(Student *, int, char *);
double averageAge(Student *, int);
void sortBySno(Student *, int);
int searchBySno(Student *, int, int);
int deleteBySno(Student *, int, int);
int *countByAge(Student *, int);
int countByNation(Student *, int, char *);

void sortByCno(Course *, int);
int searchByCno(Course *, int, int);
int *countByCredit(Course *, int);
int deleteByCno(Course *, int, int );

void searchGrade(SC *, int, Student *, int, Course *, int, char *, char * );
void searchSCByCno(SC *, int, Student *, int, int);
void searchSCBySno(SC *, int, Course *, int, int);

int deleteSCBySno(SC *, int, int);
void sortByAverageGrade(SC *, int, Student *, int);

int readFileS(FILE *, Student *);
void writeFileS(FILE *, Student *, int);
int readFileC(FILE *, Course *);
void writeFileC(FILE *, Course *, int);
int readFileSC(FILE *, SC *);
void writeFileSC(FILE *fp, SC *sc, int);


int main(void) {
	char fn1[20] = "student.dat";
	char fn2[20] = "course.dat";
	char fn3[10] = "sc.dat";
	FILE *fp1, *fp2, *fp3;
	fp1 = fopen(fn1, "ab+");
	fp2 = fopen(fn2, "ab+");
	fp3 = fopen(fn3, "ab+");
	Student *s = (Student *)malloc(sizeof(Student) * MAX_S);
	int n = readFileS(fp1, s);
	Course *c = (Course *)malloc(sizeof(Course) * MAX_C);
	int m = readFileC(fp2, c);
	SC *sc = (SC *)malloc(sizeof(SC) * MAX_SC);
	int num = readFileSC(fp3, sc);
	while (1) {
		system("cls");
		printf("\n\t\t 学生选课信息管理软件");
		printf("\n\t--------------------------------------");
		printf("\n\t\t 1--输入数据");
		printf("\n\t\t 2--查询学生数据");
		printf("\n\t\t 3--查询课程数据");
		printf("\n\t\t 4--查询学生选课及成绩数据");
		printf("\n\t\t 5--数据更新（删除）");
		printf("\n\t\t 0--退出");
		printf("\n\t---------------------------------------");
		printf("\n\t\t 请选择(0 - 5)：");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0) {
			fp1 = fopen(fn1, "wb");
			fp2 = fopen(fn2, "wb");
			fp3 = fopen(fn3, "wb");
			writeFileS(fp1, s, n);
			writeFileC(fp2, c, m);
			writeFileSC(fp3, sc, num);
			break;
		}
		if (option == 1) {
			while (1) {
				system("cls");
				printf("\n\t\t  数据输入功能");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 1--添加学生数据");
				printf("\n\t\t 2--添加课程数据");
				printf("\n\t\t 3--添加成绩数据");
				printf("\n\t\t 0--返回上级菜单");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 请选择(0 - 9)：");
				int x1;
				scanf("%d", &x1);
				fflush(stdin);
				if (x1 == 1)
					n = inputAllS(s, n);
				if (x1 == 2)
					m = inputAllC(c, m);
				if (x1 == 3)
					num = inputAllSC (s, n, c, m, sc, num);
				if (x1 == 0)
					break;
			}
		}
		if (option == 2) {
			while (1) {
				system("cls");
				printf("\n\t\t 学生数据管理");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 1--显示所有学生");
				printf("\n\t\t 2--按学号排序");
				printf("\n\t\t 3--按学号查询学生");
				printf("\n\t\t 4--按学号删除学生");
				printf("\n\t\t 5--求学生平均年龄");
				printf("\n\t\t 6--年龄对应人数统计表");
				printf("\n\t\t 7--按性别统计学生人数");
				printf("\n\t\t 8--按民族统计学生人数");
				printf("\n\t\t 0--返回上一级");
				printf("\n\t---------------------------------------");
				printf("\n\t\t 请选择(0 - 8)：");
				int x2;
				scanf("%d", &x2);
				fflush(stdin);
				if (x2 == 0) {
					break;
				}
				if (x2 == 1) {
					printf("\t\t 共有%d名学生\n", n);
					n = outputAllS(s, n);
				}
				if (x2 == 2) {
					sortBySno(s, n);
					printf("\t排序完成\n\t共有%d名学生\n", n);
					n = outputAllS(s, n);
				}
				if (x2 == 3) {
					int varSno;
					printf("\t请输入要查询的学号：");
					scanf("%d", &varSno);
					int i = searchBySno(s, n, varSno);
					if (i == -1) {
						printf("\t没有找到该学生");
					} else {
						printf("\t该学生在第%d位\n", i + 1);
					}
				}
				if (x2 == 4) {
					int varSno;
					printf("\t请输入要删除的学号：");
					scanf("%d", &varSno);
					n = deleteBySno(s, n, varSno);
					printf("\n\t删除后的学生有%d人\n", n);
					n = outputAllS(s, n);
				}
				if (x2 == 5) {
					double avg = averageAge(s, n);
					printf("\t学生的平均年龄：%.3f\n", avg);
				}
				if (x2 == 6) {
					int *p = countByAge(s, n);
					for (int i = 0; i < n; i++) {
						if (p[i] != 0) {
							printf("\t年龄: %d \n\t人数 %d\n", s[i].age, p[i]);
						}
					}
					free(p);
				}
				if ( x2 == 7) {
					printf("\t请输入想要查询的性别：");
					char *varGender = (char *)malloc(sizeof(char));
					scanf("%s", varGender);
					int count = countByGender(s, n, varGender);
					printf("\t该性别的人数为：%d\n", count);
				}
				if (x2 == 8) {
					char varNation[10];
					printf("\t请输入民族：");
					gets(varNation);
					int i = countByNation(s, n, varNation);
					printf("\n\t共%d个学生\n", i);
				}
				system("pause");
			}
		}
		if (option == 3) {
			while (1) {
				system("cls");
				printf("\n\t\t 课程数据管理");
				printf("\n\t------------------------------------");
				printf("\n\t\t1--显示所有课程");
				printf("\n\t\t2--按课程号排序");
				printf("\n\t\t3--按课程号查询课程");
				printf("\n\t\t4--按课程号删除课程");
				printf("\n\t\t5--学分对应课程门数统计表");
				printf("\n\t\t0--返回上级菜单");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 请选择(0 - 5)：");
				int x3;
				scanf("%d", &x3);
				fflush(stdin);
				if (x3 == 0) {
					break;
				}
				if (x3 == 1) {
					printf("\t\t 共%d门课程\n", m);
					m = outputAllC(c, m);
				}
				if (x3 == 2) {
					sortByCno(c, m);
					puts("\t\t 排序完成");
					printf("\t\t 共有%d门课程\n", m);
					m = outputAllC(c, m);
				}
				if (x3 == 3) {
					int varCno;
					printf("\t请输入要查询的课程号：");
					scanf("%d", &varCno);
					int i = searchByCno(c, m, varCno);
					if (i == -1) {
						printf("\t没有找到该课程");
					} else {
						printf("\t该课程在第%d位\n", i + 1);
					}
				}
				if (x3 == 4) {
					int varCno;
					printf("\t请输入要删除的课程号：");
					scanf("%d", &varCno);
					m = deleteByCno(c, m, varCno);
					printf("\n\t删除后的课程有%d门\n", m);
					m = outputAllC(c, m);
				}
				if (x3 == 5) {
					int *p = countByCredit(c, m);
					for (int i = 0; i < m; i++) {
						if (p[i] != 0) {
							printf("\t学分: %.1f \n\t门数 %d\n", c[i].credit, p[i]);
						}
					}
					free(p);
				}
				system("pause");
			}

		}
		if (option == 4) {
			while (1) {
				system("cls");
				printf("\n\t\t 学生选课及成绩管理");
				printf("\n\t------------------------------------");
				printf("\n\t\t1--输出所有学生选课及成绩数据");
				printf("\n\t\t2--按学生姓名和课程名查询成绩");
				printf("\n\t\t3--按学号查询学生成绩");
				printf("\n\t\t4--按课程号查询学生成绩");
				printf("\n\t\t5--按学生总成绩输出排行榜");
				printf("\n\t\t6--按学号和课程号删除学生成绩");
				printf("\n\t\t0--返回上级菜单");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 请选择(0 - 5)：");
				int x4;
				scanf("%d", &x4);
				fflush(stdin);
				if (x4 == 0) {
					break;
				}
				if (x4 == 1) {
					num = outputAllSC(s, n, c, m, sc, num);
				}
				if (x4 == 2) {
					char *varSname = (char *)malloc(sizeof(char));
					printf("\t\t姓名：");
					scanf("%s", varSname);
					char *varCname = (char *)malloc(sizeof(char));
					printf("\t\t课程名：");
					scanf("%s", varCname);
					searchGrade(sc, num, s, n, c, m, varSname, varCname);
				}
				if (x4 == 3) {
					int varSno;
					printf("\t\t学号：");
					scanf("%d", &varSno);
					searchSCBySno(sc, num, c, m, varSno);
				}
				if (x4 == 4) {
					int varCno;
					printf("\t\t课程号：");
					scanf("%d", &varCno);
					searchSCByCno(sc, num, s, n, varCno);
				}
				if (x4 == 5)
					sortByAverageGrade(sc, num, s, n);
				if (x4 == 6) {
					int varSno;
					printf("学号：");
					scanf("%d", &varSno);
					num = deleteSCBySno(sc, num, varSno);
				}
				system("pause");
			}
		}
		if (option == 5) {
			while (1) {
				system("cls");
				printf("\n\t\t 更新数据");
				printf("\n\t------------------------------------");
				printf("\n\t\t1--按学号删除学生（从学生表）");
				printf("\n\t\t2--按课程号课程（从课程表）");
				printf("\n\t\t3--按学号和课程号删除学生成绩（从成绩表）");
				printf("\n\t\t0--返回上级菜单");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 请选择(0 - 3)：");
				int x5;
				scanf("%d", &x5);
				fflush(stdin);
				if (x5 == 0) {
					break;
				}
				if (x5 == 1) {
					int varSno;
					printf("\t请输入要删除的学号：");
					scanf("%d", &varSno);
					n = deleteBySno(s, n, varSno);
					printf("\n\t删除后的学生有%d人\n", n);
					n = outputAllS(s, n);
				}
				if (x5 == 2) {
					int varCno;
					printf("\t请输入要删除的课程号：");
					scanf("%d", &varCno);
					m = deleteByCno(c, m, varCno);
					printf("\n\t删除后的课程有%d门\n", m);
					m = outputAllC(c, m);
				}
				if (x5 == 3) {
					int varSno;
					printf("学号：");
					scanf("%d", &varSno);
					num = deleteSCBySno(sc, num, varSno);
				}
				system("pause");
			}
		}
		system("pause");
	}
	free(s);
	free(c);
	free(sc);
	return 0;
}

void inputS(Student *p) {
	printf("\t\t姓名：");
	scanf("%s", p->sname);
	printf("\t\t性别：");
	scanf("%s", p->gender);
	printf("\t\t民族：");
	scanf("%s", p->nation);
	printf("\t\t年龄：");
	scanf("%d", &p->age);
}


int inputAllS(Student *s, int n) {
	char tmp1, tmp2 = '1';
	int i = 0;

	while (1) {
		printf("\t\t目前已录入的学生人数为：%d\n", n);
		if (n != 0) {
			int varSno;
			printf("\t\t学号：");
			scanf("%d", &varSno);
			int flag = checkSno(s, n, varSno);
			if (flag != 0) {
				puts("\t\t学号重复，请重新输入");
			} else {
				s[n + i].sno = varSno;
				Student *p;
				p = &s[i + n];
				inputS(p);
				i++;
				n++;
			}
		} else {
			int varSno;
			printf("\t\t学号：");
			scanf("%d", &varSno);
			s[i].sno = varSno;
			Student *p;
			p = &s[i];
			inputS(p);
			i++;
			n++;
		}
		puts("\t\t是否继续录入?\n\t\t按1退出，其他键继续");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	puts("\t\t已添加以上学生至系统中");
	return n;
}

void inputC(Course *p) {
	printf("\t\t课程名：");
	printf("\t\t学分：");
	scanf("%f", &p->credit);
}


int inputAllC(Course *c, int n) {
	char tmp1, tmp2 = '1';
	int i = 0;

	while (1) {
		printf("\t\t目前已录入的课程数为：%d\n", n);
		if (n != 0) {
			int varCno;
			printf("\t\t课程号：");
			scanf("%d", &varCno);
			int flag = checkCno(c, n, varCno);
			if (flag != 0) {
				puts("\t\t课程号重复，请重新输入");
			} else {
				c[n + i].cno = varCno;
				Course *p;
				p = &c[i + n];
				inputC(p);
				i++;
				n++;
			}
		} else {
			int varCno;
			printf("\t\t课程号：");
			scanf("%d", &varCno);
			c[i].cno = varCno;
			Course *p;
			p = &c[i];
			inputC(p);
			i++;
			n++;
		}
		puts("\t\t是否继续录入?\n\t\t按1退出，其他键继续");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	puts("\t\t已添加以上课程至系统中");
	return n;
}

void inputSC(SC *p, int num, Student *s, int n, Course *c, int m) {
	int varSno;
	printf("\t\t学号：");
	scanf("%d", &varSno);
	int t1 = checkSno(s, n, varSno);

	if (t1 != 1) {
		puts("\t\t该学生不存在");

	} else {
		p->sno = varSno;
		int varCno;
		printf("\t\t课程号：");
		scanf("%d", &varCno);
		int t2 = checkCno(c, m, varCno);
		if (t2 != 1) {
			puts("\n\t\t该课程不存在");
		} else {
			p->cno = varCno;
			printf("\t\t成绩：");
			scanf("%d", &p->grade);
		}
	}
}

int checkSno(Student *s, int n, int varSno) {
	int test = 0;
	int flag = 0;

	for (int i = 0; i < n; i++) {

		if (s[i].sno == varSno) {
			test = 1;
			flag = 1;

		} else if (s[n].sno != varSno && test != 1) {
			flag = 0;
		}
	}
	return flag;
}


int checkCno(Course *c, int m, int varCno) {
	int test = 0;
	int flag = 0;

	for (int i = 0; i < m; i++) {

		if (c[i].cno == varCno) {
			test = 1;
			flag = 1;

		} else if (c[m].cno != varCno && test != 1) {
			flag = 0;
		}
	}
	return flag;
}

int inputAllSC (Student *s, int n, Course *c, int m, SC *sc, int num) {
	char tmp1, tmp2 = '1';
	int i = 0;

	while (1) {

		if (num != 0) {
			SC *p;
			p = &sc[num + i];
			inputSC(p, num, s, n, c, m);
			i++;
			num++;

		} else {
			SC *p;
			p = &sc[i];
			inputSC(p, num, s, n, c, m);
			i++;
			num++;
		}
		puts("\n\t是否继续录入?\n\t按1退出，其他键继续");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	return num;
}



void outputS(Student *p) {
	printf("\t学号：%d\n \t姓名：%s\n \t性别：%s\n \t民族：%s\n \t年龄：%d\n", p->sno, p->sname, p->gender,
	       p->nation,
	       p->age);
}

int outputAllS(Student *s, int n) {
	int i;
	Student *p = s;

	for (i = 0; i < n; i++) {
		outputS(p);
		p++;
	}
	return n;
}

void outputC(Course *p) {
	printf("\t课程号：%d\n \t课程名：%s\n \t学分：%.1f\n ", p->cno, p->cname, p->credit);
}

int outputAllC(Course *c, int m) {
	int i;
	Course *p = c;

	for (i = 0; i < m; i++) {
		outputC(p);
		p++;
	}
	return m;
}

void outputSC (Student *s, int n, Course *c, int m, SC *scout, int num) {
	printf("\t学号：%d", scout->sno);

	for (int i = 0; i < n; i++) {
		if (scout->sno == s[i].sno)
			printf("\n\t姓名：%s", s[i].sname);
	}
	printf("\n\t课程号：%d", scout->cno);

	for (int i = 0; i < m; i++) {
		if (scout->cno == c[i].cno)
			printf("\n\t课程名：%s", c[i].cname);
	}
	printf("\n\t成绩：%d\n", scout->grade);
}

int outputAllSC(Student *s, int n, Course *c, int m, SC *sc, int num) {
	int i;
	SC *p = sc;

	for (i = 0; i < num; i++) {
		outputSC(s, n, c, m, p, num);
		p++;
	}
	return i;
}

int countByGender(Student *s, int n, char *varGender) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(s[i].gender, varGender) == 0) {
			count++;
		}
	}
	return count;
}

double averageAge(Student *s, int n) {
	double avg, sum;

	if (n == 0) {
		puts("\t请先添加学生！");

	} else {
		for (int i = 0; i < n; i++) {
			sum += s[i].age;
		}
	}
	avg = sum / n;
	return avg;
}

void sortBySno(Student *s, int n) {
	Student temp;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (s[j].sno > s[j + 1].sno) {
				temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}
		}
	}
}

void sortByCno(Course *c, int n) {
	Course temp;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (c[j].cno > c[j + 1].cno) {
				temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
			}
		}
	}
}

int searchBySno(Student *s, int n, int varSno) {
	int test = checkSno(s, n, varSno);
	int flag = 0;

	if (test == 0) {
		flag = -1;

	} else {
		Student *p = s;
		for (int i = 0; i < n; i++) {
			if (s[i].sno == varSno)
				outputS(p);
			p++;
		}
	}
	return flag;
}

int searchByCno(Course *c, int n, int varCno) {
	int test = checkCno(c, n, varCno);
	int flag = 0;

	if (test == 0) {
		flag = -1;

	} else {
		Course *p = c;
		for (int i = 0; i < n; i++) {
			if (c[i].cno == varCno)
				outputC(p);
			p++;
		}
	}
	return flag;
}

int deleteBySno(Student *s, int n, int varSno) {
	int num;
	int test = searchBySno(s, n, varSno);

	if (test != -1) {
		for (int j = test; j < n - 1; j++) {
			s[j] = s[j + 1];
		}
		printf("\t删除成功");
		n--;
		num = n;

	} else if (test == -1) {
		printf("\n\t未找到该学生");
		num = - 1;
	}
	return num;
}

int deleteByCno(Course *c, int n, int varCno) {
	int num;
	int test = searchByCno(c, n, varCno);

	if (test != -1) {
		for (int j = test; j < n - 1; j++) {
			c[j] = c[j + 1];
		}
		printf("\t删除成功");
		n--;
		num = n;

	} else if (test == -1) {
		printf("\n\t未找到该学生");
		num = - 1;
	}
	return num;
}

int *countByAge(Student *s, int n) {
	int *countarray = (int *)malloc(sizeof(int) * MAX_S); //该数组同时记录学生是否被统计和年龄的学生数量
	int i, count;
	for (i = 0; i < n; i++)
		countarray[i] = 1;
	for (i = 0; i < n; i++) {
		count = 1;//开始统计年龄出现次数，至少出现一次
		if (countarray[i] == 0) {
			continue;
		}
		for (int j = i + 1; j < n; j++) {
			if (s[i].age == s[j].age) {//如果相等就count+1
				countarray[j] = 0;//若为0说明学生已经被统计过
				count++;
			}
		}
		countarray[i] = count;
	}
	return countarray;
}

int countByNation(Student *s, int n, char *varNation) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(s[i].nation, varNation) == 0) {
			count++;
		}
	}
	return count;
}

int *countByCredit(Course *c, int n) {
	int *countarray = (int *)malloc(sizeof(int) * MAX_C);
	int i, count;
	for (i = 0; i < n; i++)
		countarray[i] = 1;

	for (i = 0; i < n; i++) {
		count = 1;
		if (countarray[i] == 0) {
			continue;
		}
		for (int j = i + 1; j < n; j++) {
			if (fabs(c[i].credit - c[j].credit) <= EPSILON) {
				countarray[j] = 0;
				count++;
			}
		}
		countarray[i] = count;
	}
	return countarray;
}

void searchGrade(SC *sc, int num, Student *s, int n, Course *c, int m, char *varSname, char *varCname) {
	int t1 = 0, t2 = 0;
	int a, b;

	for (int i = 0; i < n; i++) {

		if ((strcmp(varSname, s[i].sname)) == 0) {
			a = s[i].sno;
			t1 = 1;

		} else if ((strcmp(varSname, s[n].sname)) != 0 && t1 != 1) {
			puts("\t\t没有该学生");
		}
	}

	for (int i = 0; i < m; i++) {

		if ((strcmp(varCname, c[i].cname)) == 0) {
			b = c[i].cno;
			t2 = 1;

		} else if ((strcmp(varCname, c[m].cname)) != 0 && t2 != 1) {
			puts("\t\t没有该课程");
		}
	}

	for (int i = 0; i < num; i++) {
		if (a == sc[i].sno && b == sc[i].cno)
			printf("\t\t成绩：%d\n", sc[i].grade);
	}
}


void searchSCByCno(SC *sc, int num, Student *s, int n, int varCno) {
	int sum, cnum;
	float avg;

	for (int i = 0; i < num; i++) {
		if (varCno == sc[i].cno) {
			sum += sc[i].grade;
			cnum++;
			printf("\t\t学号：%d\n", sc[i].sno);
			for (int j = 0; j < n; j++) {
				if (sc[i].sno == s[j].sno)
					printf("\t\t姓名：%s\n", s[j].sname);
			}
			printf("\t\t成绩：%d", sc[i].grade);
		}
	}
	avg = sum / cnum;
	printf("\n\t\t总成绩：%d，平均成绩：%.2f\n", sum, avg);
}

void searchSCBySno(SC *sc, int num, Course *c, int m, int varSno) {
	int sum, snum;
	float avg;

	for (int i = 0; i < num; i++) {
		if (varSno == sc[i].sno) {
			sum += sc[i].grade;
			snum++;
			printf("\t\t课程号：%d\n", sc[i].cno);
			for (int j = 0; j < m; j++) {
				if (sc[i].cno == c[j].cno)
					printf("\t\t课程名：%s", c[j].cname);
			}
			printf("\n\t\t成绩：%d", sc[i].grade);
		}
	}
	avg = sum / snum;
	printf("\n\t\t总成绩：%d，平均成绩：%.2f\n", sum, avg);
}

int deleteSCBySno(SC *sc, int num, int varSno) {
	char tmp1, tmp2 = '1';

	while (1) {
		int test = 0;
		int varCno;
		printf("\t课程号：");
		scanf("%d", &varCno);
		for (int i = 0; i < num; i++) {

			if (sc[i].cno == varCno) {
				sc[i] = sc[i + 1];
				test = 1;
			}
		}
		if (test = 1) {
			printf("\t删除成功");

		} else {
			printf("\t未找到该课程");
		}

		puts("\n\t是否删除课程？\n\t按1退出，其他键继续");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	return num;
}

void sortByAverageGrade(SC *sc, int num, Student *s, int n) {
	SR *sr = (SR *)malloc(sizeof(SR) * MAX_S);

	for (int i = 0; i < n; i++) {
		sr[i].stu = s[i];
		for (int j = 0; j < num; j++) {

			if (sc[j].sno == s[i].sno) {
				sr[i].allgrade += sc[j].grade;
			}
		}
	}
	SR temp;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (sr[j].allgrade > sr[j + 1].allgrade) {
				temp = sr[j];
				sr[j] = sr[j + 1];
				sr[j + 1] = temp;
			}
		}
	}
	int rank = n;
	for (int i = 0; i < n ; i++) {
		sr[i].ranking = rank;
		rank--;
	}
	SR *p = sr;
	for (int i = 0; i < n; i++) {
		printf("\t名次：%d\n\t学号：%d\n\t姓名：%s\n\t总成绩：%d\n", p->ranking, p->stu.sno, p->stu.sname, p->allgrade);
		p++;
	}
}

int readFileS(FILE *fp, Student *s) {
	int i = 0;

	while (1) {
		fread(s + i, sizeof(Student), 1, fp);
		if (feof(fp))
			break;
		i++;
	}
	fclose(fp);
	return i;
}

void writeFileS(FILE *fp, Student *s, int n) {

	for (int i = 0; i < n; i++) {
		fwrite(s + i, sizeof(Student), 1, fp);
	}
	fclose(fp);
}

int readFileC(FILE *fp, Course *c) {
	int i = 0;

	while (1) {
		fread(c + i, sizeof(Course), 1, fp);
		if (feof(fp))
			break;
		i++;
	}
	fclose(fp);
	return i;
}

void writeFileC(FILE *fp, Course *c, int n) {

	for (int i = 0; i < n; i++) {
		fwrite(c + i, sizeof(Course), 1, fp);
	}
	fclose(fp);
}

int readFileSC(FILE *fp, SC *sc) {
	int i = 0;

	while (1) {
		fread(sc + i, sizeof(SC), 1, fp);
		if (feof(fp))
			break;
		i++;
	}
	fclose(fp);
	return i;
}

void writeFileSC(FILE *fp, SC *sc, int n) {

	for (int i = 0; i < n; i++)
		fwrite(sc + i, sizeof(SC), 1, fp);
	fclose(fp);
}
