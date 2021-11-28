#include "Compressor.h"

unsigned int Compressor::maxid = 0;
Compressor::Compressor() :id(++maxid), name(), workshops(), workshopsinwork(), performance(), connectedpipe({}) {
}


void Compressor::Edit()
{
	string value;
	cout << "������� ����� ���������� ����� � ������: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"))
		{
			cout << "������� ������������� �����,�� ����������� ����� ���������� �����!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"));
	workshopsinwork = stoi(value);

}

void Compressor::Header(ostream&out)
{
	out << setw(10) << "Id " << setw(20) << "��������" << setw(30) << "����� ���������� �����"
		<< setw(30) << "���������� ����� � ������" << setw(20) << "�������������" << endl;
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









