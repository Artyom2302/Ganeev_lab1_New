#include "EnterValue.h"




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
unsigned int EnterUInt() {
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
bool EnterBool() {
	char choice;
	bool value;
	do
	{
		choice = _getch();
		if (choice != '1' && choice != '0')
			cout << "Введите нужную клавишу\n";
	} while (choice != '1' && choice != '0');
	choice == '1' ? value=1 : value = 0;
	return value;

}

vector <int> EnterSomeIDs(const vector <int>& IDs) {
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

	} while ((IDs.size() != FindIDs.size()) && EnterBool());
	return FindIDs;
}