#include<stdio.h>
#include <stdlib.h>

typedef struct node {                //���ڵ�Ľṹ
	int value;                            //keyֵ
	int height;                          //�߶�
	struct node * parent;          //ָ�򸸽ڵ��ָ��
	struct node * l_child;          //ָ�����ӵ�ָ��
	struct node * r_child;          //ָ���Һ��ӵ�ָ��
}node;

node* createNode(int value, node* parent)       //����һ���ڵ�
{
	node* n = (node*)malloc(sizeof(node));      
	n->value = value;
	n->height = 1;                                          //��ʼ�߶�Ϊ1
	n->l_child = n->r_child =NULL;
	n->parent = parent;
	return n;
}

int height(node* n)                                       //����ĳ����ĸ߶�
{
	if (n == NULL)                                          //�սڵ�ĸ߶�Ϊ0
		return 0;
	else
	{
		return n->height;
	}
}

int maxHeight(int a, int b)
{
	return a > b ? a : b;
}

void L_Rotate(node *p)
{
	//����p�ڵ�ĸ��ڵ���Ϣ
	node * p1 = p->l_child;
	node *parent = p->parent;

	//��p�ڵ�����ӵ��Һ�����Ϊp�ڵ�����ӣ��������丸�ڵ���Ϣ
	p->l_child = p1->r_child;
	if (p1->r_child != NULL)
	{
		p1->r_child->parent = p;
	}

	//��p��Ϊp�����ӵ��Һ��ӣ��������丸�ڵ���Ϣ
	p1->r_child = p;
	p->parent = p1;
	p1->parent = parent;

	//���¸߶�
	p->height = maxHeight(height(p->l_child), height(p->r_child)) + 1;
	p1->height = maxHeight(height(p1->l_child), height(p1->r_child)) + 1;
}

void R_Rotate(node *p)  //�������������������Գ�
{
	node *p1 = p->r_child;
	node *parent = p->parent;

	p->r_child = p1->l_child;
	if (p1->l_child != NULL)
	{
		p1->l_child->parent = p;
	}

	p1->l_child = p;
	p->parent = p1;
	p1->parent = parent;

	p->height = maxHeight(height(p->l_child), height(p->r_child)) + 1;
	p1->height = maxHeight(height(p1->l_child), height(p1->r_child)) + 1;
}

node * height_adjustment(node *p, int pattern)             //����pattern��ֵѡ�����ƽ��Ĳ�����1��LL��2��LR, 3��RL ,4:RR
{
	int l_cheight = height(p->l_child);   //���ӵĸ߶�
	int r_cheight = height(p->r_child);  //�Һ��ӵĸ߶�
	if (abs(l_cheight - r_cheight) >= 2)
	{
		node* p1;
		switch (pattern)
		{
		case 1:                                  //LL
			L_Rotate(p);
			return p->parent;                 //������������ͷ���
			break;
		case 2:                                  //LR
			p1 = p->l_child;
			R_Rotate(p1);
			p->l_child = p1->parent;       //�Ȱ���p�ڵ������Ϊ������������
			p1->parent->parent = p;

			L_Rotate(p);                       //��pΪ��������������
			return p->parent;
			break;
		case 3:                                  //RL������������LR�Գ�
			p1 = p->r_child;
			L_Rotate(p1);
			p->r_child = p1->parent;
			p1->parent->parent = p;

			R_Rotate(p);
			return p->parent;
			break;
		case 4:                                    //RR,��LL�Գ�
			R_Rotate(p);
			return p->parent;
			break;
		default:
			return NULL;
		}
	}
	else
		return NULL;
}

//˼���ǣ���һ��ѭ�����Ҳ�����λ�ã��²���ĵ㶼֪�������Լ��ĸ��ڵ���˭��
//            �ڶ���ѭ���������²����ĸ��ڵ����ϼ������ƽ�Ⲣ������ֱ����鵽���ڵ�

node* inv_node(node* root, int i)                              //����ڵ�
{		
	node *p = root;
	node* parent = NULL;
	//�Ȳ��Ҳ����
	while (1)             
	{
		if (p == NULL)                //�ҵ�����㣬�����½ڵ�
		{
			p = createNode(i,parent);
			break;
		}
		else if (i < p->value)
		{
			parent = p;
			p = p->l_child;
			continue;
		}
		else if (i > p->value)
		{
			parent = p;
			p = p->r_child;
			continue;
		}
	}
	//�Բ���㿪ʼ�������ϼ������ƽ�Ⲣ����
	node *son;
	int pattern;
	parent = p->parent;
	son = p;
	while (parent != NULL)                   //ѭ��ֱ������Ϊֹ
	{
		if (son->value < parent->value)              //�½ڵ������parent����������
		{
			parent->l_child = son;
			son->parent = parent;
			int r_cheight = height(parent->r_child);

			if (son->height - r_cheight == 2)          //����������ĸ߶����޴���2
			{
				if (i < son->value)                          //�������parent����������������
					pattern = 1;
				else                                             //�������parent����������������
					pattern = 2;
				parent = height_adjustment(parent, pattern);
			}
		}
		else if (son->value > parent->value)          //�������parent������������������뵽�������Գ�
		{
			parent->r_child = son;
			son->parent = parent;

			int l_cheight = height(parent->l_child);

			if (son->height - l_cheight == 2)
			{
				if (i < son->value)
					pattern = 3;
				else
					pattern = 4;
				parent = height_adjustment(parent, pattern);
			}
		}
		//���¸߶ȣ������µ������ĸ��ڵ���ջ
		parent->height = maxHeight(height(parent->l_child), height(parent->r_child)) + 1;

		//����son��parent�Ա��´�ѭ��
		son = parent;
		parent = parent->parent;
	}
}

//���������������
void in_order_traversal(node * p)
{
	if (p == NULL)  return;
	in_order_traversal(p->l_child);
	printf("value = %d , height = %d\n", p->value, p->height);
	in_order_traversal(p->r_child);
}

//����p�ڵ�Ϊ�������������ڵ�
node* tree_matmun(node * p)
{
	node* temp = p;
	while (temp->r_child != NULL)
		temp = temp->r_child;
	return temp;
}

//��ǰ���ڵ�
//˼���ǣ�����Ҫ��i��ǰ���������ҳ���Ҫ����iʱ��i���ڵ�λ��,
//            ���i�Ѿ������ϣ�������ǰ���ڵ������������1.i����������Ϊ�գ���i��ǰ���ڵ��������������ڵ㡣
//                                                                         2.i��������Ϊ�գ���i��ǰ���ڵ���i��ĳ�����Ƚڵ�ĸ��ڵ㣬�Ҹ����Ƚڵ����丸�ڵ���Һ��ӡ�
//           ���i�������ϣ�parent��¼�˲���i�Ĺ����У�
//           i��ǰһ���ڵ�, ������ǰ���ڵ�Ҳ�����������1.���i��parent->value����i��ǰ���ڵ����parent->value
//                                                                       2.���i��parent->valueС����i��ǰ���ڵ���parent��ĳ�����Ƚڵ�ĸ��ڵ㣬�Ҹ����Ƚڵ����丸�ڵ���Һ��ӡ�
void predecessor(node* root, int i, FILE* output) 
{
	node *p = root;
	node* parent = NULL;
	node* result = NULL;

	while (1)
	{
		if (p == NULL|| i == p->value)            //����Ѿ��ҵ��ʵ���λ��
		{
			if (p != NULL&&p->l_child != NULL)        //i�Ѿ������ϵ����1
			{
				result = tree_matmun(p->l_child);
				break;
			}
			else if(p != NULL)                                 //i�Ѿ������ϵ����2
			{
				parent = p->parent;
				while (parent != NULL&&p == parent->l_child)
				{
					p = parent;
					parent = parent->parent;
				}
				result = parent;
				break;
			}
			else if (p == NULL)
			{
				if (i > parent->value)            // i�������ϵ����1
				{
					result = parent;
					break;
				}
				else                                       // i�������ϵ����2
				{
					node *pparent = parent->parent;
					while (pparent != NULL&& parent == pparent->l_child)
					{
						parent = pparent;
						pparent = pparent->parent;
					}
					result = pparent;
					break;
				}
				
			}
		}
		//������������Ϊ���ҵ�p��λ�ã�������Ĺ������Ҳ�����˼������
		else if (i < p->value)
		{
			parent = p;
			p = p->l_child;
			continue;
		}
		else if (i > p->value)
		{
			parent = p;
			p = p->r_child;
			continue;
		}
	}

	//��ӡ���
	if (result == NULL)
	{
		printf("%d have no predecessor ! \n", i);
		fprintf(output, "%d have no predecessor ! \n", i);
	}
	else
	{
		//printf("%d\n", result->value);
		//printf("The predecessor of %d is %d \n", i, result->value);
		fprintf(output, "%d\n", result->value);
	}
}


int main()
{
	node* root = NULL;            //����
	//���ļ�
	FILE *fp, *output;
	if ((fp = fopen("ops-half.txt","r")) == NULL)
	{
		printf("ops-half.txt can not be opened.\n");
		exit(1);
	}
	if ((output = fopen("output.txt", "w")) == NULL)
	{
		printf("output.txt can not be opened.\n");
		exit(1);
	}
	//���ļ���һ�У�������
	char line[80];
	char result[80];
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		char* num = line + 4;            //numָ�����ֵĵ�ַ
		switch (line[0])                      //���line[0]=='i'������б���inv number��qҲͬ��
		{
		case 'i':
			root = inv_node(root, atoi(num));
			break;
		case 'q':
			predecessor(root, atoi(num), output);
			break;
		}
	}
	printf("done!\n");                    //��ɺ��ӡdone!
}