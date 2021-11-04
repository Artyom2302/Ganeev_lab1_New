#include "Pipe.h"

Pipe::Pipe():id(0),name(""),length(0),diameter(0),repair(0)
{
}

Pipe::Pipe(int pipeid) :id(pipeid),name(),length(), diameter(),repair()
{
	string value1;
	cout << "Труба\nID №" << id << endl;
	name = EnterName();
	cout << "Введите длину: ";
	length = EnterUDouble();
	cout << endl << "Введите диаметр: ";
	diameter = EnterUInt();
	cout << endl << "Введите 1,если труба в ремонте и 0,если в эксплуатации \n";
	repair = EnterBool();

}

void Pipe::Edit()
{
	repair = !repair;
}

void Pipe::Header() {
	cout << setw(10) << "Id " << setw(20) << "Название" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(40) << "Состояние(В ремонте или нет)\n";
}


void Pipe::OutInfo()
{
	cout << setw(10) << id << setw(20) << name << setw(20) << length << setw(20) << diameter
		<< setw(40) << ((repair) ? "В ремонте\n" : "В эксплуатации\n");
}
