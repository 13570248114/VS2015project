//��ٷ���������������ĺ���
#include<stdio.h>
int w,t;           //w·�����۵���ʱ������t�����ڽ�������ʱ����
int* bestx;        //�洢����·��������
int* x;            //�洢·��������
int bestw=65535;   //���ڴ����ʹ��۵�ȫ�ֱ���
extern FILE *fp;
void Tsp(int **g, int n, int s)            //�ݹ�ʵ��ȫ����
{
	if (s == n)                           //���s=n˵��x[0]...x[n-1]�Ѿ���һ������
	{
		w = 0;                            //w���ڴ�Ÿ������µ�·�����ۺ�
		printf("bestx:");
		for (int i = 0;i < n;i++)         //����������µ�·�����ۺ�
		{
			bestx[i] = x[i];
			printf("%d ", bestx[i]);
			fprintf(fp, "%d ", bestx[i]);

			if (i < n - 1)                 //����·��x[0],x[1]...x[n-1],x[0]��·�����ۺ�
				w += g[x[i]][x[i + 1]];   
			else
				w += g[x[i]][x[0]];          
		}
       
		printf("w:%d\n", w);               //��ӡ��·���Ĵ���
		fprintf(fp,"w:%d\n", w);
		if (bestw > w)                     //����Ƿ�ȵ�ǰ����С����ҪС���ǵĻ��������С����
			bestw = w;
	}
	else
	{
		for (int i = s;i < n;i++)          //���ݹ����ȫ���У��������е�˼���˵���ĵ�
		{
			t = x[i];                      //����
			x[i] = x[s];
			x[s] = t;

			Tsp(g, n, s + 1);              //�ݹ���һ��

			t = x[i];                      //������������֤ÿһ��ݹ�󱣳���һ���˳��
			x[i] = x[s];
			x[s] = t;
		}
	}
}