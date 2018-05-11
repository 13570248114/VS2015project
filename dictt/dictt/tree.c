#include"head.h"

Node* create_node(char c, int flag) {      //创建节点，一些初始化工作
	int i;
    Node* node = malloc(sizeof(Node));
    node->ch = c;
    node->isEnd = flag;
	node->head = createlocate(-1);

    for (i = 0; i < COUNT; i++) {
        node->child[i] = NULL;
    }

    return node;
}

int insert_node(Node* n, char ch) {        //插入节点，如果字符ch不在现有的树上，则返回TRUE，否则FALSE

    Node* child_ptr =  n->child[ch-'a'];

    if (child_ptr) {
        return FALSE;
    }
    else {
        n->child[ch-'a'] = create_node(ch, FALSE);
        return TRUE;
    }
}

int insert_word(Node* root, char* str,int loca) {      //插入单词，loca是单词在文章中的位置，成功返回TRUE
    char c = *str;
	if (c != '\0'&&c!=' ')
	{
		Node* father = root;                          //通过插入节点来插入单词
		int flag = TRUE;
		while (c>='a'&&c<='z') {
			if (!insert_node(father, c)) {
				flag = FALSE;
			}
			father = father->child[c - 'a'];
			c = *(++str);
		}                                             

		if (father->isEnd)                           //如果单词已经在字典树上
			addlocate(father->head, loca);              //在字典树上单词的结尾处节点用记录单词出现的位置

		if (!father->isEnd) {                       
			flag = FALSE;                          //如果单词是字典树上已有单词的前缀，则修改标志位
			father->isEnd = TRUE;
			addlocate(father->head, loca);
		}

		return !flag;
	}
	else
	{
		return FALSE;
	}
}

int check(Node* root, char* word) {              //检查单词是否在字典树上，在则返回TRUE
	Node* ptr = root;
	int slen = strlen(word);
	int i;

	for (i = 0; i < slen; i++) {            //逐个字母开始查找树
		if (!ptr) {
			return FALSE;
		}
		if (word[i] > 'z' || word[i] < 'a')
			return FALSE;
		ptr = ptr->child[word[i] - 'a'];
	}

	if (ptr && ptr->isEnd) {                 //如果最后的字母存在结尾标志，则返回真         
		return TRUE;
	}
	else {
		return FALSE;
	}

}


void traversal(Node* root, char* str, FILE* fp3) {           //深度优先遍历函数，用于按字典顺序输出结果

	location *p;
	int i;

	if (!root) {
		return;
	}

	//现对上一次递归的内容进行拷贝
	int len_of_str = strlen(str);
	char* new_str =(char*) malloc(sizeof(char)*(len_of_str+2));
	strcpy(new_str, str);
	new_str[len_of_str] = root->ch;
	new_str[len_of_str + 1] = '\0';

	//如果已经递归到单词尾巴，则打印整个字符串和位于单词尾巴处的位置链表
	if (root->isEnd) {
		//拷贝之前递归的结果，放到一个字符数组内
		char* str_for_print = (char*)malloc(sizeof(char)*(len_of_str + 2));
		strcpy(str_for_print, new_str);
		str_for_print[len_of_str + 1] = '\0';

		//打印字符串到屏幕和文件
		printf("%s ", str_for_print);
		fprintf(fp3,"%s ", str_for_print);
        //打印位于单词尾巴处的记录不存在的单词的位置链表
		p = root->head->next;
		while (p)
		{
			printf("%d ", p->locate);
			fprintf(fp3, "%d", p->locate);
			p = p->next;
			if (p)printf(" ");
		}
		printf("\n");
		fprintf(fp3, "\n");
		free(str_for_print);
	}

	//还没递归到单词尾巴则继续递归
	for (i = 0; i < COUNT; i++) {
		traversal(root->child[i], new_str,fp3);
	}
	free(new_str);
}