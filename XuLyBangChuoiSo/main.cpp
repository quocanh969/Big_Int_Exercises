#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include"library.h"

void main()
{
	//cac chu so 0 o ben phai nghia la khong ton tai
	char a[100],b[100];
	int am1=0, am2=0;//2 bien kiem tra cac truong hop so am




flag:;//vi tri quay lai khi khong the thuc hien phep toan voi so am
	printf("THUC HIEN CAC PHEP TOAN CONG , TRU, CHIA VOI SO DUONG\n");
	printf("Nhap so a: ");
	gets_s(a);

	printf("Nhap so b: ");
	gets_s(b);

	int len1 = strlen(a), len2 = strlen(b);

	if (a[0] == '-')
	{
		Remove1Head(a, len1);
		am1 = 1;
	}

	if (b[0] == '-')
	{
		Remove1Head(b, len2);
		am2 = 1;
	}

	if (am1 == 1 || am2 == 1)
	{
		goto flag1;
	}
	int cmp = strcmp(a, b);
	int luachon;

	//Phep chia voi cac so duong
	char *thuong;
	thuong = (char *)malloc((len1 + 2) * sizeof(char));
	char *r;
	r = (char *)malloc((len1 + 2) * sizeof(char));

	if (cmp>0)
	{
		luachon = 1;
	}
	else if (cmp == 0)
	{
		luachon = 2;
	}
	else
	{
		luachon = 3;
		thuong = chia(a, b, thuong, r, len1, len2);
	}


	chuanHoa(a, b, len1, len2);

	char *s;

	//Phep cong cac so nguyen duong
	s = (char *)malloc((len1 + 2) * sizeof(char));
	s = sum(s, a, b, len1);
	printf("Tong: %s + %s = %s", a, b, s);
	free(s);

	//Phep tru cac so nguyen duong
	s = (char *)malloc((len1+1) * sizeof(char));
	
	if (cmp > 0)
	{
		s = tru(s, b, a, len1);
		printf("\nHieu: %s - %s = - %s", a, b, s);
	}
	else if (cmp == 0)
	{
		printf("\nHieu: %s - %s = 0", a, b);
	}
	else
	{
		s = tru(s, a, b, len1);
		printf("\nHieu: %s - %s = %s", a, b, s);
	}
	if(s!=NULL)	free(s);

	//Phep nhan
flag1:;
	s = (char *)malloc((len1*len2+2) * sizeof(char));
	s = nhan(s, a, b, len1*len2, len1);

	if (am1 == 1 && am2 == 1)
	{
		printf("\nTich: (- %s ) * ( - %s ) = %s", a, b, s);
	}
	else if (am1 == 1)
	{
		printf("\nTich:( - %s ) * %s = ( - %s )", a, b, s);
	}
	else if (am2 == 1)
	{
		printf("\nTich: %s * ( - %s ) = ( - %s )", a, b, s);
	}
	else
	{
		printf("\nTich: %s * %s = %s", a, b, s);
	}
	free(s);
	if (am1 == 1 || am2 == 1)
	{
		printf("Vi ban khong nhap hai so duong nen chuong trinh se khong thuc hien cac phep toan cong, tru, chia");
		goto flagEnd;
	}

	
	//Phep chia ( tiep theo)
	if (luachon == 1)
	{
		printf("\nThuong: %s : %s = 0 du %s", a, b, a);
	}
	else if (luachon == 2)
	{
		printf("\nThuong: %s : %s = 1 du 0", a, b);
	}
	else
	{
		printf("\nThuong: %s : %s = %s du %s", a, b, thuong, r);
	}

	free(thuong);
	free(r);

flagEnd:;
	_getch();
}