# Console-MenuEngine

HOW TO USE ?

first you need to create the MenuEngine object
then create a vector of string for your menu

e.g
MenuEngine obj;
std::vector <std::string> menu = {"Start","Option","Quit"};

then you can create a do-while loop to make your program run
use the isRun() method to make your program stay running

do{
// do something here
}while(obj.isRun());

DISPLAYING THE MENU
first we need to set up the menu
with method setMenu, it takes 4 argument
useclr,clr, setid

useclr is a flag argument, you need to pass 467 or just use the contexpr USE_CLR 
clr is a color code, use a color code to specify the color
setid, is for menu differentation with another menu instance, useful of you make a multiple menu in the same group instance.


this readme isn't finish
if you want to know how to use it further, you can peek the main.cpp to see how it works yourself
