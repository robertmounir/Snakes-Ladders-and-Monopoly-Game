#pragma once
#include "Action.h"
#include<fstream>
#include <string>
class SaveAction : public Action
{   string filename;
	ofstream data;
public:
	SaveAction(ApplicationManager* pApp);
	~SaveAction();
	void ReadActionParameters();
	void Execute();
};

