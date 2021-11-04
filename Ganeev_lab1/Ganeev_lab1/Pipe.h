#pragma once
#include "main.h"
using namespace std;
class Pipe
{	public:
	unsigned int id;
	string name;
	unsigned int diameter;
	double length;
	bool repair;
	Pipe();
	bool GetPipeStatus();
	Pipe(int id);
	void EditPipe();
	void static HeaderPipe();
	void OutInfo();
};

