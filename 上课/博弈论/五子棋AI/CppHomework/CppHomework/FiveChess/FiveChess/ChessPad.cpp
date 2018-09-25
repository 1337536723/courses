#include "ChessPad.h"

void ChessPad::addChess(Chess chess) {

	if (chesspadstate[lastrow][lastcolumn])//������
		chesspadstate[lastrow][lastcolumn] -= 2;//�������һ����

	chess.getPosition(lastrow, lastcolumn);//�����������һ����¼

	if (chess.getColor())//1����
		chesspadstate[lastrow][lastcolumn] = 4;
	else//����
		chesspadstate[lastrow][lastcolumn] = 3;

}

void ChessPad::getChessPadState(int chesspadstate[ROWNUM][COLUMN]) {
	for (int i = 0;i < ROWNUM;i++)
		for (int j = 0;j < COLUMN;j++)
			chesspadstate[i][j] = this->chesspadstate[i][j];
}