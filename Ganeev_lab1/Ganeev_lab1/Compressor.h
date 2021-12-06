#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "EnterValue.h"
#include <set>
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
	
	void Edit();
	double PercentOfOutWork() const;
	void static Header(ostream& out = cout);
	friend ostream& operator<<(ostream& out, const Compressor c);
	friend ifstream& operator >>(ifstream& in, Compressor& c);
	friend istream& operator >>(istream& in, Compressor& c);
	void static nullmaxid();
};