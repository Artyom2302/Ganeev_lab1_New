#include "EnterValue.h"
#include <conio.h>


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
int EnterUInt() {
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