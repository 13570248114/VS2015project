#include<stdio.h>
#include <stdlib.h>

typedef struct node {                //树节点的结构
	int value;                            //key值
	int height;                          //高度
	struct node * parent;          //指向父节点的指针
	struct node * l_child;          //指向左孩子的指针
	struct node * r_child;          //指向右孩子的指针
}node;

node* createNode(int value, node* parent)       //创建一个节点
{
	node* n = (node*)malloc(sizeof(node));      
	n->value = value;
	n->height = 1;                                          //初始高度为1
	n->l_child = n->r_child =NULL;
	n->parent = parent;
	return n;
}

int height(node* n)                                       //返回某个点的高度
{
	if (n == NULL)                                          //空节点的高度为0
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
	//保存p节点的父节点信息
	node * p1 = p->l_child;
	node *parent = p->parent;

	//将p节点的左孩子的右孩子作为p节点的左孩子，并更新其父节点信息
	p->l_child = p1->r_child;
	if (p1->r_child != NULL)
	{
		p1->r_child->parent = p;
	}

	//将p作为p的左孩子的右孩子，并更新其父节点信息
	p1->r_child = p;
	p->parent = p1;
	p1->parent = parent;

	//更新高度
	p->height = maxHeight(height(p->l_child), height(p->r_child)) + 1;
	p1->height = maxHeight(height(p1->l_child), height(p1->r_child)) + 1;
}

void R_Rotate(node *p)  //右旋与左旋操作基本对称
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

node * height_adjustment(node *p, int pattern)             //根据pattern的值选择调整平衡的操作，1：LL，2：LR, 3：RL ,4:RR
{
	int l_cheight = height(p->l_child);   //左孩子的高度
	int r_cheight = height(p->r_child);  //右孩子的高度
	if (abs(l_cheight - r_cheight) >= 2)
	{
		node* p1;
		switch (pattern)
		{
		case 1:                                  //LL
			L_Rotate(p);
			return p->parent;                 //返回新子树的头结点
			break;
		case 2:                                  //LR
			p1 = p->l_child;
			R_Rotate(p1);
			p->l_child = p1->parent;       //先把以p节点的左孩子为根的子树右旋
			p1->parent->parent = p;

			L_Rotate(p);                       //以p为根的子树再左旋
			return p->parent;
			break;
		case 3:                                  //RL，操作基本与LR对称
			p1 = p->r_child;
			L_Rotate(p1);
			p->r_child = p1->parent;
			p1->parent->parent = p;

			R_Rotate(p);
			return p->parent;
			break;
		case 4:                                    //RR,与LL对称
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

//思想是：第一个循环查找插入点的位置，新插入的点都知道他们自己的父节点是谁。
//            第二个循环则沿着新插入点的父节点向上检查树的平衡并调整，直到检查到根节点

node* inv_node(node* root, int i)                              //插入节点
{		
	node *p = root;
	node* parent = NULL;
	//先查找插入点
	while (1)             
	{
		if (p == NULL)                //找到插入点，创建新节点
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
	//自插入点开始，逐渐向上检查树的平衡并调整
	node *son;
	int pattern;
	parent = p->parent;
	son = p;
	while (parent != NULL)                   //循环直到树根为止
	{
		if (son->value < parent->value)              //新节点插在了parent的左子树上
		{
			parent->l_child = son;
			son->parent = parent;
			int r_cheight = height(parent->r_child);

			if (son->height - r_cheight == 2)          //检查左子树的高度有无大于2
			{
				if (i < son->value)                          //插入点在parent的左子树的左子树
					pattern = 1;
				else                                             //插入点在parent的坐子树的右子树
					pattern = 2;
				parent = height_adjustment(parent, pattern);
			}
		}
		else if (son->value > parent->value)          //插入点在parent的右子树，操作与插入到左子树对称
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
		//更新高度，并把新的子树的根节点入栈
		parent->height = maxHeight(height(parent->l_child), height(parent->r_child)) + 1;

		//更新son和parent以便下次循环
		son = parent;
		parent = parent->parent;
	}
}

//中序遍历，调试用
void in_order_traversal(node * p)
{
	if (p == NULL)  return;
	in_order_traversal(p->l_child);
	printf("value = %d , height = %d\n", p->value, p->height);
	in_order_traversal(p->r_child);
}

//求以p节点为树根的树的最大节点
node* tree_matmun(node * p)
{
	node* temp = p;
	while (temp->r_child != NULL)
		temp = temp->r_child;
	return temp;
}

//求前驱节点
//思想是：假设要求i的前驱，则先找出若要插入i时，i所在的位置,
//            如果i已经在树上，则他的前驱节点有两种情况：1.i的左子树不为空，则i的前驱节点是左子树的最大节点。
//                                                                         2.i的左子树为空，则i的前驱节点是i的某个祖先节点的父节点，且该祖先节点是其父节点的右孩子。
//           如果i不在树上，parent记录了查找i的过程中，
//           i的前一个节点, 则他的前驱节点也有两种情况：1.如果i比parent->value大，则i的前驱节点就是parent->value
//                                                                       2.如果i比parent->value小，则i的前驱节点是parent的某个祖先节点的父节点，且该祖先节点是其父节点的右孩子。
void predecessor(node* root, int i, FILE* output) 
{
	node *p = root;
	node* parent = NULL;
	node* result = NULL;

	while (1)
	{
		if (p == NULL|| i == p->value)            //如果已经找到适当的位置
		{
			if (p != NULL&&p->l_child != NULL)        //i已经在树上的情况1
			{
				result = tree_matmun(p->l_child);
				break;
			}
			else if(p != NULL)                                 //i已经在树上的情况2
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
				if (i > parent->value)            // i不在树上的情况1
				{
					result = parent;
					break;
				}
				else                                       // i不在树上的情况2
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
		//下面这两个是为了找到p的位置，跟插入的过程中找插入点的思想类似
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

	//打印结果
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
	node* root = NULL;            //树根
	//打开文件
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
	//从文件读一行，并处理
	char line[80];
	char result[80];
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		char* num = line + 4;            //num指向数字的地址
		switch (line[0])                      //如果line[0]=='i'，则该行必是inv number，q也同理
		{
		case 'i':
			root = inv_node(root, atoi(num));
			break;
		case 'q':
			predecessor(root, atoi(num), output);
			break;
		}
	}
	printf("done!\n");                    //完成后打印done!
}