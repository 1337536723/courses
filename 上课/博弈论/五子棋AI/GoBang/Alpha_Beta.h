#pragma once
#include "parameters.h"
#include <time.h>

class Alpha_Beta
{
private:
	Move * moves[MAX_DEPTH];
	void Alpha_Beta::InBox(RECT_T & rect, Move obj);
	int FindPath(int x,int y);
	ChessMan ChessBoard[MAX_Y + 1][MAX_X + 1];
	bool EmptyMoves();
	bool Inx(int x){return x > 0 && x <= MAX_X;}
	bool Iny(int y){return y > 0 && y <= MAX_Y;}
	RECT_T bound;
	void GetMoves(RECT_T rect, Move * moves,int & ptr);
	int Evaluate(RECT_T rect , int side);//���ۺ���
	int AlphaBeta(int depth, int alpha, int beta,int side, RECT_T rect);//�������,���ϽǺ����½Ƿ�Χ
	void MakeMove(Move mo,int side);
	void UnMakeMove(Move mo);//ˮƽ��

	Move result;
	int Judge(int CountArray[3][2][6],int side);
	int time;
	int time_begin;
	bool TimeOut(){return time <= clock() - time_begin;}
public:

	void SetTime(int t){ time = t;};
	bool IsKill(Move mov,int side);
	Move Search(Move obj);
	Alpha_Beta(void);
	int * * Chess;//����
	~Alpha_Beta(void);
	void Reload();
};
