#include "CardNine.h"

CardNine::CardNine(const CellPosition& pos ) : Card(pos)
{
	cardNumber = 9;
}

CardNine::~CardNine(void)
{
}

void CardNine::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardNine: Click on the Cell to Move to");
	CellToMoveto = pIn->GetCellClicked();
	pOut->ClearStatusBar();


}


void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	
	pGrid->PrintErrorMessage("You will Move to Cell Num " + to_string(CellToMoveto.GetCellNum())+". Click to continue ...");
	pGrid->UpdatePlayerCell(pPlayer, CellToMoveto);


}

void CardNine::Save(ofstream &OutFile, type t) {

	Card::Save(OutFile, t);

	OutFile <<CellToMoveto.GetCellNum()<<endl;
}

int CardNine::getinfo1()
{

	return int(CellToMoveto.GetCellNum());
}

void CardNine::setinfo1(int w)
{
	CellToMoveto = CellPosition(w);
}
