#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"functions.h"

int main(void)
{

	FILE* fp;
	fp = fopen("list.bin", "a+");

	if (fp == NULL)
	{
		fprintf(stderr, "파일을 열 수 없습니다.\n", fp);
		exit(1);
	}

	while (1)
	{
		int input = menu();
		switch (input)
		{
		case 1:
			add(fp);
			break;
		case 2:
			search(fp);
			break;
		case 4:
			goto exit;
		default:
			printf("잘못된 입력입니다.\n");
			break;
		}
	}

exit:
	fclose(fp);
	return 0;
}