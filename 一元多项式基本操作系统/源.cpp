#include"stdio.h"
#include"stdlib.h" 
#include"math.h" 

#define   TRUE	          1
#define   FALSE            0
#define   OK	              1
#define   ERROR		      0
#define   INFEASIBLE	     -1

typedef int status;
typedef int ElemType;

typedef struct node
{
	int exp; //������ 
	float coef; //������ 
	struct node* next; //ָ���� 
}Lnode, * LinkList;

//��������
int menu();
status Create_L(LinkList& L);
void Printf_L(LinkList L);
status Sort_L(LinkList& L);
void Evaluation_x(LinkList L);
void Addpoly(LinkList ha, LinkList hb);

//���������� 
status Create_L(LinkList& L)
{
	LinkList p, s, q, pre;
	int i, n, flag; //����nΪһԪ����ʽ������
	L = (LinkList)malloc(sizeof(Lnode)); //����ͷ���
	L->coef = 0;
	L->exp = 0;
	L->next = NULL;
	s = L;
	printf("������һԪ����ʽ������:");
	scanf("%d", &n);
	if (n == 0)
		return(OK);
	p = (LinkList)malloc(sizeof(Lnode)); //�Ƚ�����һ��Ԫ�ؽ��
	p->next = NULL;
	printf("�������1��ϵ��:");
	scanf("%f", &p->coef);
	while (p->coef == 0) //���������ϵ���Ƿ�Ϊ0
	{
		printf("����Ϊ0!����������!\n");
		printf("�������1��ϵ��:");
		scanf("%f", &p->coef);
	}
	printf("�������1��ָ��:");
	scanf("%d", &p->exp);
	s->next = p;
	s = p;
	for (i = 1;i < n;i++)
	{
		p = (LinkList)malloc(sizeof(Lnode));
		p->next = NULL;
		printf("�������%d��ϵ��:", i + 1);
		scanf("%f", &p->coef);
		while (p->coef == 0) //���������ϵ���Ƿ�Ϊ0
		{
			printf("����Ϊ0!����������!\n");
			printf("�������%d��ϵ��:", i + 1);
			scanf("%f", &p->coef);
		}
		printf("�������%d��ָ��:", i + 1);
		scanf("%d", &p->exp);
		q = L->next;
		pre = L;
		while (q)
		{
			if (p->exp == q->exp) //���ҵ�������ָͬ����ʱ���ϲ�
			{
				q->coef = q->coef + p->coef;
				flag = 1; //��ִ�н�p��������Ĳ���
				break;
			}
			else if (p->exp > q->exp)
			{
				pre = q; //��preָ���Ƶ�Ҫ����λ��֮ǰ
				q = q->next; //��qָ���Ƶ�Ҫ����λ��֮��
				flag = 0;
			}
			else if (p->exp < q->exp)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0) //ִ�н�p��������Ĳ���
		{
			p->next = q;
			pre->next = p;
		}
	}
	return(OK);
}


//���һԪ����ʽ����������Ԫ��
void Printf_L(LinkList L)
{
	LinkList p;
	p = L->next;
	if (p)
	{
		if (p->coef == 0 && p->next == NULL)
		{
			p = p->next;
			printf("0+");
		}
		while (p)
		{
			if (p->coef == 0)
			{
				p = p->next;
			}
			else
			{
				printf("%.2fx^%d+", p->coef, p->exp);
				p = p->next;
			}
		}
	}
	else
		printf("0");
	printf("\n");
}

//�����Ա�����ֵ������һԪ����ʽ��ֵ
void Evaluation_x(LinkList L)
{
	LinkList p;
	float x;
	float sum = 0;
	p = L->next;
	printf("�������Ա���x��ֵ:");
	scanf("%f", &x);
	while (p)
	{
		sum += (p->coef) * pow(x, p->exp); //���� 
		p = p->next; //pָ����һ����� 
	}
	printf("һԪ����ʽ��ֵΪ%.2f\n", sum);
	system("pause");
	system("cls");
}

//��������һԪ����ʽ����һԪ����ʽ�ĺͶ���ʽ
void Addpoly(LinkList ha, LinkList hb)
{
	LinkList qa, qb, u, pre, p;
	float x;
	qa = ha->next;
	qb = hb->next;
	pre = ha;
	while ((qa != NULL) && (qb != NULL))
	{
		if (qa->exp < qb->exp) //����һ������ʽָ��С�ڵڶ�������ʽָ��ʱ�����Ƶ�һ������ʽָ��
		{
			pre = qa; //qa����ǺͶ���ʽ�е�һ��
			qa = qa->next; //qa����, qb����
		}
		else if (qa->exp == qb->exp)
		{
			x = qa->coef + qb->coef;
			if (x != 0) //�������ϵ��Ϊ0
			{
				qa->coef = x; //�޸�qaϵ����,					
				pre = qa;
			}
			else
			{
				pre->next = qa->next;
				free(qa); //��A����ɾȥqa,					
			}
			qa = pre->next;
			u = qb;
			qb = qb->next; //qa, qb����
			free(u); //�ͷ�qb
		}
		else //qa->exp>qb->exp
		{
			u = qb->next; //qb����ǺͶ���ʽ�е�һ��
			qb->next = qa;
			pre->next = qb; //��qb����qa֮ǰ,qb����,qa����
			pre = qb;
			qb = u;
		}
	}
	if (qa == NULL) // ��qb==NULL����������qa==NULL����B��ʣ�ಿ������A��
		pre->next = qb;
	free(hb);
	printf("�Ͷ���ʽΪ:");
	p = ha->next;
	if (p == NULL)
		printf("0");
	if (p != NULL)
	{
		while (p)
		{
			printf("%.2fx^%d+", p->coef, p->exp);
			p = p->next;
		}
	}
	printf("\n");
	system("pause");
	system("cls");
}

int main()
{
	LinkList H, H1, H2;
	int k;
	do {
		k = menu();
		switch (k)
		{
		case 0:
			break;
		case 1:
			Create_L(H);
			system("pause");
			system("cls");
			break;
		case 2:
			printf("���������һԪ����ʽΪ:\n");
			Printf_L(H);
			system("pause");
			system("cls");
			break;
		case 3:
			Evaluation_x(H);
			break;
		case 4:
			printf("������Ҫ��ӵĵ�1������ʽ:\n");
			Create_L(H1);
			printf("����ĵ�һ������ʽΪ:");
			Printf_L(H1);
			printf("������Ҫ��ӵĵ�2������ʽ:\n");
			Create_L(H2);
			printf("����ĵڶ�������ʽΪ:");
			Printf_L(H2);
			Addpoly(H1, H2);
			break;
		default:
			printf("����ѡ��\n");
			system("pause");
			system("cls");
		}
	} while (k);
	return 0;
}

//�ṩ�˵�
int menu()
{
	int n = 0;
	printf("                            һԪ����ʽ��������ϵͳ\n");
	printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��   [1]:��������ͷ���ĵ�������һԪ����ʽ������ָ���������У�                   ��\n");
	printf("��   [2]:���һԪ����ʽ����������Ԫ��(����ָ���������ÿһϵ����0���ϵ����ָ��)    ��\n");
	printf("��   [3]:�����Ա�����ֵ������һԪ����ʽ��ֵ                                         ��\n");
	printf("��   [4]:��������һԪ����ʽ����һԪ����ʽ�ĺͶ���ʽ                                 ��\n");
	printf("��   [0]:�˳�                                                                       ��\n");
	printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ��: ");
	scanf("%d", &n);
	return n;
}

