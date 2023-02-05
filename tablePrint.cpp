#include <stdio.h>
#include <string.h>
#include "tablePrint.h"

void printTableHead(int tableWidth) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	for (int i = 0; i < margin; i++) printf(" ");
	printf("©°");
	for (int i = 0; i < tableWidth - 2; i++)printf("©¤");
	printf("©´\n");
}



void printTableTail(int tableWidth) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	for (int i = 0; i < margin; i++) printf(" ");
	printf("©¸");
	for (int i = 0; i < tableWidth - 2; i++)printf("©¤");
	printf("©¼\n");
}


void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	for (int i = 0; i < margin; i++) printf(" ");

	int colWidth = (tableWidth - (n + 1)) / n;

	for (int i = 0; i < n; i++) {
		printf("©¦");

		int leftSpan = (colWidth - strlen(cols[i])) / 2;
		int rightSpan = colWidth - leftSpan - strlen(cols[i]);

		for (int j = 0; j < leftSpan; j++) printf(" ");
		printf("%s", cols[i]);
		for (int j = 0; j < rightSpan; j++) printf(" ");
	}

	printf("©¦\n");
}


void printTableHead(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	printf("©°");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("©¤");
		}

		if (i < cols - 1) {
			printf("©Ð");
		}
		else {
			printf("©´");
		}
	}
	printf("\n");
}

void printTableTail(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	//©¸©¤©Ø©¤©¼
	printf("©¸");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("©¤");
		}

		if (i < cols - 1) {
			printf("©Ø");
		}
		else {
			printf("©¼");
		}
	}
	printf("\n");
}

void printTableMidLine(int tableWidth, int cols) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	int spanLen = (tableWidth - (cols + 1)) / cols;
	for (int i = 0; i < margin; i++) printf(" ");

	printf("©À");
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < spanLen; j++) {
			printf("©¤");
		}

		if (i < cols - 1) {
			printf("©à");
		}
		else {
			printf("©È");
		}
	}
	printf("\n");
}


void printTableMidInfo(int tableWidth, const char* str) {
	int margin = (WIN_WIDTH - tableWidth) / 2;
	for (int i = 0; i < margin; i++) printf(" ");
	printf("©¦");

	int len1 = (tableWidth - 2 - strlen(str)) / 2;
	for (int i = 0; i < len1; i++) printf(" ");

	printf("%s", str);

	int len2 = tableWidth - 2 - len1 - strlen(str);
	for (int i = 0; i < len2; i++) printf(" ");

	printf("©¦\n");
}

void printMidInfo(const char* str) {
	int margin = (WIN_WIDTH - strlen(str)) / 2;
	for (int i = 0; i < margin; i++) printf(" ");
	printf("%s", str);
}