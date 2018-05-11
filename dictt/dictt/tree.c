#include"head.h"

Node* create_node(char c, int flag) {      //�����ڵ㣬һЩ��ʼ������
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

int insert_node(Node* n, char ch) {        //����ڵ㣬����ַ�ch�������е����ϣ��򷵻�TRUE������FALSE

    Node* child_ptr =  n->child[ch-'a'];

    if (child_ptr) {
        return FALSE;
    }
    else {
        n->child[ch-'a'] = create_node(ch, FALSE);
        return TRUE;
    }
}

int insert_word(Node* root, char* str,int loca) {      //���뵥�ʣ�loca�ǵ����������е�λ�ã��ɹ�����TRUE
    char c = *str;
	if (c != '\0'&&c!=' ')
	{
		Node* father = root;                          //ͨ������ڵ������뵥��
		int flag = TRUE;
		while (c>='a'&&c<='z') {
			if (!insert_node(father, c)) {
				flag = FALSE;
			}
			father = father->child[c - 'a'];
			c = *(++str);
		}                                             

		if (father->isEnd)                           //��������Ѿ����ֵ�����
			addlocate(father->head, loca);              //���ֵ����ϵ��ʵĽ�β���ڵ��ü�¼���ʳ��ֵ�λ��

		if (!father->isEnd) {                       
			flag = FALSE;                          //����������ֵ��������е��ʵ�ǰ׺�����޸ı�־λ
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

int check(Node* root, char* word) {              //��鵥���Ƿ����ֵ����ϣ����򷵻�TRUE
	Node* ptr = root;
	int slen = strlen(word);
	int i;

	for (i = 0; i < slen; i++) {            //�����ĸ��ʼ������
		if (!ptr) {
			return FALSE;
		}
		if (word[i] > 'z' || word[i] < 'a')
			return FALSE;
		ptr = ptr->child[word[i] - 'a'];
	}

	if (ptr && ptr->isEnd) {                 //���������ĸ���ڽ�β��־���򷵻���         
		return TRUE;
	}
	else {
		return FALSE;
	}

}


void traversal(Node* root, char* str, FILE* fp3) {           //������ȱ������������ڰ��ֵ�˳��������

	location *p;
	int i;

	if (!root) {
		return;
	}

	//�ֶ���һ�εݹ�����ݽ��п���
	int len_of_str = strlen(str);
	char* new_str =(char*) malloc(sizeof(char)*(len_of_str+2));
	strcpy(new_str, str);
	new_str[len_of_str] = root->ch;
	new_str[len_of_str + 1] = '\0';

	//����Ѿ��ݹ鵽����β�ͣ����ӡ�����ַ�����λ�ڵ���β�ʹ���λ������
	if (root->isEnd) {
		//����֮ǰ�ݹ�Ľ�����ŵ�һ���ַ�������
		char* str_for_print = (char*)malloc(sizeof(char)*(len_of_str + 2));
		strcpy(str_for_print, new_str);
		str_for_print[len_of_str + 1] = '\0';

		//��ӡ�ַ�������Ļ���ļ�
		printf("%s ", str_for_print);
		fprintf(fp3,"%s ", str_for_print);
        //��ӡλ�ڵ���β�ʹ��ļ�¼�����ڵĵ��ʵ�λ������
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

	//��û�ݹ鵽����β��������ݹ�
	for (i = 0; i < COUNT; i++) {
		traversal(root->child[i], new_str,fp3);
	}
	free(new_str);
}