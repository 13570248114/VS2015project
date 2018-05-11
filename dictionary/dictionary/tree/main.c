#include"head.h"

int main()
{
	//定义变量
   unsigned long locate = 0;
   int j=0,i;
   Node *root = create_node('\0', FALSE);
   Node *root2 = create_node('\0', FALSE);
   char dictionary[30], words[30], longwords[100] = {"\0"};
   
   //文件打开操作
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

   //用字典创建字典树
   while (fgets(dictionary, 30, fp))
	   insert_word(root, dictionary,0);

   //下面是对文章的处理，读文章，一次最多99个字符
   while (fgets(longwords, 100, fp2))
   {
	   //按行循环
	   for (i = 0;i < strlen(longwords);i++)
	   {
		   locate++;         //用于记录当前字符的位置
		   //大写变小写
		   if (longwords[i] >= 'A'&&longwords[i] <= 'Z')
			   longwords[i] = longwords[i] - 'A' + 'a';
		   //把英文字符记录到字符串内，组成单词
		   if (longwords[i] >= 'a'&& longwords[i] <= 'z')
		   {
			   words[j] = longwords[i];
			   j++;
		   }
		   else
		   {   
			   //不是英文字符则统统变成空格
			   //longwords[i] = ' ';
			   words[j] = '\0';

			   if (!check(root, words))    //如果文章中单词不在字典内
			   {
				   insert_word(root2, words, locate - j - 1);   //把不在字典树上的单词写到新的单词树上，locate - j - 1是单词首字母的位置
				   
			   }
			   //for(j=0;j<30;j++)    //清空缓存的单词
				  // words[j] = '\0';
			   j = 0;
			   
		   }
	   }
   }

   traversal(root2, "",fp3);    //按深度优先搜索可以按字典顺序打印结果，因为分支是按'a'-'z'排序的
 
   //关闭文件
   fclose(fp);
   fclose(fp2);
   fclose(fp3);
   return 0;
}

