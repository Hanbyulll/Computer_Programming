//함수 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"functions.h"

#define SIZE 200

typedef struct info
{

	char name[SIZE];
	char total[SIZE];
	char vac[SIZE];
	float vp;

} INF;

int menu()
{

	int n;

	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("1. 입력\n");
	printf("2. 검색\n");
	printf("3. 수정\n");
	printf("4. 종료\n");
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

	printf("입력: ");
	scanf("%d", &n);

	return n;

}


void search(FILE *fp)
{

	INF data;
	char key[SIZE];

	fseek(fp, 0, SEEK_SET);
	getchar();
	printf("국가의 이름을 입력하세요: ");

	gets_s(key, SIZE);
	while (!feof(fp))
	{
		fread(&data.name, sizeof(data), 1, fp);
		if (strcmp(data.name, key) == 0)
		{
			printf("확진자 수: %s\n", data.total);
			printf("백신 접종자수: %s\n", data.vac);
			printf("백신 접종비율(%%): %.1f\n", data.vp);
			break;
		}
		else
		{
			printf("국가 %s 이(가) 존재하지 않습니다.\n", key);
			break;
		}
	}

}


void add(FILE *fp)
{
	INF data;
	float tmp = 0;

	getchar();
	input:
	printf("국가명: ");
	gets_s(data.name, SIZE);
	printf("확진자 수: ");
	gets_s(data.total, SIZE);
	printf("백신 접종자수: ");
	gets_s(data.vac, SIZE);

	printf("백신 접종비율(%%): ");
	scanf("%f", &tmp);

	fwrite(&data, sizeof(data), 1, fp);
}
