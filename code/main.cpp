#include "MagazineManage.h"

int main()
{
    read();
    while (1)
    {
        menu();
        
        char ch = getch();
        switch (ch)
        {
        case '1': add(); break; //Â¼Èë¡Ì
        case '2': modify(); break; //ÐÞ¸Ä¡Ì
        case '3': del(); break; //É¾³ý¡Ì
        case '4': find(); break; //²éÕÒ¡Ì
        case '5': analyse(); break; //Í³¼Æ
        case '6': printInfo(); break; //´òÓ¡¡Ì
        default: 
            if (save())
                exit_normal();
            else
                exit_erro();
        }
    }
    system("pause");
    return 0;
}
