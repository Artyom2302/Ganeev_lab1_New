#include "Pipe.h"

Pipe::Pipe():id(0),name(""),length(0),diameter(0),repair(0)
{
}

bool Pipe::GetPipeStatus()
{
	char x, status;
	cout << "������� 1,���� � �������   ���   0,���� � ������������\n";
	do
	{
		x = _getch();
		if (x != '0' && x != '1') { cout << "������� ������� �����!!!\n"; }
	} while (x != '1' && x != '0');
	x == '1' ? status = 1 : status = 0;
	return status;
	
}

Pipe::Pipe(int pipeid) :id(pipeid),name(),length(), diameter(),repair()
{
	string value1;
	cout << "�����\nID �" << id << endl;
	name = EnterName();

	cout << "������� �����: ";
	length = EnterUDouble();

	cout << endl << "������� �������: ";
	diameter = EnterUInt();
	cout << endl << "������� 1,���� ����� � ������� � 0,���� � ������������ \n";
	repair = EnterBool();

}

void Pipe::EditPipe()
{
	repair = !repair;
}

void Pipe::HeaderPipe() {
	cout << setw(10) << "Id " << setw(20) << "��������" << setw(20) << "�����" << setw(20) << "�������" << setw(40) << "���������(� ������� ��� ���)\n";
}


void Pipe::OutInfo()
{
	cout << setw(10) << id << setw(20) << name << setw(20) << length << setw(20) << diameter
		<< setw(40) << ((repair) ? "� �������\n" : "� ������������\n");
}
