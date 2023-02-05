#pragma once

// ´°¿Ú¿í¶È
#define WIN_WIDTH 80
// ´°¿Ú¸ß¶È
#define WIN_HEIGHT 25

#define TABLE_WIDTH 78

#define MENU_WIDTH  50
#define COL_LEN_MAX 64

void printTableHead(int tableWidth);
void printTableTail(int tableWidth);
void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n);
//void printTableHead(int tableWidth, int cols);
//void printTableTail(int tableWidth, int cols);
//void printTableMidLine(int tableWidth, int cols);
void printTableMidInfo(int tableWidth, const char* str);
void printMidInfo(const char* str);
