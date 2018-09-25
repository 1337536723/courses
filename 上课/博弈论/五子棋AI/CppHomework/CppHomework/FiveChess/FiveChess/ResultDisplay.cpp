#include "ResultDisplay.h"
using namespace std;

void ResultDisplay::display(string msg) {
	int initstate[15][15] = { 0 };
	display(initstate, msg);
}

void ResultDisplay::display(const int chesspadstate[15][15], string msg) {
	system("cls");//������
	cout << rowAcolumn << endl;//�к�
	for (int row = 0;row < 15;row++) {//��row��
		cout << rowAcolumn.at((row + 1) * 2 + 1) << " ";//�к�
		for (int column = 0;column < 15;column++) {//��column��
			switch (chesspadstate[row][column]) {
				case 0://�հ�
					cout << chesspadsymbol.at((row * 15 + column) * 2) 
						<< chesspadsymbol.at((row * 15 + column) * 2 + 1);//unicode 2���ֽ�
					break;
				case 1://����
					cout << "��";
					break;
				case 2://����
					cout << "��";
					break;
				case 3://����(���һ��)
					cout << "��";
					break;
				case 4://����(���һ��)
					cout << "��";
					break;
				default:
					//��������Ӵ���
					break;
			}
		}
		cout << endl;
	}
	cout << msg;
}