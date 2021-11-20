#include "EGTS.h"


EGTS::EGTS() :Pipes(), Compressors()
{

}

set<int> EGTS::findBranches(int Branch::* field, int parametr) {
	set<int> findedBranchesIDs;
	for (auto &branch : Branches) {
		if (branch.*field == parametr) {
			findedBranchesIDs.insert(branch.inid);
		}
	}
	return findedBranchesIDs;
};

bool EGTS::CheckUsable(int compin, int compout)
{
	for (auto [id, in, out] : Branches) {
		if (in == compin && out == compout) {
			return true;
		}

	}

	return false;
}
void EGTS::OutBranchesInfo()
{
	if (Branches.size() != 0) {
	for (auto& branch : Branches) {
		connection(branch.inid, branch.pid, branch.outid);
	}
	}
	else
	{
		cout << "��� �� ������ ����������\n";
	}
	
}
void EGTS::connection(int in, int pid, int out)
{	
	if (in != 0 && pid != 0 && out != 0)
		cout << "�� �" << in << "-->" << "����� �" << pid << "-->" << "�� �" << out << endl;
	else
	{
		cout <<"��������:\n" << "�� �" << in  << "______����� �" << pid  << "______�� �" << out<<" �� ���������\n"<<endl;
	}
}
EGTS::Branch EGTS::CreateBranch()
{
	Branch branch;
	int pipeid,incompid, outcompid;;

	do
	{
		cout << "������� id ��,������ ����� ��������� ���\n";
		incompid = EnterUInt();
		if (Compressors.find(incompid) == Compressors.end()) {
			cout << "������ �� �� ����������\n";
		}

	} while (Compressors.find(incompid)==Compressors.end());
	
	do
	{
		cout << "������� id ��,���� ����� ��������� ���\n";
		outcompid = EnterUInt();
		if (Compressors.find(incompid) == Compressors.end()) {
			cout << "������ �� �� ����������\n";
		}
		if (incompid == outcompid) {
			cout << "�� ��� ������� ������ Id \n";
		}

	} while (Compressors.find(incompid) == Compressors.end() || incompid == outcompid);

	do
	{
		cout << "������� id �����,������� ����� ��������� ��� ��� ��\n";
		pipeid = EnterUInt();
		if (Pipes.find(pipeid) == Pipes.end() ) {
			cout << "������ ����� �� ����������\n";
		}
		if (CheckUsable(incompid, outcompid)) {
			cout << "����� ��� ��������� ������ ��\n";
		}
	
	} while (Pipes.find(pipeid) == Pipes.end()|| findBranches(&Branch::pid,pipeid).size()!=0);
	branch = { pipeid,incompid, outcompid };
	
	cout << "��������� ��������� ����� ";
	connection(incompid, pipeid, outcompid);
	Branches.push_back(branch);
	Compressors[incompid].connectedpipe.insert(pipeid);
	Compressors[outcompid].connectedpipe.insert(pipeid);
	return branch;

}



void EGTS::EGTSDeleteCompressors( int IDs)
{
	set <int>finded= findBranches(&Branch::inid, IDs);
	for (auto id:finded) {
		Branches[id].inid = 0;
		Branches[id].pid = 0;
	}
	finded = findBranches(&Branch::outid, IDs);
	for (auto id : finded) {
		Branches[id].outid = 0;
		Branches[id].pid = 0;
	}
}

void EGTS::EGTSDeletePipes(int IDs)
{	
	set <int>finded = findBranches(&Branch::pid, IDs);
	for (auto id : finded) {
		Branches[id].pid = 0;
	}
}




