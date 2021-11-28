#include "EGTS.h"


EGTS::EGTS() :Pipes(), Compressors()
{

}



void EGTS::Diviner(ostream& out)
{


	for (size_t i = 0; i < 25; i++)
	{
		out << "----";
	}
	out << endl;


}

//������ ������������ ������ --������ 
//���������� �� � ����� 
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
		if (!(CheckDouble(value) && stod(value) <= +100 && stod(value) >= 0))
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
//���������� �� � �����

void EGTS::CreatePipe()
{
	Pipe p;
	cin >> p;
	Pipes.insert({ p.id, p });
	cout << "������� ����� �� ���������� ����������������:\n";
	p.Header();
	cout << p;

}
void EGTS::CreateKS()
{
	Compressor comp;
	cin >> comp;
	Compressors.insert({ comp.id,comp });
	cout << "������� ������������� ������� �� ���������� ����������������:\n";
	comp.Header();
	cout << comp;

}

void EGTS::ShowAllPipes()const {
	Diviner();
	if (Pipes.size() != 0)
	{
		cout << "�����\n";
		Pipe::Header();
		for (auto& p : Pipes)
		{
			cout << p.second;
		}
	}
	else
	{
		cout << "��� �� ����� �����\n";
	}
}
void EGTS::ShowAll�ompressors() const
{
	Diviner();

	if (Compressors.size() != 0) {
		cout << "������������� �������\n";
		Compressor::Header();
		for (auto& c : Compressors)
		{
			cout << c.second;
		}
	}
	else
	{
		cout << "��� �� ����� ������������� �������\n";
	}
	Diviner();
}


void EGTS::EditPipes()
{
	vector <int> IDs;
	for (auto p : Pipes)
	{
		IDs.push_back(p.first);
	}
	IDs = EnterSomeIDs(IDs);
	cout << "����������������� �����\n";
	Pipe::Header();
	if (IDs.size() != 0)
		for (auto id : IDs)
		{
			Pipes[id].Edit();
			cout << Pipes[id];
		}
	else
		cout << "��� �� ����� �����";
}

void EGTS::EditCompressors()
{
	vector <int> IDs;
	for (auto c : Compressors)
	{
		IDs.push_back(c.first);
	}
	IDs = EnterSomeIDs(IDs);
	cout << "����������������� ��\n";
	if (IDs.size() != 0)
		for (auto id : IDs)
		{
			cout << "� ������������� ������� c id " << id << " " << Compressors[id].workshopsinwork << " ������������� ������� � ������\n";
			Compressors[id].Edit();

		}
	else
		cout << "��� �� ����� ��";

}

void  EGTS::SaveInfo(const string& filename)const {

	ofstream fout;
	fout.open(filename);
	fout << "����� ����������\n";
	fout << "�����\n";
	Pipe::Header(fout);
	for (auto& p : Pipes)
	{
		fout << p.second;
	}

	fout << "\n������������� �������\n";
	Compressor::Header(fout);
	for (auto& c : Compressors)
	{
		fout << c.second;
	}
	fout.close();

}
void EGTS::SaveBuff(string filename)const {
	ofstream fbuff;
	filename += "buff";
	fbuff.open(filename);
	for (auto& p : Pipes) {
		fbuff << "�����\n" << p.second.id << endl << p.second.name << endl << p.second.length << endl << p.second.diameter << endl << p.second.repair << endl;
	}

	for (auto& c : Compressors) {
		fbuff << "��\n" << c.second.id << endl << c.second.name << endl << c.second.workshops << endl
			<< c.second.workshopsinwork << endl << c.second.performance << endl;
	}
	fbuff.close();
}
void EGTS::LoadInfo(string filename) {
	Pipes.clear();
	string str;
	filename += "buff";
	ifstream in(filename);
	Pipe::nullmaxid();
	Compressor::nullmaxid();
	if (in.is_open()) {
		do
		{
			getline(in, str);
			if (str == "�����") {
				Pipe pipebuff;
				in >> pipebuff;
				Pipes.insert({ pipebuff.id,pipebuff });
			}
			else if (str == "��") {
				Compressor compressorbuff;
				in >> compressorbuff;
				Compressors.insert({ compressorbuff.id,compressorbuff });
			}
		} while (str != "");
	}
	else
		cout << "������ ����� �� ����������!!!";
	in.close();
}

//������ ������������ ������ --�����

//������ ������������ ������  --������
	//������� ��� ����


bool CheckById(const Pipe& p, int pipeid) {
	return p.id == pipeid;
}
bool CheckByName(const Pipe& p, string name) {
	return p.name == name;
}
bool CheckByRepair(const Pipe& p, bool repair) {
	return p.repair == repair;
}

//������� ��� ��


bool CheckById(const Compressor& c, int compressorId) {
	return c.id == compressorId;
}

bool CheckByName(const Compressor& c, string name) {
	return c.name == name;
}

bool CheckByWorkshopsOutWork(const Compressor& c, pair	<double, double> border) {
	double percentoutwork = c.PercentOfOutWork();
	return (percentoutwork >= border.first) && (percentoutwork <= border.second);
}

//������ � ��������---������

vector<int> EGTS::FindAllPipesByName() const
{
	string name = EnterName();
	vector <int> IDs = FindPipeByFilter(Pipes, CheckByName, name);
	if (IDs.size() != 0) {
		Pipe::Header();
		for (int i = 0; i < IDs.size(); ++i) {
			cout << Pipes.at(IDs[i]);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������";
		return { };
	}

}
vector<int> EGTS::FindAllPipesByRepair() const
{
	cout << "������� 1,���� ����� ����� ���� � ������� ��� 0,���� ����� ���� � ������������\n";
	bool repair = EnterBool();
	vector <int> IDs = FindPipeByFilter(Pipes, CheckByRepair, repair);
	if (IDs.size() != 0) {
		Pipe::Header();
		for (int i = 0; i < IDs.size(); ++i) {
			cout << Pipes.at(IDs[i]);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������";
		return { };
	}
}

vector<int> EGTS::FindAllKSByName() const
{
	string name = EnterName();
	vector <int> IDs = FindCompressorByFilter(Compressors, CheckByName, name);
	if (IDs.size() != 0) {
		Compressor::Header();
		for (int id : IDs) {
			cout << Compressors.at(id);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������\n";
		return {};
	}
}
vector<int> EGTS::FindAllKSByWorkshopsOutWork() const
{
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


	auto IDs = FindCompressorByFilter(Compressors, CheckByWorkshopsOutWork, border);
	if (IDs.size() != 0) {
		Compressor::Header();
		for (int id : IDs) {
			cout << Compressors.at(id);
		}
		return IDs;
	}
	else {
		cout << "�� ������� ������� ������ �� �������\n";
		return {};
	}
}
vector<int> EGTS::FindAllPipes() const
{
	vector <int> IDs;


	cout << "������� 1,���� ����� ����� �� �������� ��� 0,���� �� ��������\n" << endl;

	if (EnterBool()) {
		IDs = EGTS::FindAllPipesByName();
	}
	else {
		IDs = EGTS::FindAllPipesByRepair();
	}
	return IDs;
}


vector <int> EGTS::FindAllCompressors()const {
	vector <int> IDs;
	cout << "������� 1,���� ����� ����� �� �������� ��� 0,���� �� �������� ����������������� �����\n" << endl;
	if (EnterBool()) {
		IDs = FindAllKSByName();
	}
	else {
		IDs = FindAllKSByWorkshopsOutWork();
	}
	return IDs;
}

//������ � ��������---����� 

//�������� �������������� ����
void EGTS::BatchPipesEditing() {
	vector <int> IDs = FindAllPipes();
	if (IDs.size() != 0)
	{
		cout << "1.������� ��������� �����\n" << "2.������������� ��������� �����\n" << "3.������� ��\n" << "����� ������� ��� ������\n";
		char choice = _getch();
		if (choice == '1') {
			IDs = EnterSomeIDs(IDs);
			for (auto id : IDs)
			{
				Pipes.erase(id);
				DeletePipe(id);

			}
		}
		else if (choice == '2')
		{
			IDs = EnterSomeIDs(IDs);
			for (auto id : IDs)
			{

				Pipes[id].Edit();
			}
		}
		else if (choice == '3') {
			for (auto id : IDs) {
				Pipes.erase(id);
				DeletePipe(id);
			}
		}
	}
}

void EGTS::BatchKSEditing()
{
	vector <int> IDs = FindAllCompressors();
	if (IDs.size() != 0) {
		cout << "1.������� ��������� ��\n" << "2.������������� ��������� ��\n" << "3.������� ��\n" << "����� ������� ��� ������\n";
		char choice = _getch();
		if (choice == '1') {
			IDs = EnterSomeIDs(IDs);
			for (auto id : IDs)
			{
				Compressors.erase(id);
				DeleteKS(id);
			}
		}
		else if (choice == '2')
		{
			IDs = EnterSomeIDs(IDs);
			for (auto id : IDs)
			{

				Compressors[id].Edit();


			}
		}
		else if (choice == '3') {
			for (auto id : IDs) {
				Compressors.erase(id);
				DeleteKS(id);
			}
		}
	}
}
//�������� �������������� ����

//������ ������������ ������--�����








//������ ������������ ������ --������
EGTS::Branch EGTS::CreateBranch()
{
	Branch branch;
	int pipeid, incompid, outcompid;;
	if (Branches.size() != Pipes.size()) {
		do
		{
			cout << "������� id ��,������ ����� ��������� ���\n";
			incompid = EnterUInt();
			if (Compressors.find(incompid) == Compressors.end()) {
				cout << "������ �� �� ����������\n";
			}

		} while (Compressors.find(incompid) == Compressors.end());

		do
		{
			cout << "������� id ��,���� ����� ��������� ���\n";
			outcompid = EnterUInt();
			if (Compressors.find(outcompid) == Compressors.end()) {
				cout << "������ �� �� ����������\n";
			}
			if (incompid == outcompid) {
				cout << "�� ��� ������� ������ Id \n";
			}

		} while (Compressors.find(outcompid) == Compressors.end() || incompid == outcompid);

		do
		{
			cout << "������� id �����,������� ����� ��������� ��� ��� ��\n";
			pipeid = EnterUInt();
			if (Pipes.find(pipeid) == Pipes.end()) {
				cout << "������ ����� �� ����������\n";
			}
			if (findBranches(&Branch::pid, pipeid).size() != 0) {
				cout << "����� ��� ��������� ������ ��\n";
			}

		} while (Pipes.find(pipeid) == Pipes.end() || findBranches(&Branch::pid, pipeid).size() != 0);
		branch = { pipeid,incompid, outcompid };
		cout << "��������� ��������� ����� ";
		Connection(incompid, pipeid, outcompid);
		Branches.push_back(branch);
		Compressors[incompid].connectedpipe.insert(pipeid);
		Compressors[outcompid].connectedpipe.insert(pipeid);
		return branch;
	}
	else
	{
		cout << "������ ���������� ������ ������,��� ��� ��� ����� ������\n";
	}

}

set<int> EGTS::findBranches(int Branch::* field, int parametr) {
	set<int> findedBranchesIDs;
	for (int i = 0; i < Branches.size();++i) {
		if (Branches[i].*field == parametr) {
			findedBranchesIDs.insert(i);
		}
	}
	return findedBranchesIDs;
};
void EGTS::OutBranchesInfo()
{
	if (Branches.size() != 0) {
	for (auto& branch : Branches) {
		Connection(branch.fromid, branch.pid, branch.toid);
	}
	}
	else
	{
		cout << "��� �� ������ ����������\n";
	}
	
}
vector<int> EGTS::AllPipeIDs ()const
{
	vector <int> IDs;
	for (auto p : Pipes)
	{
		IDs.push_back(p.first);
	}
	return IDs;
}
vector <int> EGTS::AllKSIDs()const {
	vector <int> IDs;
	for (auto c : Compressors)
	{
		IDs.push_back(c.first);
	}
	return IDs;

};

void EGTS::SaveBranches()
{
	ofstream fout;
	fout.open("EGTS");
	for (auto& branch : Branches) {
		fout << branch.fromid<<endl << branch.pid << endl << branch.toid << endl;
	}
	fout.close();
}
void EGTS::LoadBranches()
{
	ifstream fin;
	fin.open("EGTS");
	string value;
	Branch branch;

	if (fin.is_open()&&!fin.eof()) {
		getline(fin, value);
		do

		{
			branch.fromid = stoi(value);
			getline(fin, value);
			branch.pid = stoi(value);
			getline(fin, value);
			branch.toid = stoi(value);
			Branches.push_back(branch);
			getline(fin, value);
		} while (value!="");
	}
	
	
}

void EGTS::Connection(int in, int pid, int out)
{	
	if (in != 0 && pid != 0 && out != 0) {
		cout << "�� �" << in << "-->" << "����� �" << pid << "-->" << "�� �" << out;
		Pipes.at(pid).repair ? cout << " ������ ����� � �������\n" : cout << "\n";
	}

}
void EGTS::DisconnectPipe(int id) {
	set <int>	branchesid=findBranches(&Branch::pid, id);
	for (auto &id:branchesid)
	{
		Branches.erase(Branches.begin() + id);
	}
};
void EGTS::DisconnectKS(int id) {
	set <int>	branchesid = findBranches(&Branch::fromid, id);
	for (auto& id : branchesid)
	{
		Branches.erase(Branches.begin() + id);
	}
	branchesid = findBranches(&Branch::toid, id);
	for (auto& id : branchesid)
	{
		Branches.erase(Branches.begin() + id);
	}
};

void EGTS::DeletePipe(int id)
{
	set<int> branchesid = findBranches(&Branch::pid, id);
	if (branchesid.size() != 0) {
		cout << "������ ����� ������� � ���������������� ���� � ��������� ������:\n";
		for (auto& id : branchesid) {
			Connection(Branches[id].fromid, Branches[id].pid, Branches[id].toid);
		}
		cout << "�� �������,��� ������ ����������� ����0� � ������� ��� �����(1-��//0-���)\n";
		if (EnterBool()) {
			DisconnectPipe(id);
		}
	}
	else {
		DisconnectPipe(id);
	}
}
void EGTS::DeleteKS(int id)
{
	set<int> branchesinid = findBranches(&Branch::fromid, id);
	set<int> branchesoutid = findBranches(&Branch::toid, id);
	if (branchesinid.size() != 0 ||branchesoutid.size()!=0) {
		cout << "������ �� ������� � ���������������� ���� � ��������� ������:\n";
		for (auto& id : branchesinid) {
			Connection(Branches[id].fromid, Branches[id].pid, Branches[id].toid);
		}
		for (auto& id : branchesoutid) {
			Connection(Branches[id].fromid, Branches[id].pid, Branches[id].toid);
		}
		cout << "�� �������,��� ������ ����������� �� � ������� ��� �����(1-��//0-���)\n";
		if (EnterBool()) {
			DisconnectKS(id);
		}
	}
	else {
		DisconnectKS(id);
	}
}

void EGTS::DeletePipes(vector <int> IDs)
{
			for (auto id : IDs)
			{
				DeletePipe(id);
			}
}
void EGTS::DeleteCompressors(vector <int> IDs)
{
	for (auto id : IDs)
	{
		DeleteKS(id);
	}
}
vector <vector <int>> EGTS::CreateCmeshTable()
{
	vector <vector <int>> SmeschTable;
	SmeschTable.reserve(Compressors.size());
	for (size_t i = 0; i < Compressors.size(); i++)
	{
		SmeschTable.push_back({});
		SmeschTable[i].reserve(Compressors.size());
		for (int j = 0; j < Compressors.size(); ++j) {
			SmeschTable[i].push_back(0);
		}
	}
	
	/*int i = 0;
	for (auto& compressor : Compressors) {
		pair <int, int> idandindex;
		idandindex.first = compressor.first;
		idandindex.second = i++;
		idtoindex.insert(idandindex);
	}*/
	set <int> KSids;
	for (auto& compressor : Compressors) {
		KSids.insert(compressor.first);
	}

	set <int> ::iterator iterini = KSids.begin();
	for (int i = 0; i < Compressors.size(); ++i) {
		
		set<int > branchesindex= findBranches(&Branch::fromid, *iterini);
		set <int> ::iterator iterinj = KSids.begin();
		for (int j = 0; j < Compressors.size(); ++j) {
			
			for (auto index:branchesindex)
			{
				if (Branches[index].toid == *iterinj) {
					SmeschTable[i][j] = 1;
					break;
				
				}
				else {
					SmeschTable[i][j] = 0;
				}
			}
				++iterinj;
		}
		++iterini;

	}
	

	
	
	return SmeschTable;



}

vector <vector <int>> EGTS::CreateDostichimostTable(const vector <vector <int>>& Smesch) {
	vector <vector <int>> mass;
	mass = Smesch;

	for (size_t i = 0; i < mass.size(); i++)
	{
		for (size_t j = 0; j < mass.size(); j++)
		{

			if (i != j) {
				if (mass[i][j] == 1) {
					for (size_t k = 0; k < mass.size(); k++)
					{
						if (mass[j][k] == 1) {
							mass[i][k] = 1;
						}
					}
				}
			}
			else {
				mass[i][j] = 1;
			}
		

		}
	}
	return mass;

};


vector <vector <int>> EGTS::CreateIncedentTable(unordered_map<int, Compressor> Compressors) {
	vector <vector <int>> mass;
	mass.reserve(Compressors.size());
	for (size_t i = 0; i < Compressors.size(); i++)
	{
		mass.push_back({});
		mass[i].reserve(Branches.size());
		for (int j = 0; j < Branches.size(); ++j) {
			mass[i].push_back(0);
		}
	}

	set <int> KSids;
	for (auto& compressor : Compressors) {
		KSids.insert(compressor.first);
	}
	
	for (size_t j = 0; j <Branches.size() ; j++)
	{
		set <int>::iterator iter = KSids.begin();
		set <int> branchesids = findBranches(&Branch::pid, Branches[j].pid);
		for (size_t i = 0; i < Compressors.size(); i++)
		{
			
			for (auto id:branchesids)
			{
				if (Branches[id].fromid == *iter) {
					mass[i][j] = 1;
					break;
				}
				else if (Branches[id].toid == *iter) {
					mass[i][j] = -1;
					break;
				}
				else {
					mass[i][j] = 0;
				}
			}
			++iter;

		}
	}

	return mass;

};
bool EGTS::CheckCycle(vector<vector<int>> Dostichimost)
{
	for (size_t i = 0; i < Dostichimost.size(); i++)
	{
		for (size_t j = 0; j < Dostichimost[i].size(); j++)
		{
			if (Dostichimost[i][j] == Dostichimost[j][i] && i!=j) {
				return true;
			}
		}
	}

	return false;
}

void EGTS::TopologicalSort()
{
	
	if (CheckCycle(CreateDostichimostTable(CreateCmeshTable()))) {
		cout << "�������������� ���������� �� ��������, ��� ��� ���� ����\n";
	}
	else
	{
		for (auto &[id,comp]:Compressors)
		{
			SortKSnumber.emplace(id, 1);
		}	
		SaveBuff("Data");
		SaveBranches();
		int count = Compressors.size();
		for (size_t i = 0; i <count ; i++)
		{
		
			multimap <int, int> KSandOutPower;
			vector <int> outpower;
			for (auto& KS : Compressors)
			{
				KSandOutPower.emplace(OutPower(KS.first),KS.first);
			}
			
			DisconnectKS(KSandOutPower.begin()->second);
			SortKSnumber[KSandOutPower.begin()->second] = count-i;
			Compressors.erase(KSandOutPower.begin()->second);
		};
		LoadInfo("Data");
		LoadBranches();
		cout << "��������� �������������� ����������: \n\n";

		map<int,int> SortnumberKS;
		for (auto& elem: SortKSnumber) {
			SortnumberKS.emplace(elem.second, elem.first);
		}
		for (auto& elem : SortKSnumber) {
			cout << "�� id �" << elem.second << "(" << elem.first << ")" << "--->" << endl;
		}
	

	

	}
	
	
	


}

int EGTS::OutPower(int compid)
{

	set <int> ids=findBranches(&Branch::fromid, compid);
	return ids.size();
}