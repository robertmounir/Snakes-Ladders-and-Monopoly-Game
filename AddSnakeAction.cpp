#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager *pApp) : Action(pApp)
{
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters() 
{	
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void AddSnakeAction::Execute() 
{
	ReadActionParameters();
	
	Snake* pSnake = new Snake(startPos, endPos);
	Grid * pGrid = pManager->GetGrid();
	Output *pOut = pGrid->GetOutput();
	Cell* end = pGrid->getCellPointer(endPos);
	Ladder* pLadder = end->HasLadder();
if (startPos.IsValidCell()==false)
	{
		pOut->PrintMessage("Invalid Cell");
		return;
	}
	if (startPos.VCell() == NumVerticalCells-1)
	{
		pOut->PrintMessage("Start cell can't be in the first row");
		return;
	}

	if (startPos.VCell() ==  endPos.VCell())
	{
		return;
	}

	if (endPos.IsValidCell()==false)
	{
		pOut->PrintMessage("Invalid Cell");
		return;
	}
	if (startPos.VCell()>endPos.VCell() )
		{
		pOut->PrintMessage("End cell cannot be smaller than start cell.");
		return;
	}
	if (endPos.HCell()!=startPos.HCell()) 
	{
		pOut->PrintMessage("End cell and start cell are not in the same coloumn.");
	return;
	}
	if (pGrid->OverlappingSnakes(startPos,endPos) == 1)
	{
	pOut->PrintMessage("Two Snakes cannot overlap");
     	return ;
	}
	if (pGrid->OverlappingSnakes(startPos,endPos) == -1)
	{
	pOut->PrintMessage("The start of a ladder can't be the end of another snake");
	return ; 
	}

	if (pLadder!=NULL)
	{
		pOut->PrintMessage("The end of a snake can't be the start of another ladder");
     	return ;
	}

	bool added = pGrid->AddObjectToCell(pSnake);
	if (! added)
	{
		pGrid->PrintErrorMessage("Cell already has another object");
	}
}
