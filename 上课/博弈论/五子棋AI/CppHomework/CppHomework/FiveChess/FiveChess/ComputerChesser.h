#pragma once
#include "Chesser.h"
#include "ArtificialIntelligence.h"

class ComputerChesser :public Chesser {
private:
	ArtificialIntelligence computerai;//�˹�������
public:
	ComputerChesser(int color, std::string name);
	Chess giveNextChess(const int chesspadstate[15][15]);//�����²�����
};
