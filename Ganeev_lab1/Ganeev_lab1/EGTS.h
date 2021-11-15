#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Compressor.h"
#include "EnterValue.h"
class EGTS
{
	struct Branch
	{
		int pipeid, incompid, outcompid;

	};
	unordered_map <int, Pipe> pipes;
	unordered_map <int, Compressor> compressors;
	
public :

	bool ConnectKS(int pipeid ,int inid,int outid );
	EGTS();

};

