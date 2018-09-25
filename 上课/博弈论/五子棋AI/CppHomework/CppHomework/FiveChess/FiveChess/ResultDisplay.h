#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
class ResultDisplay{
private:
	std::string rowAcolumn;
	std::string chesspadsymbol;

public:
	ResultDisplay() {
		rowAcolumn = "   A B C D E F G H I J K L M N O";
		chesspadsymbol =	"���ЩЩЩЩЩЩЩЩЩЩЩЩЩ�"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"�����������������"
							"���ةةةةةةةةةةةةة�";
	}
	void display(const int chesspadstate[15][15], std::string msg);//ˢ����ʾ����
	void display(std::string msg);//��û��ʼ���壬��ʾ��Ϣ���

};
