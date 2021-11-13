#include "Pipe.h"


Pipe::Pipe():id(0),name(""),length(0),diameter(0),repair(0)
{
}

Pipe::Pipe(int pipeid) :id(pipeid),name(),length(), diameter(),repair()
{
	string value1;
	cout << "Труба\nID №" << id << endl;
	name = EnterName();
	cout << "Введите длину: ";
	length = EnterUDouble();
	cout << endl << "Введите диаметр: ";
	diameter = EnterUInt();
	cout << endl << "Введите 1,если труба в ремонте и 0,если в эксплуатации \n";
	repair = EnterBool();
}

void Pipe::Edit()
{
	repair = !repair;
}

void Pipe::Header(ostream &out) {
	out << setw(10) << "Id " << setw(20) << "Название" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(40) << "Состояние(В ремонте или нет)\n";
}
void operator<<(ostream& out, const Pipe& p)
{
	out << setw(10) << p.id << setw(20) << p.name << setw(20) << p.length << setw(20) << p.diameter
		<< setw(40) << ((p.repair) ? "В ремонте\n" : "В эксплуатации\n");
}
void operator>>(istream& in, Pipe& p)
{
	string str;
	getline(in, str);
	p.id = stoi(str);

	getline(in, str);
	p.name = str;

	getline(in, str);
	p.length = stof(str);

	getline(in, str);
	p.diameter = stoi(str);

	getline(in, str);
	p.repair = stoi(str);

}

void Pipe::SaveInfo(unordered_map<int, Pipe> pipes,string filename)
{
	ofstream fout;
	fout.open(filename);
	fout << "Общая информация\n";
	fout << "Трубы\n";
	Header(fout);
	for (auto& p : pipes)
	{
		fout << p.second;
	}
	fout.close();
}

void Pipe::SaveBuff(unordered_map<int, Pipe> pipes, string filename)
{
	ofstream fbuff;
	filename += "buff";
	fbuff.open(filename);
	for (auto& p : pipes) {
		fbuff << "Труба\n" << p.second.id << endl << p.second.name << endl << p.second.length << endl << p.second.diameter << endl << p.second.repair << endl;
	}
	fbuff.close();

}

void Pipe::LoadInfo(unordered_map<int, Pipe> &pipes, string filename)
{
	string str;
	filename += "buff";
	ifstream in(filename);
	Pipe pipebuff;
	if (in.is_open()) {
		do
		{
			getline(in, str);
			if (str == "Труба") {
				in >> pipebuff;
				pipes.insert({ pipebuff.id,pipebuff });
			}
		} while (str != "");
	}
	else 
		cout << "Такого файла не существует!!!";
	in.close();
}




