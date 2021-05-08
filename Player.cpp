#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum((playerNum >= 0 && playerNum <= MaxPlayerCount-1)? playerNum:0)
{   
	this->justRolledDiceNum=0;
	this->pCell = pCell;
	this->turnCount = 0;
	this->prevent=0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::SetTurnCount(int count) ////////bishoy///////////
{
	if (count >= 0 && count <= 3)
		turnCount = count;
}

int Player::getPlayerNum() const
{
	return playerNum;
}
int Player::GetjustRolledDiceNum()//////////////bishoy///////////////
{
	return justRolledDiceNum;
}
// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer (pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = (pCell->HasCard()) ? (UI.CellColor_HasCard) : (UI.CellColor_NoCard);
	
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{    
	Output* pOut = pGrid->GetOutput();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	if (this->getpreventP()==1)
	{
		pOut->PrintMessage("You're prevented from rolling the dice this turn...Click to continue");
		this->turnCount = this->turnCount + 1;
		this->setpreventP(0);
		return;
	
	}

	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	this->turnCount = this->turnCount + 1;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	if (this->turnCount==4)
		{   

			this->wallet = this->wallet + 10*diceNumber;
			this->turnCount=0;
			return; 
	}

	if (this->wallet<=0) return;

	// 3- Set the justRolledDiceNum with the passed diceNumber
	this->justRolledDiceNum = diceNumber;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos = pCell->GetCellPosition();
	pos.AddCellNum(diceNumber);

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this,pos);
	// 6- Apply() the game object of the reached cell (if any)
	if (pCell->GetGameObject() != NULL)
	{ 
	GameObject * game_object= pCell->GetGameObject();

	game_object->Apply(pGrid, this);
	}
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (pos.GetCellNum()==99)
		{
			pGrid->SetEndGame(true);
	int winningplayer = this->playerNum;
	pOut->PrintMessage("Player "+ to_string(winningplayer) +" is the winner");
	}
	
}
void Player::setpreventP(int i)
{
	if (i == 0 || i == 1)
		prevent = i;
	else
		prevent = 0;
}

int Player::getpreventP() {
	return prevent;
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(this->playerNum) + "(" ;
	playersInfo += to_string(this->wallet) + ", ";
	playersInfo += to_string(this->turnCount) + ")";
}