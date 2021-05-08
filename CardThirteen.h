#pragma once

#include "Card.h"

class CardThirteen :	public Card
{
	bool newCard;
public:
	static Player* CardThirteenOwner;
	static int CardThirteenPrice;
	static int CardThirteenFees;
	static bool isCardThirteenOwned;
	static int CardThirteenNUM;
	static bool saved;

	CardThirteen(const CellPosition & pos);

	virtual void ReadCardParameters(Grid * pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	
	virtual void Save(ofstream& OutFile, type t);


	virtual ~CardThirteen();
};