#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int rollThedices();

int main()
{
	srand(time(0));                   //获得生成随机数的种子
	int chips = 400, sum, betChips, point, on = 1, wins = 0, loses = 0, playCount = 0;
	printf("Game start!\n\n");

	while (on)
	{
		//以下这段代码处理筹码输入
		printf("\n\nYou have %d chips.\n\n",chips);
		do {
			printf("Input  the numbers of chips(0 - %d):", chips);
			scanf("%d", &betChips);
			if (betChips<0 || betChips>chips)
				printf("Invaild Input!, pleause input again!\n");
		} while (betChips<0 || betChips>chips);

		//随机生成两个dice的值
		sum = rollThedices();

		//以下游戏的三种情况
		if (sum == 7 || sum == 12)                    //情况1
		{
			chips += betChips;
			printf("You win! Now you have %d chips.\n", chips);
			++wins;
		}
		else if (sum == 2 || sum == 3 || sum == 10)              //情况2
		{
			chips -= betChips;
			printf("You lost! Now you have %d chips.\n", chips);
			++loses;
		}
		else                                                                          //情况3，需要继续掷骰子
		{
			point = sum;
			printf("You point is %d, now continue to roll the dices: \n", point);
			do
			{
				sum = rollThedices();                                          //重新掷骰子
				if (sum != point&&sum != 7)
					printf("You point is %d, now continue to roll the dices: \n", point);
			}while (sum != point&&sum != 7);                                       //sum不等于玩家的point或者7时就继续掷骰子

			if (sum == point)                                                                //情况3中的玩家赢
			{
				printf(" Sum = %d:  ", sum);
				chips += 2 * betChips;
				printf("You win! Now you have %d chips.\n", chips);
				++wins;
			}
			else if (sum == 7)                                                              //情况3中的玩家输
			{
				printf(" Sum = %d:  ", sum);
				chips -= betChips;
				printf("You lost! Now you have %d chips.\n", chips);
				++loses;
			}
		}

		++playCount;                                                                       //增加一次玩的次数

		printf("\nYou have played %d times:\nwin: %d times\tlose : %d times\n\n", playCount, wins, loses);

		if (chips == 0)                                                                      //筹码用光时则游戏结束
		{
			on = 0;
		}
		else                                                                                     //筹码没用光时可以选择继续玩游戏或者退出游戏
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