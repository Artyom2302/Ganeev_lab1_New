#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
class Pipe
{
	static unsigned int  Maxid;

public:
	unsigned int  id;
	string name;
	unsigned int diameter;
	double length;
	bool repair;
	Pipe();
	void Edit();
	void static Header(ostream& out=cout );
	void friend operator << (ostream& out,const Pipe &p);
	friend istream& operator>>(istream& in, Pipe& p);
	friend ifstream& operator>>(ifstream& in, Pipe& p);
	void static SaveBuff(unordered_map <int, Pipe> pipes, string filename);
	void static LoadInfo(unordered_map <int, Pipe> &pipes, string filename);

};

