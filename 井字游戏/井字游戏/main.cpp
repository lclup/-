#include <iostream>
#include <string>   //stl��׼��  ���� +�㷨
#include <vector>
#include <algorithm>
using namespace std;
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
//�㷨��ʵ�ִ���ں����У�����������弯��
void instructions(); //��ӭʹ���˻���ս��������Ϸ������������0-8�����֣�����������ʾ   �����ʼ��
char askYesNo(string question);//�ж�˭����
int askNumber(string question, int high, int low = 0);//����0-8����  �淶�û�������
char humanPiece();//�˵�����   ����ΪX����ΪO
char opponent(char piece);//��������˳��
void displayBoard(const vector<char>& board);//show����
char winner(const vector<char>& board);//�ж��Ƿ�Ӯ+����
bool isLeagel(const vector<char>& board);//�ж��Ƿ�Ϊ �� ����ʾ��������
int humanMove(const vector<char>& board,char human);//�������λ��
int computerMove(vector<char> board, char computer);//���������λ��  ��1������Ӯ�Ĳ��ԣ�2���ж����Ƿ���Ӯ
void announceWinner(char winner, char computer, char human);//��ս���  �� Ӯ ����
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
	cout << "��ӭʹ���˻���ս��������Ϸ������������0-8�����֣�����������ʾ" << endl;
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
//�淶�û�������
int askNumber(string question, int high, int low ) {
	int number;
	do {
		cout << question << "("<<low<<" - "<<high<<"):";
		cin >> number;
	} while (number >high || number<low);
	return number;
}
char humanPiece() {
	char go_first = askYesNo("���Ƿ�Ҫ��������?");
	if (go_first == 'y') {
		cout << "��Ϸ������ʼ��������������";
		return X;
	}
	else {
		cout << "��Ϸ������ʼ����������������";
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
	int move = askNumber("��������������", (board.size() - 1));
	while (!isLeagel(move, board)) {
		cout << "\n��ѡ��ĵط��Ѿ�������";
		move  = askNumber("��������������", (board.size() - 1));
	}
	return move;
}
int computerMove( vector<char> board, char computer) {
	int move = 0;
	bool found = false;

	//�����һ�ʤ����
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

	//���������Ƿ�Ҫ��ʤ���������Ҫ��ʤ����ֹ��
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
	cout << "�ҽ�����" << move << endl;
	return move;
}
void announceWinner(char winner, char computer, char human) {
	if (winner == computer) {
		cout << "�˻���ս�����Ի�ʤ" << endl;
	}
	else if (winner == human) {
		cout << "�˻���ս����һ�ʤ" << endl;
	}
	else {
		cout << "�˻���ս��˫��ƽ��" << endl;
	}
}
