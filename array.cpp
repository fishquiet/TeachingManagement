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
		printf("\n\t\t ѧ��ѡ����Ϣ�������");
		printf("\n\t--------------------------------------");
		printf("\n\t\t 1--��������");
		printf("\n\t\t 2--��ѯѧ������");
		printf("\n\t\t 3--��ѯ�γ�����");
		printf("\n\t\t 4--��ѯѧ��ѡ�μ��ɼ�����");
		printf("\n\t\t 5--���ݸ��£�ɾ����");
		printf("\n\t\t 0--�˳�");
		printf("\n\t---------------------------------------");
		printf("\n\t\t ��ѡ��(0 - 5)��");
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
				printf("\n\t\t  �������빦��");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 1--���ѧ������");
				printf("\n\t\t 2--��ӿγ�����");
				printf("\n\t\t 3--��ӳɼ�����");
				printf("\n\t\t 0--�����ϼ��˵�");
				printf("\n\t--------------------------------------");
				printf("\n\t\t ��ѡ��(0 - 9)��");
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
				printf("\n\t\t ѧ�����ݹ���");
				printf("\n\t--------------------------------------");
				printf("\n\t\t 1--��ʾ����ѧ��");
				printf("\n\t\t 2--��ѧ������");
				printf("\n\t\t 3--��ѧ�Ų�ѯѧ��");
				printf("\n\t\t 4--��ѧ��ɾ��ѧ��");
				printf("\n\t\t 5--��ѧ��ƽ������");
				printf("\n\t\t 6--�����Ӧ����ͳ�Ʊ�");
				printf("\n\t\t 7--���Ա�ͳ��ѧ������");
				printf("\n\t\t 8--������ͳ��ѧ������");
				printf("\n\t\t 0--������һ��");
				printf("\n\t---------------------------------------");
				printf("\n\t\t ��ѡ��(0 - 8)��");
				int x2;
				scanf("%d", &x2);
				fflush(stdin);
				if (x2 == 0) {
					break;
				}
				if (x2 == 1) {
					printf("\t\t ����%d��ѧ��\n", n);
					n = outputAllS(s, n);
				}
				if (x2 == 2) {
					sortBySno(s, n);
					printf("\t�������\n\t����%d��ѧ��\n", n);
					n = outputAllS(s, n);
				}
				if (x2 == 3) {
					int varSno;
					printf("\t������Ҫ��ѯ��ѧ�ţ�");
					scanf("%d", &varSno);
					int i = searchBySno(s, n, varSno);
					if (i == -1) {
						printf("\tû���ҵ���ѧ��");
					} else {
						printf("\t��ѧ���ڵ�%dλ\n", i + 1);
					}
				}
				if (x2 == 4) {
					int varSno;
					printf("\t������Ҫɾ����ѧ�ţ�");
					scanf("%d", &varSno);
					n = deleteBySno(s, n, varSno);
					printf("\n\tɾ�����ѧ����%d��\n", n);
					n = outputAllS(s, n);
				}
				if (x2 == 5) {
					double avg = averageAge(s, n);
					printf("\tѧ����ƽ�����䣺%.3f\n", avg);
				}
				if (x2 == 6) {
					int *p = countByAge(s, n);
					for (int i = 0; i < n; i++) {
						if (p[i] != 0) {
							printf("\t����: %d \n\t���� %d\n", s[i].age, p[i]);
						}
					}
					free(p);
				}
				if ( x2 == 7) {
					printf("\t��������Ҫ��ѯ���Ա�");
					char *varGender = (char *)malloc(sizeof(char));
					scanf("%s", varGender);
					int count = countByGender(s, n, varGender);
					printf("\t���Ա������Ϊ��%d\n", count);
				}
				if (x2 == 8) {
					char varNation[10];
					printf("\t���������壺");
					gets(varNation);
					int i = countByNation(s, n, varNation);
					printf("\n\t��%d��ѧ��\n", i);
				}
				system("pause");
			}
		}
		if (option == 3) {
			while (1) {
				system("cls");
				printf("\n\t\t �γ����ݹ���");
				printf("\n\t------------------------------------");
				printf("\n\t\t1--��ʾ���пγ�");
				printf("\n\t\t2--���γ̺�����");
				printf("\n\t\t3--���γ̺Ų�ѯ�γ�");
				printf("\n\t\t4--���γ̺�ɾ���γ�");
				printf("\n\t\t5--ѧ�ֶ�Ӧ�γ�����ͳ�Ʊ�");
				printf("\n\t\t0--�����ϼ��˵�");
				printf("\n\t--------------------------------------");
				printf("\n\t\t ��ѡ��(0 - 5)��");
				int x3;
				scanf("%d", &x3);
				fflush(stdin);
				if (x3 == 0) {
					break;
				}
				if (x3 == 1) {
					printf("\t\t ��%d�ſγ�\n", m);
					m = outputAllC(c, m);
				}
				if (x3 == 2) {
					sortByCno(c, m);
					puts("\t\t �������");
					printf("\t\t ����%d�ſγ�\n", m);
					m = outputAllC(c, m);
				}
				if (x3 == 3) {
					int varCno;
					printf("\t������Ҫ��ѯ�Ŀγ̺ţ�");
					scanf("%d", &varCno);
					int i = searchByCno(c, m, varCno);
					if (i == -1) {
						printf("\tû���ҵ��ÿγ�");
					} else {
						printf("\t�ÿγ��ڵ�%dλ\n", i + 1);
					}
				}
				if (x3 == 4) {
					int varCno;
					printf("\t������Ҫɾ���Ŀγ̺ţ�");
					scanf("%d", &varCno);
					m = deleteByCno(c, m, varCno);
					printf("\n\tɾ����Ŀγ���%d��\n", m);
					m = outputAllC(c, m);
				}
				if (x3 == 5) {
					int *p = countByCredit(c, m);
					for (int i = 0; i < m; i++) {
						if (p[i] != 0) {
							printf("\tѧ��: %.1f \n\t���� %d\n", c[i].credit, p[i]);
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
				printf("\n\t\t ѧ��ѡ�μ��ɼ�����");
				printf("\n\t------------------------------------");
				printf("\n\t\t1--�������ѧ��ѡ�μ��ɼ�����");
				printf("\n\t\t2--��ѧ�������Ϳγ�����ѯ�ɼ�");
				printf("\n\t\t3--��ѧ�Ų�ѯѧ���ɼ�");
				printf("\n\t\t4--���γ̺Ų�ѯѧ���ɼ�");
				printf("\n\t\t5--��ѧ���ܳɼ�������а�");
				printf("\n\t\t6--��ѧ�źͿγ̺�ɾ��ѧ���ɼ�");
				printf("\n\t\t0--�����ϼ��˵�");
				printf("\n\t--------------------------------------");
				printf("\n\t\t ��ѡ��(0 - 5)��");
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
					printf("\t\t������");
					scanf("%s", varSname);
					char *varCname = (char *)malloc(sizeof(char));
					printf("\t\t�γ�����");
					scanf("%s", varCname);
					searchGrade(sc, num, s, n, c, m, varSname, varCname);
				}
				if (x4 == 3) {
					int varSno;
					printf("\t\tѧ�ţ�");
					scanf("%d", &varSno);
					searchSCBySno(sc, num, c, m, varSno);
				}
				if (x4 == 4) {
					int varCno;
					printf("\t\t�γ̺ţ�");
					scanf("%d", &varCno);
					searchSCByCno(sc, num, s, n, varCno);
				}
				if (x4 == 5)
					sortByAverageGrade(sc, num, s, n);
				if (x4 == 6) {
					int varSno;
					printf("ѧ�ţ�");
					scanf("%d", &varSno);
					num = deleteSCBySno(sc, num, varSno);
				}
				system("pause");
			}
		}
		if (option == 5) {
			while (1) {
				system("cls");
				printf("\n\t\t ��������");
				printf("\n\t------------------------------------");
				printf("\n\t\t1--��ѧ��ɾ��ѧ������ѧ����");
				printf("\n\t\t2--���γ̺ſγ̣��ӿγ̱�");
				printf("\n\t\t3--��ѧ�źͿγ̺�ɾ��ѧ���ɼ����ӳɼ���");
				printf("\n\t\t0--�����ϼ��˵�");
				printf("\n\t--------------------------------------");
				printf("\n\t\t ��ѡ��(0 - 3)��");
				int x5;
				scanf("%d", &x5);
				fflush(stdin);
				if (x5 == 0) {
					break;
				}
				if (x5 == 1) {
					int varSno;
					printf("\t������Ҫɾ����ѧ�ţ�");
					scanf("%d", &varSno);
					n = deleteBySno(s, n, varSno);
					printf("\n\tɾ�����ѧ����%d��\n", n);
					n = outputAllS(s, n);
				}
				if (x5 == 2) {
					int varCno;
					printf("\t������Ҫɾ���Ŀγ̺ţ�");
					scanf("%d", &varCno);
					m = deleteByCno(c, m, varCno);
					printf("\n\tɾ����Ŀγ���%d��\n", m);
					m = outputAllC(c, m);
				}
				if (x5 == 3) {
					int varSno;
					printf("ѧ�ţ�");
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
	printf("\t\t������");
	scanf("%s", p->sname);
	printf("\t\t�Ա�");
	scanf("%s", p->gender);
	printf("\t\t���壺");
	scanf("%s", p->nation);
	printf("\t\t���䣺");
	scanf("%d", &p->age);
}


int inputAllS(Student *s, int n) {
	char tmp1, tmp2 = '1';
	int i = 0;

	while (1) {
		printf("\t\tĿǰ��¼���ѧ������Ϊ��%d\n", n);
		if (n != 0) {
			int varSno;
			printf("\t\tѧ�ţ�");
			scanf("%d", &varSno);
			int flag = checkSno(s, n, varSno);
			if (flag != 0) {
				puts("\t\tѧ���ظ�������������");
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
			printf("\t\tѧ�ţ�");
			scanf("%d", &varSno);
			s[i].sno = varSno;
			Student *p;
			p = &s[i];
			inputS(p);
			i++;
			n++;
		}
		puts("\t\t�Ƿ����¼��?\n\t\t��1�˳�������������");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	puts("\t\t���������ѧ����ϵͳ��");
	return n;
}

void inputC(Course *p) {
	printf("\t\t�γ�����");
	printf("\t\tѧ�֣�");
	scanf("%f", &p->credit);
}


int inputAllC(Course *c, int n) {
	char tmp1, tmp2 = '1';
	int i = 0;

	while (1) {
		printf("\t\tĿǰ��¼��Ŀγ���Ϊ��%d\n", n);
		if (n != 0) {
			int varCno;
			printf("\t\t�γ̺ţ�");
			scanf("%d", &varCno);
			int flag = checkCno(c, n, varCno);
			if (flag != 0) {
				puts("\t\t�γ̺��ظ�������������");
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
			printf("\t\t�γ̺ţ�");
			scanf("%d", &varCno);
			c[i].cno = varCno;
			Course *p;
			p = &c[i];
			inputC(p);
			i++;
			n++;
		}
		puts("\t\t�Ƿ����¼��?\n\t\t��1�˳�������������");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	puts("\t\t��������Ͽγ���ϵͳ��");
	return n;
}

void inputSC(SC *p, int num, Student *s, int n, Course *c, int m) {
	int varSno;
	printf("\t\tѧ�ţ�");
	scanf("%d", &varSno);
	int t1 = checkSno(s, n, varSno);

	if (t1 != 1) {
		puts("\t\t��ѧ��������");

	} else {
		p->sno = varSno;
		int varCno;
		printf("\t\t�γ̺ţ�");
		scanf("%d", &varCno);
		int t2 = checkCno(c, m, varCno);
		if (t2 != 1) {
			puts("\n\t\t�ÿγ̲�����");
		} else {
			p->cno = varCno;
			printf("\t\t�ɼ���");
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
		puts("\n\t�Ƿ����¼��?\n\t��1�˳�������������");
		getchar();
		scanf("%c", &tmp1);
		if (tmp1 == tmp2)
			break;
	}
	return num;
}



void outputS(Student *p) {
	printf("\tѧ�ţ�%d\n \t������%s\n \t�Ա�%s\n \t���壺%s\n \t���䣺%d\n", p->sno, p->sname, p->gender,
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
	printf("\t�γ̺ţ�%d\n \t�γ�����%s\n \tѧ�֣�%.1f\n ", p->cno, p->cname, p->credit);
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
	printf("\tѧ�ţ�%d", scout->sno);

	for (int i = 0; i < n; i++) {
		if (scout->sno == s[i].sno)
			printf("\n\t������%s", s[i].sname);
	}
	printf("\n\t�γ̺ţ�%d", scout->cno);

	for (int i = 0; i < m; i++) {
		if (scout->cno == c[i].cno)
			printf("\n\t�γ�����%s", c[i].cname);
	}
	printf("\n\t�ɼ���%d\n", scout->grade);
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
		puts("\t�������ѧ����");

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
		printf("\tɾ���ɹ�");
		n--;
		num = n;

	} else if (test == -1) {
		printf("\n\tδ�ҵ���ѧ��");
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
		printf("\tɾ���ɹ�");
		n--;
		num = n;

	} else if (test == -1) {
		printf("\n\tδ�ҵ���ѧ��");
		num = - 1;
	}
	return num;
}

int *countByAge(Student *s, int n) {
	int *countarray = (int *)malloc(sizeof(int) * MAX_S); //������ͬʱ��¼ѧ���Ƿ�ͳ�ƺ������ѧ������
	int i, count;
	for (i = 0; i < n; i++)
		countarray[i] = 1;
	for (i = 0; i < n; i++) {
		count = 1;//��ʼͳ��������ִ��������ٳ���һ��
		if (countarray[i] == 0) {
			continue;
		}
		for (int j = i + 1; j < n; j++) {
			if (s[i].age == s[j].age) {//�����Ⱦ�count+1
				countarray[j] = 0;//��Ϊ0˵��ѧ���Ѿ���ͳ�ƹ�
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
			puts("\t\tû�и�ѧ��");
		}
	}

	for (int i = 0; i < m; i++) {

		if ((strcmp(varCname, c[i].cname)) == 0) {
			b = c[i].cno;
			t2 = 1;

		} else if ((strcmp(varCname, c[m].cname)) != 0 && t2 != 1) {
			puts("\t\tû�иÿγ�");
		}
	}

	for (int i = 0; i < num; i++) {
		if (a == sc[i].sno && b == sc[i].cno)
			printf("\t\t�ɼ���%d\n", sc[i].grade);
	}
}


void searchSCByCno(SC *sc, int num, Student *s, int n, int varCno) {
	int sum, cnum;
	float avg;

	for (int i = 0; i < num; i++) {
		if (varCno == sc[i].cno) {
			sum += sc[i].grade;
			cnum++;
			printf("\t\tѧ�ţ�%d\n", sc[i].sno);
			for (int j = 0; j < n; j++) {
				if (sc[i].sno == s[j].sno)
					printf("\t\t������%s\n", s[j].sname);
			}
			printf("\t\t�ɼ���%d", sc[i].grade);
		}
	}
	avg = sum / cnum;
	printf("\n\t\t�ܳɼ���%d��ƽ���ɼ���%.2f\n", sum, avg);
}

void searchSCBySno(SC *sc, int num, Course *c, int m, int varSno) {
	int sum, snum;
	float avg;

	for (int i = 0; i < num; i++) {
		if (varSno == sc[i].sno) {
			sum += sc[i].grade;
			snum++;
			printf("\t\t�γ̺ţ�%d\n", sc[i].cno);
			for (int j = 0; j < m; j++) {
				if (sc[i].cno == c[j].cno)
					printf("\t\t�γ�����%s", c[j].cname);
			}
			printf("\n\t\t�ɼ���%d", sc[i].grade);
		}
	}
	avg = sum / snum;
	printf("\n\t\t�ܳɼ���%d��ƽ���ɼ���%.2f\n", sum, avg);
}

int deleteSCBySno(SC *sc, int num, int varSno) {
	char tmp1, tmp2 = '1';

	while (1) {
		int test = 0;
		int varCno;
		printf("\t�γ̺ţ�");
		scanf("%d", &varCno);
		for (int i = 0; i < num; i++) {

			if (sc[i].cno == varCno) {
				sc[i] = sc[i + 1];
				test = 1;
			}
		}
		if (test = 1) {
			printf("\tɾ���ɹ�");

		} else {
			printf("\tδ�ҵ��ÿγ�");
		}

		puts("\n\t�Ƿ�ɾ���γ̣�\n\t��1�˳�������������");
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
		printf("\t���Σ�%d\n\tѧ�ţ�%d\n\t������%s\n\t�ܳɼ���%d\n", p->ranking, p->stu.sno, p->stu.sname, p->allgrade);
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
