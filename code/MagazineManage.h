#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include "tablePrint.h"

typedef struct subscription //单个订阅信息
{
    int uid;//编号
    char id[8];//杂志代码
    char name[10];//订阅户名
    char idnum[20];//身份证号
    int much;//份数
    float pmoney;//单价
    float tmoney;//小计
}sub;

int uid_max = 0;//存储uid当前最大值，以类推下一记录的uid

typedef struct Node //节点
{
    sub data;
    struct Node* pNext; //指向下一个节点的指针
}Node;

Node *g_pHead = NULL;//头节点

void menu() {
    //设置控制台窗口
    char cmd[128];
    sprintf(cmd, "mode con lines=%d cols=%d", WIN_HEIGHT, WIN_WIDTH);
    system(cmd);
    //打印一个表格菜单
    system("cls");//清空屏幕
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "杂志订阅管理系统 功能菜单");
    printTableMidInfo(MENU_WIDTH, "");

    const char* subMenus[] = {
    "1. 新增订阅信息",
    "2. 修改订阅信息",
    "3. 删除订阅信息",
    "4. 查找订阅信息",
    "5. 统计...",
    "6. 打印...",
    "0. 退出系统   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("请输入所需功能（0-6）：");
}

void pinfo(Node* p)
{
    //通过此函数可以输出参数节点的数据信息
    printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│  UID  │  杂志代码  │  订阅户名  │      身份证号      │订阅份数│  单价  │  小计  │\n");
    printf("│%7d│%12s│%12s│%20s│%8d│%8.2f│%8.2f│\n",
        p->data.uid,
        p->data.id,
        p->data.name,
        p->data.idnum,
        p->data.much,
        p->data.pmoney,
        p->data.tmoney);
    printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}

bool save()
{
    //此函数用于将内存中的信息保存到文件

    //打开文件
    FILE* fp = fopen("data.txt", "w");
    if (fp == NULL)
        return false;
    
    //遍历链表
    Node* p = g_pHead;
    while (p != NULL)
    {
        if (fwrite(&p->data, sizeof(sub), 1, fp) != 1)
        {
            fclose(fp);
            return false;
        }
        p = p->pNext;
    }

    //关闭文件
    fclose(fp);
    return true;
}

void read()
{
    //此函数用于每次启动时自动读取先前数据
    FILE* fp = fopen("data.txt", "r"); //r-只读，b-打开二进制文件
    if (fp == NULL) {
        system("cls");
        printTableHead(MENU_WIDTH+10);
        printTableMidInfo(MENU_WIDTH+10, "警告：没有检测到初始文件，将新建空白数据开始");
        printTableTail(MENU_WIDTH+10);
        system("pause");
        return;
    }

    //创建临时判断结点
    sub temp;
    //读一次数据放入临时结点中，如果成功读入，代表文件没有读完，反之则已读完结束循环
    while (fread(&temp, sizeof(sub), 1, fp) == 1) {
        //创建节点
        Node* pNewNode = (Node*)malloc(sizeof(Node));
        pNewNode->pNext = NULL;

        memcpy(pNewNode, &temp, sizeof(sub));
        if (pNewNode->data.uid >= uid_max)
            uid_max = pNewNode->data.uid;
        
        //头插法
        if (g_pHead == NULL) //原来什么都没有
            g_pHead = pNewNode; //将新创节点作为头
        else
        {
            pNewNode->pNext = g_pHead;
            g_pHead = pNewNode;
        }
    }
}

void del_work(Node* p)
{
    //此函数用于协助驱动“删除订阅信息”功能，进行删除的具体操作
    //判断删除节点是否是头节点
    if (p == g_pHead)
    {
        Node* p1 = g_pHead; //先备份头节点
        g_pHead = g_pHead->pNext;//将头节点的下一节点作为头
        free(p1);//删除“备份的头节点”，即原来要删除的节点
        return;
    }
    else //不是头节点
    {
        Node* p2;
        p2 = p->pNext;
        p->pNext = p2->pNext;
        free(p2);
        return;
    }
}

void add()
{
    //此函数驱动添加订阅信息功能
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 新增订阅信息 >");
    printTableTail(MENU_WIDTH);
    //创建节点
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->pNext = NULL;
    
    //头插法
    if (g_pHead == NULL) //原来什么都没有
        g_pHead = pNewNode; //将新创节点作为头
    else
    {
        pNewNode->pNext = g_pHead;
        g_pHead = pNewNode;
    }

    //信息录入
    printMidInfo("请输入 < 杂志代码 > :");
    scanf("%s", pNewNode->data.id);
    printMidInfo("请输入 < 订阅户名 > :");
    scanf("%s", pNewNode->data.name);
    printMidInfo("请输入 < 身份证号 > :");
    scanf("%s", pNewNode->data.idnum);
    printMidInfo("请输入 < 订阅份数 > :");
    scanf("%d", &pNewNode->data.much);
    printMidInfo("请输入 < 出售单价 > :");
    scanf("%f", &pNewNode->data.pmoney);
    pNewNode->data.tmoney = pNewNode->data.much * pNewNode->data.pmoney;
    printMidInfo("已计算 < 小计 > : ");
    printf("%.2f\n", pNewNode->data.tmoney);
    
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "请确认信息是否正确...");
    printTableMidInfo(MENU_WIDTH, "确认录入 Y/y");
    printTableMidInfo(MENU_WIDTH, "重新录入 N/n");
    printTableMidInfo(MENU_WIDTH, "确认并继续录入... R/r");
    printTableTail(MENU_WIDTH);
    while (1)
    {
        char confirm = getch();
        if (confirm == 'Y' || confirm == 'y')
        {
            pNewNode->data.uid = ++uid_max;
            system("cls");
            if (save())
            {
                printTableHead(MENU_WIDTH);
                printTableMidInfo(MENU_WIDTH, "信息录入成功!");
                printTableTail(MENU_WIDTH);
                printf("\n");
                system("pause");
            }
            else
            {
                printTableHead(MENU_WIDTH);
                printTableMidInfo(MENU_WIDTH, "信息录入失败 x_x");
                printTableTail(MENU_WIDTH);
                printf("\n");
                system("pause");
            }
            break;
        }
        else if (confirm == 'N' || confirm == 'n')
        {
            del_work(pNewNode);
            add(); break;
        }
        else if (confirm == 'R' || confirm == 'r')
        {
            pNewNode->data.uid = ++uid_max;
            add(); break;
        }
        else
            printMidInfo("指令错误，请重新输入（确认 Y/y、返回N/n）： \n");
    }

}

void modify_menu(Node* p)
{
    //此函数协助驱动“修改订阅信息”功能，用于输出修改菜单
    system("cls");//清空屏幕
    printf("您正在更改的记录现有值：\n");
    pinfo(p);
    printf("\n");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "您正在修改订阅信息...");
    printTableMidInfo(MENU_WIDTH, "");
    const char* subMenus[] = {
    "1. 修改 < 杂志代码 >",
    "2. 修改 < 订阅户名 >",
    "3. 修改 < 身份证号 >",
    "4. 修改 < 订阅份数 >",
    "5. 修改 < 订阅单价 >",
    "0. 修改完成   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("请输入所需功能（0-5）");
}

void modi_work(Node* p, const char* type1, void* type2)
{
    //此函数协助驱动“修改订阅信息”功能，用于修改具体信息。
    system("cls");//清空屏幕
    printf("您正在更改的记录现有值：\n");
    pinfo(p);
    printf("\n");
    printTableHead(MENU_WIDTH);
    char info1[40];
    sprintf(info1, "当前操作 < 修改 %s >", type1);
    printTableMidInfo(MENU_WIDTH, info1);
    printTableTail(MENU_WIDTH);
    char info2[40];
    sprintf(info2, "请输入 < 修改后的 %s > :", type1);
    printMidInfo(info2);
    if (type1 == "订阅份数") 
    {
        scanf("%d", type2);
        p->data.tmoney = p->data.much * p->data.pmoney;
    }
    else if (type1 == "订阅单价")
    {
        scanf("%f", type2);
        p->data.tmoney = p->data.much * p->data.pmoney;
    }
    else
        scanf("%s", type2);

    system("cls");
    if (save())
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "信息修改并保存成功!");
        printTableTail(MENU_WIDTH);
        printf("\n");
        printf("您修改完成后的记录值：\n");
        pinfo(p);
        printf("\n");
        system("pause");
    }
    else
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "信息修改失败（未保存） x_x");
        printTableTail(MENU_WIDTH);
        printf("\n");
        system("pause");
    }
}

void modify()
{
    //此函数驱动修改订阅信息功能
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 修改订阅信息 >");
    printTableTail(MENU_WIDTH);
    
    //通过记录的uid查找要修改的记录
    int modi_uid;
    printMidInfo("请输入 < 所需修改的记录的 UID > :");
    scanf("%d", &modi_uid);

    bool find_ok = false;
    Node* p = g_pHead;
    while (p != NULL) //从头开始查找uid
    {
        if (p->data.uid == modi_uid)
        {
            find_ok = true;
            pinfo(p);
            printTableHead(MENU_WIDTH);
            printTableMidInfo(MENU_WIDTH, "请确认这是否是您要修改的记录...");
            printTableMidInfo(MENU_WIDTH, "确认 Y/y");
            printTableMidInfo(MENU_WIDTH, "返回 N/n");
            printTableTail(MENU_WIDTH);
            while (1)
            {
                char confirm = getch();
                if (confirm == 'Y' || confirm == 'y')
                    break;
                else if (confirm == 'N' || confirm == 'n')
                {
                    modify(); return;
                }
                else
                    printMidInfo("指令错误，请重新输入（确认 Y/y、返回N/n）： \n");
            }
            while (1)
            {
                modify_menu(p);
                char ch = getch();
                switch (ch)
                {
                case '1': modi_work(p, "杂志代码",&p->data.id); break; //杂志代码
                case '2': modi_work(p, "订阅户名", &p->data.name); break; //订阅户名
                case '3': modi_work(p, "身份证号", &p->data.idnum); break; //身份证号
                case '4': modi_work(p, "订阅份数", &p->data.much); break; //订阅份数
                case '5': modi_work(p, "订阅单价", &p->data.pmoney); break; //订阅单价
                default: return;
                }
            }
        }
        p = p->pNext;
    }
    if (!find_ok)
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "错误：无法通过此UID找到对应记录，请查正后重试！");
        printTableTail(MENU_WIDTH);
        system("pause");
    }
}

void del()
{
    //此函数驱动删除订阅信息功能
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 删除订阅信息 >");
    printTableTail(MENU_WIDTH);

    //通过记录的uid查找要修改的记录
    int modi_uid;
    printMidInfo("请输入 < 所需修改的记录的 UID > :");
    scanf("%d", &modi_uid);

    bool find_ok = false;
    Node* p = g_pHead;
    while (p->pNext != NULL) //从头开始查找uid
    {
        if (p->pNext->data.uid == modi_uid || p->data.uid == modi_uid)
        {
            find_ok = true;
            pinfo(p);
            printTableHead(MENU_WIDTH);
            printTableMidInfo(MENU_WIDTH, "请确认这是否是您要删除的记录...");
            printTableMidInfo(MENU_WIDTH, "确认 Y/y");
            printTableMidInfo(MENU_WIDTH, "返回 N/n");
            printTableTail(MENU_WIDTH);
            while (1)
            {
                char confirm = getch();
                if (confirm == 'Y' || confirm == 'y')
                {
                    del_work(p);
                    system("cls");
                    if (save())
                    {
                        printTableHead(MENU_WIDTH);
                        printTableMidInfo(MENU_WIDTH, "信息删除并保存成功!");
                        printTableTail(MENU_WIDTH);
                        printf("\n");
                        system("pause");
                    }
                    else
                    {
                        printTableHead(MENU_WIDTH+10);
                        printTableMidInfo(MENU_WIDTH+10, "信息删除成功但保存失败 x_x");
                        printTableTail(MENU_WIDTH+10);
                        printf("\n");
                        system("pause");
                    }
                    return;
                }
                else if (confirm == 'N' || confirm == 'n')
                {
                    return;
                }
                else
                    printMidInfo("指令错误，请重新输入（确认 Y/y、返回N/n）： \n");
            }
        }
        p = p->pNext;
    }
    if (!find_ok)
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "错误：无法通过此UID找到对应记录，请查正后重试！");
        printTableTail(MENU_WIDTH);
        system("pause");
    }
}

void find_menu()
{
    //此函数协助驱动“查找订阅信息”功能，用于输出查找方式菜单
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "请选择查找方式...");
    printTableMidInfo(MENU_WIDTH, "");
    const char* subMenus[] = {
    "1. 通过 < 记录UID > 查找",
    "2. 通过 < 杂志代码 > 查找",
    "3. 通过 < 订阅户名 > 查找",
    "4. 通过 < 身份证号 > 查找",
    "0. 结束查找   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("请输入所需功能（0-4）");
}

void find_work(const char* type1)
{
    //此函数协助驱动“查找订阅信息”功能，用于进行查找工作
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 查找订阅信息 >");
    printTableTail(MENU_WIDTH);

    //通过记录的uid查找要修改的记录
    int modi_uid;
    char info1[50];
    sprintf(info1, "请输入 < 所需查找的记录的 %s > :", type1);
    printMidInfo(info1);

    int temp_uid; char temp_char[20]; bool find_ok = false;
    if (type1 == "UID") //通过UID查找
    {
        scanf("%d", &temp_uid);
        Node* p = g_pHead;
        while (p != NULL) //从头开始查找
        {
            if (p->data.uid == temp_uid)
            {
                find_ok = true;
                system("cls");
                printf("以下是查找出的记录：\n");
                pinfo(p);
                system("pause");
                return;
            }
            p = p->pNext;
        }
        if (!find_ok)
        {
            printTableHead(MENU_WIDTH);
            printTableMidInfo(MENU_WIDTH, "错误：无法通过此UID找到对应记录，请查正后重试！");
            printTableTail(MENU_WIDTH);
            system("pause");
            return;
        }
    }
    else if (type1 == "杂志代码")
    {
        scanf("%s", temp_char);
        Node* p = g_pHead;
        while (p != NULL)
        {
            if (strcmp(p->data.id,temp_char) == 0)
            {
                if (!find_ok)
                {
                    system("cls");
                    printf("以下是查找出的记录：\n");
                    printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
                    printf("│  UID  │  杂志代码  │  订阅户名  │      身份证号      │订阅份数│  单价  │  小计  │\n");
                }
                find_ok = true;
                printf("│%7d│%12s│%12s│%20s│%8d│%8.2f│%8.2f│\n",
                    p->data.uid,
                    p->data.id,
                    p->data.name,
                    p->data.idnum,
                    p->data.much,
                    p->data.pmoney,
                    p->data.tmoney);
            }
            p = p->pNext;
        }
         
        if (!find_ok)
        {
            printTableHead(MENU_WIDTH + 10);
            printTableMidInfo(MENU_WIDTH+10, "错误：无法通过此杂志代码找到对应记录，请查正后重试！");
            printTableTail(MENU_WIDTH + 10);
            system("pause");
            return;
        }
        else
        {
            printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
            system("pause");
            return;
        }
    }
    else if (type1 == "订阅户名")
    {
        scanf("%s", temp_char);
        Node* p = g_pHead;
        while (p != NULL)
        {
            if (strcmp(p->data.name, temp_char) == 0)
            {
                if (!find_ok)
                {
                    printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
                    printf("│  UID  │  杂志代码  │  订阅户名  │      身份证号      │订阅份数│  单价  │  小计  │\n");
                }
                find_ok = true;
                printf("│%7d│%12s│%12s│%20s│%8d│%8.2f│%8.2f│\n",
                    p->data.uid,
                    p->data.id,
                    p->data.name,
                    p->data.idnum,
                    p->data.much,
                    p->data.pmoney,
                    p->data.tmoney);
            }
            p = p->pNext;
        }

        if (!find_ok)
        {
            printTableHead(MENU_WIDTH + 10);
            printTableMidInfo(MENU_WIDTH+10, "错误：无法通过此订阅户名找到对应记录，请查正后重试！");
            printTableTail(MENU_WIDTH + 10);
            system("pause");
            return;
        }
        else
        {
            printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
            system("pause");
            return;
        }
    }  
    else if (type1 == "身份证号")
    {
        scanf("%s", temp_char);
        Node* p = g_pHead;
        while (p != NULL)
        {
            if (strcmp(p->data.idnum, temp_char) == 0)
            {
                if (!find_ok)
                {
                    printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
                    printf("│  UID  │  杂志代码  │  订阅户名  │      身份证号      │订阅份数│  单价  │  小计  │\n");
                }
                find_ok = true;
                printf("│%7d│%12s│%12s│%20s│%8d│%8.2f│%8.2f│\n",
                    p->data.uid,
                    p->data.id,
                    p->data.name,
                    p->data.idnum,
                    p->data.much,
                    p->data.pmoney,
                    p->data.tmoney);
            }
            p = p->pNext;
        }

        if (!find_ok)
        {
            printTableHead(MENU_WIDTH + 10);
            printTableMidInfo(MENU_WIDTH+10, "错误：无法通过此身份证号找到对应记录，请查正后重试！");
            printTableTail(MENU_WIDTH + 10);
            system("pause");
            return;
        }
        else
        {
            printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
            system("pause");
            return;
        }
    }
}

void find()
{
    //此函数驱动查找订阅信息功能
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 查找订阅信息 >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    find_menu();
    while (1)
    {
        char ch = getch();
        switch (ch)
        {
        case '1': find_work("UID"); return; //记录UID
        case '2': find_work("杂志代码"); return; //杂志代码
        case '3': find_work("订阅户名"); return; //订阅户名
        case '4': find_work("身份证号"); return; //身份证号
        default: return;
        }
    }
}

void analyse_menu()
{
    //此函数协助驱动“统计...”功能，用于输出统计方式菜单
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "请选择统计方式...");
    printTableMidInfo(MENU_WIDTH, "");
    const char* subMenus[] = {
    "1. 统计 < 当前杂志销量 >",
    "2. 统计 < 用户购买信息 >",
    "3. 统计 < 当前收入信息 >",
    "0. 结束统计   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("请输入所需功能（0-3）");
}

void analyse_work_magzine()
{
    //此函数协助驱动“统计”功能，用于统计杂志销量
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 统计杂志销量... >");
    printTableTail(MENU_WIDTH);

    char temp[20]; bool find_ok = false;
    int much=0; float income=0;
    printMidInfo("请输入所需统计的 < 杂志代码 > :");
    scanf("%s", temp);
    Node* p = g_pHead;
    while (p != NULL) //从头开始查找
    {
        if (strcmp(p->data.id, temp) == 0)
        {
            find_ok = true;
            much++;
            income += p->data.tmoney;
        }
        p = p->pNext;
    }
    if (!find_ok)
    {
        printTableHead(MENU_WIDTH+10);
        printTableMidInfo(MENU_WIDTH+10, "错误：无法通过此杂志代码找到对应记录，请查正后重试！");
        printTableTail(MENU_WIDTH+10);
        system("pause");
        return;
    }
    else
    {
        printTableHead(MENU_WIDTH);
        char info1[50];
        sprintf(info1, "杂志代码 < %s > 的统计信息：", temp);
        printTableMidInfo(MENU_WIDTH, info1);
        printTableMidInfo(MENU_WIDTH, "");
        char info2[50];
        sprintf(info2, "订阅份数 总计： %d份", much);
        printTableMidInfo(MENU_WIDTH, info2);
        char info3[50];
        sprintf(info3, "订阅收入 总计： %.2f元", income);
        printTableMidInfo(MENU_WIDTH, info3);
        printTableTail(MENU_WIDTH);
        system("pause");
        return;
    }
}

void analyse_work_user()
{
    //此函数协助驱动“统计”功能，用于统计用户支出信息
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 统计用户支出信息... >");
    printTableTail(MENU_WIDTH);

    char temp[20],name[10]; bool find_ok = false;
    float pay = 0;
    printMidInfo("请输入所需统计的用户的 < 身份证号 > :");
    scanf("%s", temp);
    Node* p = g_pHead;
    while (p != NULL) //从头开始查找
    {
        if (strcmp(p->data.idnum, temp) == 0)
        {
            find_ok = true;
            strcpy(name,p->data.name);
            pay += p->data.tmoney;
        }
        p = p->pNext;
    }
    if (!find_ok)
    {
        printTableHead(MENU_WIDTH + 10);
        printTableMidInfo(MENU_WIDTH + 10, "错误：无法通过此身份证号找到对应记录，请查正后重试！");
        printTableTail(MENU_WIDTH + 10);
        system("pause");
        return;
    }
    else
    {
        printTableHead(MENU_WIDTH);
        char info1[50];
        sprintf(info1, "订阅用户 < %s > 的统计信息：", name);
        printTableMidInfo(MENU_WIDTH, info1);
        printTableMidInfo(MENU_WIDTH, "");
        char info2[50];
        sprintf(info2, "用户 身份证号： %s", temp);
        printTableMidInfo(MENU_WIDTH, info2);
        char info3[50];
        sprintf(info3, "支出金额 总计： %.2f元", pay);
        printTableMidInfo(MENU_WIDTH, info3);
        printTableTail(MENU_WIDTH);
        system("pause");
        return;
    }
}

void analyse_work_income()
{
    //此函数协助驱动“统计”功能，用于统计用户支出信息
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 统计当前收入信息... >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    float income = 0;
    //遍历链表
    Node* p = g_pHead;
    while (p != NULL)
    {
        income += p->data.tmoney;
        p = p->pNext;
    }
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前收入信息：");
    printTableMidInfo(MENU_WIDTH, "");
    char info[50];
    sprintf(info, "当前收入 总计： %.2f元", income);
    printTableMidInfo(MENU_WIDTH, info);
    printTableTail(MENU_WIDTH);
    system("pause");
    return;
}

void analyse()
{
    //此函数驱动统计..功能
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 统计... >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    analyse_menu();
    while (1)
    {
        char ch = getch();
        switch (ch)
        {
        case '1': analyse_work_magzine(); return; //杂志销量
        case '2': analyse_work_user(); return; //用户支出信息
        case '3': analyse_work_income(); return; //当前收入信息
        default: return;
        }
    }
}

void printInfo()
{
    //此函数驱动打印...功能
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "当前操作 < 打印... >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│  UID  │  杂志代码  │  订阅户名  │      身份证号      │订阅份数│  单价  │  小计  │\n");
    
    //遍历链表
    Node* p = g_pHead;
    while (p != NULL)
    {
        printf("│%7d│%12s│%12s│%20s│%8d│%8.2f│%8.2f│\n", 
            p->data.uid,
            p->data.id, 
            p->data.name, 
            p->data.idnum, 
            p->data.much, 
            p->data.pmoney, 
            p->data.tmoney);

        p = p->pNext;
    }
    printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
    system("pause");
}

void exit_normal()
{
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "信息保存成功！系统正常退出...");
    printTableMidInfo(MENU_WIDTH, "感谢您的使用 =w=");
    printTableTail(MENU_WIDTH);
    exit(0);
}

void exit_erro()
{
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "信息保存失败！数据将回到上一次正常保存...");
    printTableMidInfo(MENU_WIDTH, "感谢您的使用 =w=");
    printTableTail(MENU_WIDTH);
    exit(0);
}
