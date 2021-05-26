#pragma once
//constexpression
constexpr auto USE_COLOR = 467;;
constexpr auto CLR_RED = 4;;


 
/*   DEPRECATED

BUILT IN SETPOS MENUENGINE FUNCTION IS DEPRECATED
USE SetPos INSTEAD

*/

/* HOW TO USE
please include stdafx first
YOURSOURCEFILE.CPP
#include "stdafx.h"
#include "MenuEngine.h"
*/

class MenuEngine
{
public:
	//construct/deconstruct
	MenuEngine();

	//var
	int Index;

	//fungsi
	void setMenu(std::vector<std::string> A,int useclr,int color,int setId);
	void drawMenu(int x,int y,int spacing,int id);
	void setPos(SHORT x, SHORT y);
	template<typename arg>
	void drawItem(int x, int y,int indx_highlight,arg args)
	{
		if (CLR_USED) {
			setPos(x, y); clr(color_cd, indx_highlight); std::cout << args;
		}
		SetConsoleTextAttribute(konsol, 7);
		if (!CLR_USED)
		{
			setPos(x, y); std::cout << args;
		}
	}
	void keyinput(int toIndex);
	void kill();

	bool returnsAtIndex(int atIndex);

	//aksessor
	const bool isrun() { return this->isRun; }
private:
	//var
	std::vector<std::string> menus;
	HANDLE konsol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD kordinat;
	bool returnKey[999];
	bool isRun;
	bool CLR_USED;
	int color_cd;
	int menId;
	//fungsi privat
	void arrow(int iter,int);
	void clrd(int clrcd,int indx,int);
	void clr(int clrcd,int indx);
};



void NavKey(MenuEngine& obj, int toIndex);
bool enterAt(MenuEngine& obj, int at);
void SetPos(SHORT x, SHORT y);