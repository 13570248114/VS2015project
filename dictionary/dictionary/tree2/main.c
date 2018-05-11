#include"head.h"

int main()
{
	//�������
   unsigned long locate = 0;
   int j=0,i;
   Node *root = create_node('\0', FALSE);
   Node *root2 = create_node('\0', FALSE);
   char dictionary[30], words[30], longwords[100] = {"\0"};
   
   //�ļ��򿪲���
   FILE *fp = fopen("dictionary.txt", "r");
   if (fp == NULL)
   {
	   printf("FILE ERROR");
	   return -1;
   }
   FILE* fp2= fopen("article.txt", "r");
   if (fp2 == NULL)
   {
	   printf("FILE ERROR");
	   return -1;
   }
   FILE* fp3 = fopen("misspelling.txt", "w");
   if (fp3 == NULL)
   {
	   printf("FILE ERROR");
	   return -1;
   }
   fclose(fp3);
   fp3 = fopen("misspelling.txt", "a");
   if (fp3 == NULL)
   {
	   printf("FILE ERROR");
	   return -1;
   }

   //���ֵ䴴���ֵ���
   while (fgets(dictionary, 30, fp))
	   insert_word(root, dictionary,0);

   //�����Ƕ����µĴ��������£�һ�����99���ַ�
   while (fgets(longwords, 100, fp2))
   {
	   //����ѭ��
	   for (i = 0;i < strlen(longwords);i++)
	   {
		   locate++;         //���ڼ�¼��ǰ�ַ���λ��
		   //��д��Сд
		   if (longwords[i] >= 'A'&&longwords[i] <= 'Z')
			   longwords[i] = longwords[i] - 'A' + 'a';
		   //��Ӣ���ַ���¼���ַ����ڣ���ɵ���
		   if (longwords[i] >= 'a'&& longwords[i] <= 'z')
		   {
			   words[j] = longwords[i];
			   j++;
		   }
		   else
		   {   
			   //����Ӣ���ַ���ͳͳ��ɿո�
			   //longwords[i] = ' ';
			   words[j] = '\0';

			   if (!check(root, words))    //��������е��ʲ����ֵ���
			   {
				   insert_word(root2, words, locate - j - 1);   //�Ѳ����ֵ����ϵĵ���д���µĵ������ϣ�locate - j - 1�ǵ�������ĸ��λ��
				   
			   }
			   //for(j=0;j<30;j++)    //��ջ���ĵ���
				  // words[j] = '\0';
			   j = 0;
			   
		   }
	   }
   }

   traversal(root2, "",fp3);    //����������������԰��ֵ�˳���ӡ�������Ϊ��֧�ǰ�'a'-'z'�����
 
   //�ر��ļ�
   fclose(fp);
   fclose(fp2);
   fclose(fp3);
   return 0;
}

