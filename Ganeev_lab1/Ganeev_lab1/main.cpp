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
	cout << "Компрессорная станция\nID №" << c.id << endl;
	c.name = EnterName();


	cout << "Введите общее количество цехов: ";
	c.workshops = EnterUInt();

	cout << "Введите  количество цехов в работе: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= c.workshops)) || value == "0"))
		{
			cout << "Введите целочисленное число,не превышающее общее количество цехов!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= c.workshops)) || value == "0"));
	c.workshopsinwork = stoi(value);


	cout << endl << "Введите эффективность в %: ";
	do
	{
		getline(cin, value);
		if (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0))
		{
			cout << "Введите значение верно !!! Эффективность:  ";
		}

	} while (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0));
	c.performance = stod(value);
	return in;
}

istream& operator >>(istream& in, Pipe& p)
{
	string value1;
	cout << "Труба\nID №" << p.id << endl;
	p.name = EnterName();
	cout << "Введите длину: ";
	p.length = EnterUDouble();
	cout << endl << "Введите диаметр: ";
	p.diameter = EnterUInt();
	cout << endl << "Введите 1,если труба в ремонте и 0,если в эксплуатации \n";
	p.repair = EnterBool();
	return in;
}



void MainMenu()
{
	cout << endl << "1. Добавить трубу" << endl <<
		"2. Добавить КС" << endl <<
		"3. Просмотр всех объектов" << endl <<
		"4. Редактировать трубу" << endl <<
		"5. Редактировать КС" << endl <<
		"6. Сохранить" << endl <<
		"7. Загрузить" << endl <<
		"8. Поиск труб" << endl <<
		"9. Поиск КС" << endl <<
		"10.Удаление  труб " << endl <<
		"11.Удаление  КС " << endl <<
		"12.Вывод на печать " << endl <<
		"13.Выход" << endl <<
		"Введите пункт меню: " << endl;
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
		cout <<"Введите Id: \n";
		int id = EnterUInt();
		if (FindPipeByFilter(pipesmap, CheckById, id).size()==0)
		{
			cout << "Tрубы c данным id нету(Попробуйте другой id)\n";
		}
		else
		{	for (auto ID:IDs)
				if (id==ID)	
				{
				cout<<"Вы уже вводили данный id,попробуйте другой \n";
				id = 0;
				}
		if (id!=0)
		IDs.push_back(id);
		}
			
		cout << " Продолжить ввод ID?(1-да |0-нет )\n";

	} while (EnterBool() &&	IDs.size()!=pipesmap.size());
	return IDs;
}

vector <int> EnterIDs(const unordered_map <int, Compressor>& compressorsmap) {
	vector <int> IDs;
	
	do
	{
		cout << "Введите Id: \n";
		int id = EnterUInt();
		if (FindCompressorByFilter(compressorsmap, CheckById, id).size() == 0)
		{
			cout << "КС c данным id нету(Попробуйте другой id)\n";
		}
		else
		{
			for (auto ID : IDs)
				if (id == ID)
				{
					cout << "Вы уже вводили данный id,попробуйте другой \n";
					id = 0;
				}
			if (id != 0)
				IDs.push_back(id);


		}

		cout << " Продолжить ввод ID?(1-да |0-нет )\n";
	} while (EnterBool());
	return IDs;
}

void ShowAllPipes(const unordered_map <int, Pipe> &pipes) {
	Seporator();
	if (pipes.size() != 0)
	{
		cout << "Трубы\n";
		Pipe::Header();
		for (auto& p : pipes)
		{
			cout << p.second;
		}
	}
	else
	{
		cout << "Нет ни одной трубы\n";
	}
}
void ShowAllCompressors(const unordered_map <int, Compressor> &compressors) {
	Seporator();

	if (compressors.size() != 0) {
		cout << "Компрессорные станции\n";
		Compressor::Header();
		for (auto& c : compressors)
		{
			cout << c.second;
		}
	}
	else
	{
		cout << "Нет ни одной компрессорной станции\n";
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
		cout << "По данному фильтру ничего не найдено";
		return { };
	}
}

vector <int> FindAllPipesByRepair(const unordered_map <int, Pipe>& pipesmap) {
	cout << "Нажмите 1,если нужен поиск труб в ремонте или 0,если поиск труб в эксплуатации\n";
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
		cout << "По данному фильтру ничего не найдено";
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
		cout << "По данному фильтру ничего не найдено\n";
		return {};
	}
}
vector <int> FindAllKSByWorkshopsOutWork(const unordered_map <int, Compressor>& compressorsmap) {
	int min, max;
	cout << "Введите интервал в процентах незадействованных цехов\n";
	do
	{
		cout << "min: ";
		min = EnterUDouble();
		cout << "max: ";
		max = EnterUDouble();
		if ((min > max) && ((min >= 0) && (min <= 100)) && ((max >= 0) && (max <= 100)))
			cout << "Минимальное должно быть больше чем максимальное и они должны быть от 0 до 100\n";
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
		cout << "Введите Id:\n";
		id = EnterUInt();
		if (find(IDs.begin(), IDs.end(), id) != IDs.end()) {
			if (find(FindIDs.begin(), FindIDs.end(), id) == FindIDs.end()) {
				FindIDs.push_back(id);
			}
			else {
				cout << "Данный id уже введен,попробуйте другой\n";
			}
		}
		else {
			cout << "Данного id нет в списке\n";
		}
		if (IDs.size() != FindIDs.size())
		cout << "Продолжить ввод (1) || Выйти (0)\n";

	} while ((IDs.size()!=FindIDs.size()) && EnterBool());
	return FindIDs;
}
vector <int> FindAllPipes(const unordered_map <int, Pipe> &pipesmap) {

	vector <int> IDs;


	cout << "Нажмите 1,если нужен поиск по названию или 0,если по признаку\n" << endl;

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
	cout << "Нажмите 1,если нужен поиск по названию или 0,если по проценту незадействованных цехов\n" << endl;
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
			cout << "Введена труба со следующими характеристиками:\n";
			p.Header();
			cout<<p;
			break;
		}

		case 2: {
			
			Compressor comp;
			compressorsmap.insert({ comp.id,comp });
			cout << "Введена компрессорная станция со следующими характеристиками:\n";
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
			cout << "Отредактированные трубы\n";
			Pipe::Header();
			if (IDs.size()!=0)
			for (auto id : IDs)
			{
				pipesmap[id].Edit();
				cout<<pipesmap[id];
			}
			else 
				cout << "Нет ни одной трубы";
			
			break;
		}
		case 5:
			{
			vector <int> IDs = EnterIDs(compressorsmap);
			cout << "Отредактированные КС\n";
			if (IDs.size() != 0)
				for (auto id : IDs)
				{	
					cout << "У компрессорной станции c id "<<id<<" "<< compressorsmap[id].workshopsinwork<< " компрессорных станций в работе\n";
					compressorsmap[id].Edit();
					
				}
			else
				cout << "Нет ни одной КС";
			break;
			}
		case 6: {
			cout << "Поиск файла для сохранения\n";
			string filename = EnterName();
			Pipe::SaveBuff(pipesmap, filename);
			Compressor::SaveBuff(compressorsmap,filename);
			break;
		}
		case 7: {
			cout << "Поиск файла для загрузки\n";
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
				cout << "1.Удалить некоторые трубы\n" << "2.Редактировать некоторые трубы\n"<<"3.Удалить всё\n" << "Любую клавишу для выхода\n";
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
			cout << "1.Удалить некоторые КС\n" << "2.Редактировать некоторые КС\n" <<"3.Удалить всё" << "Любую клавишу для выхода\n";
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
			cout << "Удалились следующие трубы:\n";
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
			cout << "Удалились следующие КС:\n";
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
			cout << "Поиск файла для сохранения\n";
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
