#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Compressor.h"
#include "EnterValue.h"
#include <set>

class EGTS
{
	
public :

	unordered_map <int, Pipe > Pipes;
	unordered_map <int, Compressor> Compressors;
	struct Branch
	{
		int pid, inid, outid;
	};
	vector	<Branch> Branches;
	EGTS();	
	bool CheckUsable(int compin, int compout);
	Branch CreateBranch();
	set<int> findBranches(int Branch::*field, int parametr);
	void EGTSDeletePipes(int IDs);
	void EGTSDeleteCompressors(int IDs);
	void OutBranchesInfo();
	void static connection(int in, int pid, int out);
};


