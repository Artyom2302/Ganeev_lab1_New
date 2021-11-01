#include <iostream>//in out �����
#include <vector>//������ � ������������� ���������
#include <sstream>// ��� ������ �� �������� getline()
#include <clocale>// ��� �������� �����
#include  <conio.h>// ��� ����� � ���������� _getch()
#include <cstring> //
#include <iomanip>//��������������� �����
#include <fstream>
#include <cstdlib>// rand
#include <windows.h>
#include <unordered_map>



using namespace std;

//C������� ��������� �����
struct pipe {
	unsigned int id;
	string name;
	unsigned int diameter;
	double length;
	bool repair;
};
//C������� ��������� ������������� �������
struct compressor {
	unsigned int id = 0;
	string name;
	unsigned int workshops = 0;//����
	unsigned int workshopsinwork = 0;//���� � ������
	double performance = 0;//�������������
};






//������� ��������
bool CheckInt(string s) {
	if (!((s.size() != 0) && (s[0] != '0')))
		return false;

	for (size_t i = 0; i < s.size(); i++)
		if (!isdigit(s[i]))
			return false;

	return true;
}
bool CheckDouble(string s) {
	if (s.size() == 0) {
		return false;
	}
	int tochka = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '.') {//�������� �� �����
			tochka += 1;
		}
		if (tochka > 1) {// ������� ���� ����� ������ �����
			return false;
		}
		if (!(isdigit(s[i]) || (s[i] == '.')))
			return false;
	}
	return true;
}
bool CheckAllSpace(string s) {
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			return false;
		}
	}
	return true;
}
//����� ������� ��������
void Seporator(ostream& out = cout) {
	for (size_t i = 0; i < 25; i++)
	{
		out << "----";
	}
	out << endl;
}

char EnterChoice() {
	char choice;
	do
	{
		choice = _getch();
		if (choice != '1' && choice != '2')
			cout << "������� ������ �������\n";
	} while (choice != '1' && choice != '2');
	return choice;
}
string EnterName() {
	string name;
	cout << "������� ��������: ";
	do {
		getline(cin, name);
	} while (name == "" || CheckAllSpace(name));
	return name;
}

double EnterUDouble() {
	string value;
	do {
		getline(cin, value);
		if (!(CheckDouble(value))) {

			cout << "�������� ������� �������\n������� ��� ���: ";
		}
	} while (!(CheckDouble(value)));
	return stod(value);
}
int EnterUInt() {
	string value;
	do
	{
		getline(cin, value);
		if (!(CheckInt(value))) {
			cout << "������� ������������� ��������: ";
		}

	} while (!(CheckInt(value)));
	return stoi(value);
}
int RandomId() {
	return rand();
}






void MainMenu()
{
	cout << endl << "1. �������� �����" << endl <<
		"2. �������� ��" << endl <<
		"3. �������� ���� ��������" << endl <<
		"4. ������������� �����" << endl <<
		"5. ������������� ��" << endl <<
		"6. ���������" << endl <<
		"7. ���������" << endl <<
		"8. ����� ����" << endl <<
		"9. ����� ��" << endl <<
		"0. �����" << endl <<
		"������� ����� ����: " << endl;
}

bool GetPipeStatus() {
	char x,status;
	cout << "������� 1,���� � �������   ���   0,���� � ������������\n";
	do
	{
		x = _getch();
		if (x != '0' && x != '1') { cout << "������� ������� �����!!!\n"; }
	} while (x != '1' && x != '0');
	x == '1' ? status = 1 : status = 0;
	return status;
}
pipe AddPipe(int id)
{
	string value1;
	int key;
	pipe p;

	p.id = id;

	cout << "�����\nID �" << p.id << endl;
	p.name = EnterName();
	cout << "������� �����: ";

	p.length = EnterUDouble();


	cout << endl << "������� �������: ";

	p.diameter = EnterUInt();


	p.repair = GetPipeStatus();

	

	return p;

}

compressor AddCompressor(int id)
{
	compressor comp;
	string value;
	comp.id = id;

	cout << "������������� �������\nID �" << comp.id<<endl;
	comp.name = EnterName();


	cout << "������� ����� ���������� �����: ";
	comp.workshops = EnterUInt();

	cout << "�������  ���������� ����� � ������: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"))
		{
			cout << "������� ������������� �����,�� ����������� ����� ���������� �����!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"));
	comp.workshopsinwork = stoi(value);


	cout << endl << "������� ������������� � %: ";
	do
	{
		getline(cin, value);
		if (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0))
		{
			cout << "������� �������� ����� !!! �������������:  ";
		}

	} while (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0));
	comp.performance = stod(value);
	return comp;
}

double PercentOfCompressorsOutWork(compressor c) {
	double value;
	value = c.workshops - c.workshopsinwork;
	value /= c.workshops;
	return value * 100;
}

void OutInfo(const pipe& p) {
	cout << setw(10) << p.id << setw(20) << p.name << setw(20) << p.length << setw(20) << p.diameter
		<< setw(40) << ((p.repair) ? "� �������\n" : "� ������������\n");
}
void OutInfo(const compressor& comp) {
	cout << setw(10) << comp.id << setw(20) << comp.name << setw(30) << comp.workshops << setw(30)
		<< comp.workshopsinwork << setw(20) << comp.performance << endl;
}
void HeaderPipe() {
	cout << setw(10) << "Id " << setw(20) << "��������" << setw(20) << "�����" << setw(20) << "�������" << setw(40) << "���������(� ������� ��� ���)\n";
}
void HeaderCompressor() {
	cout << setw(10) << "Id " << setw(20) << "��������" << setw(30) << "����� ���������� �����"
		<< setw(30) << "���������� ����� � ������" << setw(20) << "�������������" << endl;
}

void EditPipe(pipe& p) {
	p.repair = !p.repair;
}

void EditCompressor(compressor& comp) {
	string value;
	cout << "������� ����� ���������� ����� � ������: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"))
		{
			cout << "������� ������������� �����,�� ����������� ����� ���������� �����!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"));
	comp.workshopsinwork = stoi(value);
}
void SaveBuff(const unordered_map <int, pipe>& pipes, const unordered_map <int, compressor>& compressors, string filename) {
	ofstream fbuff;
	filename += "buff";
	fbuff.open(filename);
	for (auto& p : pipes)
		fbuff << "�����\n" << p.second.id << endl << p.second.name << endl << p.second.length << endl << p.second.diameter << endl << p.second.repair << endl;
	for (auto& c : compressors)
		fbuff << "��\n" << c.second.id << endl << c.second.name << endl << c.second.workshops << endl
		<< c.second.workshopsinwork << endl << c.second.performance << endl;
	fbuff.close();
}


void SaveInfo(const unordered_map <int, pipe>& pipes, const unordered_map <int, compressor>& compressors, string filename) {
	ofstream fout;
	fout.open(filename);
	fout << "����� ����������\n";
	fout << "�����\n";
	fout << setw(10) << "Id " << setw(20) << "���" << setw(20) << "�����" << setw(20) << "�������" << setw(40) << "���������(� ������� ��� ���)\n";
	for (auto& p : pipes)
	{
		fout << setw(10) << p.second.id << setw(20) << p.second.name << setw(20) << p.second.length << setw(20) << p.second.diameter;
		if (p.second.repair) {
			fout << setw(40) << "� �������\n";
		}
		else
		{
			fout << setw(40) << "� ������������\n";
		}

	}

	fout << "\n������������� �������\n";
	fout << setw(10) << "Id " << setw(20) << "��������" << setw(30) << "����� ���������� �����"
		<< setw(30) << "���������� ����� � ������" << setw(20) << "�������������" << endl;
	for (auto& c : compressors)
	{
		fout << setw(10) << c.second.id << setw(20) << c.second.name << setw(30) << c.second.workshops << setw(30)
			<< c.second.workshopsinwork << setw(20) << c.second.performance << endl;
	}
	fout.close();

}
void LoadInfo(unordered_map <int, pipe>& pipes, unordered_map <int, compressor>& compressors, string filename) {
	string str;
	filename += "buff";
	ifstream in(filename);
	pipe pipebuff;
	compressor compressorbuff;
	if (in.is_open()) {
		do
		{
			getline(in, str);
			if (str == "�����") {

				getline(in, str);
				pipebuff.id = stoi(str);

				getline(in, str);
				pipebuff.name = str;

				getline(in, str);
				pipebuff.length = stof(str);

				getline(in, str);
				pipebuff.diameter = stoi(str);

				getline(in, str);
				pipebuff.repair = stoi(str);
				pipes.insert({ pipebuff.id,pipebuff });
			}
			else if (str == "��") {//else
				getline(in, str);
				compressorbuff.id = stoi(str);
				getline(in, str);
				compressorbuff.name = str;
				getline(in, str);
				compressorbuff.workshops = stoi(str);
				getline(in, str);
				compressorbuff.workshopsinwork = stoi(str);
				getline(in, str);
				compressorbuff.performance = stod(str);
				compressors.insert({ compressorbuff.id,compressorbuff });

			}
		} while (str != "");
	}
	else {
		cout << "������ ����� �� ����������!!!";
	}

	in.close();
};

template<typename T_param>
using PipeFilter = bool(*)(const  pipe& p, T_param param);

bool CheckByName(const pipe& p,string name ) {
	return p.name == name;
}
bool CheckByRepair(const pipe& p, bool repair) {
	return p.repair == repair;
}

template<typename T_param>
using CompressorFilter = bool(*)(const  compressor& c, T_param param);
bool CheckByName(const compressor& c, string name) {
	return c.name == name;
}

bool CheckByWorkshopsOutWork(const compressor& c, pair	<double,double> border) {
	int percentoutwork;
	percentoutwork = PercentOfCompressorsOutWork(c);
	return (percentoutwork >= border.first) && (percentoutwork <=border.second);
}


template<typename T_param>
vector <int> FindPipeByFilter(const unordered_map <int, pipe> &pipes, PipeFilter<T_param> f, T_param parametr) {
	vector <int> id;
		for (auto& p : pipes) {
			if (f(p.second, parametr)) {
				id.push_back(p.first);
			};
		}
	return id;
}

template<typename T_param>
vector <int> FindCompressorByFilter(const unordered_map <int, compressor> &compressors, CompressorFilter<T_param> f, T_param parametr) {
	vector <int> id;
	for (auto& c : compressors) {
		if (f(c.second, parametr)) {
			id.push_back(c.first);
		};
	}
	return id;
}


vector <int> SearchCompressors(unordered_map <int, compressor> compressors,string parametr) {
	string name;
	int min=0,max=100;
	vector <int> id;
	double percentoutwork;
	if (parametr == "name")
	{
		name = EnterName();
		for (auto& c : compressors) {
			if (c.second.name == name) {

				id.push_back(c.first);
			}
		}
		return id;
	}
	if (parametr == "unworkpercent") {
		cout << "������� �������� � ��������� ����������������� �����\n";
		do
		{
			cout << "min: ";
			min = EnterUDouble();
			cout << "max: ";
			max = EnterUDouble();
			if ((min > max) &&((min>=0)&&(min<=100))&&((max>=0)&&(max<=100)))
				cout << "����������� ������ ���� ������ ��� ������������ � ��� ������ ���� �� 0 �� 100\n";
		} while (min>max);
		for (auto& c : compressors) {
			percentoutwork = PercentOfCompressorsOutWork(c.second);
			if (percentoutwork>=min && percentoutwork <=max)
			{
				id.push_back(c.first);
			}
		}

		return id;
		}
	return {};
	}
		

			
	



int main() {
	setlocale(LC_CTYPE, "Russian");
	vector <pipe> pipes;
	vector <compressor> compressors;
	int compressorsid = 0, pipesid = 0;
	unordered_map <int, pipe> pipesmap;
	unordered_map <int, compressor> compressorsmap;
	while (true)
	{
		MainMenu();
		switch (EnterUInt())
		{
		case 1:
		{
			pipesid += 1;
			pipe p = AddPipe(pipesid);
			pipesmap.insert({ p.id, p });
			cout << "������� ����� �� ���������� ����������������:\n";
			HeaderPipe();
			OutInfo(p);
			break;
		}

		case 2: {
			compressorsid += 1;
			compressor comp = AddCompressor(compressorsid);
			compressorsmap.insert({ compressorsid,comp });
			cout << "������� ������������� ������� �� ���������� ����������������:\n";
			HeaderCompressor();
			OutInfo(comp);
			break;
		}
		case 3:
			Seporator();
			if (pipesmap.size() != 0)
			{
				cout << "�����\n";
				HeaderPipe();
				for (auto& p : pipesmap)
				{
					OutInfo(p.second);
				}
			}
			else
			{
				cout << "��� �� ����� �����\n";
			}
			Seporator();

			if (compressorsmap.size() != 0) {
				cout << "������������� �������\n";
				HeaderCompressor();
				for (auto& c : compressorsmap)
				{
					OutInfo(c.second);
				}
			}
			else
			{
				cout << "��� �� ����� ������������� �������\n";
			}
			Seporator();
			break;

		case 4:
			if (pipesmap.size() == 0)
			{
				cout << "��� �� ����� �����\n";
			}
			else {
				auto pipeid = 0u;
				do
				{
					cout << "������� c����������� id: ";
					pipeid = EnterUInt();
				} while (pipesmap.find(pipeid) == pipesmap.end());
				cout << (pipesmap[pipeid].repair ? "\n����� � �������\n" : "\n����� � ������������\n");//�������� �������
				cout << "��� ��������� ������� ����� �������\n";
				_getch();
				EditPipe(pipesmap[pipeid]);
			}
			break;

		case 5:
			if (compressors.size() == 0)
			{
				cout << "��� �� ����� ������������� �������\n";
			}
			else {

				unsigned int compressorid = 0;
				do
				{
					cout << "������� c����������� id: ";
					compressorid = EnterUInt();
				} while (compressorsmap.find(compressorid) == compressorsmap.end());
				EditCompressor(compressors[compressorid]);
			}

			break;

		case 6: {
			cout << "����� ����� ��� ����������\n";
			string filename = EnterName();
			SaveInfo(pipesmap, compressorsmap, filename);
			SaveBuff(pipesmap, compressorsmap, filename);
			break;
		}
		case 7: {
			cout << "����� ����� ��� ��������\n";
			string filename = EnterName();
			pipesmap.clear();
			compressorsmap.clear();
			LoadInfo(pipesmap, compressorsmap, filename);
			break; }

		case 8:
		{
		cout << "������� 1,���� ����� ����� �� �������� ��� 2,���� �� ��������"<<endl;
		char choice = EnterChoice();
			vector <int> id ;
			if (choice == '1') {
				id = {};
				string name = EnterName();
				id = FindPipeByFilter(pipesmap,CheckByName,name);
				if (id.size() != 0) {
					HeaderPipe();
					for (int i = 0; i < id.size(); ++i) {
						OutInfo(pipesmap[id[i]]);
					}
					

				}
				else {
					cout << "�� ������� ������� ������ �� �������";
				}

			}
			else if (choice == '2') {
				id = {};
				bool repair = GetPipeStatus();
				id = FindPipeByFilter(pipesmap, CheckByRepair, repair);
				if (id.size() != 0) {
					HeaderPipe();

					for (int i = 0; i < id.size(); ++i) {
						OutInfo(pipesmap[id[i]]);
					}
					cout << "������� 1,����� ����� � 2,����� ���������������  �����\n";
					choice = EnterChoice();
					if (choice == '1') {
						break;
					}
					else if(choice=='2')
					{
						for (int i = 0; i < id.size(); ++i) {
							EditPipe(pipesmap[id[i]]);
						}
					}
				}
				else {
					cout << "�� ������� ������� ������ �� �������\n";
				}

			}
	

			break;

		}


		break;
		case 9:
		{
		cout << "������� 1,���� ����� ����� �� �������� ��� 2,���� �� �������� ����������������� �����" << endl;
		char choice = EnterChoice();
		
	
		vector <int> id;
		if (choice == '1') {

			string name = EnterName();
			id = FindCompressorByFilter(compressorsmap, CheckByName, name);
			if (id.size() != 0) {
				HeaderCompressor();
				for (int i = 0; i < id.size(); ++i) {
					OutInfo(compressorsmap[id[i]]);
				}
			}
			else {
				cout << "�� ������� ������� ������ �� �������";
			}

		}
		else if (choice == '2') {
			int min, max;
			cout << "������� �������� � ��������� ����������������� �����\n";
			do
			{
				cout << "min: ";
				min = EnterUDouble();
				cout << "max: ";
				max = EnterUDouble();
				if ((min > max) && ((min >= 0) && (min <= 100)) && ((max >= 0) && (max <= 100)))
					cout << "����������� ������ ���� ������ ��� ������������ � ��� ������ ���� �� 0 �� 100\n";
			} while (min > max);


			pair <double,double> border;
			border.first = min;
			border.second = max;
	

			id = FindCompressorByFilter(compressorsmap, CheckByWorkshopsOutWork, border);


			if (id.size() != 0) {
				HeaderCompressor();
				for (int i = 0; i < id.size(); ++i) {
					OutInfo(compressorsmap[id[i]]);
				}

				cout << "������� 1,����� ����� � 2,����� ���������������  ������������� �������\n";
				choice = EnterChoice();
				if (choice == '1') {
					break;
				}
				else if (choice == '2')
				{
					for (int i = 0; i < id.size(); ++i) {
						EditCompressor(compressorsmap[id[i]]);
					}
				}
			}
			else {
				cout << "�� ������� ������� ������ �� �������";
			}
		}
		
		break;
		}
		
		case 0:
			return 0;

		default:
			break;
		}

	}

	return 0;

}
