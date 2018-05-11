#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int rollThedices();

int main()
{
	srand(time(0));                   //������������������
	int chips = 400, sum, betChips, point, on = 1, wins = 0, loses = 0, playCount = 0;
	printf("Game start!\n\n");

	while (on)
	{
		//������δ��봦���������
		printf("\n\nYou have %d chips.\n\n",chips);
		do {
			printf("Input  the numbers of chips(0 - %d):", chips);
			scanf("%d", &betChips);
			if (betChips<0 || betChips>chips)
				printf("Invaild Input!, pleause input again!\n");
		} while (betChips<0 || betChips>chips);

		//�����������dice��ֵ
		sum = rollThedices();

		//������Ϸ���������
		if (sum == 7 || sum == 12)                    //���1
		{
			chips += betChips;
			printf("You win! Now you have %d chips.\n", chips);
			++wins;
		}
		else if (sum == 2 || sum == 3 || sum == 10)              //���2
		{
			chips -= betChips;
			printf("You lost! Now you have %d chips.\n", chips);
			++loses;
		}
		else                                                                          //���3����Ҫ����������
		{
			point = sum;
			printf("You point is %d, now continue to roll the dices: \n", point);
			do
			{
				sum = rollThedices();                                          //����������
				if (sum != point&&sum != 7)
					printf("You point is %d, now continue to roll the dices: \n", point);
			}while (sum != point&&sum != 7);                                       //sum��������ҵ�point����7ʱ�ͼ���������

			if (sum == point)                                                                //���3�е����Ӯ
			{
				printf(" Sum = %d:  ", sum);
				chips += 2 * betChips;
				printf("You win! Now you have %d chips.\n", chips);
				++wins;
			}
			else if (sum == 7)                                                              //���3�е������
			{
				printf(" Sum = %d:  ", sum);
				chips -= betChips;
				printf("You lost! Now you have %d chips.\n", chips);
				++loses;
			}
		}

		++playCount;                                                                       //����һ����Ĵ���

		printf("\nYou have played %d times:\nwin: %d times\tlose : %d times\n\n", playCount, wins, loses);

		if (chips == 0)                                                                      //�����ù�ʱ����Ϸ����
		{
			on = 0;
		}
		else                                                                                     //����û�ù�ʱ����ѡ���������Ϸ�����˳���Ϸ
		{
			printf("\n\nInout 1 to continue the game\nInout 0 to quit the game\n");
			scanf("%d", &on);
		}

		if(on == 0)
			printf("\n\nGAME OVER!\n\n");

	}
	exit(0);
}

int rollThedices()
{
	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;
	int sum = dice1 + dice2;
	printf("dice1 : %d\tdice2 : %d\tsum : %d\n", dice1, dice2, sum);
	return sum;
}