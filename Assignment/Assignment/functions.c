#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>
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

	printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
	printf("1. �Է�\n");
	printf("2. �˻�\n");
	printf("3. ����\n");
	printf("4. ����\n");
	printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");

	printf("�Է�: ");
	scanf("%d", &n);

	return n;

}


void search(FILE *fp)
{

	INF data;
	char key[SIZE];

	fseek(fp, 0, SEEK_SET);
	getchar();
	printf("������ �̸��� �Է��ϼ���: ");

	gets_s(key, SIZE);
	while (!feof(fp))
	{
		fread(&data.name, sizeof(data), 1, fp);
		if (strcmp(data.name, key) == 0)
		{
			printf("Ȯ���� ��: %s\n", data.total);
			printf("��� �����ڼ�: %s\n", data.vac);
			printf("��� ��������(%%): %.1f\n", data.vp);
			break;
		}
		else
		{
			printf("���� %s ��(��) �������� �ʽ��ϴ�.\n", key);
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
	printf("������: ");
	gets_s(data.name, SIZE);
	printf("Ȯ���� ��: ");
	gets_s(data.total, SIZE);
	printf("��� �����ڼ�: ");
	gets_s(data.vac, SIZE);

	printf("��� ��������(%%): ");
	scanf("%f", &tmp);

	fwrite(&data, sizeof(data), 1, fp);
}