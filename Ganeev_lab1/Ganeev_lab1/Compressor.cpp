#include "Compressor.h"
Compressor::Compressor() :id(0), name(), workshops(), workshopsinwork(), performance(){
}

Compressor::Compressor(int compressorid):id(compressorid), name(), workshops(), workshopsinwork(), performance() {

	string value;

	cout << "������������� �������\nID �" << id << endl;
	name = EnterName();


	cout << "������� ����� ���������� �����: ";
	workshops = EnterUInt();

	cout << "�������  ���������� ����� � ������: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"))
		{
			cout << "������� ������������� �����,�� ����������� ����� ���������� �����!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"));
	workshopsinwork = stoi(value);


	cout << endl << "������� ������������� � %: ";
	do
	{
		getline(cin, value);
		if (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0))
		{
			cout << "������� �������� ����� !!! �������������:  ";
		}

	} while (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0));
	performance = stod(value);	
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

void Compressor::Header()
{
	cout << setw(10) << "Id " << setw(20) << "��������" << setw(30) << "����� ���������� �����"
		<< setw(30) << "���������� ����� � ������" << setw(20) << "�������������" << endl;
}

void Compressor::OutInfo()
{
	cout << setw(10) << id << setw(20) << name << setw(30) << workshops << setw(30)
		<< workshopsinwork << setw(20) << performance << endl;
}

double Compressor::PercentOfOutWork() const
{
	double value;
	value = workshops - workshopsinwork;
	value /= workshops;
	return value * 100;
}




