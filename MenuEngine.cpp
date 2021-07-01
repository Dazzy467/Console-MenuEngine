#include "stdafx.h"
#include "MenuEngine.h"


MenuEngine::MenuEngine()
{
	kordinat.X = 0;
	kordinat.Y = 0;
	Index = 0;
	menId = 0;
	isRun = true;
	CLR_USED = 0;
	color_cd = 0;
	fromKeyinput = UpdateMenu;
	MessageListener = standBy;
	msg_pointer = &this->MessageListener;
}

void MenuEngine::setMenu(std::vector<std::string>* A,flags useclr,int color,int setId)
{
	menId = setId;
	this->menus = A;
	//check for vector size
	if (returnKey.size() != A->size())
	returnKey.resize(A->size(),false);
	if (useclr != Ignore)
	drawMenuFlg = useclr;
	color_cd = color;
}

void MenuEngine::drawMenu(int x, int y,int spacing,int id)
{
	if (fromKeyinput == UpdateMenu || MessageListener == UpdateMenu)
	{
		if (drawMenuFlg == USE_ARROW)
			for (size_t i = 0; i < menus->size(); i++)
			{
				setPos(x, y + (i * spacing)); arrow(i, id); std::cout << menus->at(i);
			}
		else if (drawMenuFlg == USE_COLOR)
		{
			for (size_t i = 0; i < menus->size(); i++)
			{
				setPos(x, y + (i * spacing)); clrd(color_cd, i, id); std::cout << menus->at(i);
			}
			SetConsoleTextAttribute(konsol, 7);
		}
		overrideMessage(MenuHalt);
	}
}
//experimental

void MenuEngine::keyinput(int toIndex)
{
	static bool keydown[2]{false,false};
	if (GetAsyncKeyState(VK_DOWN) < 0)
	{
		if (Index < toIndex && keydown[0] != true)
		{
			keydown[0] = true;
			Index++;
			fromKeyinput = UpdateMenu;
		}
		if (Index == toIndex && keydown[0] != true)
		{
			keydown[0] = true;
			Index = 0;
			fromKeyinput = UpdateMenu;
		}
	}
	else {
		keydown[0] = false;
		
	}
	if (GetAsyncKeyState(VK_UP) < 0 )
	{
		if (Index > 0 && keydown[1] != true)
		{
			keydown[1] = true;
			Index--;
			fromKeyinput = UpdateMenu;
		}
		if (Index == 0 && keydown[1] != true)
		{
			keydown[1] = true;
			Index = toIndex;
			fromKeyinput = UpdateMenu;
		}
	}
	else {
		keydown[1] = false;
		
	}

}

void MenuEngine::kill()
{
	this->isRun = false;
}

bool MenuEngine::returnsAtIndex(int atIndex)
{
	if (GetAsyncKeyState(VK_RETURN) < 0 && Index == atIndex)
	{
		if (returnKey[atIndex] != true)
			{
				returnKey[atIndex]  = true;
			}
	}
	else if (returnKey[atIndex]  == true && GetAsyncKeyState(VK_RETURN) == 0)    // New index needs a new boolean variable so i used an array of bool to make this work
	{                                                                              // i think this looks like a bad programming, is it innefficient ?
		returnKey[atIndex]  = false;
		return true;
		return false;

	}
	else returnKey[atIndex]  = false;
	return false;
}

void MenuEngine::sendMessage(messanger msg)
{
	MessageListener = msg;
}

void MenuEngine::setFlag(flags flg)
{
	FLAG = flg;
}

void MenuEngine::setPos(SHORT x, SHORT y)
{
	kordinat.X = x;
	kordinat.Y = y;
	SetConsoleCursorPosition(konsol, kordinat);
}

void MenuEngine::arrow(int iter,int indx_x)
{
	if (Index == iter && menId == indx_x )
		std::cout << "->";
	else std::cout << "  ";
}

void MenuEngine::clrd(int clrcd,int indx,int indx_x)
{
	if(Index == indx && menId == indx_x )
	SetConsoleTextAttribute(konsol, clrcd);
	else SetConsoleTextAttribute(konsol, 7);
}

void MenuEngine::clr(int clrcd, int indx)
{
	if (Index == indx)
		SetConsoleTextAttribute(konsol, clrcd);
	else SetConsoleTextAttribute(konsol, 7);
}

void MenuEngine::overrideMessage(messanger msg)
{
	fromKeyinput = msg;
	MessageListener = msg;
}

void MenuEngine::reInit()
{
	menus = nullptr;
	Index = 0;
	isRun = true;
}

void NavKey(MenuEngine& obj, int toIndex)
{
	static bool keydown[2]{false,false};
	if (GetAsyncKeyState(VK_DOWN) < 0)
	{


		if (obj.Index < toIndex && keydown[0] != true)
		{
			keydown[0] = true;
			obj.Index++;
		}
		if (obj.Index == toIndex && keydown[0] != true)
		{
			keydown[0] = true;
			obj.Index = 0;
		}
	}
	else keydown[0] = false;
	if (GetAsyncKeyState(VK_UP) < 0)
	{
		if (obj.Index > 0 && keydown[1] != true)
		{
			keydown[1] = true;
			obj.Index--;
		}
		if (obj.Index == 0 && keydown[1] != true)
		{
			keydown[1] = true;
			obj.Index = toIndex;
		}
	}
	else keydown[1] = false;
}

bool enterAt(MenuEngine& obj, int at)
{
	static bool returnkey = false;
	if (GetAsyncKeyState(VK_RETURN) < 0 && obj.Index == at)
	{
		     returnkey  = true;                        // i don't know why i make another "ENTER KEY PROCESSOR" function
	}                                                  // i thought i could optimize it a bit so i done it anyways
    else returnkey  = false;
	return returnkey;
}

void SetPos(SHORT x, SHORT y)
{
	COORD pos{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}