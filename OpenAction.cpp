#include "OpenAction.h"

#include "CellPosition.h"

#include "Ladder.h"
#include "Snake.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"

#include <fstream>

OpenAction::OpenAction(ApplicationManager *pApp) : Action(pApp)
{
}

OpenAction::~OpenAction()
{
}

void OpenAction::ReadActionParameters() 
{	
}

void OpenAction::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	Output * pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter File Name In Format (Name.txt)");
	filename = pIn->GetSrting(pOut);
	Infile.open (filename.c_str());
	if(Infile.bad())
	{
		pOut->PrintMessage("File doesn't exist!");
	}
	else{
	int d,z,f;
	Infile >> d;
	for(int i=0;i<d;i++)
	{
		Infile >> z;
		Infile >> f;
		CellPosition cellpo(z);
		CellPosition cellpos(f);
		Ladder* Ladp = new Ladder(cellpo,cellpos);
		//Ladp->Read(Infile);
		pGrid->AddObjectToCell(Ladp);
	}
	Infile >> d; //now d = number of snakes
	Infile >> d; //now d = number of cards
	CardTen::CardTenNUM =0;
	for(int i=0;i<d;i++)
	{
		Infile >> z;
		switch(z){
		case 10:
			Infile >> f;
			CellPosition cellposs(f);
			CardTen* cp = new CardTen(cellposs);
			pGrid->AddObjectToCell(cp);
			cp->Read(Infile);
			break;
			//and so on
		}
		
	}
	}
	Infile.close();
}
