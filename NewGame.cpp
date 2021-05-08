#include "NewGame.h"
#include "Grid.h"
#include "Player.h"


NewGame::NewGame(ApplicationManager* pApp) :Action(pApp)
{

}

void NewGame::ReadActionParameters()
{

}

void NewGame::Execute()
{
	Grid* Gptr = pManager->GetGrid();
	//Gptr->ClearGridArea();
	Gptr->ResetPlayers();
	Gptr->UpdateInterface();
}

NewGame::~NewGame()
{

}