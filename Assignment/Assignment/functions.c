#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"functions.h"

//�ʿ��� �Լ����� ����� �����س��� ����(�Լ� ���)

#define SIZE 200 //�ڷ����� ũ�⸦ �̸� ������

typedef struct info
{
	char name[SIZE];
	char total[SIZE];
	char vac[SIZE];
	float vp;
} INF; //������, Ȯ���� ��, ��� ������ ��, ��� �������� ����ü�� ����(����ü ���)

INF input_strc();
void replace(FILE *fp, FILE *tmp);
//function.c ������ �߰��� ����ؾ��ϴ� �Լ���

int menu() //�޴� ��� �� ���ð� ��ȯ
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

void search(FILE *fp) //������� �������� �˻� �� ǥ��
{
	INF data;
	char key[SIZE];

	getchar();
	printf("������ �̸��� �Է��ϼ���: "); //�������� �������� �˻�
	gets_s(key, SIZE);

	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		fread(&data.name, sizeof(data), 1, fp);
		if (strcmp(data.name, key) == 0) //���ڿ� ������ ��ġ ����(strcmp ���)
		{
			printf("Ȯ���� ��: %s\n", data.total);
			printf("��� �����ڼ�: %s\n", data.vac);
			printf("��� ��������(%%): %.1f\n", data.vp);
			return; //��ġ�ϴ� ������ ã���� ��� �� return
		}
	}

	printf("������ %s ��(��) ã�� �� �����ϴ�.\n", key); //return ���� ������ ��� == ��ġ�ϴ� �������� �������� ����
}


void add(FILE *fp) //���ο� ���� �� ������ �߰�
{
	getchar();

	INF data = input_strc(); //����ü ���·� �Է�, �Է� ������ input_strc() �� ���ǵ�

	fwrite(&data, sizeof(data), 1, fp); //list.bin�� �߰�(append)
}

void mod(FILE *fp)
{
	INF data;
	FILE* tmp;
	char key[SIZE];

	getchar();

	//���� ����
	printf("������ ������ �̸��� �Է��ϼ���: ");
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
			//�ӽ� ���� ���� �� ������� �Է� �� �ӽ� ���Ͽ� ����

			fseek(fp, 0, SEEK_SET);
			while (!feof(fp))
			{
				fread(&data, sizeof(data), 1, fp);
				//�ߺ� ������ ���� �̸��� ���� �����͸� tmp�� ����
				if(strcmp(data.name, key) != 0)
					fwrite(&data, sizeof(data), 1, tmp);
			}
			//���� ������ �ʱ�ȭ�� �ӽ� ���Ͽ� ��ü ������ �����

			replace(fp, tmp);
			//���� ���� ���� �� �ӽ� ������ �������� �� ���� ����
			//fp�� �����ϴ� �ݺ����� �����Ƿ� �Լ��� ���
			return;
		}	
	}
	printf("������ %s ��(��) ã�� �� �����ϴ�.\n", key);
	return;
}

INF input_strc() //������ �Է¹޾Ƽ� ����ü�� ��ȯ
{
	INF data;

	printf("������: ");
	gets_s(data.name, SIZE);
	printf("Ȯ���� ��: ");
	gets_s(data.total, SIZE);
	printf("��� �����ڼ�: ");
	gets_s(data.vac, SIZE);
	printf("��� ��������(%%): ");
	scanf("%f", &data.vp);

	return data;
}

void replace(FILE* fp, FILE* tmp)
{
	INF data;

	fclose(fp);
	if (-1 == remove("list.bin"))
	{
		printf("���� ���� ����\n");
		exit(1);
	}
	//���� list.bin ���� �� ���н� �ȳ� ���� ��� �� ���α׷� ����
	
	fp = fopen("list.bin", "a+"); //fp�� ���� ����(���ο� �� list.bin ����)
	fseek(tmp, 0, SEEK_SET);
	while (!feof(tmp))
	{
		fread(&data, sizeof(data), 1, tmp);
		fwrite(&data, sizeof(data), 1, fp);
		//�ӽ� ������ ������ ���ο� list.bin �� ����
	}

	fclose(tmp);
	remove("temp.bin");
	//�ӽ� ���� ���� �� �ӽ� ������ ������ �ݱ�
}