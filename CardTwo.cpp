#include "CardTwo.h"

CardTwo::CardTwo(const CellPosition & pos) : Card(pos) 
{
	cardNumber = 2; 
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::ReadCardParameters(Grid * pGrid)
{
	Output * pOut = pGrid->GetOutput();
	Input *pIn = pGrid->GetInput();
	pOut->PrintMessage( "New CardTwo: Enter a positive wallet amount to be added (or it'll be set to 100)");
	int amount = pIn->GetInteger(pOut);
	walletAmount= amount>=0 ? amount:100;
	pOut-> ClearStatusBar();

}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	
	Card::Apply(pGrid,pPlayer);
	pPlayer->SetWallet(pPlayer->GetWallet()+walletAmount);
}

void CardTwo::Save(ofstream &OutFile, type t) {

	Card::Save(OutFile, t);

	OutFile << walletAmount<<endl;
}

int CardTwo::getinfo1()
{
	return walletAmount;
}

void CardTwo::setinfo1(int w)
{
	walletAmount = w;
}
