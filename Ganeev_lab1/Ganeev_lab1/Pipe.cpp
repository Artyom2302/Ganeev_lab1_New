#include "Pipe.h"

unsigned int Pipe::Maxid = 0;

Pipe::Pipe():id(++Maxid),name(""),length(0),diameter(0),repair(0)
{
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

ifstream& operator>>(ifstream& in, Pipe& p)
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
	return in;
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
	--Maxid;
	if (in.is_open()) {
		do
		{
			getline(in, str);
			if (str == "Труба") {
				in >> pipebuff;
				pipes.insert({ pipebuff.id,pipebuff });
				++Maxid;
			}
		} while (str != "");
	}
	else 
		cout << "Такого файла не существует!!!";
	in.close();
}




