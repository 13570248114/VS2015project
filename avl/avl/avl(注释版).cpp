#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);
#include<cmath>
#include<stack>

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;
	int child; //0: this node is a left child of its parent; 1: right child; -1 this node is the tree root
	node * parent;
	node * l_child;
	node * r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node * root;
	avl_tree() {
		root = nullptr;
	}
	void add_node(int i);//You need to implement this.
	void in_order_traversal(node *p);  //provided.
	node * height_adjustment(node *p, int &pattern); //You need to implement this
													 /*
													 This function is invoked by add_node and remove_node.
													 p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
													 All nodes whose heights need to be updated will be performed in this function.
													 If no imbalance is detected, the function returns nullptr.
													 If an imbalance is detected, the funciton returns the address of Action Node.
													 In addition, value of pattern will be set to 1, 2, 3, 4 for LL, LR, RL, RR pattern, respectively.
													 */




	void L_Rotate(node *p); //You need to implement this.
							//p points to the node around which the rotation will be performed.

	void R_Rotate(node *p); //You need to implement this.
							//p points to the node around which the rotation will be performed.

	void remove_node(int i);// You need to implement this.
							//Remove the node with value i.  Assume that all node values are distinct.


	node * replace(node * p1);
	/*
	This funciton is invoked by the remove_node.
	p1 points to the node to be removed.  The function returns the first node we need to check for possible height update after a node replcement.

	*/
	int height(node *p);
};

//�߶�
int avl_tree::height(node *p)
{
	if (p == nullptr)
		return 0;
	else
	{
		return p->height;
	}
}

//����
void avl_tree::L_Rotate(node *p)
{
	//����p�ڵ�ĸ��ڵ���Ϣ
	node * p1 = p->l_child;
	node *parent = p->parent;
	int child = p->child;

	//��p�ڵ�����ӵ��Һ�����Ϊp�ڵ�����ӣ��������丸�ڵ���Ϣ
	p->l_child = p1->r_child;
	if (p1->r_child != nullptr)
	{
		p1->r_child->parent = p;
		p1->r_child->child = 0;
	}

	//��p��Ϊp�����ӵ��Һ��ӣ��������丸�ڵ���Ϣ
	p1->r_child = p;
	p->parent = p1;
	p->child = 1;
	p1->parent = parent;
	p1->child = child;

	//���¸߶�
	p->height = max(height(p->l_child), height(p->r_child)) + 1;
	p1->height = max(height(p1->l_child), height(p1->r_child)) + 1;
	
}

void avl_tree::R_Rotate(node *p)  //�������������������Գ�
{
	node *p1 = p->r_child;
	node *parent = p->parent;
	int child = p->child;

	p->r_child = p1->l_child;
	if (p1->l_child != nullptr)
	{
		p1->l_child->parent = p;
		p1->l_child->child = 1;
	}

	p1->l_child = p;
	p->parent = p1;
	p->child = 0;
	p1->parent = parent;
	p1->child = child;

	p->height = max(height(p->l_child), height(p->r_child)) + 1;
	p1->height = max(height(p1->l_child), height(p1->r_child)) + 1;
}

node * avl_tree::height_adjustment(node *p, int &pattern)
{
	int l_cheight = p->l_child != nullptr? p->l_child->height : 0;   //���ӵĸ߶�
	int r_cheight = p->r_child != nullptr ? p->r_child->height : 0;  //�Һ��ӵĸ߶�
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

			L_Rotate(p);                       //��pΪ��������������
			return p->parent;
			break;
		case 3:                                  //RL������������LR�Գ�
			p1 = p->r_child;
			L_Rotate(p1);
			p->r_child = p1->parent;

			R_Rotate(p);
			return p->parent;
			break;
		case 4:                                    //RR,��LL�Գ�
			R_Rotate(p);
			return p->parent;
			break;
		default:
			return nullptr;
		}
	}
	else
		return nullptr;
}

void avl_tree::add_node(int i)
{
	stack<node*> route;         //���ڴ�Ų��Ҳ����Ĺ������������ڵ��ջ
	//�Ȳ��Ҳ����
	node *p = root;
	while (1)
	{
	    if (p == nullptr)
		{
			p=new node(i);
			route.push(p);
			break;
		}
		else if (i < p->value)
		{
			route.push(p);
			p = p->l_child;
			continue;
		}
		else if (i > p->value)
		{
			route.push(p);
			p = p->r_child;
			continue;
		}
	}
	//�Բ���㿪ʼ���������ƽ�Ⲣ����
	node *son, *parent;
	int pattern;
	while (1)                   //ѭ��ֱ����Ų����Ĺ������������ڵ��ջΪ��Ϊֹ
	{
		son = route.top();
		route.pop();
		if (route.empty())        //ջ������ջ��һ���Ǹ����
		{
			root = son;
			root->child = -1;
			break;
		}

		parent = route.top();
		route.pop();
		if (son->value < parent->value)              //�½ڵ������parent����������
		{
			parent->l_child = son;
			son->parent = parent;
			son->child = 0;
			int r_cheight = parent->r_child != nullptr ? parent->r_child->height : 0;
			
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
			son->child = 1;
			int l_cheight = parent->l_child != nullptr ? parent->l_child->height : 0;

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
		int l_cheight = parent->l_child != nullptr ? parent->l_child->height : 0;
		int r_cheight = parent->r_child != nullptr ? parent->r_child->height : 0;
		parent->height = max(l_cheight, r_cheight) + 1;
		route.push(parent);
	}
}

node * avl_tree::replace(node * p1)   //�����滻��
{
	node* rep = p1->l_child;              
	if (rep != nullptr)                          //���p1�ڵ����������Ϊ��
	{
		if (rep->r_child != nullptr)          //���p1�ڵ������������������Ϊ�գ����������������ĵ����滻p1��value��ֵ
		{
			while (rep->r_child != nullptr)
				rep = rep->r_child;
			p1->value = rep->value;
			node *parent = rep->parent;
			parent->r_child = rep->l_child;
			if (rep->l_child != nullptr)
			{
				rep->l_child->parent = p1;
				rep->l_child->child = 1;
			}
			delete rep;
			parent->height= max(height(parent->l_child), height(parent->r_child)) + 1;
			return parent;
		}
		else                                      //������p1�ڵ����������������Ϊ�գ���ֱ��ȡp1�ڵ�����ӵ�ֵ���滻����ɾ��p1�ڵ������
		{
			p1->value = rep->value;
			p1->l_child = rep->l_child;
			if (rep->l_child != nullptr)
			{
				rep->l_child->parent = p1;
				rep->l_child->child = 0;
			}
			delete rep;
			p1->height = max(height(p1->l_child), height(p1->r_child)) + 1;
			return p1;
		}
	}
	else                                          //���p1�ڵ��������Ϊ�գ���ֱ��ɾ��p1�ڵ㣬����������
	{
		node *parent = p1->parent;
		if (p1->child == 0)                  //���p1�ڵ����丸�ڵ�����ӣ���p1�ڵ���Һ�����Ϊp1�ڵ㸸�ڵ������
		{
			p1->parent->l_child = p1->r_child;
			if (p1->r_child != nullptr)
			{
				p1->r_child->parent = p1->parent;
				p1->parent->child = 0;
			}
			parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;
		}
		else if (p1->child == 1)          //���p1�ڵ����丸�ڵ���Һ��ӣ���p1�ڵ���Һ�����Ϊp1�ڵ㸸�ڵ���Һ���
		{
			p1->parent->r_child = p1->r_child;
			if (p1->r_child != nullptr)
			{
				p1->r_child->parent = p1->parent;
				p1->parent->child = 1;
			}
			parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;
		}
		else if (p1->child == -1)       //���p1�ڵ��Ǹ������ø��¸��ڵ���Ϣ��ֱ��ɾ��
		{
			root = p1->r_child;
			if (root != nullptr)
			{
				root->child = -1;
				root->parent = nullptr;
			}
		}

		delete p1;
		return parent;
	}
	
}

void avl_tree::remove_node(int i)
{
	if (root == nullptr)
		cout << "empty!" << endl;
	//�Ȳ�����Ҫɾ���Ľڵ��λ��
	node *p = root;
	while (1)
	{
		if (p == nullptr)
		{
			cout << i <<" not in avl tree" << endl;
			return;
		}
		if (p->value == i)
		{
			break;
		}
		else if (i < p->value)
		{
			p = p->l_child;
			continue;
		}
		else if (i > p->value)
		{
			p = p->r_child;
			continue;
		}
	}
	//�ҵ�֮����������һ��ֵ���
	node* parent = replace(p);
	//���¸߶���Ϣ������ƽ��
	if (parent != nullptr)
	{
		int pattern;
		while (parent)
		{
			if (height(parent->r_child) - height(parent->l_child) == 2)         //��Ϊ�滻�Ĺ����п��Ա�֤���������������ߣ�����ֻ�������������������2�����
			{
				int rl_ch = height(parent->r_child->l_child);
				int rr_ch = height(parent->r_child->r_child);
				if (rr_ch >= rl_ch)                     //���parent�����������������ĸ߶ȴ��ڵ���parent�����������������ĸ߶ȣ���RR
					pattern = 4;
				else if (rr_ch < rl_ch)                //����RL
					pattern = 3;

				parent = height_adjustment(parent, pattern);            //����ƽ��
				parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;       //���¸߶�
			}
			parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;
			if (parent->parent == nullptr)                               //�������ĸ��ڵ�
				root = parent;
			parent = parent->parent;
		}
	}
	else
		root = nullptr;
}


void avl_tree::in_order_traversal(node * p) {
	if (p == nullptr)  return;
	in_order_traversal(p->l_child);
	cout << "value = " << p->value << " " << "height = " << p->height << "   ";
	in_order_traversal(p->r_child);
}




int main() {
	avl_tree t1;
	t1.add_node(45);
	//t1.in_order_traversal(t1.root);
	t1.remove_node(45);
	//t1.in_order_traversal(t1.root);
	t1.add_node(50);
	t1.add_node(47);
	t1.add_node(30);
	t1.add_node(35);

	
	t1.add_node(46);
	t1.add_node(78);
	t1.add_node(23);
	t1.add_node(66);
	t1.add_node(90);
	t1.add_node(2);
	t1.add_node(6);
	
	//t1.in_order_traversal(t1.root);
	//cout << "\n\n" << endl;
	t1.remove_node(47);
	//t1.remove_node(45);
	//t1.in_order_traversal(t1.root);
	
	
	t1.remove_node(30);
	t1.remove_node(23);
	t1.add_node(100);
	t1.add_node(98);
	t1.add_node(150);
	t1.add_node(160);
	t1.add_node(128);
	t1.add_node(130);
	t1.remove_node(35);
	t1.remove_node(150);
	t1.in_order_traversal(t1.root);
	getchar();
	getchar();

	return 0;
}