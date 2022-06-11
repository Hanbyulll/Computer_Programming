#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"functions.h" //functions.c ����� ���� ���

/*

202201079 ���Ѻ�
���� �ֿ� ������ �ڷγ�19 Ȯ���� ��, ��� �����ڼ�, ������ ��Ȳ
������ Ȯ���� ��, ��� �����ڼ�, �������� ���� ��ȸ, �˻�, �߰� ����� ������.

�ʿ��� �Լ����� ����� �Բ� functions.c �� ������ ������. 

*/

int main(void)
{
	int in_list[4] = { 1, 2, 3, 4 }; //�Է°��� ���(�迭 Ȱ��)

	FILE* fp; //���� ������ ����(������ ���)
	fp = fopen("list.bin", "a+"); //�����Ͱ� �Էµ� ����(���� ����� Ȱ��)
	//list.bin �� ������ �̸� ���ǵǾ� ����.

	if (fp == NULL)
	{
		fprintf(stderr, "������ �� �� �����ϴ�.\n");
		exit(1);
	}

	while (1)
	{
		void (*pf)(FILE *fp); //�Լ� ������ ���(������ Ȱ��)
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
			printf("�߸��� �Է��Դϴ�.\n");
	}

exit:
	fclose(fp);
	return 0;
}
/*

list.bin �� �̸� ���ǵ� ������:
�̱�, ĳ����, ����, ������, ������, ����, �״�����, ������, ��Ű, ��Ż����, ���þ�, �Ϻ�, �ѱ�, �븸, �ε�

*/