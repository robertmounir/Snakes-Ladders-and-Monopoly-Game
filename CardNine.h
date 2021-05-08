#pragma once
#include"CellPosition.h"
#include "Card.h"

class CardNine : public Card
{
	CellPosition CellToMoveto;
public:
	CardNine(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // 

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream &OutFile, type t);
	virtual int getinfo1();
	virtual void setinfo1(int w);


	virtual ~CardNine(); // A Virtual Destructor
};

