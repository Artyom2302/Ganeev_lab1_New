#include <iostream>//in out поток
#include <vector>//работа с динамическими массивами
#include <sstream>// для работы со строками getline()
#include <clocale>// для русского языка
#include  <conio.h>// Для ввода с клавиатуры _getch()
#include <cstring> //
#include <iomanip>//форматированный вывод
#include <fstream>
#include <cstdlib>// rand
#include <windows.h>
#include <unordered_map>



using namespace std;

//Cоздание структуры Труба
struct pipe {
	unsigned int id;
	string name;
	unsigned int diameter;
	double length;
	bool repair;
};
//Cоздание структуры Компрессорная станция
struct compressor {
	unsigned int id = 0;
	string name;
	unsigned int workshops = 0;//цехи
	unsigned int workshopsinwork = 0;//цехи в работе
	double performance = 0;//эффективность
};

//Функция проверки
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
		if (s[i] == '.') {//проверка на точки
			tochka += 1;
		}
		if (tochka > 1) {// возврат если точек больше одной
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
//Конец функции проверки
void Seporator(ostream& out = cout) {
	for (size_t i = 0; i < 25; i++)
	{
		out << "----";
	}
	out << endl;
}

string EnterName() {
	string name;
	cout << "Введите название: ";
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

			cout << "Значение введено неверно\nВведите еще раз: ";
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
			cout << "Введите целочисленное значение: ";
		}

	} while (!(CheckInt(value)));
	return stoi(value);
}
int RandomId() {
	return rand();
}




bool CheckPipeId(int value, const vector <pipe>& pipes) {

	for (size_t i = 0; i < pipes.size(); i++) {
		if (value == pipes[i].id)
		{
			return  true;
			break;
		}
	}
	return false;
}

bool CheckCompressorId(int value, const vector <compressor>& compressors) {
	for (size_t i = 0; i < compressors.size(); i++) {
		if (value == compressors[i].id)
		{
			return  true;
			break;
		}
	}
	return false;

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
		"0. Выход" << endl <<
		"Введите пункт меню: " << endl;
}

bool GetPipeStatus() {
	char x,status;
	cout << "Введите 1,если в ремонте   или   0,если в эксплуатации\n";
	do
	{
		x = _getch();
		if (x != '0' && x != '1') { cout << "Нажмите клавишу верно!!!\n"; }
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

	cout << "Труба\nID №" << p.id << endl;
	p.name = EnterName();
	cout << "Введите длину: ";

	p.length = EnterUDouble();


	cout << endl << "Введите диаметр: ";

	p.diameter = EnterUInt();


	p.repair = GetPipeStatus();

	

	return p;

}

compressor AddCompressor(int id)
{
	compressor comp;
	string value;
	comp.id = id;

	cout << "Компрессорная станция\nID №" << comp.id;
	comp.name = EnterName();


	cout << "Введите общее количество цехов: ";
	comp.workshops = EnterUInt();

	cout << "Введите  количество цехов в работе: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"))
		{
			cout << "Введите целочисленное число,не превышающее общее количество цехов!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"));
	comp.workshopsinwork = stoi(value);


	cout << endl << "Введите эффективность в %: ";
	do
	{
		getline(cin, value);
		if (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0))
		{
			cout << "Введите значение верно !!! Эффективность:  ";
		}

	} while (!(CheckDouble(value) && stod(value) <= 100 && stod(value) >= 0));
	comp.performance = stod(value);
	return comp;
}

double CompressorsOutWork(compressor c) {
	double value;
	value = c.workshops - c.workshopsinwork;
	value /= c.workshops;
	return value * 100;
}

void OutInfo(const pipe& p) {
	cout << setw(10) << p.id << setw(20) << p.name << setw(20) << p.length << setw(20) << p.diameter
		<< setw(40) << ((p.repair) ? "В ремонте\n" : "В эксплуатации\n");
}
void OutInfo(const compressor& comp) {
	cout << setw(10) << comp.id << setw(20) << comp.name << setw(30) << comp.workshops << setw(30)
		<< comp.workshopsinwork << setw(20) << comp.performance << endl;
}
void HeaderPipe() {
	cout << setw(10) << "Id " << setw(20) << "Название" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(40) << "Состояние(В ремонте или нет)\n";
}
void HeaderCompressor() {
	cout << setw(10) << "Id " << setw(20) << "Название" << setw(30) << "Общее количество цехов"
		<< setw(30) << "Количество цехов в работе" << setw(20) << "Эффективность" << endl;
}



//int SearchPipeIndexById(int id, unordered_map <int, pipe> pipesmap) {
//	if (pipesmap.find(id)!=pipesmap.end()) {
//		return id;
//	}
//	return -1;
//}

//int SearchCompressorIndexById( int id,const vector <compressor>& compressors) {
//	for (size_t i = 0; i < compressors.size(); i++)
//	{
//		if ( id== compressors[i].id)
//		{
//			return i;
//		}
//	}
//	return -1;
//}



void EditPipe(pipe& p) {
	p.repair = !p.repair;
}

void EditCompressor(compressor& comp) {
	string value;
	cout << "Введите новое количество цехов в работе: ";
	do
	{
		getline(cin, value);
		if (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"))
		{
			cout << "Введите целочисленное число,не превышающее общее количество цехов!!!\n";
		}

	} while (!((CheckInt(value) && (stoi(value) <= comp.workshops)) || value == "0"));
	comp.workshopsinwork = stoi(value);
}
void SaveBuff(const unordered_map <int, pipe>& pipes, const unordered_map <int, compressor>& compressors, string filename) {
	ofstream fbuff;
	filename += "buff";
	fbuff.open(filename);
	for (auto& p : pipes)
		fbuff << "Труба\n" << p.second.id << endl << p.second.name << endl << p.second.length << endl << p.second.diameter << endl << p.second.repair << endl;
	for (auto& c : compressors)
		fbuff << "КС\n" << c.second.id << endl << c.second.name << endl << c.second.workshops << endl
		<< c.second.workshopsinwork << endl << c.second.performance << endl;
	fbuff.close();
}


void SaveInfo(const unordered_map <int, pipe>& pipes, const unordered_map <int, compressor>& compressors, string filename) {
	ofstream fout;
	fout.open(filename);
	fout << "Общая информация\n";
	fout << "Трубы\n";
	fout << setw(10) << "Id " << setw(20) << "Имя" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(40) << "Состояние(В ремонте или нет)\n";
	for (auto& p : pipes)
	{
		fout << setw(10) << p.second.id << setw(20) << p.second.name << setw(20) << p.second.length << setw(20) << p.second.diameter;
		if (p.second.repair) {
			fout << setw(40) << "В ремонте\n";
		}
		else
		{
			fout << setw(40) << "В эксплуатации\n";
		}

	}

	fout << "\nКомпрессорные станции\n";
	fout << setw(10) << "Id " << setw(20) << "Название" << setw(30) << "Общее количество цехов"
		<< setw(30) << "Количество цехов в работе" << setw(20) << "Эффективность" << endl;
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
			if (str == "Труба") {

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
			else if (str == "КС") {//else
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
		cout << "Такого файла не существует!!!";
	}

	in.close();
};

vector <int> SearchPipe(unordered_map <int, pipe> pipes, string parametr) {
	string name;
	bool repair;
	vector <int> id;
	
	if (parametr == "name")
	{
		name = EnterName();
		for (auto& p : pipes) {
			if (p.second.name == name) {

				id.push_back(p.first);

			};
		}
		return id;
	}
	if (parametr == "repair") {

		repair=GetPipeStatus();
		for (auto& p : pipes) {
			if (p.second.repair ==repair) {

				id.push_back(p.first);

			};
		}
		return id;
	}

	return {};
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
		cout << "Введите интервал в процентах незадействованных цехов\n";
		do
		{
			cout << "min: ";
			min = EnterUDouble();
			cout << "max: ";
			max = EnterUDouble();
			if ((min > max) &&((min>=0)&&(min<=100))&&((max>=0)&&(max<=100)))
				cout << "Минимальное должно быть больше чем максимальное и они должны быть от 0 до 100\n";
		} while (min>max);
		for (auto& c : compressors) {
			percentoutwork = CompressorsOutWork(c.second);
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
			cout << "Введена труба со следующими характеристиками:\n";
			HeaderPipe();
			OutInfo(p);
			break;
		}

		case 2: {
			compressorsid += 1;
			compressor comp = AddCompressor(compressorsid);
			compressorsmap.insert({ compressorsid,comp });
			cout << "Введена компрессорная станция со следующими характеристиками:\n";
			HeaderCompressor();
			OutInfo(comp);
			break;
		}
		case 3:
			Seporator();
			if (pipesmap.size() != 0)
			{
				cout << "Трубы\n";
				HeaderPipe();
				for (auto& p : pipesmap)
				{
					OutInfo(p.second);
				}
			}
			else
			{
				cout << "Нет ни одной трубы\n";
			}
			Seporator();

			if (compressorsmap.size() != 0) {
				cout << "Компрессорные станции\n";
				HeaderCompressor();
				for (auto& c : compressorsmap)
				{
					OutInfo(c.second);
				}
			}
			else
			{
				cout << "Нет ни одной компрессорной станции\n";
			}
			Seporator();
			break;

		case 4:
			if (pipesmap.size() == 0)
			{
				cout << "Нет ни одной трубы\n";
			}
			else {
				auto pipeid = 0u;
				do
				{
					cout << "Введите cуществующий id: ";
					pipeid = EnterUInt();
				} while (pipesmap.find(pipeid) == pipesmap.end());
				cout << (pipesmap[pipeid].repair ? "\nТруба в ремонте\n" : "\nТруба в эксплуатации\n");//добавить функцию
				cout << "Для изменения нажмите любую клавишу\n";
				_getch();
				EditPipe(pipesmap[pipeid]);
			}
			break;

		case 5:
			if (compressors.size() == 0)
			{
				cout << "Нет ни одной компрессорной станции\n";
			}
			else {

				unsigned int compressorid = 0;
				do
				{
					cout << "Введите cуществующий id: ";
					compressorid = EnterUInt();
				} while (compressorsmap.find(compressorid) == compressorsmap.end());
				EditCompressor(compressors[compressorid]);
			}

			break;

		case 6: {
			cout << "Введите имя файла";
			string filename = EnterName();
			SaveInfo(pipesmap, compressorsmap, filename);
			SaveBuff(pipesmap, compressorsmap, filename);
			break;
		}
		case 7: {
			cout << "Введите имя файла";
			string filename = EnterName();
			pipesmap.clear();
			compressorsmap.clear();
			LoadInfo(pipesmap, compressorsmap, filename);
			break; }

		case 8:
		{int choice;
		cout << "Нажмите 1,если нужен поиск по названию или 2,если по признаку"<<endl;
		choice = _getch();
			vector <int> id ;
			if (choice == '1') {
				id = {};
				id = SearchPipe(pipesmap, "name");
				if (id.size() != 0) {
					HeaderPipe();


					for (int i = 0; i < id.size(); ++i) {
						OutInfo(pipesmap[id[i]]);
					}
				}

			}
			else if (choice == '2') {
				id = {};
				id = SearchPipe(pipesmap, "repair");
				if (id.size() != 0) {
					HeaderPipe();

					for (int i = 0; i < id.size(); ++i) {
						OutInfo(pipesmap[id[i]]);
					}
				}

			}
			else
				cout << "Нажата не та клавиша";


			break;

		}


		break;
		case 9:
		{int choice;
		cout << "Нажмите 1,если нужен поиск по названию или 2,если по проценту незадействованных цехов" << endl;
		choice = _getch();
		vector <int> id;
		if (choice == '1') {
			id = {};
			id = SearchCompressors(compressorsmap, "name");
			if (id.size() != 0) {
				HeaderCompressor();
				for (int i = 0; i < id.size(); ++i) {
					OutInfo(compressorsmap[id[i]]);
				}
			}

		}
		else if (choice == '2') {
			id = {};
			id = SearchCompressors(compressorsmap, "unworkpercent");
			if (id.size() != 0) {
				HeaderCompressor();

				for (int i = 0; i < id.size(); ++i) {
					OutInfo(compressorsmap[id[i]]);
				}
			}
		}
		else
			cout << "Нажата не та клавиша";
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
