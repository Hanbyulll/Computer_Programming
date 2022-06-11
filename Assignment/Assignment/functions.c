#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"functions.h"

//필요한 함수들의 기능을 구현해놓은 파일(함수 사용)

#define SIZE 200 //자료형의 크기를 미리 정의함

typedef struct info
{
	char name[SIZE];
	char total[SIZE];
	char vac[SIZE];
	float vp;
} INF; //국가명, 확진자 수, 백신 접종자 수, 백신 접종률을 구조체로 선언(구조체 사용)

INF input_strc();
void replace(FILE *fp, FILE *tmp);
//function.c 내에서 추가로 사용해야하는 함수들

int menu() //메뉴 출력 및 선택값 반환
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

void search(FILE *fp) //국가명과 정보들을 검색 및 표시
{
	INF data;
	char key[SIZE];

	getchar();
	printf("국가의 이름을 입력하세요: "); //국가명을 기준으로 검색
	gets_s(key, SIZE);

	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		fread(&data.name, sizeof(data), 1, fp);
		if (strcmp(data.name, key) == 0) //문자열 끼리의 일치 여부(strcmp 사용)
		{
			printf("확진자 수: %s\n", data.total);
			printf("백신 접종자수: %s\n", data.vac);
			printf("백신 접종비율(%%): %.1f\n", data.vp);
			return; //일치하는 국가를 찾으면 출력 후 return
		}
	}

	printf("국가명 %s 을(를) 찾을 수 없습니다.\n", key); //return 되지 못했을 경우 == 일치하는 국가명이 존재하지 않음
}


void add(FILE *fp) //새로운 국가 및 정보를 추가
{
	getchar();

	INF data = input_strc(); //구조체 형태로 입력, 입력 내용은 input_strc() 에 정의됨

	fwrite(&data, sizeof(data), 1, fp); //list.bin에 추가(append)
}

void mod(FILE *fp)
{
	INF data;
	FILE* tmp;
	char key[SIZE];

	getchar();

	//내용 변경
	printf("수정할 국가의 이름을 입력하세요: ");
	gets_s(key, SIZE);

	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		fread(&data.name, sizeof(data), 1, fp);
		if (strcmp(data.name, key) == 0)
		{
			data = input_strc();
			tmp = fopen("temp.bin", "a+");
			fwrite(&data, sizeof(data), 1, tmp);
			//임시 파일 생성 및 변경사항 입력 후 임시 파일에 저장

			fseek(fp, 0, SEEK_SET);
			while (!feof(fp))
			{
				fread(&data, sizeof(data), 1, fp);
				//중복 방지를 위해 이름이 같지 않은것만 tmp에 쓰기
				if(strcmp(data.name, key) != 0)
					fwrite(&data, sizeof(data), 1, tmp);
			}
			//파일 포인터 초기화후 임시 파일에 전체 내용을 덮어쓰기

			replace(fp, tmp);
			//기존 파일 삭제 후 임시 파일을 기준으로 새 파일 생성
			//fp를 참조하는 반복문이 있으므로 함수를 사용
			return;
		}	
	}
	printf("국가명 %s 을(를) 찾을 수 없습니다.\n", key);
	return;
}

INF input_strc() //정보를 입력받아서 구조체로 반환
{
	INF data;

	printf("국가명: ");
	gets_s(data.name, SIZE);
	printf("확진자 수: ");
	gets_s(data.total, SIZE);
	printf("백신 접종자수: ");
	gets_s(data.vac, SIZE);
	printf("백신 접종비율(%%): ");
	scanf("%f", &data.vp);

	return data;
}

void replace(FILE* fp, FILE* tmp)
{
	INF data;

	fclose(fp);
	if (-1 == remove("list.bin"))
	{
		printf("파일 삭제 실패\n");
		exit(1);
	}
	//원본 list.bin 삭제 및 실패시 안내 문구 출력 및 프로그램 종료
	
	fp = fopen("list.bin", "a+"); //fp를 새로 정의(새로운 빈 list.bin 생성)
	fseek(tmp, 0, SEEK_SET);
	while (!feof(tmp))
	{
		fread(&data, sizeof(data), 1, tmp);
		fwrite(&data, sizeof(data), 1, fp);
		//임시 파일의 내용을 새로운 list.bin 에 쓰기
	}

	fclose(tmp);
	remove("temp.bin");
	//임시 파일 삭제 및 임시 파일의 포인터 닫기
}