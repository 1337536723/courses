#pragma once
class Judge {
private:
	int currentchesser;//0�ڷ���1�׷�

public:
	Judge() {
		currentchesser = 1;
	}
	int judgeResult(const int chesspadstate[15][15]);//�жϱ��������0Ϊ��δ���ж�ʤ����1Ϊ�ڷ�ʤ��2Ϊ�׷�ʤ��3Ϊ����

	int  nextChesser() {//��һ������
		if (currentchesser)
			currentchesser = 0;
		else
			currentchesser = 1;
		return currentchesser;
	}
};
