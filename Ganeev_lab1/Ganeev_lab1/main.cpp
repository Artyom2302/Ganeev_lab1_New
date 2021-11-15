#include "main.h"




using namespace std;


void Seporator(ostream& out = cout) {
	for (size_t i = 0; i < 25; i++)
	{
		out << "----";
	}
	out << endl;
}



int RandomId() {
	return rand();
}
istream& operator>>(istream& in, Compressor& c)
{
	string value;
	cout << "������������� �������\nID �" << c.id << endl;
	c.name = EnterName();


	cout << "������� ����� ���������� �����: ";
	c.workshops = EnterUInt();

	cout << "�������  ���������� ����� � ������: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= c.workshops)) || value == "0"))
		{
			cout << "������� ������������� �����,�� ����������� ����� ���������� �����!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= c.workshops)) || value == "0"));
	c.workshopsinwork = stoi(value);


	cout << endl << "������� ������������� � %: ";
	do
	{
		getline(cin, value);
		if (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0))
		{
			cout << "������� �������� ����� !!! �������������:  ";
		}

	} while (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0));
	c.performance = stod(value);
	return in;
}

istream& operator >>(istream& in, Pipe& p)
{
	string value1;
	cout << "�����\nID �" << p.id << endl;
	p.name = EnterName();
	cout << "������� �����: ";
	p.length = EnterUDouble();
	cout << endl << "������� �������: ";
	p.diameter = EnterUInt();
	cout << endl << "������� 1,���� ����� � ������� � 0,���� � ������������ \n";
	p.repair = EnterBool();
	return in;
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
		"10.��������  ���� " << endl <<
		"11.��������  �� " << endl <<
		"12.����� �� ������ " << endl <<
		"13.�����" << endl <<
		"������� ����� ����: " << endl;
}



template<typename T_param>
using PipeFilter = bool(*)(const  Pipe& p, T_param param);
bool CheckById(const Pipe&p,int pipeid) {
	return p.id == pipeid;
}

bool CheckByName(const Pipe& p,string name ) {
	return p.name == name;
}
bool CheckByRepair(const Pipe& p, bool repair) {
	return p.repair == repair;
}

template<typename T_param>
vector <int> FindPipeByFilter(const unordered_map <int, Pipe>& pipes, PipeFilter<T_param> f, T_param parametr) {
	vector <int> id;
	for (auto& p : pipes) {
		if (f(p.second, parametr)) {
			id.push_back(p.first);
		};
	}
	return id;
}

template<typename T_param>
using CompressorFilter = bool(*)(const  Compressor& c, T_param param);
bool CheckById(const Compressor& c, int compressorId) {
	return c.id==compressorId;
}

bool CheckByName(const Compressor& c, string name) {
	return c.name == name;
}

bool CheckByWorkshopsOutWork(const Compressor& c, pair	<double,double> border) {
	double percentoutwork = c.PercentOfOutWork();
	return (percentoutwork >= border.first) && (percentoutwork <=border.second);
}




template<typename T_param>
vector <int> FindCompressorByFilter(const unordered_map <int, Compressor> &compressors, CompressorFilter<T_param> f, T_param parametr) {
	vector <int> id;
	for (auto& c : compressors) {
		if (f(c.second, parametr)) {
			id.push_back(c.first);
		};
	}
	return id;
}


vector <int> EnterIDs(const unordered_map <int, Pipe>& pipesmap) {
	vector <int> IDs;
	do
	{
		cout <<"������� Id: \n";
		int id = EnterUInt();
		if (FindPipeByFilter(pipesmap, CheckById, id).size()==0)
		{
			cout << "T���� c ������ id ����(���������� ������ id)\n";
		}
		else
		{	for (auto ID:IDs)
				if (id==ID)	
				{
				cout<<"�� ��� ������� ������ id,���������� ������ \n";
				id = 0;
				}
		if (id!=0)
		IDs.push_back(id);
		}
			
		cout << " ���������� ���� ID?(1-�� |0-��� )\n";

	} while (EnterBool() &&	IDs.size()!=pipesmap.size());
	return IDs;
}

vector <int> EnterIDs(const unordered_map <int, Compressor>& compressorsmap) {
	vector <int> IDs;
	
	do
	{
		cout << "������� Id: \n";
		int id = EnterUInt();
		if (FindCompressorByFilter(compressorsmap, CheckById, id).size() == 0)
		{
			cout << "�� c ������ id ����(���������� ������ id)\n";
		}
		else
		{
			for (auto ID : IDs)
				if (id == ID)
				{
					cout << "�� ��� ������� ������ id,���������� ������ \n";
					id = 0;
				}
			if (id != 0)
				IDs.push_back(id);


		}

		cout << " ���������� ���� ID?(1-�� |0-��� )\n";
	} while (EnterBool());
	return IDs;
}

void ShowAllPipes(const unordered_map <int, Pipe> &pipes) {
	Seporator();
	if (pipes.size() != 0)
	{
		cout << "�����\n";
		Pipe::Header();
		for (auto& p : pipes)
		{
			cout << p.second;
		}
	}
	else
	{
		cout << "��� �� ����� �����\n";
	}
}
void ShowAllCompressors(const unordered_map <int, Compressor> &compressors) {
	Seporator();

	if (compressors.size() != 0) {
		cout << "������������� �������\n";
		Compressor::Header();
		for (auto& c : compressors)
		{
			cout << c.second;
		}
	}
	else
	{
		cout << "��� �� ����� ������������� �������\n";
	}
	Seporator();
}

vector <int> FindAllPipesByName(const unordered_map <int, Pipe>& pipesmap) {
	string name = EnterName();
	vector <int> IDs = FindPipeByFilter(pipesmap, CheckByName, name);
	if (IDs.size() != 0) {
		Pipe::Header();
		for (int i = 0; i < IDs.size(); ++i) {
			cout << pipesmap.at(IDs[i]);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������";
		return { };
	}
}

vector <int> FindAllPipesByRepair(const unordered_map <int, Pipe>& pipesmap) {
	cout << "������� 1,���� ����� ����� ���� � ������� ��� 0,���� ����� ���� � ������������\n";
	bool repair = EnterBool();
	vector <int> IDs = FindPipeByFilter(pipesmap, CheckByRepair, repair);
	if (IDs.size() != 0) {
		Pipe::Header();
		for (int i = 0; i < IDs.size(); ++i) {
			cout << pipesmap.at(IDs[i]);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������";
		return { };
	}
}
vector <int> FindAllKSByName(const unordered_map <int, Compressor>& compressorsmap) {
	string name = EnterName();
	vector <int> IDs = FindCompressorByFilter(compressorsmap, CheckByName, name);
	if (IDs.size() != 0) {
		Compressor::Header();
		for (int id:IDs) {
			cout << compressorsmap.at(id);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������\n";
		return {};
	}
}
vector <int> FindAllKSByWorkshopsOutWork(const unordered_map <int, Compressor>& compressorsmap) {
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


	pair <double, double> border;
	border.first = min;
	border.second = max;


	auto IDs = FindCompressorByFilter(compressorsmap, CheckByWorkshopsOutWork, border);
	return IDs;

}


vector <int> FindSomeIDs(const vector <int> &IDs) {
	vector <int> FindIDs;
	int id;
	do
	{
		cout << "������� Id:\n";
		id = EnterUInt();
		if (find(IDs.begin(), IDs.end(), id) != IDs.end()) {
			if (find(FindIDs.begin(), FindIDs.end(), id) == FindIDs.end()) {
				FindIDs.push_back(id);
			}
			else {
				cout << "������ id ��� ������,���������� ������\n";
			}
		}
		else {
			cout << "������� id ��� � ������\n";
		}
		if (IDs.size() != FindIDs.size())
		cout << "���������� ���� (1) || ����� (0)\n";

	} while ((IDs.size()!=FindIDs.size()) && EnterBool());
	return FindIDs;
}
vector <int> FindAllPipes(const unordered_map <int, Pipe> &pipesmap) {

	vector <int> IDs;


	cout << "������� 1,���� ����� ����� �� �������� ��� 0,���� �� ��������\n" << endl;

	if (EnterBool()) {
		IDs = FindAllPipesByName(pipesmap);
	}
	else {
		IDs = FindAllPipesByRepair(pipesmap);
	}
	return IDs;
}

vector <int> FindAllCompressors(const unordered_map <int, Compressor>& compressorsmap) {
	vector <int> IDs;
	cout << "������� 1,���� ����� ����� �� �������� ��� 0,���� �� �������� ����������������� �����\n" << endl;
	if (EnterBool()) {
		IDs=FindAllKSByName(compressorsmap);
	}
	else {
		IDs=FindAllKSByWorkshopsOutWork(compressorsmap);
	}
	return IDs;
}




int main() {
	setlocale(LC_CTYPE, "Russian");

	unordered_map <int, Pipe> pipesmap;
	unordered_map <int, Compressor> compressorsmap;
	while (true)
	{
		MainMenu();
		switch (EnterUInt())
		{
		case 1:
		{
			Pipe p;
			cin >> p;
			pipesmap.insert({ p.id, p });
			cout << "������� ����� �� ���������� ����������������:\n";
			p.Header();
			cout<<p;
			break;
		}

		case 2: {
			
			Compressor comp;
			compressorsmap.insert({ comp.id,comp });
			cout << "������� ������������� ������� �� ���������� ����������������:\n";
			comp.Header();
			cout<<comp;
			break;
		}
		case 3:
			ShowAllPipes(pipesmap);
			ShowAllCompressors(compressorsmap);
			
			break;

		case 4: {
			vector <int> IDs = EnterIDs(pipesmap);
			cout << "����������������� �����\n";
			Pipe::Header();
			if (IDs.size()!=0)
			for (auto id : IDs)
			{
				pipesmap[id].Edit();
				cout<<pipesmap[id];
			}
			else 
				cout << "��� �� ����� �����";
			
			break;
		}
		case 5:
			{
			vector <int> IDs = EnterIDs(compressorsmap);
			cout << "����������������� ��\n";
			if (IDs.size() != 0)
				for (auto id : IDs)
				{	
					cout << "� ������������� ������� c id "<<id<<" "<< compressorsmap[id].workshopsinwork<< " ������������� ������� � ������\n";
					compressorsmap[id].Edit();
					
				}
			else
				cout << "��� �� ����� ��";
			break;
			}
		case 6: {
			cout << "����� ����� ��� ����������\n";
			string filename = EnterName();
			Pipe::SaveBuff(pipesmap, filename);
			Compressor::SaveBuff(compressorsmap,filename);
			break;
		}
		case 7: {
			cout << "����� ����� ��� ��������\n";
			string filename = EnterName();
			pipesmap.clear();
			compressorsmap.clear();
			Pipe::LoadInfo(pipesmap, filename);
			Compressor::LoadInfo(compressorsmap, filename);
			break; }

		case 8:
		{
			vector <int> IDs=FindAllPipes(pipesmap);
			if (IDs.size() != 0)
			{
				cout << "1.������� ��������� �����\n" << "2.������������� ��������� �����\n"<<"3.������� ��\n" << "����� ������� ��� ������\n";
				char choice = _getch();
				if (choice == '1') {
					IDs = FindSomeIDs(IDs);
					for (auto id : IDs)
					{
						pipesmap.erase(id);
					}
				}
				else if (choice == '2')
				{
					IDs = FindSomeIDs(IDs);
					for (auto id : IDs)
					{

						pipesmap[id].Edit();
					}
				}
				else if (choice == '3') {
					for (auto id : IDs) {
						pipesmap.erase(id);
					}
				}
			}
			break;

		}

		case 9:
		{vector <int> IDs = FindAllCompressors(compressorsmap);
		if (IDs.size() != 0) {
			cout << "1.������� ��������� ��\n" << "2.������������� ��������� ��\n" <<"3.������� ��" << "����� ������� ��� ������\n";
			char choice = _getch();
			if (choice == '1') {
				IDs = FindSomeIDs(IDs);
				for (auto id : IDs)
				{
					compressorsmap.erase(id);
				}
			}
			else if (choice == '2')
			{
				IDs = FindSomeIDs(IDs);
				for (auto id : IDs)
				{

					compressorsmap[id].Edit();
				}
			}
			else if (choice == '3') {
				for (auto id : IDs) {
					compressorsmap.erase(id);
				}
			}
		}
	
		break;
		}
		case 10: {
			vector <int> IDs = EnterIDs(pipesmap);
			cout << "��������� ��������� �����:\n";
			Pipe::Header();
			for (auto id : IDs)
			{
				cout << pipesmap[id];;
				pipesmap.erase(id);
			}
			break
				;
		}
			
		case 11:
		{
			vector <int> IDs = EnterIDs(compressorsmap);
			cout << "��������� ��������� ��:\n";
			Compressor::Header();
			for (auto id : IDs)
			{
				cout << compressorsmap[id];
				compressorsmap.erase(id);
			}
			break
				;
		}
		case 12: {
			cout << "����� ����� ��� ����������\n";
			string filename = EnterName();
			Pipe::SaveInfo(pipesmap, filename);
			Compressor::SaveInfo(compressorsmap, filename);
			break;
		}
		case 13:
			return 0;
		default:
			break;
		}

	}

	return 0;

}
