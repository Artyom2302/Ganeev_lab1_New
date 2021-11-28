#include "Pipe.h"

unsigned int Pipe::Maxid = 0;

Pipe::Pipe():id(++Maxid),name(""),length(0),diameter(0),repair(0)
{
}


void Pipe::Edit()
{
	repair = !repair;
}

void Pipe::Header(ostream &out) {
	out << setw(10) << "Id " << setw(20) << "Название" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(40) << "Состояние(В ремонте или нет)\n";
}
void Pipe::nullmaxid()
{
	Maxid = 0;
}
void operator<<(ostream& out, const Pipe& p)
{
	out << setw(10) << p.id << setw(20) << p.name << setw(20) << p.length << setw(20) << p.diameter
		<< setw(40) << ((p.repair) ? "В ремонте\n" : "В эксплуатации\n");
}

ifstream& operator>>(ifstream& in, Pipe& p)
{
	string str;
	getline(in, str);
	p.id = stoi(str);

	getline(in, str);
	p.name = str;

	getline(in, str);
	p.length = stof(str);

	getline(in, str);
	p.diameter = stoi(str);

	getline(in, str);
	p.repair = stoi(str);
	return in;
}







