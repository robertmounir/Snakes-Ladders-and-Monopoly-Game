#include "CardFive.h"


CardFive::CardFive(const CellPosition &pos) : Card(pos)
{
	cardNumber = 5;
	newcellposition = pos;
}
void CardFive::ReadCardParameters(Grid* pGrid) {
	//this fuction does not take any parameters
}
void CardFive::Apply(Grid* pGrid, Player* pPlayer) 
{
	Card::Apply(pGrid, pPlayer);
	newcellposition.AddCellNum(pPlayer->GetjustRolledDiceNum());
	pGrid->UpdatePlayerCell(pPlayer,newcellposition);
}
CardFive::~CardFive() {
	////////an empty destructor///////////
}

void CardFive::Save(ofstream &OutFile, type t) {

	Card::Save(OutFile, t);

	OutFile <<endl;
}

