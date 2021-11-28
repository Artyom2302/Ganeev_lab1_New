#include "Compressor.h"

unsigned int Compressor::maxid = 0;
Compressor::Compressor() :id(++maxid), name(), workshops(), workshopsinwork(), performance(), connectedpipe({}) {
}


void Compressor::Edit()
{
	string value;
	cout << "Введите новое количество цехов в работе: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"))
		{
			cout << "Введите целочисленное число,не превышающее общее количество цехов!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"));
	workshopsinwork = stoi(value);

}

void Compressor::Header(ostream&out)
{
	out << setw(10) << "Id " << setw(20) << "Название" << setw(30) << "Общее количество цехов"
		<< setw(30) << "Количество цехов в работе" << setw(20) << "Эффективность" << endl;
}

void Compressor::nullmaxid()
{
	maxid = 0;
}


double Compressor::PercentOfOutWork() const
{
	double value;
	value = workshops - workshopsinwork;
	value /= workshops;
	return value * 100;
}

ostream& operator<<(ostream& out, const Compressor c)
{
	out << setw(10) << c.id << setw(20) << c.name << setw(30) << c.workshops << setw(30)
		<< c.workshopsinwork << setw(20) << c.performance << endl;
	return out;
}

ifstream& operator >>(ifstream& in, Compressor& c)
{
	string str;
	getline(in, str);
	c.id = stoi(str);
	getline(in, str);
	c.name = str;
	getline(in, str);
	c.workshops = stoi(str);
	getline(in, str);
	c.workshopsinwork = stoi(str);
	getline(in, str);
	c.performance = stod(str);
	return in;
}









