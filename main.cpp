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
        case '1': add(); break; //¼���
        case '2': modify(); break; //�޸ġ�
        case '3': del(); break; //ɾ����
        case '4': find(); break; //���ҡ�
        case '5': analyse(); break; //ͳ��
        case '6': printInfo(); break; //��ӡ��
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