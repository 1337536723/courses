#include "PeopleChesser.h"
#include <iostream>
PeopleChesser::PeopleChesser(int color, std::string name) {
	this->color = color;
	this->name = name;
}
Chess PeopleChesser::giveNextChess(const int chesspadstate[15][15]) {
	int x, y;
	char a, b;

	while (1) {
		
		do {
			std::cout << "�������²��壬��H��A��,������HA����(ע���д):";
			std::cin.clear();
			std::cin.sync();
			std::cin >> a;
			std::cin >> b;
		} while (!('A' <= a && a <= 'O') || !('A' <= b && b <= 'O'));//������Ϲ���

		x = a - 'A';//�ж��Ƿ�������
		y = b - 'A';
		if (chesspadstate[x][y]) {//��������
			std::cout << "��λ���Ѿ��������ˣ����±��λ��\n";
			continue;
		}
		else//����
			break;

	}
	return Chess(color, x, y);
}