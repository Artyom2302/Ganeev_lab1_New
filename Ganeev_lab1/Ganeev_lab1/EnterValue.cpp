#include "EnterValue.h"
#include <conio.h>


string EnterName() {
	string name;
	cout << "¬ведите название: ";
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

			cout << "«начение введено неверно\n¬ведите еще раз: ";
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
			cout << "¬ведите целочисленное значение: ";
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
			cout << "¬ведите нужную клавишу\n";
	} while (choice != '1' && choice != '0');
	choice == '1' ? value=1 : value = 0;
	return value;

}