#include <string>
#include "Check.h"
//Функция проверки
bool CheckInt(string s) {
	if (!((s.size() != 0) && (s[0] != '0')))
		return false;

	for (size_t i = 0; i < s.size(); i++)
		if (!isdigit(s[i]))
			return false;

	return true;
}
bool CheckDouble(string s) {
	if (s.size() == 0) {
		return false;
	}
	int tochka = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '.') {//проверка на точки
			tochka += 1;
		}
		if (tochka > 1) {// возврат если точек больше одной
			return false;
		}
		if (!(isdigit(s[i]) || (s[i] == '.')))
			return false;
	}
	return true;
}
bool CheckAllSpace(string s) {
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			return false;
		}
	}
	return true;
}
