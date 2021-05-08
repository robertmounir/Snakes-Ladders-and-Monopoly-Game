#pragma once

#include "Card.h"

class CardTen :	public Card
{
	bool newCard;
public:
	static Player* CardTenOwner;
	static int CardTenPrice;
	static int CardTenFees;
	static bool isCardTenOwned;
	static int CardTenNUM;
	static bool saved;

	CardTen(const CellPosition & pos);

	virtual void ReadCardParameters(Grid * pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	void Read(ifstream &Infile);

	virtual void Save(ofstream& OutFile, type t);

	
	virtual ~CardTen();
};