#include "Ladder.h"
#include <fstream>
Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{ if (endCellPos.VCell()>startCellPos.VCell() || endCellPos.HCell()!=startCellPos.HCell()|| startCellPos.VCell()==0) 
		return;
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output * pOut = pGrid->GetOutput();
	Input *pIn = pGrid->GetInput();
	int x,y;
	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a ladder. Click to continue");
	pIn->GetPointClicked(x,y);
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	pGrid->UpdatePlayerCell(pPlayer,this->GetEndPosition());
	//    Review the "pGrid" functions and decide which function can be used for that
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream &OutFile,type t )
{
	OutFile <<position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
	
}

Ladder::~Ladder()
{
}
