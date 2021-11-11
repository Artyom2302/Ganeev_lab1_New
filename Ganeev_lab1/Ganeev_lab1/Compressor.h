#pragma once
#include "main.h"
using namespace std;
class Compressor {
	static unsigned int  maxid;

public:
	unsigned int id;
	string name;
	unsigned int workshops ;
	unsigned int workshopsinwork;
	double performance ;
	

	Compressor();
	Compressor(int compressorid);
	void Edit();
	void static Header();
	void OutInfo();
	double PercentOfOutWork() const;
	
};