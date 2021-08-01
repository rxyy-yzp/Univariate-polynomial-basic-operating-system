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
	int exp; //数据域 
	float coef; //数据域 
	struct node* next; //指针域 
}Lnode, * LinkList;

//函数声明
int menu();
status Create_L(LinkList& L);
void Printf_L(LinkList L);
status Sort_L(LinkList& L);
void Evaluation_x(LinkList L);
void Addpoly(LinkList ha, LinkList hb);

//建立单链表 
status Create_L(LinkList& L)
{
	LinkList p, s, q, pre;
	int i, n, flag; //定义n为一元多项式的项数
	L = (LinkList)malloc(sizeof(Lnode)); //建立头结点
	L->coef = 0;
	L->exp = 0;
	L->next = NULL;
	s = L;
	printf("请输入一元多项式的项数:");
	scanf("%d", &n);
	if (n == 0)
		return(OK);
	p = (LinkList)malloc(sizeof(Lnode)); //先建立第一个元素结点
	p->next = NULL;
	printf("请输入第1项系数:");
	scanf("%f", &p->coef);
	while (p->coef == 0) //检查输入项系数是否为0
	{
		printf("该项为0!请重新输入!\n");
		printf("请输入第1项系数:");
		scanf("%f", &p->coef);
	}
	printf("请输入第1项指数:");
	scanf("%d", &p->exp);
	s->next = p;
	s = p;
	for (i = 1;i < n;i++)
	{
		p = (LinkList)malloc(sizeof(Lnode));
		p->next = NULL;
		printf("请输入第%d项系数:", i + 1);
		scanf("%f", &p->coef);
		while (p->coef == 0) //检查输入项系数是否为0
		{
			printf("该项为0!请重新输入!\n");
			printf("请输入第%d项系数:", i + 1);
			scanf("%f", &p->coef);
		}
		printf("请输入第%d项指数:", i + 1);
		scanf("%d", &p->exp);
		q = L->next;
		pre = L;
		while (q)
		{
			if (p->exp == q->exp) //当找到已有相同指数项时，合并
			{
				q->coef = q->coef + p->coef;
				flag = 1; //不执行将p插入链表的操作
				break;
			}
			else if (p->exp > q->exp)
			{
				pre = q; //将pre指针移到要插入位置之前
				q = q->next; //将q指针移到要插入位置之后
				flag = 0;
			}
			else if (p->exp < q->exp)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0) //执行将p插入链表的操作
		{
			p->next = q;
			pre->next = p;
		}
	}
	return(OK);
}


//输出一元多项式的所有数据元素
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

//输入自变量的值，计算一元多项式的值
void Evaluation_x(LinkList L)
{
	LinkList p;
	float x;
	float sum = 0;
	p = L->next;
	printf("请输入自变量x的值:");
	scanf("%f", &x);
	while (p)
	{
		sum += (p->coef) * pow(x, p->exp); //计算 
		p = p->next; //p指向下一个结点 
	}
	printf("一元多项式的值为%.2f\n", sum);
	system("pause");
	system("cls");
}

//输入两个一元多项式，求一元多项式的和多项式
void Addpoly(LinkList ha, LinkList hb)
{
	LinkList qa, qb, u, pre, p;
	float x;
	qa = ha->next;
	qb = hb->next;
	pre = ha;
	while ((qa != NULL) && (qb != NULL))
	{
		if (qa->exp < qb->exp) //当第一个多项式指数小于第二个多项式指数时，后移第一个多项式指针
		{
			pre = qa; //qa结点是和多项式中的一项
			qa = qa->next; //qa后移, qb不动
		}
		else if (qa->exp == qb->exp)
		{
			x = qa->coef + qb->coef;
			if (x != 0) //两项相加系数为0
			{
				qa->coef = x; //修改qa系数域,					
				pre = qa;
			}
			else
			{
				pre->next = qa->next;
				free(qa); //从A表中删去qa,					
			}
			qa = pre->next;
			u = qb;
			qb = qb->next; //qa, qb后移
			free(u); //释放qb
		}
		else //qa->exp>qb->exp
		{
			u = qb->next; //qb结点是和多项式中的一项
			qb->next = qa;
			pre->next = qb; //将qb插在qa之前,qb后移,qa不动
			pre = qb;
			qb = u;
		}
	}
	if (qa == NULL) // 若qb==NULL，结束，若qa==NULL，将B中剩余部分连到A上
		pre->next = qb;
	free(hb);
	printf("和多项式为:");
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
			printf("升序排序的一元多项式为:\n");
			Printf_L(H);
			system("pause");
			system("cls");
			break;
		case 3:
			Evaluation_x(H);
			break;
		case 4:
			printf("请输入要相加的第1个多项式:\n");
			Create_L(H1);
			printf("输入的第一个多项式为:");
			Printf_L(H1);
			printf("请输入要相加的第2个多项式:\n");
			Create_L(H2);
			printf("输入的第二个多项式为:");
			Printf_L(H2);
			Addpoly(H1, H2);
			break;
		default:
			printf("错误选择\n");
			system("pause");
			system("cls");
		}
	} while (k);
	return 0;
}

//提供菜单
int menu()
{
	int n = 0;
	printf("                            一元多项式基本操作系统\n");
	printf("┌──────────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│   [1]:建立带表头结点的单链表存放一元多项式（按照指数升序排列）                   │\n");
	printf("│   [2]:输出一元多项式的所有数据元素(按照指数升序输出每一系数非0项的系数和指数)    │\n");
	printf("│   [3]:输入自变量的值，计算一元多项式的值                                         │\n");
	printf("│   [4]:输入两个一元多项式，求一元多项式的和多项式                                 │\n");
	printf("│   [0]:退出                                                                       │\n");
	printf("└──────────────────────────────────────────────────────────────────────────────────┘\n");
	printf("请选择: ");
	scanf("%d", &n);
	return n;
}

