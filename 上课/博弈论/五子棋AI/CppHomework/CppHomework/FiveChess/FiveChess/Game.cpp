#include "Game.h"
#include <iostream>
using namespace std;

void Game::chooseMode() {
	//ѡ��ģʽ
	do {
		resultdisplay.display("ѡ�����ģʽ0Ϊ�˻����ģ�1Ϊ���˶��ģ�");
		cin.clear();
		cin.sync();//VS2015������ջ�������vs2012���ԣ�����
		cin >> mode;
	} while (2 <= mode || mode < 0);
}

void Game::initOrder() {
	//��ʼ��
	do {//ѡ��˳��
		resultdisplay.display("��������������0��������������1��");
		cin.clear();
		cin.sync();//VS2015������ջ�������vs2012���ԣ�����
		cin >> first;
	} while (2 <= first || first < 0);
}
void Game::initOrderAName() {
	
	if (mode) {//����ģʽ
			   //��ʼ��
		resultdisplay.display("������ڷ����ֵ����֣�Ĭ�Ϻڷ����£���");
		cin.clear();
		cin.sync();//VS2015������ջ�������vs2012����
		getline(cin,blackname);
		resultdisplay.display("������׷����ֵ����֣�Ĭ�Ϻڷ����£���");
		cin.clear();
		cin.sync();//VS2015������ջ�������vs2012����
		getline(cin,whitename);
	}
	else {//�˻�ģʽ
		initOrder();//ѡ��˳��
		if (first) {
			blackname = "�û�";
			whitename = "����";
		}
		else {
			blackname = "����";
			whitename = "�û�";
		}
	}
}

void Game::initGame(){
	chooseMode();//ѡ��ģʽ
	initOrderAName();//ѡ������˳��ͳ�ʼ������
}

void Game::startGame() {
	if (mode) {//����ģʽ
		
		//��ʼ��ѡ��
		PeopleChesser black(0, blackname);
		PeopleChesser white(1, whitename);
		//����
		playchess(black, white, judge, chesspad, resultdisplay);
	}
	else {//�˻�
		if (first) {//��������
			
			//��ʼ��ѡ��
			ComputerChesser white(1, "����");
			PeopleChesser black(0, "�û�");
			//����
			playchess(black, white, judge, chesspad, resultdisplay);
		}
		else {//��������
			
			//��ʼ��ѡ��
			ComputerChesser black(0, "����");
			PeopleChesser white(1, "�û�");
			//����
			playchess(black, white, judge, chesspad, resultdisplay);
		}
	}
}

void Game::playchess(Chesser &black, Chesser &white, Judge &judge, ChessPad &chesspad, ResultDisplay &resultdisplay) {
	int result;
	int state[15][15] = { 0 };
	//����׶�
	while (!(result = judge.judgeResult(state))) {
		if (judge.nextChesser()) {
			resultdisplay.display(state, "�׷���" + white.getName() + "\n");
			chesspad.addChess(white.giveNextChess(state));
		}
		else {
			resultdisplay.display(state, "�ڷ���" + black.getName() + "\n");
			chesspad.addChess(black.giveNextChess(state));
		}
		chesspad.getChessPadState(state);
	}
	//�����
	switch (result) {
	case 1:
		resultdisplay.display(state, "�ڷ�:" + black.getName() + "ʤ\n��e���˳�");
		break;
	case 2:
		resultdisplay.display(state, "�׷�:" + white.getName() + "ʤ\n��e���˳�");
		break;
	case 3:
		resultdisplay.display(state, "���ֽ��������Ǵ�ƽ\n��e���˳�");
		break;
	default:
		//������
		break;
	}
	//�˳�
	char exit;
	do {
		cin.clear();
		cin.sync();
		cin >> exit;
	} while (exit != 'e' && exit != 'E');
}
