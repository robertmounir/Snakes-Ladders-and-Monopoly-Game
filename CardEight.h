#pragma once

#include "Card.h"

class CardEight : public Card
{

	public:
		CardEight(const CellPosition& pos); // A Constructor takes card position

		virtual void ReadCardParameters(Grid* pGrid); // 

		virtual void Apply(Grid* pGrid, Player* pPlayer);

		virtual void Save(ofstream &OutFile, type t);

		virtual ~CardEight(); // A Virtual Destructor
};

