#include "ComputerChesser.h"


ComputerChesser::ComputerChesser(int color, std::string name) {
	this->color = color;
	this->name = name;
}
Chess ComputerChesser::giveNextChess(const int chesspadstate[15][15]) {
	Position position;

	position = computerai.getPosition(chesspadstate, color);//����λ��

	return Chess(color, position.x, position.y);//�������Ӷ���
}