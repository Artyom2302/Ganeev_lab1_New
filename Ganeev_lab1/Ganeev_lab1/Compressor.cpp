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

void Compressor::Header(ostream&out)
{
	out << setw(10) << "Id " << setw(20) << "��������" << setw(30) << "����� ���������� �����"
		<< setw(30) << "���������� ����� � ������" << setw(20) << "�������������" << endl;
}


double Compressor::PercentOfOutWork() const
{
	double value;
	value = workshops - workshopsinwork;
	value /= workshops;
	return value * 100;
}

void operator<<(ostream& out, const Compressor c)
{
	out << setw(10) << c.id << setw(20) << c.name << setw(30) << c.workshops << setw(30)
		<< c.workshopsinwork << setw(20) << c.performance << endl;
}

void operator>>(istream& in, Compressor& c)
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

}

void Compressor::SaveInfo(unordered_map<int, Compressor>compressors, string filename)
{
	ofstream fout;
	fout.open(filename,ios::app);
	fout << "\n������������� �������\n";
	Header(fout);
	for (auto& c : compressors)
	{
		fout << c.second;
	}
	fout.close();
	
}

void Compressor::SaveBuff(unordered_map<int, Compressor> compressors, string filename)
{
	ofstream fbuff;
	filename += "buff";
	fbuff.open(filename,ios::app);

	for (auto& c : compressors) {
		fbuff << "��\n" << c.second.id << endl << c.second.name << endl << c.second.workshops << endl
			<< c.second.workshopsinwork << endl << c.second.performance << endl;
	}
		
	fbuff.close();
}





void Compressor::LoadInfo(unordered_map<int, Compressor> &compressors, string filename)
{
	string str;
	filename += "buff";
	ifstream in(filename);
	Compressor compressorbuff;
	if (in.is_open()) {
		do
		{
			getline(in, str);

			if (str == "��") {
				in >> compressorbuff;
				compressors.insert({ compressorbuff.id,compressorbuff });

			}
		} while (str != "");
	}
	else {
		cout << "������ ����� �� ����������!!!";
	}
	in.close();

}
