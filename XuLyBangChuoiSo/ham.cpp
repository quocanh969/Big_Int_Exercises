#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"library.h"

void GiaoDienLuaChonPhepToan(int &tuychon)
{
flag:;
	printf("\n=============================================================");
	printf("\n=Nhap so thich hop tuong ung voi cac lua chon:              =");
	printf("\n=1. Phep cong cac so duong.                                 =");
	printf("\n=2. Phep tru cac so duong.                                  =");
	printf("\n=3. Phep nhan     so duong.                                 =");
	printf("\n=4. Phep chia cac so duong.                                 =");
	printf("\n=5. Lam phep toan khac.                                     =");
	printf("\n=============================================================");
	printf("\nTuy chon cua ban: ");scanf_s("%d", &tuychon);
	if (tuychon > 5 && tuychon < 1)
	{
		system("cls");
		printf("Loi!!! Khong ton tai lua chon do, bat dau lai");
		goto flag;
	}
}

void Remove1Head(char a[], int &len)
{
	for (int i = 0;i < len - 1;i++)
	{
		a[i] = a[i + 1];
	}
	a[len - 1] = 0;
	len--;
}

int stringToNum(char c)     // chuyen char sang so
{
	if (c < '0'|| c>'9')return 0;
	else return c - '0';
}

char numToString(int n)     // chuyen so sang char
{
	return (char)(n + 48);
}

void Add1Head(char a[], char x, int &len)
{
	len++;
	for (int i = len - 1;i >= 0;i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
}

void AddHead(char a[], char x, int l, int &len)
{
	len = len + l;
	char *temp;
	temp = (char *)malloc(len * sizeof(char));

	for (int i = l;i < len;i++)
	{
		temp[i] = a[i - l];
	}
	for (int i = 0;i < l;i++)
	{
		temp[i] = x;
	}

	for (int i = 0;i < len;i++)
	{
		a[i] = temp[i];
	}
	free(temp);
	a[len] = 0;
}

void chuanHoa(char a[], char b[], int &l1, int &l2) // lam 2 xau co do dai bang nhau
{
	//int l1 = strlen(a), l2 = strlen(b);
	if (l1 >= l2)
	{
		AddHead(b, '0', l1 - l2, l2);    // chen vao dau cua b cac ky tu '0'
	}
	else
	{
		AddHead(a, '0', l2 - l1, l1);    // chen vao dau cua a cac ky tu '0'
	}

}

char *sum(char *&s, char a[], char b[], int l)  // tong 2 so da chuan hoa
{
	int temp = 0;//so nho neu phep cong cac chu so co ket qua > 10


	for (int i = l - 1; i >= 0; i--)   // duyet va cong
	{
		temp = stringToNum(a[i]) + stringToNum(b[i]) + temp;    // tinh tong tung doi mot
		s[i] = numToString(temp % 10);  // gan phan don vi vao
		temp = temp / 10;     // lay lai phan hang chuc
	}

	if (temp>0)  // neu hang chuc > 0 thi them vao KQ
	{
		Add1Head(s, numToString(temp), l);
	}

	s[l] = 0;

	return s;
}

//Phep tru hai tru so nguyen lon
char *tru(char *&s, char a[], char b[], int len)
{
	int temp = 0;//bien temp nham xac dinh gia tri sau moi lan tru o tung hang don vi
	int kt1 = 0;//bien kt1 kiem tra xem phep tru co nho khong


	for (int i = len - 1;i >= 0;i--)
	{
		if(kt1==0)temp = stringToNum(a[i]) - stringToNum(b[i]); //Tinh hieu tung hang
		else temp = stringToNum(a[i]) - (stringToNum(b[i]) + 1); //Neu hang truoc co nho thi phai tru them 1 don vi nua
		

		if (temp < 0)
		{
			kt1 = 1;
			temp += 10;
		}
		else
		{
			kt1 = 0;
		}

		s[i] = numToString(temp);
	}

	s[len] = 0;
	
	return s;
}

// nhan so co 1 chu so voi so co nhieu chu so (VD 4 va 7826), lam tuong tu nhu phep cong
char *nhanNho(char a, char b[], int len, int k)
{
	char *s;
	s = (char *)malloc((len*len+1)*sizeof(char));
	int temp = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		temp = stringToNum(a) * stringToNum(b[i]) + temp;
		s[i] = numToString(temp % 10);
		temp = temp / 10;
	}

	for (int i = len;i < len + k;i++)
	{
		s[i] = '0';
	}

	len = len + k;
	if (temp>0)
	{
		Add1Head(s, numToString(temp), len);
	}
	s[len] = 0;

	return s;
}

char *nhan(char *&s, char a[], char b[], int len, int l)// nhan 2 so lon
{
	char *s1;
	int k = len;
	for (int i = l - 1; i >= 0; i--)   // nhan tung chu so cua a voi b sau do cong don vao
	{
		s1 = nhanNho(b[i], a, l, l - 1 - i);// nhan tung so cua a voi b
		int l2 = strlen(s1);
		chuanHoa(s, s1, len, l2);
		s = sum(s, s, s1, len);  // cong don theo cach cong so lon
 		free(s1);
	}

	
	return s;
}

char *chia(char a[], char b[], char *&s, char *&r, int lenA, int lenB)
{
	int k = 0;//bien k danh dau so phan tu cua ket qua
	char* temp;
	temp = (char *)malloc((lenA+2) * sizeof(char));//xay dung chuoi temp nham thay doi gia tri chuoi qua moi lan tinh toan hoac phai tinh them mot chu so
	//vi du 98 -> 098 -> 0098
	strcpy(temp, b);
	int l = strlen(temp);

	char *s1;
	int p = lenB;
	s1 = (char *)malloc((lenA + 2) * sizeof(char));//La bien so lay theo so ki tu cua B trong chuoi A, la nhung chuoi con nham xet khi chia cho b
	//La ket qua trung gian trong qua trinh chia
	
	for (int i = 0;i < p;i++)
	{
		s1[i] = a[i];
	}
	s1[p] = 0;

	do
	{
		s[k] = '0';

		while (strcmp(s1, temp) >= 0)//Qua trinh lap de tim so thich hop dien vao vi tri thuong
		{
			s[k]++;//Tang dan qua tan vong lap cung nhu tang dan so lan cua b
			
			s1 = tru(s1, s1, temp, p);//s1 giam bot temp lan moi vong lap
		}

		Add1Head(temp, '0', l);
		temp[l] = 0;
		p++;
		s1[p - 1] = a[p - 1];
		s1[p] = 0;

		k++;
	} while (p < lenA + 1);

	

	s[k] = 0;

	strcpy(r, s1);//thiet lap chuoi so du sau phep chia

	free(s1);
	free(temp);
	return s;
}