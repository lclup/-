#include <iostream>
#include <string>   //stl标准库  容器 +算法
#include <vector>
#include <algorithm>
using namespace std;
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
//算法的实现大多在函数中：函数是语句体集合
void instructions(); //欢迎使用人机对战井字棋游戏，您可以输入0-8的数字，棋盘如下所示   界面初始化
char askYesNo(string question);//判断谁先下
int askNumber(string question, int high, int low = 0);//输入0-8数字  规范用户的输入
char humanPiece();//人的棋子   先者为X后者为O
char opponent(char piece);//交换先手顺序
void displayBoard(const vector<char>& board);//show棋盘
char winner(const vector<char>& board);//判断是否赢+和棋
bool isLeagel(const vector<char>& board);//判断是否为 ‘ ’表示可以下棋
int humanMove(const vector<char>& board,char human);//人下棋的位置
int computerMove(vector<char> board, char computer);//机器下棋的位置  （1）先找赢的策略（2）判断人是否能赢
void announceWinner(char winner, char computer, char human);//对战结果  输 赢 和棋
int main(void) {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(board);

	while ((winner(board)) == NO_ONE) {
		if (turn == human) {
			move = humanMove(board, human);
			board[move] = human;
		}
		else {
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	system("pause");
	return 0;
}

void instructions() {
	cout << "欢迎使用人机对战井字棋游戏，您可以输入0-8的数字，棋盘如下所示" << endl;
	cout << "0  |  1|  2" << endl;
	cout << "3  |  4|  5" << endl;
	cout << "6  |  7|  8" << endl;
}
char askYesNo(string question) {
	char response;
	do {
		cout << question << "(y/n)";
		cin >> response;
	} while (response != 'y'&& response != 'n');
	return response;
}
//规范用户的输入
int askNumber(string question, int high, int low ) {
	int number;
	do {
		cout << question << "("<<low<<" - "<<high<<"):";
		cin >> number;
	} while (number >high || number<low);
	return number;
}
char humanPiece() {
	char go_first = askYesNo("您是否要先手走棋?");
	if (go_first == 'y') {
		cout << "游戏即将开始，您将先手走棋";
		return X;
	}
	else {
		cout << "游戏即将开始，机器将先手走棋";
		return O;
	}
}
char opponent(char piece) {
	if (piece == X) {
		return O;
	}
	else {
		return X;
	}
}
void displayBoard(const vector<char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2]  ;
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << endl;
}
char winner(const vector<char>& board) {
	const int WIN_ROWS[8][3] = {
		{0,1,2},{3,4,5},{6,7,8},
		{0,3,6},{1,4,7},{2,5,8},
		{0,4,8},{2,4,6}
	};

	const int TOTOAL_ROWS = 8;
	for (int row = 0;row < TOTOAL_ROWS;row++) {
		if ((board[WIN_ROWS[row][0]] != EMPTY) &&
			(board[WIN_ROWS[row][0]] == board[WIN_ROWS[row][1]]) &&
			(board[WIN_ROWS[row][1]] == board[WIN_ROWS[row][2]])) {
			return board[WIN_ROWS[row][0]];
		}
	}

	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	return NO_ONE;
}
bool isLeagel(int move,const vector<char>& board) {
	return (board[move] == EMPTY);
}
int humanMove(const vector<char>& board, char human) {
	int move = askNumber("您将在哪里落子", (board.size() - 1));
	while (!isLeagel(move, board)) {
		cout << "\n您选择的地方已经有子了";
		move  = askNumber("您将在哪里落子", (board.size() - 1));
	}
	return move;
}
int computerMove( vector<char> board, char computer) {
	int move = 0;
	bool found = false;

	//首先找获胜策略
	while (!found && move < board.size()) {
		if (isLeagel(move, board)) {
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}

		if (!found) {
			++move;
		}
	}

	//看看人类是否要获胜，如果人类要获胜，阻止它
	if (!found) {
		move = 0;
		char human = opponent(computer);

		while (!found && move < board.size()) {
			if (isLeagel(move, board)) {
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}

			if (!found)
				++move;
		}
	}

	if (!found) {
		move = 0;
		int i = 0;
		const int BEST_STRATEGY[] = { 4,0,2,6,8,1,3,5,7 };
		while (!found && i < board.size()) {
			move = BEST_STRATEGY[i];
			if (isLeagel(move, board)) {
				found = true;
			}
			++i;
		}
	}
	cout << "我将放在" << move << endl;
	return move;
}
void announceWinner(char winner, char computer, char human) {
	if (winner == computer) {
		cout << "人机大战，电脑获胜" << endl;
	}
	else if (winner == human) {
		cout << "人机大战，玩家获胜" << endl;
	}
	else {
		cout << "人机大战，双方平手" << endl;
	}
}
