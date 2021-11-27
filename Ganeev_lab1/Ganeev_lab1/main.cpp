#include "main.h"




using namespace std;

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
		"13.Соединить КС и трубами" << endl <<
		"14.Вывести все соединения" << endl <<
		"15.Cохранить связи труб и КС" << endl <<
		"16.Загрузить связи труб и КС" << endl <<
		"17.Выход" << endl <<
		"Введите пункт меню: " << endl;
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
			egts.ShowAllСompressors();
			break;

		case 4: {
			egts.EditPipes();
			
			break;
		}
		case 5:
			egts.EditCompressors();
			break;
			
		case 6: {
			cout << "Поиск файла для сохранения\n";
			string filename = EnterName();
			egts.SaveInfo(filename);
			break;
		}
		case 7: {
			cout << "Поиск файла для загрузки\n";
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
			cout << "Поиск файла для сохранения\n";
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
