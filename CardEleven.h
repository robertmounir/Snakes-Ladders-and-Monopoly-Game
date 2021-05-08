#pragma once

#include "Card.h"

class CardEleven :	public Card
{
	bool newCard;
public:
	static Player* CardElevenOwner;
	static int CardElevenPrice;
	static int CardElevenFees;
	static bool isCardElevenOwned;
	static int CardElevenNUM;
	static bool saved;


	CardEleven(const CellPosition & pos);

	virtual void ReadCardParameters(Grid * pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual void Save(ofstream& OutFile, type t);

	
	virtual ~CardEleven();
};