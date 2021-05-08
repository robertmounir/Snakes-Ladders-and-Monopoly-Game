#include "SaveAction.h"
#include "Grid.h"

SaveAction::SaveAction(ApplicationManager* pApp):Action(pApp)
{
}

SaveAction::~SaveAction()
{
}

void SaveAction::ReadActionParameters()
{
}

void SaveAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
    Output * pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter File Name In Format (Name.txt)");
	filename = pIn->GetSrting(pOut);
	data.open (filename.c_str());
	if (data.is_open()==false)
	{
	ofstream data (filename.c_str());
	}
	pGrid->calcnumberofobjects();
	pGrid->SaveAll(data, ladder);
	pGrid->SaveAll(data, snake);
	pGrid->SaveAll(data, card);
	data.close();
	pOut->PrintMessage("Grid Data Saved");
}
