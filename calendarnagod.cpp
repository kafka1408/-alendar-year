#include "stdafx.h"
#include <ctime>
#include <cstring>
#include<clocale>
#include <cstdlib>

using namespace std;

void f0(int k);

int m[6][7][12];
int Mv[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int Mnv[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int g, denN, denM[12], mes, x, y;

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		// Пользователь ввел год
		g = atoi(argv[1]);

	}
	else
	{
		time_t seconds;
		seconds = time(NULL) / (60 * 60 * 24);
		int d17 = seconds - (365 * 35) - (366 * 12); // Прошло дней с начала 2017 года
		int v = (d17 / 365) / 4;
		int nv = d17 / 365 - v;
		g = 2017 + v + nv;
	}
	if ((g - 1900) % 4 == 0)	                  //При истинном условии цикла значение находится для високосного года
		denN = (g - 1900 + (g - 1900) / 4 - 1) % 7;  //При ложном-для невисосного
	else denN = (g - 1900 + (g - 1900) / 4) % 7;
	//Заполение матрицы
	for (; mes < 12; mes++)
	{
		denM[mes] = denN;
		// С какого дня начнется месяц?
		if (!((g - 1900) % 4))  //При истинном условии находится значение для високосного года
		{                      //При ложном-для невисокосного
			for (int i = 0; i < mes; i++)
				denM[mes] += Mv[i];
		}
		else
		{
			for (int i = 0; i < mes; i++)
				denM[mes] += Mnv[i];
		}
		denM[mes] = denM[mes] % 7;
		int s = 1;
		for (int j = 0; j < denM[mes]; j++)  m[0][j][mes] = ' ';
		for (int j = denM[mes]; j < 7; j++)  m[0][j][mes] = s++;
		if ((g - 1900) % 4 > 0)
		{
			// Если условие истинно-для невисокосного года
			for (int i = 1; s <= Mnv[mes]; i++) // Если ложно-для високосного
				for (int j = 0; (s <= Mnv[mes]) && (j < 7); j++)
				{
					m[i][j][mes] = s++;
					x = i;
					y = j;
				}
		}
		else
		{
			for (int i = 1; s <= Mv[mes]; i++)
				for (int j = 0; (s <= Mv[mes]) && (j < 7); j++)
				{
					m[i][j][mes] = s++;
					x = i;
					y = j;
				}
		}
		if (y == 6)
		{
			for (int i = ++x; i < 6; i++)
				for (int j = 0; j < 7; j++)
					m[i][j][mes] = ' ';
		}
		else
		{
			for (int j = y + 1; j < 7; j++) 
			{
				m[x][j][mes] = ' ';
				y = j;
			}
				for (int i = ++x; i < 6; i++)
					for (int j = 0; j < 7; j++)
						m[i][j][mes] = ' ';
			
		}
	}
	// Выводим календарь
	for (mes = 0; mes < 12; mes = mes + 3)
	{
		for (int d = mes; d < mes + 3; d++) f0(d);
		for (int d = mes; d < mes + 3; d++)
		{
			printf(" Пн Вт Ср Чт Пт Сб Вс");
			if (d - mes == 2) printf("\n");
			else printf("    ");
		}
		for (int i = 0; i < 6; i++)
		{
			for (int d = mes; d < mes + 3; d++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (m[i][j][d] == ' ') printf("%3c", m[i][j][d]);
					else printf("%3d", m[i][j][d]);
				}
				printf("    ");
			}
			printf("\n");
		}
		
	}
	return 0;
}

void f0(int k)
{
	setlocale(LC_ALL, "RUS");
	char *Mes[] = {
		"Январь",
		"Февраль",
		"Март",
		"Апрель",
		"Май",
		"Июнь",
		"Июль",
		"Август",
		"Сентябрь",
		"Октябрь",
		"Ноябрь",
		"Декабрь"
	};
	printf("     %s %d", Mes[k], g);
	if (k - mes == 2) printf("\n");
	else 
	{
		int p = strlen(Mes[k]) - 1;
		for (int t = 0; t < (14 - p); t++)
			printf(" ");
	}
}
