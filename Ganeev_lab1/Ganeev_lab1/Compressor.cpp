#include "Compressor.h"
Compressor::Compressor() :id(0), name(), workshops(), workshopsinwork(), performance(){
}

Compressor::Compressor(int compressorid):id(compressorid), name(), workshops(), workshopsinwork(), performance() {

	string value;

	cout << " омпрессорна€ станци€\nID є" << id << endl;
	name = EnterName();


	cout << "¬ведите общее количество цехов: ";
	workshops = EnterUInt();

	cout << "¬ведите  количество цехов в работе: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"))
		{
			cout << "¬ведите целочисленное число,не превышающее общее количество цехов!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"));
	workshopsinwork = stoi(value);


	cout << endl << "¬ведите эффективность в %: ";
	do
	{
		getline(cin, value);
		if (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0))
		{
			cout << "¬ведите значение верно !!! Ёффективность:  ";
		}

	} while (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0));
	performance = stod(value);	
}

void Compressor::Edit()
{
	string value;
	cout << "¬ведите новое количество цехов в работе: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"))
		{
			cout << "¬ведите целочисленное число,не превышающее общее количество цехов!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= workshops)) || value == "0"));
	workshopsinwork = stoi(value);

}

void Compressor::Header()
{
	cout << setw(10) << "Id " << setw(20) << "Ќазвание" << setw(30) << "ќбщее количество цехов"
		<< setw(30) << " оличество цехов в работе" << setw(20) << "Ёффективность" << endl;
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




