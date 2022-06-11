#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"functions.h" //functions.c 사용을 위한 헤더

/*

202201079 김한별
세계 주요 국가별 코로나19 확진자 수, 백신 접종자수, 접종률 현황
국가별 확진자 수, 백신 접종자수, 접종률의 정보 조회, 검색, 추가 기능을 제공함.

필요한 함수들을 설명과 함께 functions.c 에 정의해 놓았음. 

*/

int main(void)
{
	int in_list[4] = { 1, 2, 3, 4 }; //입력가능 목록(배열 활용)

	FILE* fp; //파일 포인터 정의(포인터 사용)
	fp = fopen("list.bin", "a+"); //데이터가 입력된 파일(파일 입출력 활용)
	//list.bin 의 내용은 미리 정의되어 있음.

	if (fp == NULL)
	{
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}

	while (1)
	{
		void (*pf)(FILE *fp); //함수 포인터 사용(포인터 사용, 포인터 활용)
		int input = menu();

		if (input == in_list[0])
		{
			pf = add;
			pf(fp);
		}
		else if (input == in_list[1])
		{
			pf = search;
			pf(fp);
		}
		else if (input == in_list[2])
		{
			pf = mod;
			pf(fp);
		}
		else if (input == in_list[3])
			goto exit;
		else
			printf("잘못된 입력입니다.\n");
	}

exit:
	fclose(fp);
	return 0;
}
/*

list.bin 에 미리 정의된 국가들:
미국, 캐나다, 독일, 프랑스, 폴란드, 영국, 네덜란드, 스페인, 터키, 이탈리아, 러시아, 일본, 한국, 대만, 인도

*/
