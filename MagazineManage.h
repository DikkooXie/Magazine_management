#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include "tablePrint.h"

typedef struct subscription //����������Ϣ
{
    int uid;//���
    char id[8];//��־����
    char name[10];//���Ļ���
    char idnum[20];//���֤��
    int much;//����
    float pmoney;//����
    float tmoney;//С��
}sub;

int uid_max = 0;//�洢uid��ǰ���ֵ����������һ��¼��uid

typedef struct Node //�ڵ�
{
    sub data;
    struct Node* pNext; //ָ����һ���ڵ��ָ��
}Node;

Node *g_pHead = NULL;//ͷ�ڵ�

void menu() {
    //���ÿ���̨����
    char cmd[128];
    sprintf(cmd, "mode con lines=%d cols=%d", WIN_HEIGHT, WIN_WIDTH);
    system(cmd);
    //��ӡһ�����˵�
    system("cls");//�����Ļ
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��־���Ĺ���ϵͳ ���ܲ˵�");
    printTableMidInfo(MENU_WIDTH, "");

    const char* subMenus[] = {
    "1. ����������Ϣ",
    "2. �޸Ķ�����Ϣ",
    "3. ɾ��������Ϣ",
    "4. ���Ҷ�����Ϣ",
    "5. ͳ��...",
    "6. ��ӡ...",
    "0. �˳�ϵͳ   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("���������蹦�ܣ�0-6����");
}

void pinfo(Node* p)
{
    //ͨ���˺���������������ڵ��������Ϣ
    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��  UID  ��  ��־����  ��  ���Ļ���  ��      ���֤��      �����ķ�����  ����  ��  С��  ��\n");
    printf("��%7d��%12s��%12s��%20s��%8d��%8.2f��%8.2f��\n",
        p->data.uid,
        p->data.id,
        p->data.name,
        p->data.idnum,
        p->data.much,
        p->data.pmoney,
        p->data.tmoney);
    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("\n");
}

bool save()
{
    //�˺������ڽ��ڴ��е���Ϣ���浽�ļ�

    //���ļ�
    FILE* fp = fopen("data.txt", "w");
    if (fp == NULL)
        return false;
    
    //��������
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

    //�ر��ļ�
    fclose(fp);
    return true;
}

void read()
{
    //�˺�������ÿ������ʱ�Զ���ȡ��ǰ����
    FILE* fp = fopen("data.txt", "r"); //r-ֻ����b-�򿪶������ļ�
    if (fp == NULL) {
        system("cls");
        printTableHead(MENU_WIDTH+10);
        printTableMidInfo(MENU_WIDTH+10, "���棺û�м�⵽��ʼ�ļ������½��հ����ݿ�ʼ");
        printTableTail(MENU_WIDTH+10);
        system("pause");
        return;
    }

    //������ʱ�жϽ��
    sub temp;
    //��һ�����ݷ�����ʱ����У�����ɹ����룬�����ļ�û�ж��꣬��֮���Ѷ������ѭ��
    while (fread(&temp, sizeof(sub), 1, fp) == 1) {
        //�����ڵ�
        Node* pNewNode = (Node*)malloc(sizeof(Node));
        pNewNode->pNext = NULL;

        memcpy(pNewNode, &temp, sizeof(sub));
        if (pNewNode->data.uid >= uid_max)
            uid_max = pNewNode->data.uid;
        
        //ͷ�巨
        if (g_pHead == NULL) //ԭ��ʲô��û��
            g_pHead = pNewNode; //���´��ڵ���Ϊͷ
        else
        {
            pNewNode->pNext = g_pHead;
            g_pHead = pNewNode;
        }
    }
}

void del_work(Node* p)
{
    //�˺�������Э��������ɾ��������Ϣ�����ܣ�����ɾ���ľ������
    //�ж�ɾ���ڵ��Ƿ���ͷ�ڵ�
    if (p == g_pHead)
    {
        Node* p1 = g_pHead; //�ȱ���ͷ�ڵ�
        g_pHead = g_pHead->pNext;//��ͷ�ڵ����һ�ڵ���Ϊͷ
        free(p1);//ɾ�������ݵ�ͷ�ڵ㡱����ԭ��Ҫɾ���Ľڵ�
        return;
    }
    else //����ͷ�ڵ�
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
    //�˺���������Ӷ�����Ϣ����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ����������Ϣ >");
    printTableTail(MENU_WIDTH);
    //�����ڵ�
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->pNext = NULL;
    
    //ͷ�巨
    if (g_pHead == NULL) //ԭ��ʲô��û��
        g_pHead = pNewNode; //���´��ڵ���Ϊͷ
    else
    {
        pNewNode->pNext = g_pHead;
        g_pHead = pNewNode;
    }

    //��Ϣ¼��
    printMidInfo("������ < ��־���� > :");
    scanf("%s", pNewNode->data.id);
    printMidInfo("������ < ���Ļ��� > :");
    scanf("%s", pNewNode->data.name);
    printMidInfo("������ < ���֤�� > :");
    scanf("%s", pNewNode->data.idnum);
    printMidInfo("������ < ���ķ��� > :");
    scanf("%d", &pNewNode->data.much);
    printMidInfo("������ < ���۵��� > :");
    scanf("%f", &pNewNode->data.pmoney);
    pNewNode->data.tmoney = pNewNode->data.much * pNewNode->data.pmoney;
    printMidInfo("�Ѽ��� < С�� > : ");
    printf("%.2f\n", pNewNode->data.tmoney);
    
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ȷ����Ϣ�Ƿ���ȷ...");
    printTableMidInfo(MENU_WIDTH, "ȷ��¼�� Y/y");
    printTableMidInfo(MENU_WIDTH, "����¼�� N/n");
    printTableMidInfo(MENU_WIDTH, "ȷ�ϲ�����¼��... R/r");
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
                printTableMidInfo(MENU_WIDTH, "��Ϣ¼��ɹ�!");
                printTableTail(MENU_WIDTH);
                printf("\n");
                system("pause");
            }
            else
            {
                printTableHead(MENU_WIDTH);
                printTableMidInfo(MENU_WIDTH, "��Ϣ¼��ʧ�� x_x");
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
            printMidInfo("ָ��������������루ȷ�� Y/y������N/n���� \n");
    }

}

void modify_menu(Node* p)
{
    //�˺���Э���������޸Ķ�����Ϣ�����ܣ���������޸Ĳ˵�
    system("cls");//�����Ļ
    printf("�����ڸ��ĵļ�¼����ֵ��\n");
    pinfo(p);
    printf("\n");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "�������޸Ķ�����Ϣ...");
    printTableMidInfo(MENU_WIDTH, "");
    const char* subMenus[] = {
    "1. �޸� < ��־���� >",
    "2. �޸� < ���Ļ��� >",
    "3. �޸� < ���֤�� >",
    "4. �޸� < ���ķ��� >",
    "5. �޸� < ���ĵ��� >",
    "0. �޸����   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("���������蹦�ܣ�0-5��");
}

void modi_work(Node* p, const char* type1, void* type2)
{
    //�˺���Э���������޸Ķ�����Ϣ�����ܣ������޸ľ�����Ϣ��
    system("cls");//�����Ļ
    printf("�����ڸ��ĵļ�¼����ֵ��\n");
    pinfo(p);
    printf("\n");
    printTableHead(MENU_WIDTH);
    char info1[40];
    sprintf(info1, "��ǰ���� < �޸� %s >", type1);
    printTableMidInfo(MENU_WIDTH, info1);
    printTableTail(MENU_WIDTH);
    char info2[40];
    sprintf(info2, "������ < �޸ĺ�� %s > :", type1);
    printMidInfo(info2);
    if (type1 == "���ķ���") 
    {
        scanf("%d", type2);
        p->data.tmoney = p->data.much * p->data.pmoney;
    }
    else if (type1 == "���ĵ���")
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
        printTableMidInfo(MENU_WIDTH, "��Ϣ�޸Ĳ�����ɹ�!");
        printTableTail(MENU_WIDTH);
        printf("\n");
        printf("���޸���ɺ�ļ�¼ֵ��\n");
        pinfo(p);
        printf("\n");
        system("pause");
    }
    else
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "��Ϣ�޸�ʧ�ܣ�δ���棩 x_x");
        printTableTail(MENU_WIDTH);
        printf("\n");
        system("pause");
    }
}

void modify()
{
    //�˺��������޸Ķ�����Ϣ����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < �޸Ķ�����Ϣ >");
    printTableTail(MENU_WIDTH);
    
    //ͨ����¼��uid����Ҫ�޸ĵļ�¼
    int modi_uid;
    printMidInfo("������ < �����޸ĵļ�¼�� UID > :");
    scanf("%d", &modi_uid);

    bool find_ok = false;
    Node* p = g_pHead;
    while (p != NULL) //��ͷ��ʼ����uid
    {
        if (p->data.uid == modi_uid)
        {
            find_ok = true;
            pinfo(p);
            printTableHead(MENU_WIDTH);
            printTableMidInfo(MENU_WIDTH, "��ȷ�����Ƿ�����Ҫ�޸ĵļ�¼...");
            printTableMidInfo(MENU_WIDTH, "ȷ�� Y/y");
            printTableMidInfo(MENU_WIDTH, "���� N/n");
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
                    printMidInfo("ָ��������������루ȷ�� Y/y������N/n���� \n");
            }
            while (1)
            {
                modify_menu(p);
                char ch = getch();
                switch (ch)
                {
                case '1': modi_work(p, "��־����",&p->data.id); break; //��־����
                case '2': modi_work(p, "���Ļ���", &p->data.name); break; //���Ļ���
                case '3': modi_work(p, "���֤��", &p->data.idnum); break; //���֤��
                case '4': modi_work(p, "���ķ���", &p->data.much); break; //���ķ���
                case '5': modi_work(p, "���ĵ���", &p->data.pmoney); break; //���ĵ���
                default: return;
                }
            }
        }
        p = p->pNext;
    }
    if (!find_ok)
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "�����޷�ͨ����UID�ҵ���Ӧ��¼������������ԣ�");
        printTableTail(MENU_WIDTH);
        system("pause");
    }
}

void del()
{
    //�˺�������ɾ��������Ϣ����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ɾ��������Ϣ >");
    printTableTail(MENU_WIDTH);

    //ͨ����¼��uid����Ҫ�޸ĵļ�¼
    int modi_uid;
    printMidInfo("������ < �����޸ĵļ�¼�� UID > :");
    scanf("%d", &modi_uid);

    bool find_ok = false;
    Node* p = g_pHead;
    while (p->pNext != NULL) //��ͷ��ʼ����uid
    {
        if (p->pNext->data.uid == modi_uid || p->data.uid == modi_uid)
        {
            find_ok = true;
            pinfo(p);
            printTableHead(MENU_WIDTH);
            printTableMidInfo(MENU_WIDTH, "��ȷ�����Ƿ�����Ҫɾ���ļ�¼...");
            printTableMidInfo(MENU_WIDTH, "ȷ�� Y/y");
            printTableMidInfo(MENU_WIDTH, "���� N/n");
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
                        printTableMidInfo(MENU_WIDTH, "��Ϣɾ��������ɹ�!");
                        printTableTail(MENU_WIDTH);
                        printf("\n");
                        system("pause");
                    }
                    else
                    {
                        printTableHead(MENU_WIDTH+10);
                        printTableMidInfo(MENU_WIDTH+10, "��Ϣɾ���ɹ�������ʧ�� x_x");
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
                    printMidInfo("ָ��������������루ȷ�� Y/y������N/n���� \n");
            }
        }
        p = p->pNext;
    }
    if (!find_ok)
    {
        printTableHead(MENU_WIDTH);
        printTableMidInfo(MENU_WIDTH, "�����޷�ͨ����UID�ҵ���Ӧ��¼������������ԣ�");
        printTableTail(MENU_WIDTH);
        system("pause");
    }
}

void find_menu()
{
    //�˺���Э�����������Ҷ�����Ϣ�����ܣ�����������ҷ�ʽ�˵�
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ѡ����ҷ�ʽ...");
    printTableMidInfo(MENU_WIDTH, "");
    const char* subMenus[] = {
    "1. ͨ�� < ��¼UID > ����",
    "2. ͨ�� < ��־���� > ����",
    "3. ͨ�� < ���Ļ��� > ����",
    "4. ͨ�� < ���֤�� > ����",
    "0. ��������   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("���������蹦�ܣ�0-4��");
}

void find_work(const char* type1)
{
    //�˺���Э�����������Ҷ�����Ϣ�����ܣ����ڽ��в��ҹ���
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ���Ҷ�����Ϣ >");
    printTableTail(MENU_WIDTH);

    //ͨ����¼��uid����Ҫ�޸ĵļ�¼
    int modi_uid;
    char info1[50];
    sprintf(info1, "������ < ������ҵļ�¼�� %s > :", type1);
    printMidInfo(info1);

    int temp_uid; char temp_char[20]; bool find_ok = false;
    if (type1 == "UID") //ͨ��UID����
    {
        scanf("%d", &temp_uid);
        Node* p = g_pHead;
        while (p != NULL) //��ͷ��ʼ����
        {
            if (p->data.uid == temp_uid)
            {
                find_ok = true;
                system("cls");
                printf("�����ǲ��ҳ��ļ�¼��\n");
                pinfo(p);
                system("pause");
                return;
            }
            p = p->pNext;
        }
        if (!find_ok)
        {
            printTableHead(MENU_WIDTH);
            printTableMidInfo(MENU_WIDTH, "�����޷�ͨ����UID�ҵ���Ӧ��¼������������ԣ�");
            printTableTail(MENU_WIDTH);
            system("pause");
            return;
        }
    }
    else if (type1 == "��־����")
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
                    printf("�����ǲ��ҳ��ļ�¼��\n");
                    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��  UID  ��  ��־����  ��  ���Ļ���  ��      ���֤��      �����ķ�����  ����  ��  С��  ��\n");
                }
                find_ok = true;
                printf("��%7d��%12s��%12s��%20s��%8d��%8.2f��%8.2f��\n",
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
            printTableMidInfo(MENU_WIDTH+10, "�����޷�ͨ������־�����ҵ���Ӧ��¼������������ԣ�");
            printTableTail(MENU_WIDTH + 10);
            system("pause");
            return;
        }
        else
        {
            printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
            system("pause");
            return;
        }
    }
    else if (type1 == "���Ļ���")
    {
        scanf("%s", temp_char);
        Node* p = g_pHead;
        while (p != NULL)
        {
            if (strcmp(p->data.name, temp_char) == 0)
            {
                if (!find_ok)
                {
                    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��  UID  ��  ��־����  ��  ���Ļ���  ��      ���֤��      �����ķ�����  ����  ��  С��  ��\n");
                }
                find_ok = true;
                printf("��%7d��%12s��%12s��%20s��%8d��%8.2f��%8.2f��\n",
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
            printTableMidInfo(MENU_WIDTH+10, "�����޷�ͨ���˶��Ļ����ҵ���Ӧ��¼������������ԣ�");
            printTableTail(MENU_WIDTH + 10);
            system("pause");
            return;
        }
        else
        {
            printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
            system("pause");
            return;
        }
    }  
    else if (type1 == "���֤��")
    {
        scanf("%s", temp_char);
        Node* p = g_pHead;
        while (p != NULL)
        {
            if (strcmp(p->data.idnum, temp_char) == 0)
            {
                if (!find_ok)
                {
                    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
                    printf("��  UID  ��  ��־����  ��  ���Ļ���  ��      ���֤��      �����ķ�����  ����  ��  С��  ��\n");
                }
                find_ok = true;
                printf("��%7d��%12s��%12s��%20s��%8d��%8.2f��%8.2f��\n",
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
            printTableMidInfo(MENU_WIDTH+10, "�����޷�ͨ�������֤���ҵ���Ӧ��¼������������ԣ�");
            printTableTail(MENU_WIDTH + 10);
            system("pause");
            return;
        }
        else
        {
            printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
            system("pause");
            return;
        }
    }
}

void find()
{
    //�˺����������Ҷ�����Ϣ����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ���Ҷ�����Ϣ >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    find_menu();
    while (1)
    {
        char ch = getch();
        switch (ch)
        {
        case '1': find_work("UID"); return; //��¼UID
        case '2': find_work("��־����"); return; //��־����
        case '3': find_work("���Ļ���"); return; //���Ļ���
        case '4': find_work("���֤��"); return; //���֤��
        default: return;
        }
    }
}

void analyse_menu()
{
    //�˺���Э��������ͳ��...�����ܣ��������ͳ�Ʒ�ʽ�˵�
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ѡ��ͳ�Ʒ�ʽ...");
    printTableMidInfo(MENU_WIDTH, "");
    const char* subMenus[] = {
    "1. ͳ�� < ��ǰ��־���� >",
    "2. ͳ�� < �û�������Ϣ >",
    "3. ͳ�� < ��ǰ������Ϣ >",
    "0. ����ͳ��   "
    };

    int count = sizeof(subMenus) / sizeof(subMenus[0]);
    for (int i = 0; i < count; i++) {
        printTableMidInfo(MENU_WIDTH, subMenus[i]);
    }
    printTableMidInfo(MENU_WIDTH, "");
    printTableTail(MENU_WIDTH);

    printMidInfo("���������蹦�ܣ�0-3��");
}

void analyse_work_magzine()
{
    //�˺���Э��������ͳ�ơ����ܣ�����ͳ����־����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ͳ����־����... >");
    printTableTail(MENU_WIDTH);

    char temp[20]; bool find_ok = false;
    int much=0; float income=0;
    printMidInfo("����������ͳ�Ƶ� < ��־���� > :");
    scanf("%s", temp);
    Node* p = g_pHead;
    while (p != NULL) //��ͷ��ʼ����
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
        printTableMidInfo(MENU_WIDTH+10, "�����޷�ͨ������־�����ҵ���Ӧ��¼������������ԣ�");
        printTableTail(MENU_WIDTH+10);
        system("pause");
        return;
    }
    else
    {
        printTableHead(MENU_WIDTH);
        char info1[50];
        sprintf(info1, "��־���� < %s > ��ͳ����Ϣ��", temp);
        printTableMidInfo(MENU_WIDTH, info1);
        printTableMidInfo(MENU_WIDTH, "");
        char info2[50];
        sprintf(info2, "���ķ��� �ܼƣ� %d��", much);
        printTableMidInfo(MENU_WIDTH, info2);
        char info3[50];
        sprintf(info3, "�������� �ܼƣ� %.2fԪ", income);
        printTableMidInfo(MENU_WIDTH, info3);
        printTableTail(MENU_WIDTH);
        system("pause");
        return;
    }
}

void analyse_work_user()
{
    //�˺���Э��������ͳ�ơ����ܣ�����ͳ���û�֧����Ϣ
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ͳ���û�֧����Ϣ... >");
    printTableTail(MENU_WIDTH);

    char temp[20],name[10]; bool find_ok = false;
    float pay = 0;
    printMidInfo("����������ͳ�Ƶ��û��� < ���֤�� > :");
    scanf("%s", temp);
    Node* p = g_pHead;
    while (p != NULL) //��ͷ��ʼ����
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
        printTableMidInfo(MENU_WIDTH + 10, "�����޷�ͨ�������֤���ҵ���Ӧ��¼������������ԣ�");
        printTableTail(MENU_WIDTH + 10);
        system("pause");
        return;
    }
    else
    {
        printTableHead(MENU_WIDTH);
        char info1[50];
        sprintf(info1, "�����û� < %s > ��ͳ����Ϣ��", name);
        printTableMidInfo(MENU_WIDTH, info1);
        printTableMidInfo(MENU_WIDTH, "");
        char info2[50];
        sprintf(info2, "�û� ���֤�ţ� %s", temp);
        printTableMidInfo(MENU_WIDTH, info2);
        char info3[50];
        sprintf(info3, "֧����� �ܼƣ� %.2fԪ", pay);
        printTableMidInfo(MENU_WIDTH, info3);
        printTableTail(MENU_WIDTH);
        system("pause");
        return;
    }
}

void analyse_work_income()
{
    //�˺���Э��������ͳ�ơ����ܣ�����ͳ���û�֧����Ϣ
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ͳ�Ƶ�ǰ������Ϣ... >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    float income = 0;
    //��������
    Node* p = g_pHead;
    while (p != NULL)
    {
        income += p->data.tmoney;
        p = p->pNext;
    }
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ������Ϣ��");
    printTableMidInfo(MENU_WIDTH, "");
    char info[50];
    sprintf(info, "��ǰ���� �ܼƣ� %.2fԪ", income);
    printTableMidInfo(MENU_WIDTH, info);
    printTableTail(MENU_WIDTH);
    system("pause");
    return;
}

void analyse()
{
    //�˺�������ͳ��..����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ͳ��... >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    analyse_menu();
    while (1)
    {
        char ch = getch();
        switch (ch)
        {
        case '1': analyse_work_magzine(); return; //��־����
        case '2': analyse_work_user(); return; //�û�֧����Ϣ
        case '3': analyse_work_income(); return; //��ǰ������Ϣ
        default: return;
        }
    }
}

void printInfo()
{
    //�˺���������ӡ...����
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��ǰ���� < ��ӡ... >");
    printTableTail(MENU_WIDTH);
    printf("\n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��  UID  ��  ��־����  ��  ���Ļ���  ��      ���֤��      �����ķ�����  ����  ��  С��  ��\n");
    
    //��������
    Node* p = g_pHead;
    while (p != NULL)
    {
        printf("��%7d��%12s��%12s��%20s��%8d��%8.2f��%8.2f��\n", 
            p->data.uid,
            p->data.id, 
            p->data.name, 
            p->data.idnum, 
            p->data.much, 
            p->data.pmoney, 
            p->data.tmoney);

        p = p->pNext;
    }
    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    system("pause");
}

void exit_normal()
{
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��Ϣ����ɹ���ϵͳ�����˳�...");
    printTableMidInfo(MENU_WIDTH, "��л����ʹ�� =w=");
    printTableTail(MENU_WIDTH);
    exit(0);
}

void exit_erro()
{
    system("cls");
    printTableHead(MENU_WIDTH);
    printTableMidInfo(MENU_WIDTH, "��Ϣ����ʧ�ܣ����ݽ��ص���һ����������...");
    printTableMidInfo(MENU_WIDTH, "��л����ʹ�� =w=");
    printTableTail(MENU_WIDTH);
    exit(0);
}