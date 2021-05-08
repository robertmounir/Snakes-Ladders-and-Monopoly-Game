#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Snake.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		delete CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

Cell* Grid::getCellPointer(CellPosition pos)
{
	Cell * p = CellList[pos.VCell()][pos.HCell()];
	return p;
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			//Mariam
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder()!=NULL)
				return CellList[i][j]->HasLadder();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}
//Mariam
Snake * Grid::GetNextSnake(const CellPosition & position)
{

	int startH = position.HCell();
	for (int i = position.VCell(); i >= 0; i--) 
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasSnake()!=NULL)
				return CellList[i][j]->HasSnake();

		}
		startH = 0;
	}
	return NULL; 
}

int Grid::OverlappingSnakes (CellPosition&start, CellPosition&end)
{
	int top= start.VCell();
	int bottom = end.VCell();
	int hCell = start.HCell();
	for ( int i= top; i<= bottom-top ; i++)
	{
		if (CellList[i][hCell]->HasSnake())
			return 1;
	}
	for ( int i= top; i<= NumVerticalCells-1 ; i++)
	{
		if (CellList[i][hCell]->HasLadder())
		{
	     Ladder * pLadder = CellList[i][hCell]->HasLadder();
	     if ((pLadder->GetEndPosition()).VCell() == top)
			return -1;
		}
	}
	for ( int i= top; i>=0 ; i--)
	{
		if (CellList[i][hCell]->HasSnake())
		{
			Snake * pSnake = CellList[i][hCell]->HasSnake();
			if ( (pSnake->GetEndPosition()).VCell() >= top)
				return 1;
		}
	}
	return 0;
}

int Grid::OverlappingLadders (CellPosition&start, CellPosition&end)
{
	int bottom= start.VCell();
	int top = end.VCell();
	int hCell = start.HCell();
	for ( int i= bottom; i>= top ; i--)
	{
		if (CellList[i][hCell]->HasLadder())
			return 1;
	}

	for ( int i= top; i<= NumVerticalCells-1 ; i++)
	{
		if (CellList[i][hCell]->HasSnake())
		{
	     Snake * pSnake = CellList[i][hCell]->HasSnake();
		 if ((pSnake->GetEndPosition()).VCell() == bottom)
			return -1;
		}
		}
	for ( int i= bottom; i<=NumVerticalCells-1 ; i++)
	{
		if (CellList[i][hCell]->HasLadder())
		{
			Ladder * pLadder = CellList[i][hCell]->HasLadder();
			if ( (pLadder->GetEndPosition()).VCell() <= bottom)
				return 1;
		}
	}
	return 0;
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}

void Grid::calcnumberofobjects()
{
	numladders = 0;
	numsnakes = 0;
	numcards = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder() != NULL)
				numladders++;
			else if (CellList[i][j]->HasSnake() != NULL)
				numsnakes++;
			else if (CellList[i][j]->HasCard() != NULL)
				numcards++;
		}
	}

}

void Grid::SaveAll(ofstream &OutFile, type t)
{

	switch (t)
	{
	case ladder:
		OutFile<<numladders<<endl;

		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasLadder() != NULL)
					CellList[i][j]->HasLadder()->Save(OutFile, t);

			}
		}
		break;
	case snake :
		OutFile << numsnakes << endl;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasSnake() != NULL)
					CellList[i][j]->HasSnake()->Save(OutFile, t);

			}
		}
		break;
	case card :
		OutFile << numcards << endl;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
					if (CellList[i][j]->HasCard() != NULL)
						CellList[i][j]->HasCard()->Save(OutFile, t);
			}
		}
		CardTen::saved = false;
		CardEleven::saved = false;
		CardTwelve::saved = false;
		CardThirteen::saved = false;
		CardFourteen::saved = false;
		
		break;

	}

}

void Grid::ClearGridArea()  ////////////////not complete/////////////////////
{
	for (int i = 0; i < NumVerticalCells; ++i) {
		for (int j = 0; j < NumHorizontalCells; ++j) {
			Ladder* Lptr = CellList[i][j]->HasLadder();
			Snake* Sptr = CellList[i][j]->HasSnake();
			Card* Cptr = CellList[i][j]->HasCard();
			CellPosition pos(i, j);
			if (Lptr != NULL) {
				RemoveObjectFromCell(pos);
				Lptr = NULL;
			}
			else if (Sptr != NULL) {
				RemoveObjectFromCell(pos);
				Sptr = NULL;
			}
			else if (Cptr != NULL) {
				RemoveObjectFromCell(pos);
				Cptr = NULL;
			}
			else {}
		}
	}

}

void Grid::ResetPlayers() //////////// done ///////////
{
	CellPosition pos(NumVerticalCells - 1, 0);

	for (int i = 0; i < MaxPlayerCount; ++i) {
		PlayerList[i]->SetWallet(100);
		Cell* Cptr = PlayerList[i]->GetCell();
		
		UpdatePlayerCell(PlayerList[i], pos);
		PlayerList[i]->SetTurnCount(0);
		currPlayerNumber = 0;
	}
	for (int i = 0; i < NumVerticalCells; ++i) {
	for (int j = 0; j < NumHorizontalCells; ++j) {
		Card* Cptr = CellList[i][j]->HasCard();
		if (Cptr != NULL) {
			CardTen* Tenptr = dynamic_cast<CardTen*>(Cptr);
			if (Tenptr != NULL) {
				Tenptr->isCardTenOwned = false;
				Tenptr->CardTenOwner = NULL;
			}
			CardEleven* Elevenptr = dynamic_cast<CardEleven*>(Cptr);
			if (Elevenptr != NULL) {
				Elevenptr->isCardElevenOwned = false;
				Elevenptr->CardElevenOwner = NULL;
			}
			CardTwelve* Twelveptr = dynamic_cast<CardTwelve*>(Cptr);
			if (Twelveptr != NULL) {
				Twelveptr->isCardTwelveOwned = false;
				Twelveptr->CardTwelveOwner = NULL;
			}
			CardThirteen* Thirteenptr = dynamic_cast<CardThirteen*>(Cptr);
			if (Thirteenptr != NULL) {
				Thirteenptr->isCardThirteenOwned = false;
				Thirteenptr->CardThirteenOwner = NULL;
			}
			CardFourteen* Fourteenptr = dynamic_cast<CardFourteen*>(Cptr);
			if (Fourteenptr != NULL) {
				Fourteenptr->isCardFourteenOwned = false;
				Fourteenptr->CardFourteenOwner = NULL;
			}
		}
	}
  }

}

