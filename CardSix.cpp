#include "CardSix.h"

CardSix::CardSix(const CellPosition& pos) : Card(pos)
{
	cardNumber = 6 ;
	newcellposition = pos;
}

void CardSix::ReadCardParameters(Grid* pGrid)
{

}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	newcellposition.AddCellNum(-(pPlayer->GetjustRolledDiceNum()));
	pGrid->UpdatePlayerCell(pPlayer, newcellposition);

}

CardSix::~CardSix()
{

}

void CardSix::Save(ofstream &OutFile, type t) {

	Card::Save(OutFile, t);

	OutFile <<endl;
}
