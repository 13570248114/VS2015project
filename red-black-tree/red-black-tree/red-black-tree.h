#ifndef RED-BLACK-TREE_H
#define RED-BLACK-TREE_H


using namespace std;

struct TreeNode {
	static enum colors
	{
		red = 0,
		black = 1
	};

	colors color;
	int key;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode() :color(red), left(nullptr), right(nullptr), parent(nullptr), key(0) {};
	TreeNode(colors c, TreeNode* l, TreeNode* r, TreeNode* p, int k) :color(c), left(l), right(r), parent(p), key(k) {};
};

class redBlackTree {
private:
	TreeNode* _root;
	static  TreeNode* nil;
private:
	void __LeftRotate(TreeNode*  x);
	void __RightRotate(TreeNode*  x);
	void __rb_insert_fix(TreeNode*  z);
	void __rb_transplant(TreeNode* u, TreeNode* v);
	void __rb_delete_fix(TreeNode*  x);
	TreeNode* __tree_minimun(TreeNode*  z);
public:
	redBlackTree() :_root(nil) {};
	void rb_insert(TreeNode*  z);
	void rb_delete(TreeNode*  z);
	
};
#endif // !RED-BLACK-TREE_H

