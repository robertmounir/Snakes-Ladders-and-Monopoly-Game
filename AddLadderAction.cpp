#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	
	pOut->ClearStatusBar();
}

void AddLadderAction::Execute() 
{
	ReadActionParameters();
	Ladder * pLadder = new Ladder(startPos, endPos);
	Grid * pGrid = pManager->GetGrid();
	Output* pOut= pGrid->GetOutput();
	Cell* end = pGrid->getCellPointer(endPos);
	Snake* pSnake = end->HasSnake();
	if (startPos.IsValidCell()==false)
	{
		pOut->PrintMessage("Invalid Cell");
		return;
	}
	if (startPos.VCell()==0)
	{
		pOut->PrintMessage("Start cell cannot be the last row");
			return;
	}
	if (pGrid->OverlappingLadders(startPos,endPos) == 1)
	{
	pOut->PrintMessage("Two Ladders cannot overlap");
     	return ;
	}
	if (startPos.VCell() ==  endPos.VCell())
	{
		return;
	}
	if (pGrid->OverlappingLadders(startPos,endPos) == -1)
	{
	pOut->PrintMessage("The start of a ladder can't be the end of another snake");
     	return ;
	}
	if (endPos.IsValidCell()==false)
	{
		pOut->PrintMessage("Invalid Cell");
		return;
	}
	
	if (startPos.VCell()<endPos.VCell() )
		{
		pOut->PrintMessage("End cell cannot be smaller than start cell.");
		return;
	}
	if (endPos.HCell()!=startPos.HCell()) 
	{
		pOut->PrintMessage("End cell and start cell are not in the same coloumn.");
	return;
	}
	if (pSnake!=NULL)
	{
	pOut->PrintMessage("The start of a ladder can't be the end of another snake");
	return ;
	}
	
	bool added = pGrid->AddObjectToCell(pLadder);
	if (! added)
	{
		pGrid->PrintErrorMessage("Cell already has another object");
	}

}
