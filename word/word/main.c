#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define SUB_NODE_COUNT 26

typedef struct node {
    struct node* children[SUB_NODE_COUNT];
    int flag;
    char character;
} Node;

Node* create_node(char c, int flag) {
    Node* n = malloc(sizeof(Node));
    n->character = c;
    n->flag = flag;
    for (int i = 0; i < SUB_NODE_COUNT; i++) {
        n->children[i] = NULL;
    }
    return n;
}

int append_node(Node* n, char c) {

    Node* child_ptr =  n->children[c-'a'];
    if (child_ptr) {
        return FALSE;
    }
    else {
        n->children[c-'a'] = create_node(c, FALSE);
        return TRUE;
    }
}

int add_word(Node* root, char* str) {
    char c = *str;
    Node* ptr = root;
    int flag = TRUE;
    while(c != '\n'&&c>0) {
        if (!append_node(ptr, c)) {
             flag = FALSE;
        }
        ptr = ptr->children[c-'a'];
        c = *(++str);
    }
    if (!ptr->flag) {
        flag = FALSE;
        ptr->flag = TRUE;
    }
    return !flag;
}

int main(void) {
    Node *root = create_node('$', FALSE);
	char dictionary[20];
	FILE *fp = fopen("E:\\project\\1706-1-2505\\dictionary.txt", "r");
    //²âÊÔadd_ wordº¯Êý
	while (fgets(dictionary, 15, fp))
		add_word(root, dictionary);
    
    return EXIT_SUCCESS;
}