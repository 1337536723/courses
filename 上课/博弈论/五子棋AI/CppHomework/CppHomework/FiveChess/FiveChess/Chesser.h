#pragma once
#include <string>
#include "Chess.h"
class Chesser {
protected:
	int color;//0�ڷ���1�׷�
	std::string name;//����
public:
	virtual Chess giveNextChess(const int chesspadstate[15][15]) = 0;//���麯��
	std::string getName() {
		return name;
	}
};

