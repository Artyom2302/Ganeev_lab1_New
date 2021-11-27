#include "EnterValue.h"




string EnterName() {
	string name;
	cout << "������� ��������: ";
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

			cout << "�������� ������� �������\n������� ��� ���: ";
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
			cout << "������� ������������� ��������: ";
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
			cout << "������� ������ �������\n";
	} while (choice != '1' && choice != '0');
	choice == '1' ? value=1 : value = 0;
	return value;

}

vector <int> EnterSomeIDs(const vector <int>& IDs) {
	vector <int> FindIDs;
	int id;
	do
	{
		cout << "������� Id:\n";
		id = EnterUInt();
		if (find(IDs.begin(), IDs.end(), id) != IDs.end()) {
			if (find(FindIDs.begin(), FindIDs.end(), id) == FindIDs.end()) {
				FindIDs.push_back(id);
			}
			else {
				cout << "������ id ��� ������,���������� ������\n";
			}
		}
		else {
			cout << "������� id ��� � ������\n";
		}
		if (IDs.size() != FindIDs.size())
			cout << "���������� ���� (1) || ����� (0)\n";

	} while ((IDs.size() != FindIDs.size()) && EnterBool());
	return FindIDs;
}