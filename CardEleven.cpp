#include "CardEleven.h"

Player* CardEleven::CardElevenOwner = NULL;
int CardEleven::CardElevenPrice = 0;
int CardEleven::CardElevenFees = 0;
bool CardEleven::isCardElevenOwned = false;
int CardEleven::CardElevenNUM = 0;
bool CardEleven::saved = false;


CardEleven::CardEleven(const CellPosition & pos) : Card(pos), newCard(true)
{
	cardNumber = 11;
}

CardEleven::~CardEleven(void)
{
}



void CardEleven::ReadCardParameters(Grid * pGrid)
{
	if(CardElevenNUM==0 || newCard == false)
	{
		Output * pOut = pGrid->GetOutput();
		Input *pIn = pGrid->GetInput();


		pOut->PrintMessage( "Enter Card Price");
		int P=pIn->GetInteger(pOut);
		CardElevenPrice=P;

		pOut-> ClearStatusBar();

		pOut->PrintMessage( "Enter Fees to be removed");
		int F=pIn->GetInteger(pOut);
		CardElevenFees = F;

		pOut-> ClearStatusBar();
	}
	CardElevenNUM++;
	newCard = false;
}


void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	Output * pOut = pGrid->GetOutput();
	Input *pIn = pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);
	if (isCardElevenOwned == false)
	{
		pOut->PrintMessage( "Do you want to buy this card? 1=YES 0=NO");
		int s=pIn->GetInteger(pOut);
		pOut-> ClearStatusBar();
		if (s==1)
			if(pPlayer->GetWallet()>= CardElevenPrice)
			{
				pPlayer->SetWallet(pPlayer->GetWallet()-CardElevenPrice);
				CardElevenOwner =pPlayer;
				isCardElevenOwned =true;
				pOut->PrintMessage( "Done!");
			}
			else
				pOut->PrintMessage( "Not enough money!");
	}
	else
	{
		if(!(pPlayer->getPlayerNum()==CardElevenOwner->getPlayerNum()))
		{
			pPlayer->SetWallet(pPlayer->GetWallet()-CardElevenFees);
		}
	}
}

void CardEleven::Save(ofstream& OutFile, type t)
{
	Card::Save(OutFile, t);
	if (!saved)
	{
		OutFile << CardElevenPrice << " " << CardElevenFees << endl;
		saved = true;
	}
	else
		OutFile << endl;
}