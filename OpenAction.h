#pragma once
#include<fstream>

#include "Action.h"

class OpenAction : public Action
{
	string filename;
	ifstream Infile;
public:
	OpenAction(ApplicationManager *pApp); 
		
	virtual void ReadActionParameters();
	
	virtual void Execute(); 


	virtual ~OpenAction();
};
