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
List* nextp = (List*)malloc(sizeof(List));


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
}//初始化棋盘，横刀立马开局，在这里修改开局阵法

void pshow(List* board)
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

bool repeat(List* p)
{
	/*while (board->father)
	{
		List* p = board->father;
		if (p->state == board->state)
			return true;
		else
			p = p->father;
	}*/
	List* traverse;
	traverse = (List*)head;
	int record = 0, sum = 0;//record记录对比，sum对比总次数
	while (traverse->next)
	{
		int remark = record;//跳出双循环
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (p->state[i][j] != traverse->state[i][j])//状态矩阵出现同位置不同元素，认为是2中不同状态
				{
					record = record + 1;
					break;
				}//检查到是一个新状态，记录一次重复
			}
			if (remark != record)break;
		}

		//循环对比后，发现是旧状态
		traverse = traverse->next;
		sum = sum + 1;
	}
	//遍历结束,对比sum和record，若sum==record 代表每次对比都出现不同状态，说明是一种新状态
	if (sum == record)return false;
	else return true;
}//遍历整个棋盘历史状态，寻找是否有重复

void save(List* board)
{
	current->next = board;
	board->father = current;
	current = current->next;
}//向链表后续入保存棋盘状态


int move(int a[][4], int i, int j, int x, int y, List*& next_node)//待移动目标a[i][j]，移动到位置a[x][y]
{
	List* p;
	next_node->next = new List;
	p = next_node->next;
	p->next = NULL;

	for (int b = 0; b < 5; b++)
	{
		for (int c = 0; c < 4; c++)
		{
			p->state[b][c] = a[b][c];
		}
	}//建立新状态结点
	int t;
	t = p->state[i][j];
	p->state[i][j] = p->state[x][y];
	p->state[x][y] = t;

	if (repeat(p) == true)
	{
		delete p;
		next_node->next = NULL;
		return 1;
	};//检查重复

	p->father = current;

	//next_node->next = &new_state;
	next_node = p;

	if (victory(p))
	{
		//找到了目标状态，输出移动过程
		stack <List*> show_way;

		while (next_node->father == NULL)
		{
			show_way.push(next_node);
			next_node = next_node->father;
		}

		List* show; int x = 0;
		show = show_way.top();
		while (show_way.empty() == false)
		{
			cout << "第" << x << "步：" << endl;
			pshow(show);
			show_way.pop();
			x = x + 1;
		}
		exit(0);
	}
	return 0;
}
int move(int a[][4], int i1, int j1, int x1, int y1, int i2, int j2, int x2, int y2, List*& next_node)
//待移动目标a1[i1][j1]，移动到位置a1[x1][y1],待移动目标a2[i2][j2]，移动到位置a2[x2][y2]
{
	List* p;
	next_node->next = new List;
	p = next_node->next;
	p->next = NULL;

	for (int b = 0; b < 5; b++)
	{
		for (int c = 0; c < 4; c++)
		{
			p->state[b][c] = a[b][c];
		}
	}//建立新状态结点

	/* 移动 */
	int t;
	t = p->state[i1][j1];
	p->state[i1][j1] = p->state[x1][y1];
	p->state[x1][y1] = t;

	t = p->state[i2][j2];
	p->state[i2][j2] = p->state[x2][y2];
	p->state[x2][y2] = t;

	if (repeat(p) == true)
	{
		delete p;
		next_node->next = NULL;
		return 1;
	};//检查重复

	p->father = current;
	//next_node->next = &new_state;
	next_node = p;

	if (victory(p))
	{
		//找到了目标状态，输出移动过程
		stack <List*> show_way;

		while (next_node->father != NULL)
		{
			show_way.push(next_node);
			next_node = next_node->father;
		}

		List* show; int x = 1;
		show = show_way.top();
		while (show_way.empty() == false)
		{
			cout << "di" << x << "setps:" << endl;
			pshow(show);
			show_way.pop();
			if (show_way.size() != 0)
				show = show_way.top();
			x = x + 1;
		}
		exit(0);
	}
	return 0;
}
bool is_one(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == 1 && p[i][j] == p[i + 1][j] && p[i][j] == p[i][j + 1] && p[i][j] == p[i + 1][j + 1])//is 1 or not
	{
		if (p[i - 1][j] == 0 && p[i - 1][j + 1] == 0 && i > 0) { move(p, i + 1, j, i - 1, j, i + 1, j + 1, i - 1, j + 1, n); }//up,2
		if (p[i + 2][j] == 0 && p[i + 2][j + 1] == 0 && i < 3) { move(p, i, j, i + 2, j, i, j + 1, i + 2, j + 1, n); }//down,2
		if (p[i][j - 1] == 0 && p[i + 1][j - 1] == 0 && j > 0) { move(p, i, j + 1, i, j - 1, i + 1, j + 1, i + 1, j - 1, n); }//left,2
		if (p[i][j + 2] == 0 && p[i + 1][j + 2] == 0 && j < 2) { move(p, i, j, i, j + 2, i + 1, j, i + 1, j + 2, n); }//right,2
		return true;//move success
	}
	else return 0;//can not move
}
bool is_two(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == p[i + 1][j] && p[i][j] == 2 && p[i + 1][j] == 2)//is 2 or not
	{
		if (p[i - 1][j] == 0 && i > 0) { move(p, i + 1, j, i - 1, j, n); }//UP
		if (p[i + 2][j] == 0 && i < 3) { move(p, i, j, i + 2, j, n); }//DOWN
		if (p[i][j - 1] == 0 && p[i + 1][j - 1] == 0 && j > 0) { move(p, i, j, i, j - 1, i + 1, j, i + 1, j - 1, n); }//left,2
		if (p[i][j + 1] == 0 && p[i + 1][j + 1] == 0 && j < 3) { move(p, i, j, i, j + 1, i + 1, j, i + 1, j + 1, n); }//right,2
		return true;//move success
	}
	else return false;//move faild
}
bool is_three(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == p[i + 1][j] && p[i][j] == 3 && p[i + 1][j] == 3)//is 3 or not
	{
		if (p[i - 1][j] == 0 && i > 0) { move(p, i + 1, j, i - 1, j, n); }//UP
		if (p[i + 2][j] == 0 && i < 3) { move(p, i, j, i + 2, j, n); }//DOWN
		if (p[i][j - 1] == 0 && p[i + 1][j - 1] == 0 && j > 0) { move(p, i, j, i, j - 1, i + 1, j, i + 1, j - 1, n); }//left,2
		if (p[i][j + 1] == 0 && p[i + 1][j + 1] == 0 && j < 3) { move(p, i, j, i, j + 1, i + 1, j, i + 1, j + 1, n); }//right,2
		return true;//move success
	}
	else return false;//move faild
}
bool is_four(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == p[i + 1][j] && p[i][j] == 4 && p[i + 1][j] == 4)//is 4 or not
	{
		if (p[i - 1][j] == 0 && i > 0) { move(p, i + 1, j, i - 1, j, n); }//UP
		if (p[i + 2][j] == 0 && i < 3) { move(p, i, j, i + 2, j, n); }//DOWN
		if (p[i][j - 1] == 0 && p[i + 1][j - 1] == 0 && j > 0) { move(p, i, j, i, j - 1, i + 1, j, i + 1, j - 1, n); }//left,2
		if (p[i][j + 1] == 0 && p[i + 1][j + 1] == 0 && j < 3) { move(p, i, j, i, j + 1, i + 1, j, i + 1, j + 1, n); }//right,2
		return true;//move success
	}
	else return false;//move faild
}
bool is_five(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == p[i + 1][j] && p[i][j] == 5 && p[i + 1][j] == 5)//is 5 or not
	{
		if (p[i - 1][j] == 0 && i > 0) { move(p, i + 1, j, i - 1, j, n); }//UP
		if (p[i + 2][j] == 0 && i < 3) { move(p, i, j, i + 2, j, n); }//DOWN
		if (p[i][j - 1] == 0 && p[i + 1][j - 1] == 0 && j > 0) { move(p, i, j, i, j - 1, i + 1, j, i + 1, j - 1, n); }//left,2
		if (p[i][j + 1] == 0 && p[i + 1][j + 1] == 0 && j < 3) { move(p, i, j, i, j + 1, i + 1, j, i + 1, j + 1, n); }//right,2
		return true;//move success
	}
	else return false;//move faild
}
bool is_six(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == p[i][j + 1] && p[i][j] == 6 && p[i][j + 1] == 6)
	{
		if (p[i - 1][j] == 0 && p[i - 1][j + 1] == 0 && i > 0) { move(p, i, j, i - 1, j, i, j + 1, i - 1, j + 1, n); }//up,2
		if (p[i + 1][j] == 0 && p[i + 1][j + 1] == 0 && i < 4) { move(p, i, j, i + 1, j, i, j + 1, i + 1, j + 1, n); }//down,2
		if (p[i][j - 1] == 0 && j > 0) { move(p, i, j + 1, i, j - 1, n); }//left
		if (p[i][j + 2] == 0 && j < 2) { move(p, i, j, i, j + 2, n); }//right
		return true;//move success
	}
	else return false;//move faild
}
bool is_seven(int p[][4], int i, int j, List*& n)
{
	if (p[i][j] == 7)
	{
		if (p[i - 1][j] == 0 && i > 0) { move(p, i, j, i - 1, j, n); }//up
		if (p[i + 1][j] == 0 && i < 4) { move(p, i, j, i + 1, j, n); }//down
		if (p[i][j - 1] == 0 && j > 0) { move(p, i, j, i, j - 1, n); }//left
		if (p[i][j + 1] == 0 && j < 3) { move(p, i, j, i, j + 1, n); }//right
		return true;//move success
	}
	else return false;//move faild
}
//int a = 0;
void build_tree(List*& c, List*& n)
{

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			is_one(c->state, i, j, n);
			is_two(c->state, i, j, n);
			is_three(c->state, i, j, n);
			is_four(c->state, i, j, n);
			is_five(c->state, i, j, n);
			is_six(c->state, i, j, n);
			is_seven(c->state, i, j, n);
		}

	}//判断当前状态图可移动的情况，给每种情况生成子节点

	c = c->next;//当前结点移动到下一个节点

}

int main()
{

	List* board = init();
	head = board;
	current = board;
	nextp = board;
	pshow(board);
	while (1)
	{
		build_tree(current, nextp);
	}
}
