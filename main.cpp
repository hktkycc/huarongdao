#include <iostream>
using namespace std;
#include <stack>

typedef struct List
{
	List* father;
	int state[5][4];
	List* next;
};//棋盘状态链表，用于存储棋盘经历过的状态

List* current = (List*)malloc(sizeof(List));
List* head = (List*)malloc(sizeof(List));
List* next = (List*)malloc(sizeof(List));

List *init()
{
	List* board = (List*)malloc(sizeof(List));
	board->father = NULL;
	board->next = NULL;
	board->state[0][0] = 2; board->state[0][1] = 1; board->state[0][2] = 1; board->state[0][3] = 3;
	board->state[1][0] = 2; board->state[1][1] = 1; board->state[1][2] = 1; board->state[1][3] = 3;
	board->state[2][0] = 4; board->state[2][1] = 6; board->state[2][2] = 6; board->state[2][3] = 5;
	board->state[3][0] = 4; board->state[3][1] = 7; board->state[3][2] = 7; board->state[3][3] = 5;
	board->state[4][0] = 7; board->state[4][1] = 0; board->state[4][2] = 0; board->state[4][3] = 7;
	return board;
}//初始化棋盘，横刀立马开局

void show(List* board)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << board->state[i][j] << " ";
		}
		cout << endl;
	}
}//打印棋盘

bool victory(List* board)
{
	if (board->state[3][1] == 1 && board->state[3][2] == 1 && board->state[4][1] == 1 && board->state[4][2] == 1)
		return true;
	else
		return false;
}//胜利判断条件

bool repeat(List* board)
{
	while (board->father)
	{
		List* p = board->father;
		if (p->state == board->state)
			return true;
		else
			p = p->father;
	}
}//遍历整个棋盘历史状态，寻找是否有重复

void save(List* board)
{
	current->next = board;
	board->father = current;
	current = current->next;
}//向链表后续入保存棋盘状态



int main()
{
	List* board = init();
	head = board;
	show(board);
}
