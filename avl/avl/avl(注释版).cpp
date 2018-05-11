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

//高度
int avl_tree::height(node *p)
{
	if (p == nullptr)
		return 0;
	else
	{
		return p->height;
	}
}

//左旋
void avl_tree::L_Rotate(node *p)
{
	//保存p节点的父节点信息
	node * p1 = p->l_child;
	node *parent = p->parent;
	int child = p->child;

	//将p节点的左孩子的右孩子作为p节点的左孩子，并更新其父节点信息
	p->l_child = p1->r_child;
	if (p1->r_child != nullptr)
	{
		p1->r_child->parent = p;
		p1->r_child->child = 0;
	}

	//将p作为p的左孩子的右孩子，并更新其父节点信息
	p1->r_child = p;
	p->parent = p1;
	p->child = 1;
	p1->parent = parent;
	p1->child = child;

	//更新高度
	p->height = max(height(p->l_child), height(p->r_child)) + 1;
	p1->height = max(height(p1->l_child), height(p1->r_child)) + 1;
	
}

void avl_tree::R_Rotate(node *p)  //右旋与左旋操作基本对称
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
	int l_cheight = p->l_child != nullptr? p->l_child->height : 0;   //左孩子的高度
	int r_cheight = p->r_child != nullptr ? p->r_child->height : 0;  //右孩子的高度
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

			L_Rotate(p);                       //以p为根的子树再左旋
			return p->parent;
			break;
		case 3:                                  //RL，操作基本与LR对称
			p1 = p->r_child;
			L_Rotate(p1);
			p->r_child = p1->parent;

			R_Rotate(p);
			return p->parent;
			break;
		case 4:                                    //RR,与LL对称
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
	stack<node*> route;         //用于存放查找插入点的过程中所经过节点的栈
	//先查找插入点
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
	//自插入点开始，检查树的平衡并调整
	node *son, *parent;
	int pattern;
	while (1)                   //循环直到存放插入点的过程中所经过节点的栈为空为止
	{
		son = route.top();
		route.pop();
		if (route.empty())        //栈内最后出栈的一定是根结点
		{
			root = son;
			root->child = -1;
			break;
		}

		parent = route.top();
		route.pop();
		if (son->value < parent->value)              //新节点插在了parent的左子树上
		{
			parent->l_child = son;
			son->parent = parent;
			son->child = 0;
			int r_cheight = parent->r_child != nullptr ? parent->r_child->height : 0;
			
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
		//更新高度，并把新的子树的根节点入栈
		int l_cheight = parent->l_child != nullptr ? parent->l_child->height : 0;
		int r_cheight = parent->r_child != nullptr ? parent->r_child->height : 0;
		parent->height = max(l_cheight, r_cheight) + 1;
		route.push(parent);
	}
}

node * avl_tree::replace(node * p1)   //查找替换点
{
	node* rep = p1->l_child;              
	if (rep != nullptr)                          //如果p1节点的左子树不为空
	{
		if (rep->r_child != nullptr)          //如果p1节点的左子树的右子树不为空，则找左子树的最大的点来替换p1的value的值
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
		else                                      //否则，若p1节点的左子树的右子树为空，则直接取p1节点的左孩子的值来替换，并删除p1节点的左孩子
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
	else                                          //如果p1节点的左子树为空，则直接删掉p1节点，并更新连接
	{
		node *parent = p1->parent;
		if (p1->child == 0)                  //如果p1节点是其父节点的左孩子，则将p1节点的右孩子作为p1节点父节点的左孩子
		{
			p1->parent->l_child = p1->r_child;
			if (p1->r_child != nullptr)
			{
				p1->r_child->parent = p1->parent;
				p1->parent->child = 0;
			}
			parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;
		}
		else if (p1->child == 1)          //如果p1节点是其父节点的右孩子，则将p1节点的右孩子作为p1节点父节点的右孩子
		{
			p1->parent->r_child = p1->r_child;
			if (p1->r_child != nullptr)
			{
				p1->r_child->parent = p1->parent;
				p1->parent->child = 1;
			}
			parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;
		}
		else if (p1->child == -1)       //如果p1节点是根，则不用更新父节点信息，直接删除
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
	//先查找需要删除的节点的位置
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
	//找到之后在树种找一个值替代
	node* parent = replace(p);
	//更新高度信息并调整平衡
	if (parent != nullptr)
	{
		int pattern;
		while (parent)
		{
			if (height(parent->r_child) - height(parent->l_child) == 2)         //因为替换的过程中可以保证右子树比左子树高，所以只检查右子树比左子树高2的情况
			{
				int rl_ch = height(parent->r_child->l_child);
				int rr_ch = height(parent->r_child->r_child);
				if (rr_ch >= rl_ch)                     //如果parent的右子树的左子树的高度大于等于parent的右子树的右子树的高度，则RR
					pattern = 4;
				else if (rr_ch < rl_ch)                //否则RL
					pattern = 3;

				parent = height_adjustment(parent, pattern);            //调整平衡
				parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;       //更新高度
			}
			parent->height = max(height(parent->l_child), height(parent->r_child)) + 1;
			if (parent->parent == nullptr)                               //更新树的根节点
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