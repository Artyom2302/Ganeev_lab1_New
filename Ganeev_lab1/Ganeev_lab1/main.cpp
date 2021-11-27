#include "main.h"




using namespace std;

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
		"13.��������� �� � �������" << endl <<
		"14.������� ��� ����������" << endl <<
		"15.C�������� ����� ���� � ��" << endl <<
		"16.��������� ����� ���� � ��" << endl <<
		"17.�����" << endl <<
		"������� ����� ����: " << endl;
}


int main() {
	setlocale(LC_CTYPE, "Russian");
	EGTS egts;

	while (true)
	{
		MainMenu();
		switch (EnterUInt())
		{
		case 1:
		{
			egts.CreatePipe();
			break;
		}

		case 2: {
			egts.CreateKS();
			break;
		}
		case 3:
			egts.ShowAllPipes();
			egts.ShowAll�ompressors();
			break;

		case 4: {
			egts.EditPipes();
			
			break;
		}
		case 5:
			egts.EditCompressors();
			break;
			
		case 6: {
			cout << "����� ����� ��� ����������\n";
			string filename = EnterName();
			egts.SaveInfo(filename);
			break;
		}
		case 7: {
			cout << "����� ����� ��� ��������\n";
			string filename = EnterName();
			egts.LoadInfo(filename);
			break; }

		case 8:
		{
			egts.BatchPipesEditing();
			break;

		}

		case 9:
		{
			egts.BatchKSEditing();
		break;
		}
		case 10: {
			vector <int> IDs=egts.AllPipeIDs();
			egts.DeletePipes(IDs);
			break;
		}
			
		case 11:
		{
			
			vector <int> IDs = egts.AllKSIDs();
			egts.DeleteCompressors(IDs);
			break;
		}
		case 12: {
			cout << "����� ����� ��� ����������\n";
			string filename = EnterName();
			egts.SaveBuff(filename);
			break;
		}
		case 13:
		{	
			EGTS::Branch branch = egts.CreateBranch();
			break;
		}
		case 14:
				egts.OutBranchesInfo();
			/*	egts.CreateGraphTable();*/
			break;
		case 15:
			egts.SaveBranches();
			break;
		case 16:
			egts.LoadInfo("Data");
			egts.LoadBranches();
			break;
		case 17:
			return 0;
		default:
			break;
		}

	}

	return 0;

}
