#include "stdafx.h"
#include "MenuEngine.h"

std::vector<std::vector<std::string>> main_menu = {{"Start","Option","Exit"},{"AA","SHADOW","LIGHTING","Exit"}};
MenuEngine menu_instance;
int menu_flag = 0;
// 1 MENUENGINE INSTANCE TO HANDLE A MENU
int main()
{
    menu_instance.setMenu(&main_menu[0],0,0,0);
    do{
        menu_instance.drawMenu(30,10,1,0);
        if (menu_flag == 0)
        {
          menu_instance.keyinput(main_menu[0].size()-1);
          if (menu_instance.returnsAtIndex(1))
          {
              menu_instance.sendMessage(UpdateMenu);
              menu_flag = 1;
              menu_instance.setMenu(&main_menu[1],0,0,0);
              menu_instance.Index = 0;
              system("cls");
          }
          if (menu_instance.returnsAtIndex(2))
              menu_instance.kill();
        }
        else if (menu_flag == 1)
        {
            menu_instance.keyinput(main_menu[1].size()-1);
            if (menu_instance.returnsAtIndex(3))
            {
                menu_instance.sendMessage(UpdateMenu);
                menu_flag = 0;
                menu_instance.setMenu(&main_menu[0],0,0,0);
                menu_instance.Index = 1;
                system("cls");
            }
        }
    Sleep(1);
    }while(menu_instance.isrun());
}