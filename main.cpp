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
    std::vector<std::string> menus = {"Mulai","Opsi",dropMenu[0],"Keluar"};
    std::vector<std::string> dummyMenu = {"Dummy1","Dummy2","Dummy3"};
    men.setMenu(&menus,NULL,NULL,0);
    men2.setMenu(&dummyMenu,NULL,NULL,1);
    std::cout << "Memory usage check\n";
    std::cout << "Size of menus vector: " << sizeof(menus) << std::endl;
    std::cout << "Size of men return key: "<< men.SizeOfreturnKey() << std::endl;
    std::cout << "Size of men2 return key: "<< men2.SizeOfreturnKey() << std::endl;
    system("pause");
    system("cls");
    do{
        men.drawMenu(30,10,1,index_y);
        men2.drawMenu(30,25,1,index_y);
        SetPos(50,10); std::cout <<"men2 index: "<< men2.Index;
        SetPos(50,11); std::cout <<"Index Y: "<< index_y;
        SetPos(50,12); std::cout << "Size of men return key: "<< men.SizeOfreturnKey();
        SetPos(50,13); std::cout << "Size of men2 return key: "<< men2.SizeOfreturnKey();
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
         if (men.returnsAtIndex(1))
         {
             //init
             index_y = 0;
             system("cls");
             std::vector<std::string> opsi_1 = {"AA","Ambient occlusion","Shadow quality","Kembali"};
             std::vector<std::string> opsi_2 = {"Subtitle","Language","Sound volume"};
             MenuEngine opsi[2];
             opsi[0].setMenu(&opsi_1,0,0,0);
             opsi[1].setMenu(&opsi_2,0,0,1);
             do{
                 opsi[0].drawMenu(20,5,1,index_y);
                 opsi[1].drawMenu(60,5,1,index_y);
                 if (GetAsyncKeyState(VK_RIGHT) < 0 && index_y == 0)
                 {
                     if (opsi[0].Index != 3)
                     opsi[1].Index = opsi[0].Index;
                     else if (opsi[0].Index == 3)
                     opsi[1].Index = opsi[0].Index - 1;

                     if (index_y < 1)
                     index_y++;
                 }
                 if (GetAsyncKeyState(VK_LEFT) < 0 && index_y == 1)
                 {
                     opsi[0].Index = opsi[1].Index;
                     if (index_y > 0)
                     index_y--;
                 }

                 if(index_y == 0)
                 {
                  NavKey(opsi[0],3);
                  if (opsi[0].returnsAtIndex(3))
                  { 
                      opsi[0].kill();
                      system("cls");
                      index_y = 0;
                  }
                 }
                 else NavKey(opsi[1],2);
                Sleep(15);
             }while(opsi[0].isrun());
         }
         if (men.returnsAtIndex(2))
         {
            system("cls");
            std::cout << "stringVecptr memory before allocation: " << stringVecptr << "\n";
            stringVecptr = new std::vector<std::string>;
            std::cout << "stringVecptr memory after allocation: " << stringVecptr << "\n";
            std::cout << "stringVecptr after allocation: " << stringVecptr->size() << "\n";
            for(int i = 0; i < sizeof(dropMenu)/sizeof(*dropMenu); i++)
            {
                stringVecptr->push_back(dropMenu[i]);
            }
            MenuEngine dropMen;
            dropMen.setMenu(stringVecptr,NULL,NULL,0);
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
                        std::cout << std::endl;
                        std::cout << "stringVecptr before deletion: " << stringVecptr->size() << std::endl;
                        delete stringVecptr;
                        std::cout << "stringVecptr after deletion: " << stringVecptr->size() << std::endl;
                        stringVecptr = nullptr;
                        system("pause");
                        system("cls");
                        break;
                    }
                }
            Sleep(15);
            }while(dropMen.isrun());
        }
         if (men.returnsAtIndex(3))
        {
            system("cls");
            men.kill();
    std::cout << "Memory usage check\n";
    std::cout << "Size of menus vector: " << sizeof(menus) << std::endl;
    std::cout << "Size of men return key: "<< men.SizeOfreturnKey() << std::endl;
    std::cout << "Size of men2 return key: "<< men2.SizeOfreturnKey() << std::endl;
    system("pause");
        }
     }
     Sleep(15);
    }while(men.isrun());
}