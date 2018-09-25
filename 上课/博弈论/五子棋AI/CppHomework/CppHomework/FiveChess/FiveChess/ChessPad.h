#pragma once
#include "Chess.h"
class ChessPad {
private:
	int lastrow;//��һ��λ�õ� ��
	int lastcolumn;//��һ��λ�õ� ��
	static const int ROWNUM = 15;//��������
	static const int COLUMN = 15;//��������
	int chesspadstate[ROWNUM][COLUMN];//���̱�־
	
public:
	ChessPad() {
		lastrow = 0;
		lastcolumn = 0;
		for (int i = 0;i < ROWNUM;i++)
			for (int j = 0;j < COLUMN;j++)
				chesspadstate[i][j] = 0;
	}
	void addChess(Chess chess);//�������
	void getChessPadState(int chesspadstate[15][15]);//��ȡ����״̬
};
