#include<iostream>
#include <iomanip>
#include<memory>
#include<string>
#include<ctime>
#include<vector>
#include<queue>

using namespace std;

class TreeNode {
	friend class Tree;
public:
	TreeNode(int key, TreeNode* leftChild, TreeNode* rightChild) :_key(key), _height(0), _letfChild(leftChild), _rightChild(rightChild) {}
private:
	int _key;
	int _height;
	TreeNode* _letfChild;
	TreeNode* _rightChild;
};

class Tree {
private:
	string _output;
	TreeNode* _root;
	int height(TreeNode* root);
	int max(int a, int);
	TreeNode* minNode(TreeNode* root);
	TreeNode* maxNode(TreeNode* root);
	void preOrder(TreeNode* root);
	void inOrder(TreeNode* root);
	void postOrder(TreeNode* root);
	TreeNode* singleLeftRot(TreeNode* k);
	TreeNode* singleRightRot(TreeNode* k);
	TreeNode* doubleLRRot(TreeNode* k);
	TreeNode* doubleRLRot(TreeNode* k);
	TreeNode* insert(TreeNode* &root, int key);
	TreeNode* del(TreeNode* &root, int key);
	void fixBalance(TreeNode* &root);
	void destory(TreeNode* &root);
	void print(TreeNode* root, int key, int dir);
public:
	Tree() :_root(nullptr) {}
	string preOrder();
	string inOrder();
	string postOrder();
	void insert(int key);
	void del(int key);
	void destory();
	void print();
};

int Tree::max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int Tree::height(TreeNode* root)
{
	if (root == nullptr)
		return -1;
	else
		return root->_height;
}

void Tree::preOrder(TreeNode* root) {
	if (root != nullptr) {
		_output += to_string(root->_key);
		_output += " ";
		preOrder(root->_letfChild);
		preOrder(root->_rightChild);
	}
}

string Tree::preOrder() {
	if (_root == nullptr)
		return "EMPTY";
	else {
		_output.clear();
		preOrder(_root);
		return _output;
	}
	
}

void Tree::inOrder(TreeNode* root) {
	if (root != nullptr) {
		inOrder(root->_letfChild);
		_output += to_string(root->_key);
		_output += " ";
		inOrder(root->_rightChild);
	}
}

string Tree::inOrder() {
	if (_root == nullptr)
		return "EMPTY";
	else {
		_output.clear();
		inOrder(_root);
		return _output;
	}
}

void Tree::postOrder(TreeNode* root) {
	if (root != nullptr) {
		postOrder(root->_letfChild);
		postOrder(root->_rightChild);
		_output += to_string(root->_key);
		_output += " ";
	}
}

string Tree::postOrder() {
	if (_root == nullptr)
		return "EMPTY";
	else {
		_output.clear();
		postOrder(_root);
		return _output;
	}
}

TreeNode* Tree::maxNode(TreeNode* root)
{
	if (root == nullptr)
		return nullptr;
	else {
		while (root->_rightChild != nullptr)
			root = root->_rightChild;
		return root;
	}
}

TreeNode* Tree::minNode(TreeNode* root)
{
	if (root == nullptr)
		return nullptr;
	else {
		while (root->_letfChild != nullptr)
			root = root->_letfChild;
		return root;
	}
}

TreeNode* Tree::singleLeftRot(TreeNode* k2)
{
	TreeNode* k1 = k2->_letfChild;
	k2->_letfChild = k1->_rightChild;
	k1->_rightChild = k2;
	k2->_height = max(height(k2->_letfChild), height(k2->_rightChild)) + 1;
	k1->_height = max(height(k1->_letfChild), height(k1->_rightChild)) + 1;
	return k1;
}

TreeNode* Tree::singleRightRot(TreeNode* k1)
{
	TreeNode* k2 = k1->_rightChild;
	k1->_rightChild = k2->_letfChild;
	k2->_letfChild = k1;
	k2->_height = max(height(k2->_letfChild), height(k2->_rightChild)) + 1;
	k1->_height = max(height(k1->_letfChild), height(k1->_rightChild)) + 1;
	return k2;
}

TreeNode* Tree::doubleLRRot(TreeNode* k3)
{
	k3->_letfChild = singleRightRot(k3->_letfChild);
	return singleLeftRot(k3);
}

TreeNode* Tree::doubleRLRot(TreeNode* k1)
{
	k1->_rightChild = singleLeftRot(k1->_rightChild);
	return singleRightRot(k1);
}

void Tree::fixBalance(TreeNode* &root)
{
	if (height(root->_rightChild) - height(root->_letfChild) == 2)
	{
		if (height(root->_rightChild->_rightChild) >= height(root->_rightChild->_letfChild))
			root = singleRightRot(root);
		else
			root = doubleRLRot(root);
	}
	else if (height(root->_letfChild) - height(root->_rightChild) == 2)
	{
		if (height(root->_letfChild->_letfChild) >= height(root->_letfChild->_rightChild))
			root = singleLeftRot(root);
		else
			root = doubleLRRot(root);
	}
}

TreeNode* Tree::insert(TreeNode* &root, int key)
{
	if (root == nullptr)
	{
		root = new TreeNode(key, nullptr, nullptr);
	}
	else if (key != root->_key)
	{
		if (key < root->_key)
		{
			root->_letfChild = insert(root->_letfChild, key);
			root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
		}
		else
		{
			root->_rightChild = insert(root->_rightChild, key);
			root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
		}
		fixBalance(root);
	}
	root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
	return root;
}

void Tree::insert(int key)
{
	insert(_root, key);
}

TreeNode* Tree::del(TreeNode* &root, int key)
{
	if (root == nullptr)
		return nullptr;
	if (key == root->_key) {
		if (root->_letfChild != nullptr&&root->_rightChild != nullptr) {
			TreeNode* tmp = maxNode(root->_letfChild);
			root->_key = tmp->_key;
			root->_letfChild = del(root->_letfChild, tmp->_key);
			root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
			fixBalance(root);
			root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
		}
		else {
			TreeNode* tmp = root;
			if (root->_letfChild == nullptr)
				root = root->_rightChild;
			else if (root->_rightChild == nullptr)
				root = root->_letfChild;
			delete tmp;
		}
	}
	else if (key < root->_key) {
		root->_letfChild = del(root->_letfChild, key);
		root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
		fixBalance(root);
		root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
	}
	else if (key > root->_key) {
		root->_rightChild = del(root->_rightChild, key);
		root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
		fixBalance(root);
		root->_height = max(height(root->_letfChild), height(root->_rightChild)) + 1;
	}
	return root;
}

void Tree::del(int key)
{
	_root = del(_root, key);
}

void Tree::destory(TreeNode* &root)
{
	if (root == nullptr)
		return;
	else {
		if (root->_letfChild != nullptr)
			destory(root->_letfChild);
		if (root->_rightChild != nullptr)
			destory(root->_rightChild);
		delete root;
	}
}

void Tree::destory()
{
	destory(_root);
}

void Tree::print(TreeNode* root, int key, int dir)
{
	if (root != NULL)
	{
		if (dir == 0)    
			cout << setw(2) << root->_key << " is root" << endl;
		else                
			cout << setw(2) << root->_key << " is " << setw(2) << key << "'s " << setw(12) << (dir == 1 ? "right child" : "left child") << endl;

		print(root->_letfChild, root->_key, -1);
		print(root->_rightChild, root->_key, 1);
	}
}


void Tree::print()
{
	print(_root,_root->_key,0);
}

int main()
{
	Tree tree;
	string input, temp;
	getline(cin, input);
	vector<string> act;
	for (auto ch : input) {
		if (ch != ' ')
			temp += ch;
		else {
			act.push_back(temp);
			temp.clear();
		}
	}
	if (temp != ""&&temp != " ")
		act.push_back(temp);
	string num;
	for (auto v : act)
	{
		if (v[0] == 'A')
		{
			num = v.substr(1, v.length() - 1);
			tree.insert(stoi(num));
		}
		else if (v[0] == 'D')
		{
			num = v.substr(1, v.length() - 1);
			tree.del(stoi(num));
		}
		else if (v[1] == 'R') {
			cout << tree.preOrder()<<endl;
		}
		else if (v[1] == 'N') {
			cout << tree.inOrder() << endl;
		}
		else if (v[1] == 'O') {
			cout << tree.postOrder() << endl;
		}
	}
	cout << endl;
	tree.print();////////////////////////////////////////////这行用完可以注释掉
	tree.destory();
}
