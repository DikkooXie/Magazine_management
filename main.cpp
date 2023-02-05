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
        case '1': add(); break; //录入√
        case '2': modify(); break; //修改√
        case '3': del(); break; //删除√
        case '4': find(); break; //查找√
        case '5': analyse(); break; //统计
        case '6': printInfo(); break; //打印√
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