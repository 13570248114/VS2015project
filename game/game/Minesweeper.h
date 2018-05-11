#include<fstream>
using std::ifstream;
class Minesweeper                           //ɨ����Ϸ����
{

private:
	int** map;                             //�ö�ά�����ͼ
	int gridNumOfX;                        //����
	int gridNumOfY;                        //����
	int bombNum;                           //ը����
	int markNum;                           //�����
	int derection[3] = { 0,1,-1 };         //���ڴ����ٽ���
	bool gameON;                           //��Ϸ���ڽ��еı�־
	bool Win_or_Lose;                      //Ӯ��ı�־��ӮΪ1����Ϊ0

public:
	Minesweeper() {};                      //�������캯��
	Minesweeper(int X, int Y, int bombs) ;
	Minesweeper(ifstream& in);
	~Minesweeper();                        //��������
	int calculate(int x, int y);           //����㣨x,y������Χ�ж��ٸ�ը��
	void setMap(int x, int y);             //����ͼ�ϸ����ֵ
	void print(bool gameON);               //��ӡ����
	bool win();                            //�ж��Ƿ���˳���թ��֮�����и��ӵĺ�����ֻ��ʤ����һ������
	void marked(int x, int y);             //���ڱ��ĳ���Ƿ�Ϊը���ĺ���
	void revealed(int x, int y);           //��ĳһ�����ӵĺ���
	bool getGameON() { return gameON; }    //��ȡ��Ϸ�Ƿ��ڽ��е�״̬
	void saveGame();                       //������Ϸ
	void playing();                        //����Ϸ
};

