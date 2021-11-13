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
	void static Header(ostream& out=cout );
	void friend operator << (ostream& out,const Pipe &p);
	void friend operator >>(istream& in, Pipe& p);
	void static SaveInfo(unordered_map <int, Pipe> pipes, string filename);
	void static SaveBuff(unordered_map <int, Pipe> pipes, string filename);
	void static LoadInfo(unordered_map <int, Pipe> &pipes, string filename);

};

