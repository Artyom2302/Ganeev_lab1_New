#pragma once
#include "main.h"
using namespace std;
class Compressor {
public:
	unsigned int id = 0;
	string name;
	unsigned int workshops = 0;//����
	unsigned int workshopsinwork = 0;//���� � ������
	double performance = 0;//�������������
	

	Compressor();
	Compressor(int compressorid);
	void Edit();
	void static Header();
	void OutInfo();
	double static PercentOfOutWork(Compressor c);
	
};