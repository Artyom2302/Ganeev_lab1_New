#include "main.h"




using namespace std;


//Cоздание структуры Компрессорная станция


//Конец функции проверки
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


void SaveBuff(const unordered_map <int, Pipe>& pipes, const unordered_map <int, Compressor>& compressors, string filename) {
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


void SaveInfo(const unordered_map <int, Pipe>& pipes, const unordered_map <int, Compressor>& compressors, string filename) {
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
void LoadInfo(unordered_map <int, Pipe>& pipes, unordered_map <int, Compressor>& compressors, string filename) {
	string str;
	filename += "buff";
	ifstream in(filename);
	Pipe pipebuff;
	Compressor compressorbuff;
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
			else if (str == "КС") {
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

template<typename T_param>
using PipeFilter = bool(*)(const  Pipe& p, T_param param);

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

bool CheckByName(const Compressor& c, string name) {
	return c.name == name;
}

bool CheckByWorkshopsOutWork(const Compressor& c, pair	<double,double> border) {
	double percentoutwork;
	percentoutwork = Compressor::PercentOfOutWork(c);
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


vector <int> SearchCompressors(unordered_map <int, Compressor> compressors,string parametr) {
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
			percentoutwork = Compressor::PercentOfOutWork(c.second);
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
	
	int compressorsid = 0, pipesid = 0;
	unordered_map <int, Pipe> pipesmap;
	unordered_map <int, Compressor> compressorsmap;
	while (true)
	{
		MainMenu();
		switch (EnterUInt())
		{
		case 1:
		{
			pipesid += 1;
			Pipe p(pipesid);
			pipesmap.insert({ p.id, p });
			cout << "Введена труба со следующими характеристиками:\n";
			p.Header();
			p.OutInfo();
			break;
		}

		case 2: {
			compressorsid += 1;
			Compressor comp(compressorsid);
			compressorsmap.insert({ compressorsid,comp });
			cout << "Введена компрессорная станция со следующими характеристиками:\n";
			comp.Header();
			comp.OutInfo();
			break;
		}
		case 3:
			Seporator();
			if (pipesmap.size() != 0)
			{
				cout << "Трубы\n";
				Pipe::Header();
				for (auto& p : pipesmap)
				{
					p.second.OutInfo();
				}
			}
			else
			{
				cout << "Нет ни одной трубы\n";
			}
			Seporator();

			if (compressorsmap.size() != 0) {
				cout << "Компрессорные станции\n";
				Compressor::Header();
				for (auto& c : compressorsmap)
				{
					c.second.OutInfo();
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
				pipesmap[pipeid].Edit();
			}
			break;

		case 5:
			
			{
				unsigned int compressorid = 0;
				do
				{
					cout << "Введите cуществующий id: ";
					compressorid = EnterUInt();
				} while (compressorsmap.find(compressorid) == compressorsmap.end());
				compressorsmap[compressorid].Edit();
			}

			break;

		case 6: {
			cout << "Поиск файла для сохранения\n";
			string filename = EnterName();
			SaveInfo(pipesmap, compressorsmap, filename);
			SaveBuff(pipesmap, compressorsmap, filename);
			break;
		}
		case 7: {
			cout << "Поиск файла для загрузки\n";
			string filename = EnterName();
			pipesmap.clear();
			compressorsmap.clear();
			LoadInfo(pipesmap, compressorsmap, filename);
			break; }

		case 8:
		{
		cout << "Нажмите 1,если нужен поиск по названию или 0,если по признаку"<<endl;
		char choice = EnterBool();
			vector <int> id ;
			if (choice == true) {
				id = {};
				string name = EnterName();
				id = FindPipeByFilter(pipesmap,CheckByName,name);
				if (id.size() != 0) {
					Pipe::Header();
					for (int i = 0; i < id.size(); ++i) {
						pipesmap[id[i]].OutInfo();
					}
					

				}
				else {
					cout << "По данному фильтру ничего не найдено";
				}

			}
			else if (choice == false) {
				id = {};
				cout << "Нажмите 1,если нужен поиск труб в ремонте или 0,если поиск труб в эксплуатации\n";
				bool repair = EnterBool();
				id = FindPipeByFilter(pipesmap, CheckByRepair, repair);
				if (id.size() != 0) {
					Pipe::Header();

					for (int i = 0; i < id.size(); ++i) {
						pipesmap[id[i]].OutInfo();
					}
					cout << "Нажмите 0,чтобы выйти и 1,чтобы отредактировать  трубы\n";
					choice = EnterBool();
					if (choice == false) {
						break;
					}
					else if(choice==true)
					{
						for (int i = 0; i < id.size(); ++i) {
						pipesmap[id[i]].Edit();
						}
					}
				}
				else {
					cout << "По данному фильтру ничего не найдено\n";
				}

			}
	

			break;

		}


		break;
		case 9:
		{
		cout << "Нажмите 1,если нужен поиск по названию или 0,если по проценту незадействованных цехов" << endl;
		char choice = EnterBool();
		
	
		vector <int> id;
		if (choice == true) {

			string name = EnterName();
			id = FindCompressorByFilter(compressorsmap, CheckByName, name);
			if (id.size() != 0) {
				Compressor::Header();
				for (int i = 0; i < id.size(); ++i) {
					compressorsmap[id[i]].OutInfo();
				}
			}
			else {
				cout << "По данному фильтру ничего не найдено";
			}

		}
		else if (choice == false) {
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


			pair <double,double> border;
			border.first = min;
			border.second = max;
	

			id = FindCompressorByFilter(compressorsmap, CheckByWorkshopsOutWork, border);


			if (id.size() != 0) {
				Compressor::Header();
				for (int i = 0; i < id.size(); ++i) {
					compressorsmap[id[i]].OutInfo();
				}

				cout << "Нажмите 0,чтобы выйти и 1,чтобы отредактировать  компрессорные станции\n";
				choice = EnterBool();
				if (choice == '1') {
					break;
				}
				else if (choice == '2')
				{
					for (int i = 0; i < id.size(); ++i) {
						compressorsmap[id[i]].Edit();
					}
				}
			}
			else {
				cout << "По данному фильтру ничего не найдено";
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
