#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EPSILON 0.01

typedef struct Student {
	int sno;
	char sname[20];
	char gender[3];
	char nation[10];
	int age;
} stu;

typedef struct Course {
	int cno;
	char cname[20];
	float credit;
} cour;

struct SC {
	int sno;
	int cno;
	int grade;
};

struct S_Node {
	Student data;
	S_Node *next;
};

struct C_Node {
	Course data;
	C_Node *next;
};

struct SC_Node {
	SC data;
	SC_Node *next;
};

struct SA {
	int age;
	int num;
};

struct SN {
	char nation[10];
	int num;
};

struct CC {
	float credit;
	int num;
};

struct SR {
	Student stu;
	int allgrade;
	int ranking;
	SR *next;
};


S_Node *S_phead = NULL;
C_Node *C_phead = NULL;
SC_Node *SC_phead = NULL;
SR *SR_phead = NULL;
void menu1();
void menu2();
void menu3();
void menu4();
void menu5();

int checkSno(S_Node *, int);
int checkCno(C_Node *, int);
int countstu(S_Node *);

void writeFileS(FILE *, S_Node *);
S_Node *readFileS(FILE *fp);
void writeFileC(FILE *, C_Node *);
C_Node *readFileC(FILE *fp);
void writeFileSC(FILE *, SC_Node *);
SC_Node *readFileSC(FILE *fp);

int main(void) {
	char fn1[20] = "student.dat";
	char fn2[20] = "course.dat";
	char fn3[10] = "sc.dat";
	FILE *fp1, *fp2, *fp3;
	fp1 = fopen(fn1, "ab+");
	fp2 = fopen(fn2, "ab+");
	fp3 = fopen(fn3, "ab+");
	S_phead = readFileS(fp1);
	C_phead = readFileC(fp2);
	SC_phead = readFileSC(fp3);
	while (1) {
		system("cls");
		printf("\n\t\t\t ��ѧ�������(�����)���ƿ�222�ྲ��");
		printf("\n\t\t-------------------------------------");
		printf("\n\t\t\t 1--��������");
		printf("\n\t\t\t 2--��ѯѧ������");
		printf("\n\t\t\t 3--��ѯ�γ�����");
		printf("\n\t\t\t 4--��ѯѧ��ѡ�μ��ɼ�����");
		printf("\n\t\t\t 5--���ݸ���(ɾ��)");
		printf("\n\t\t\t 0--�˳�");
		printf("\n\t\t-------------------------------------");
		printf("\n\t\t\t ��ѡ��(0 - 5)��");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0) {
			fp1 = fopen(fn1, "wb");
			fp2 = fopen(fn2, "wb");
			fp3 = fopen(fn3, "wb");
			writeFileS(fp1, S_phead);
			fclose(fp1);
			writeFileC(fp2, C_phead);
			fclose(fp2);
			writeFileSC(fp3, SC_phead);
			fclose(fp3);
			exit(0);
		}
		if (option == 1) {
			menu1();
		}
		if (option == 2) {
			menu2();
		}
		if (option == 3) {
			menu3();
		}
		if (option == 4) {
			menu4();
		}
		if (option == 5) {
			menu5();
		}
	}
}

void menu1() {
	while (1) {
		system("cls");
		printf("\n\t\t �������빦��");
		printf("\n\t\t--------------------");
		printf("\n\t\t 1--����ѧ������");
		printf("\n\t\t 2--���ӿγ�����");
		printf("\n\t\t 3--����ѧ��ѡ������");
		printf("\n\t\t 0--�����ϼ��˵�");
		printf("\n\t\t--------------------");
		printf("\n\t\t ��ѡ��(0 - 3)��");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0) {
			return;
		}
		if (option == 1) {
			char tmp1, tmp2 = '1';
			int flag;
			while (1) {
				if (S_phead == NULL) {
					S_Node *pnew = (S_Node *)malloc(sizeof(S_Node));
					pnew->next = NULL;
					S_phead = pnew;
					printf("\t\tѧ�� : ");
					scanf("%d", &pnew->data.sno);
					printf("\t\t����: ");
					scanf("%s", pnew->data.sname);
					printf("\t\t�Ա�");
					scanf("%s", pnew->data.gender);
					printf("\t\t���壺");
					scanf("%s", pnew->data.nation);
					printf("\t\t����: ");
					scanf("%d", &pnew->data.age);
				} else {
					int varSno;
					printf("\t\tѧ�� : ");
					scanf("%d", &varSno);
					flag = checkSno(S_phead, varSno);
					if (flag != 0) {
						puts("\t\tѧ���ظ�������������");
						continue;
					} else {
						S_Node *pnew = (S_Node *)malloc(sizeof(S_Node));
						pnew->next = NULL;
						pnew->data.sno = varSno;
						pnew->next = S_phead;
						S_phead = pnew;
						printf("\t\t����: ");
						scanf("%s", pnew->data.sname);
						printf("\t\t�Ա�");
						scanf("%s", pnew->data.gender);
						printf("\t\t���壺");
						scanf("%s", pnew->data.nation);
						printf("\t\t����: ");
						scanf("%d", &pnew->data.age);
					}
				}
				printf("\t\t��ѧ����Ϣ������ϣ�\n\n");
				puts("\t\t�Ƿ����¼��?\n\t\t��1�˳�������������");
				getchar();
				scanf("%c", &tmp1);
				if (tmp1 == tmp2)
					break;
			}
		}
		if (option == 2) {
			char tmp1, tmp2 = '1';
			int flag;
			while (1) {
				C_Node *pnew = (C_Node *)malloc(sizeof(C_Node));
				pnew->next = NULL;
				if (C_phead == NULL) {
					C_phead = pnew;
					printf("\t\t�γ̺� : ");
					scanf("%d", &pnew->data.cno);
				} else {
					pnew->next = C_phead;
					C_phead = pnew;
					int varCno;
					printf("\t\t�γ̺� : ");
					scanf("%d", &varCno);
					flag = checkCno(C_phead, varCno);
					if (flag != 0) {
						puts("\t\t�γ̺��ظ�������������");
						continue;
					} else {
						pnew->data.cno = varCno;
					}
				}
				printf("\t\t�γ���: ");
				scanf("%s", pnew->data.cname);
				printf("\t\tѧ�֣�");
				scanf("%f", &pnew->data.credit);
				puts("\t\t�Ƿ����¼��?\n\t\t��1�˳�������������");
				getchar();
				scanf("%c", &tmp1);
				if (tmp1 == tmp2) {
					break;
				}
			}
		}
		if (option == 3) {
			char tmp1, tmp2 = '1';
			int flag1 = 0, flag2 = 0;
			while (1) {
				SC_Node *pnew = (SC_Node *)malloc(sizeof(SC_Node));
				pnew->next = NULL;
				if (SC_phead == NULL) {
					SC_phead = pnew;
					printf("\t\tѧ�ţ�");
					scanf("%d", &pnew->data.sno);
					printf("\t\t�γ̺� : ");
					scanf("%d", &pnew->data.cno);
				} else {
					pnew->next = SC_phead;
					SC_phead = pnew;
					int varSno;
					printf("\t\tѧ�� : ");
					scanf("%d", &varSno);
					int varCno;
					printf("\t\t�γ̺� : ");
					scanf("%d", &varCno);
					flag2 = checkCno(C_phead, varCno);
					if (flag1 != 1 || flag2 != 1) {
						puts("\t\tѧ����γ̲����ڣ�����������");
						continue;
					} else {
						pnew->data.cno = varCno;
					}
				}
				printf("\t\t�ɼ���");
				scanf("%d", &pnew->data.grade);
				puts("\t\t�Ƿ����¼��?\n\t\t��1�˳�������������");
				getchar();
				scanf("%c", &tmp1);
				if (tmp1 == tmp2) {
					break;
				}
			}
		}
	}
	system("pause");
}

void menu2() {
	while (1) {
		system("cls");
		printf("\n\t\t ѧ�����ݲ�ѯ����");
		printf("\n\t--------------------------------------");
		printf("\n\t\t 1--��ʾ����ѧ��");
		printf("\n\t\t 2--���Ա�ͳ��ѧ������");
		printf("\n\t\t 3--��ѧ��ƽ������");
		printf("\n\t\t 4--��ѧ������");
		printf("\n\t\t 5--��ѧ�Ų�ѯѧ��");
		printf("\n\t\t 6--�����Ӧ����ͳ�Ʊ�");
		printf("\n\t\t 7--�����Ӧ����ͳ�Ʊ�");
		printf("\n\t\t 0--�����ϼ��˵�");
		printf("\n\t---------------------------------------");
		printf("\n\t\t ��ѡ��(0 - 7)��");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0)
			return;
		if (option == 1) {
			S_Node *p = S_phead;
			if (S_phead != NULL) {
				while (p != NULL) {
					printf("\t\tѧ�ţ�%d\n \t\t������%s\n \t\t�Ա�%s\n \t\t���壺%s\n \t\t���䣺%d\n", p->data.sno, p->data.sname,
					       p->data.gender,
					       p->data.nation,
					       p->data.age);
					p = p->next;
				}
			} else {
				puts("\t\t�������ѧ����");
			}
		}
		if (option == 2) {
			int count = 0;
			S_Node *p = S_phead;
			printf("\t\t��������Ҫ��ѯ���Ա�");
			char *varGender = (char *)malloc(sizeof(char));
			scanf("%s", varGender);
			if (S_phead != NULL) {
				while (p != NULL) {
					if (strcmp(p->data.gender, varGender) == 0) {
						count++;
					}
					p = p->next;
				}
				printf("\t\t���Ա������Ϊ��%d\n", count);
			} else {
				puts("\t\t�������ѧ����");
			}
		}
		if (option == 3) {
			double avg, sum;
			S_Node *p = S_phead;
			if (S_phead != NULL) {
				while (p != NULL) {
					sum += p->data.age;
					p = p->next;
				}
				int n = countstu(S_phead);
				avg = sum / n;
				printf("\t\t%d��ѧ����ƽ������Ϊ��%.2lf", n, avg);
			} else {
				puts("\t\t�������ѧ����");
			}
		}
		if (option == 4) {
			stu temp;
			S_Node *p = S_phead;
			while (p != NULL) {
				if (p->data.sno > p->next->data.sno) {
					temp = p->data;
					p->data = p->next->data;
					p->next->data = temp;
				}
				p = p->next;
			}
			S_Node *q = S_phead;
			while (q != NULL) {
				printf("\t\tѧ�ţ�%d\n \t\t������%s\n \t\t�Ա�%s\n \t\t���壺%s\n \t\t���䣺%d\n", q->data.sno, q->data.sname,
				       q->data.gender,
				       q->data.nation,
				       q->data.age);
				q = q->next;
			}
		}
		if (option == 5) {
			int num;
			printf("\t\t������Ҫ���ҵ�ѧ��ѧ�ţ�");
			scanf("%d", &num);
			S_Node *p = S_phead;
			int flag = 0;
			while (p != NULL) {
				if (p->data.sno == num) {
					printf("\t\tѧ�ţ�%d\n \t\t������%s\n \t\t�Ա�%s\n \t\t���壺%s\n \t\t���䣺%d\n", p->data.sno, p->data.sname,
					       p->data.gender,
					       p->data.nation,
					       p->data.age);
					flag = 1;
				}
				p = p->next;
			}
			if (flag != 1) {
				printf("\t\t�޸�ѧ����Ϣ");
			}
		}
		if (option == 6) {
			SA *sa = (SA *)malloc(sizeof(SA) * 50);
			if (S_phead = NULL) {
				puts("\t\t�������ѧ����");
			} else {
				int i = 0;
				S_Node *p = S_phead;
				sa[i].age = p->data.age;
				sa[i].num = 1;
				i++;
				p = p->next;
				while (p != NULL) {
					int flag = 0; //�ж�p�������Ƿ����sa������
					for (int j = 0; j < i; j++) {
						if (p->data.age == sa[j].age) {
							sa[j].num++;
							flag = 1;
						}
					}
					if (flag != 1) {
						sa[i].age = p->data.age;
						sa[i].num = 1;
						i++;
					}
					p = p->next;
				}
				for (int k = 0; k < i; k++) {
					printf("\t\t���䣺%d��������%d", sa[k].age, sa[k].num);
				}
			}
		}
		if (option == 7) {
			SN *sn = (SN *)malloc(sizeof(SN) * 50);
			if (S_phead = NULL) {
				puts("\t\t�������ѧ����");
			} else {
				int i = 0;
				S_Node *p = S_phead;
				strcpy(sn[i].nation, p->data.nation);
				sn[i].num = 1;
				i++;
				p = p->next;
				while (p != NULL) {
					int flag = 0;
					for (int j = 0; j < i; j++) {
						if (strcmp(sn[i].nation, p->data.nation) == 0) {
							sn[j].num++;
							flag = 1;
						}
					}
					if (flag != 1) {
						strcpy(sn[i].nation, p->data.nation);
						sn[i].num = 1;
						i++;
					}
					p = p->next;
				}
				for (int k = 0; k < i; k++) {
					printf("\t\t���壺%s��������%d", sn[k].nation, sn[k].num);
				}
			}
		}
		system("pause");
	}
}

void menu3() {
	while (1) {
		system("cls");
		printf("\n\t\t ��ѯ�γ����ݹ���");
		printf("\n\t\t--------------------------");
		printf("\n\t\t 1--��ʾ���пγ�");
		printf("\n\t\t 2--���γ̺�����");
		printf("\n\t\t 3--���γ̺Ų�ѯ�γ�");
		printf("\n\t\t 4--ѧ�ֶ�Ӧ�γ�����ͳ�Ʊ�");
		printf("\n\t\t 0--�����ϼ��˵�");
		printf("\n\t\t--------------------------");
		printf("\n\t\t ��ѡ��(0 - 4)��");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0)
			return;
		if (option == 1) {
			C_Node *p = C_phead;
			if (C_phead != NULL) {
				while (p != NULL) {
					printf("\t\t�γ̺ţ�%d\n \t\t�γ�����%s\n \t\tѧ�֣�%.1f\n ", p->data.cno, p->data.cname, p->data.credit);
					p = p->next;
				}
			} else {
				puts("\t\t������ӿγ̣�");
			}
		}
		if (option == 2) {
			cour temp;
			C_Node *p = C_phead;
			while (p != NULL) {
				if (p->data.cno > p->next->data.cno) {
					temp = p->data;
					p->data = p->next->data;
					p->next->data = temp;
				}
				p = p->next;
			}
			C_Node *q = C_phead;
			while (q != NULL) {
				printf("\t\t�γ̺ţ�%d\n \t\t�γ�����%s\n \t\tѧ�֣�%.1f\n ", q->data.cno, q->data.cname, q->data.credit);
				q = q->next;
			}
		}
		if (option == 3) {
			int num;
			printf("\t\t������Ҫ���ҵĿγ̺ţ�");
			scanf("%d", &num);
			C_Node *p = C_phead;
			int flag = 0;
			while (p != NULL) {
				if (p->data.cno == num) {
					printf("\t\t�γ̺ţ�%d\n \t\t�γ�����%s\n \t\tѧ�֣�%.1f\n ", p->data.cno, p->data.cname, p->data.credit);
					flag = 1;
				}
				p = p->next;
			}
			if (flag != 1) {
				printf("\t\t�޸ÿγ���Ϣ");
			}
		}
		if (option == 4) {
			CC *cc = (CC *)malloc(sizeof(CC) * 50);
			if (C_phead = NULL) {
				puts("\t\t������ӿγ�");
			} else {
				int i = 0;
				C_Node *p = C_phead;
				cc[i].credit = p->data.cno;
				cc[i].num = 1;
				i++;
				p = p->next;
				while (p != NULL) {
					int flag = 0;
					for (int j = 0; j < i; j++) {
						if (fabs(cc[j].credit - p->data.credit) <= EPSILON) {
							cc[j].num++;
							flag = 1;
						}
					}
					if (flag != 1) {
						cc[i].credit = p->data.cno;
						cc[i].num = 1;
						i++;
					}
					p = p->next;
				}
				for (int k = 0; k < i; k++) {
					printf("\t\tѧ�֣�%.1f��������%d", cc[k].credit, cc[k].num);
				}
			}
		}
		system("pause");
	}
}


void menu4() {
	while (1) {
		system("cls");
		printf("\n\t\t ѧ��ѡ�μ��ɼ���ѯ����");
		printf("\n\t\t--------------------------------");
		printf("\n\t\t 1--�������ѧ��ѡ�μ��ɼ�����");
		printf("\n\t\t 2--��ѯĳѧ��ѡĳ�γ̵ĳɼ�");
		printf("\n\t\t 3--��ѯĳ�γ�ѧ��ѡ����ϸ���");
		printf("\n\t\t 4--��ѯĳѧ��ѡ����ϸ���");
		printf("\n\t\t 5--��ѧ���ܳɼ�������а�");
		printf("\n\t\t 0--�����ϼ��˵�");
		printf("\n\t\t--------------------------------");
		printf("\n\t\t ��ѡ��(0 - 5)��");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0)
			return;
		if (option == 1) {
			SC_Node *p = SC_phead;
			if (SC_phead != NULL) {
				while (p != NULL) {
					printf("\t\tѧ�ţ�%d\n \t\t�γ̺ţ�%d\n \t\t�ɼ���%d\n ", p->data.sno, p->data.cno, p->data.grade);
					p = p->next;
				}
			} else {
				puts("\t\t������ӳɼ�");
			}
		}
		if (option == 2) {
			int varSno, varCno;
			printf("\t\tѧ�ţ�");
			scanf("%d", &varSno);
			printf("\t\t�γ̺ţ�");
			scanf("%d", &varCno);
			SC_Node *p = SC_phead;
			while (p != NULL) {
				if (p->data.sno == varSno && p->data.cno == varCno)
					printf("\t\tѧ�ţ�%d\n \t\t�γ̺ţ�%d\n \t\t�ɼ���%d\n ", p->data.sno, p->data.cno, p->data.grade);
				p = p->next;
			}
		}
		if (option == 3) {
			int varCno;
			printf("\t\t�γ̺ţ�");
			scanf("%d", &varCno);
			SC_Node *p = SC_phead;
			while (p != NULL) {
				if (p->data.cno == varCno)
					printf("\t\tѧ�ţ�%d\n \t\t�γ̺ţ�%d\n \t\t�ɼ���%d\n ", p->data.sno, p->data.cno, p->data.grade);
				p = p->next;
			}
		}
		if (option == 4) {
			int varSno;
			printf("\t\tѧ�ţ�");
			scanf("%d", &varSno);
			SC_Node *p = SC_phead;
			while (p != NULL) {
				if (p->data.sno == varSno)
					printf("\t\tѧ�ţ�%d\n \t\t�γ̺ţ�%d\n \t\t�ɼ���%d\n ", p->data.sno, p->data.cno, p->data.grade);
				p = p->next;
			}
		}
		if (option == 5) {
			int n = countstu(S_phead);
			S_Node *s = S_phead;
			SR_phead = (SR *)malloc(sizeof(SR));//��������
			SR_phead->next = NULL;//�ÿ���һ�ڵ�
			while (s != NULL) {
				if (SR_phead = NULL) {//����Ϊ��
					SC_Node *sc = SC_phead;
					SR_phead->stu = s->data;
					while (sc != NULL) {
						if (SR_phead->stu.sno == sc->data.sno) {
							SR_phead->allgrade += sc->data.grade;
						}
						sc = sc->next;
					}
					s = s->next;
				} else {
					SR *p = (SR *)malloc(sizeof(SR));
					p->stu = s->data;
					SC_Node *sc = SC_phead;
					while (sc != NULL) {
						if (p->stu.sno == sc->data.sno) {
							p->allgrade += sc->data.sno;
						}
						sc = sc->next;
					}
					if (p->allgrade >= SR_phead->allgrade) {
						p->next = SR_phead->next;
						SR_phead->next = p;
					} else {
						SR_phead->next = p;
						p->next = NULL;
					}
					s = s->next;
				}
			}
			SR *q = SR_phead;
			for (int i = 1; i <= n ; i++) {
				q->ranking = i;
				q = q->next;
			}

			SR *sr = SR_phead;
			while (sr != NULL) {
				printf("\t\t���Σ�%d\n\t\tѧ�ţ�%d\n\t\t������%s\n\t\t�ܳɼ���%d\n", sr->ranking, sr->stu.sno, sr->stu.sname,
				       sr->allgrade);
				sr = sr->next;
			}
		}
		system("pause");
	}
}


void menu5() {
	while (1) {
		system("cls");
		printf("\n\t\t ɾ�����ݹ���");
		printf("\n\t\t------------------------------");
		printf("\n\t\t 1--ɾ��ĳѧ��(��ѧ����)");
		printf("\n\t\t 2--ɾ��ĳ�γ�(�ӿγ̱�)");
		printf("\n\t\t 3--ɾ��ĳѧ������Ӧ��ѡ����ϸ");
		printf("\n\t\t 0--�����ϼ��˵�");
		printf("\n\t\t------------------------------");
		printf("\n\t\t ��ѡ��(0 - 3)��");
		int option;
		scanf("%d", &option);
		fflush(stdin);
		if (option == 0)
			return;
		if (option == 1) {
			int num;
			S_Node *p;
			S_Node *q;
			p = S_phead->next;
			printf("\n׼��ɾ����ѧ�ţ�");
			scanf("%d", &num);
			if (p->data.sno == num) {
				printf("\tѧ�ţ�%d\n \t������%s\n \t�Ա�%s\n \t���壺%s\n \t���䣺%d\n", p->data.sno, p->data.sname, p->data.gender,
				       p->data.nation,
				       p->data.age);
				S_phead->next = p->next;
				free(p);
				printf("��ͬѧ��Ϣ�Ѿ�ɾ��\n");
			} else {
				while (p->next != NULL && p->next->data.sno != num)
					p = p->next;
				if (p->next == NULL)
					printf("���޴���\n");
				else {
					q = p->next;
					printf("\tѧ�ţ�%d\n \t������%s\n \t�Ա�%s\n \t���壺%s\n \t���䣺%d\n", p->data.sno, p->data.sname, p->data.gender,
					       p->data.nation,
					       p->data.age);
					p->next = q->next;
					free(q);
					printf("\t\t��ͬѧ��Ϣ�Ѿ�ɾ����\n");
				}
			}
		}
		if (option == 2) {
			int num;
			C_Node *p;
			C_Node *q;
			p = C_phead->next;
			printf("\t\t׼��ɾ���Ŀγ̺ţ�");
			scanf("%d", &num);
			if (p->data.cno == num) {
				printf("\t\t�γ̺ţ�%d\n \t\t�γ�����%s\n \t\tѧ�֣�%.1f\n ", p->data.cno, p->data.cname, p->data.credit);
				C_phead->next = p->next;
				free(p);
				printf("\t\t�ÿγ��Ѿ�ɾ��\n");
			} else {
				while (p->next != NULL && p->next->data.cno != num)
					p = p->next;
				if (p->next == NULL)
					printf("\t\tû�иÿγ�\n");
				else {
					q = p->next;
					printf("\t\t�γ̺ţ�%d\n \t\t�γ�����%s\n \t\tѧ�֣�%.1f\n ", p->data.cno, p->data.cname, p->data.credit);
					p->next = q->next;
					free(q);
					printf("\t\t�ÿγ���Ϣ�Ѿ�ɾ��\n");
				}
			}
		}
		if (option == 3) {
			int n, m;
			SC_Node *p;
			SC_Node *q;
			p = SC_phead->next;
			printf("\t\t׼��ɾ����ѧ�ţ�");
			scanf("%d", &n);
			printf("\t\t׼��ɾ���Ŀγ̺ţ�");
			scanf("%d", &m);
			if (p->data.sno == n && p->data.cno == m) {
				printf("\t\tѧ�ţ�%d\n\t\t�γ̺ţ�%d\n\t\t�ɼ���%d\n", p->data.sno, p->data.cno, p->data.grade);
				SC_phead->next = p->next;
				free(p);
				printf("\t\t��ͬѧ��Ϣ�Ѿ�ɾ��\n");
			} else {
				while (p->next != NULL && (p->next->data.sno != n || p->next->data.cno != m) )
					p = p->next;
				if (p->next == NULL)
					printf("\t\t���޴���\n");
				else {
					q = p->next;
					printf("\t\tѧ�ţ�%d\n\t\t�γ̺ţ�%d\n\t\t�ɼ���%d\n", p->data.sno, p->data.cno, p->data.grade);
					p->next = q->next;
					free(q);
					printf("\t\t��ͬѧ��Ϣ�Ѿ�ɾ��\n");
				}
			}
		}
	}
}

int checkCno(C_Node *C_phead, int varCno) {
	C_Node *p = C_phead;
	int flag;
	while (p != NULL) {
		if (p->data.cno == varCno) {
			flag = 1;
			break;
		} else {
			p = p->next;
			flag = 0;
		}
	}
	return flag;
}

int checkSno(S_Node *S_phead, int varSno) {
	S_Node *p = S_phead;
	int flag;
	while (p != NULL) {
		if (p->data.sno == varSno) {
			flag = 1;
			break;
		} else {
			p = p->next;
			flag = 0;
		}
	}
	return flag;
}

int countstu(S_Node *S_phead) {
	S_Node *p = S_phead;
	int num = 0;

	while (p != NULL) {
		num++;
		p = p->next;
	}
	return num;
}

void writeFileS(FILE *fp, S_Node *S_phead) {
	int i = 0;
	S_Node *p = S_phead;
	while (p != NULL) {
		fwrite(p + i, sizeof(S_Node), 1, fp);
		p = p->next;
	}
	return;
}

S_Node *readFileS(FILE *fp) {
	S_Node *phead = NULL, *pnew = NULL, *ptail = NULL;
	S_Node data;
	int i = 0;
	while (1) {
		fread(&data, sizeof(S_Node), 1, fp);
		if (feof(fp) != NULL)
			break;
		pnew = (S_Node *)malloc(sizeof(S_Node));
		*pnew = data;
		pnew->next = NULL;
		if (i == 0) {
			phead = pnew;
			ptail = pnew;
			i++;
		} else {
			ptail->next = pnew;
			ptail = ptail->next;
		}
	}
	return phead;
}

void writeFileC(FILE *fp, C_Node *C_phead) {
	int i = 0;
	C_Node *p = C_phead;
	while (p != NULL) {
		fwrite(p + i, sizeof(C_Node), 1, fp);
		p = p->next;
	}
	return;
}

C_Node *readFileC(FILE *fp) {
	C_Node *phead = NULL, *pnew = NULL, *ptail = NULL;
	C_Node data;
	int i = 0;
	while (1) {
		fread(&data, sizeof(C_Node), 1, fp);
		if (feof(fp) != NULL)
			break;
		pnew = (C_Node *)malloc(sizeof(C_Node));
		*pnew = data;
		pnew->next = NULL;
		if (i == 0) {
			phead = pnew;
			ptail = pnew;
			i++;
		} else {
			ptail->next = pnew;
			ptail = ptail->next;
		}
	}
	return phead;
}

void writeFileSC(FILE *fp, SC_Node *SC_phead) {
	int i = 0;
	SC_Node *p = SC_phead;
	while (p != NULL) {
		fwrite(p + i, sizeof(SC_Node), 1, fp);
		p = p->next;
	}
	return;
}

SC_Node *readFileSC(FILE *fp) {
	SC_Node *phead = NULL, *pnew = NULL, *ptail = NULL;
	SC_Node data;
	int i = 0;
	while (1) {
		fread(&data, sizeof(SC_Node), 1, fp);
		if (feof(fp) != NULL)
			break;
		pnew = (SC_Node *)malloc(sizeof(SC_Node));
		*pnew = data;
		pnew->next = NULL;
		if (i == 0) {
			phead = pnew;
			ptail = pnew;
			i++;
		} else {
			ptail->next = pnew;
			ptail = ptail->next;
		}
	}
	return phead;
}