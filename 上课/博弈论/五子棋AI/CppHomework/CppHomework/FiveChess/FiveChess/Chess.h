#pragma once
class Chess{
private:
	int color;//0�ڣ�1��
	int row;//��
	int column;//��

public:
	Chess(int color, int row, int column) {
		this->color = color;
		this->row = row;
		this->column = column;
	}

	int getColor() {
		return color;
	}

	void getPosition(int &row, int &column) {
		row = this->row;
		column = this->column;
	}

	void setcolor(int color) {
		this->color = color;
	}
	
	void setPosition(int row, int column) {
		this->row = row;
		this->column = column;
	}
};
