#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Compressor.h"
#include "EnterValue.h"
#include <set>
#include <algorithm>
#include <map>
#include <unordered_set>

class EGTS
{	

	unordered_map <int, Pipe > Pipes;
	unordered_map <int, Compressor> Compressors;
	 map <int, int> SortnumberKS;
public :

	struct Branch
	{
		int pid, fromid, toid;
	};
	unordered_map <int,Branch> Branches;
	EGTS();	
	void  static Diviner(ostream& out = cout);
	//Первая лабораторная работа--начало
	friend istream& operator >>(istream& in, Pipe& p);
	friend istream& operator>>(istream& in, Compressor& c);
	void CreatePipe();
	void CreateKS();
	void ShowAllPipes()const;
	void ShowAllСompressors()const;
	void EditPipes();
	void EditCompressors();
	//Cохранение и загрузка
	//Трубы
	 void  SaveInfo(const string &filename)const;
	 void SaveBuff(string filename)const ;
	 void LoadInfo(string filename);
	 //Сохранение и загрузка 
	//Первая лабораторная работа --конец

		//Вторая лабораторная работа --начало
	//Работа с фильтром---Начало 
	 vector <int> FindAllPipesByName() const;
	 vector <int> FindAllPipesByRepair()const;
	 vector <int> FindAllKSByName()const;
	 vector <int> FindAllKSByWorkshopsOutWork()const;
	 vector <int> FindAllPipes()const;
	 vector <int> FindAllCompressors()const;
	 ////Работа с фильтром---Конец 

	 //Пакетное редактирование меню
	 void BatchPipesEditing();
	 void BatchKSEditing();
	 //Пакетное редактирование меню

	 //Вторая лабораторная работа --конец

	 //Третья лаюораторная работа
	 

	Branch CreateBranch();
	set<int> findBranches(unordered_map <int, Branch>Branches,int Branch::*field, int parametr);
	vector <int> AllPipeIDs()const;
	vector <int> AllKSIDs()const;
	void OutBranchesInfo();
	void Connection(int in, int pid, int out);	
	void SaveBranches();
	void LoadBranches();
	void DisconnectPipe(int id);
	void DisconnectKS(int id);
	void DeletePipe(int id);
	void DeleteKS(int id);
	void DeletePipes(vector <int> IDs);
	void DeleteCompressors(vector <int> IDs);
	vector <vector <int>> CreateCmeshTable();
	vector <vector <int>> CreateDostichimostTable(const vector <vector <int>> &Smeschnost);
	vector <vector <int>> CreateIncedentTable(unordered_map <int, Compressor> KSS);
	void FloydAlgorithm(int from,int to);


	bool CheckCycle(vector <vector <int>> Dostichimost);
	void  TopologicalSort();
	

	//Третья лабораторная работа 
	//Четвертая лабораторная работа 
	void SearchShortWay();
	//Четвертая лабораторная работа 

};

template<typename T_param>
using PipeFilter = bool(*)(const  Pipe& p, T_param param);
//Фильтры для труб
bool CheckById(const Pipe& p, int pipeid);
bool CheckByName(const Pipe& p, string name);
bool CheckByRepair(const Pipe& p, bool repair);
template<typename T_param>
vector <int> FindPipeByFilter(const unordered_map <int, Pipe>& pipes, PipeFilter<T_param> f, T_param parametr) {
	vector <int> id;
	for (auto& p : pipes) {
		if (f(p.second, parametr)) {
			id.push_back(p.first);
		};
	}
	return id;
}







template<typename T_param>
using CompressorFilter = bool(*)(const  Compressor& c, T_param param);
//Фильтры для КС
bool CheckById(const Compressor& c, int compressorId);
bool CheckByName(const Compressor& c, string name);
bool CheckByWorkshopsOutWork(const Compressor& c, pair	<double, double> border);

template<typename T_param>
vector <int> FindCompressorByFilter(const unordered_map <int, Compressor>& compressors, CompressorFilter<T_param> f, T_param parametr) {
	vector <int> id;
	for (auto& c : compressors) {
		if (f(c.second, parametr)) {
			id.push_back(c.first);
		};
	}
	return id;
}



