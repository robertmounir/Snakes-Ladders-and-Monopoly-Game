#include "CellPosition.h"
#include "UI_Info.h"
#include <cmath>
CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v >= 0 && v < 9)
	{	vCell = v;
	return true;
}
	else 
	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h) 
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)

	if (h >= 0 && h <11 )
	{
		hCell = h;
		return true;
	}
	else
	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	///TODO: Implement this function as described in the .h file
	if (vCell < 9 && vCell >= 0 && hCell >= 0 && hCell < 11)
		return true;
	else 
	return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	int hori = cellPosition.HCell();
	int ver = cellPosition.VCell();   ////////////////RObert/////////////
	int cellnum = ((9 - ver) * 11) + (hori-10);


	return cellnum; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	int x = cellNum % 11;
	int y;
	if (cellNum%11 ==0)
    y = 9-cellNum/11;
	else y= 8-cellNum/11;
	position.SetVCell((int)y);
	if (x == 0)
		position.SetHCell(10);
	else
		position.SetHCell(x - 1);

	//////////////////////////////////////////robert////////////////
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum( int addedNum)
{

	/// TODO: Implement this function as described in the .h file
	CellPosition pos;
	int newposition;
	newposition = this->GetCellNum() + addedNum;
	if (newposition < 99)
			pos=this->GetCellPositionFromNum(newposition);
	else
		pos=this->GetCellPositionFromNum(99);
	this->SetHCell(pos.HCell());
	this->SetVCell(pos.VCell());
		// Note: this function updates the data members (vCell and hCell) of the calling object

}