#include "stdafx.h"
#include "MenuEngine.h"
//global
std::string dropMenu[] 
{"Pilihan 1",
 "Pilihan 2",
 "Pilihan 3"};
int pilihanDropmen = 0;
int index_y = 0;
std::vector<std::string>* stringVecptr = NULL;
//fungsi
void localNavkey(MenuEngine& obj, int maxIndx,int minIndx,bool cycle)
{
    static bool keydown[2]{false,false};
    if (GetAsyncKeyState(VK_DOWN) < 0)
    {
        if (obj.Index < maxIndx && keydown[0] != true)
        {
            keydown[0] = true;
            obj.Index++;
        }
        if (cycle)
        {
            if (obj.Index == maxIndx && keydown[0] != true)
            {
                keydown[0] = true;
                obj.Index = 0;
            }
        }
    }else keydown[0] = false;
    if (GetAsyncKeyState(VK_UP) < 0)
    {
        if (obj.Index > minIndx && keydown[1] != true)
        {
            keydown[1] = true;
            obj.Index--;
        }
        if (cycle)
        {
            if (obj.Index == minIndx && keydown[1] != true)
            {
                keydown[1] = true;
                obj.Index = maxIndx;
            }
        }
    }else keydown[1] = false;
}

int main()
{
    MenuEngine men;
    MenuEngine men2;
    std::vector <std::string> menus = {"Mulai","Opsi",dropMenu[0],"Keluar"};
    std::vector<std::string> dummyMenu = {"Dummy1","Dummy2","Dummy3"};
    
    men2.setMenu(dummyMenu,NULL,NULL,1);
    std::cout << "Size: " << menus.size() << std::endl;
    std::cin.get();
    do{
        men.setMenu(menus,NULL,NULL,0);
        men.drawMenu(30,10,1,index_y);
        men2.drawMenu(30,25,1,index_y);
        SetPos(50,10); std::cout <<"men2 index: "<< men2.Index;
        SetPos(50,11); std::cout <<"Index Y: "<< index_y;

        //men.drawItem(48,12,NULL,dropMenu[pilihanDropmen]);
        if (men.Index != 4 && index_y != 1)
        {
            localNavkey(men,menus.size(),0,false);
            men2.Index = 0;
        }
        else index_y = 1;
        if (men2.Index != -1 && index_y == 1)
            {
                localNavkey(men2,dummyMenu.size()-1,-1,false);
                men.Index = 3;
            }
        else index_y = 0;
        
    if (index_y == 0)
    {
         if (men.returnsAtIndex(2))
         {
            system("cls");
            stringVecptr = new std::vector<std::string>;
            for(int i = 0; i < sizeof(dropMenu)/sizeof(*dropMenu); i++)
            {
                stringVecptr->push_back(dropMenu[i]);
            }
            MenuEngine dropMen;
            dropMen.setMenu(*stringVecptr,NULL,NULL,0);
            do{
                dropMen.drawMenu(30,10,1,0);
                NavKey(dropMen,stringVecptr->size()-1);
                for (int i = 0 ; i < 3; i++)
                {
                    if (dropMen.returnsAtIndex(i))
                    {
                        pilihanDropmen = i;
                        menus[2] = dropMenu[i];
                        dropMen.kill();
                        system("cls");
                        delete stringVecptr;
                        break;
                    }
                }

            }while(dropMen.isrun());
        }

         if (men.returnsAtIndex(3))
        {
            men.kill();
        }
     }
    }while(men.isrun());
}