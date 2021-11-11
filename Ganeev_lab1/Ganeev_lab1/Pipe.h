#pragma once
#include "main.h"
using namespace std;
class Pipe
{
	static unsigned int  maxid;

public:
	unsigned int  id;
	string name;
	unsigned int diameter;
	double length;
	bool repair;

	Pipe();
	Pipe(int id);
	void Edit();
	void static Header();
	void OutInfo();
};

