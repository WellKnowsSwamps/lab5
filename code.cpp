#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <memory.h>
#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <cstring> 
#include <math.h>

int menu();
char * InputStrin(char* inp);
int countOfGap(char* inp, int leng);
int countOfGap1(char* inp, int leng);
char** arrayWords(char** words, char* inp, int countProbel);
int countOfSymbols(int leng, int countProbel);
char* Itog(char* strItog, int countProbel, int countOfSymbol, char** words, int chetnoe, int ostatok);


int main()
{
	setlocale(LC_ALL, "Rus");
	char *inp = nullptr;
	int lengI = 0;
	bool chek1 = false;
	int punkt = 0;
	char* temp = NULL;
	char** words = NULL;
	char* strItog = NULL;
	int countProbel = 0;

	do
	{
		punkt = menu();

		switch (punkt)
		{

		case 1:
			system("cls");
			delete[] inp;

			do
			{
				inp = InputStrin(inp);
				lengI = strlen(inp);
			} while ((inp[0] == ' ') || (inp[lengI - 1] == ' '));
			
			
			chek1 = true;
			getchar();
			system("cls");
			break;
		case 2:
			system("cls");
			if (chek1 == false)
			{
				printf("Пожалуйста, для начала введите строку");
				getchar();
				system("cls");
				break;
			}
			else
			{
					//----------------------------------------------------------

					int leng = strlen(inp);
					countProbel = countOfGap(inp, leng);
					temp = new char[lengI + 1];
					strcpy(temp, inp);

					//----------------------------------------------------------

					words = new char*[countProbel + 1];
					words = arrayWords(words, temp, countProbel);

					//----------------------------------------------------------
					if (countProbel + 1 == 1)
					{
						printf("Нельзя расширить строку, состоящую лишь из одного слова");
					}
					else
					{
						int countOfSymbol = countOfSymbols(leng, countProbel);
						int probels = countOfGap1(inp, leng);

						int chetnoe = floor((countOfSymbol - leng + probels) / countProbel);
						int ostatok = ((countOfSymbol - leng + probels) % countProbel);

						//----------------------------------------------------------

						strItog = new char[countOfSymbol + 1];
						strItog = Itog(strItog, countProbel, countOfSymbol, words, chetnoe, ostatok);

						printf("Измененная строка, состоящая из %d символов: %s\n", strlen(strItog), strItog);
				
					}
					//----------------------------------------------------------
				delete[] strItog;
				delete[] temp;
				getchar();
				system("cls");
				break;
			}
		case 3:
		{
			system("cls");
			if (chek1 == false)
			{
				printf("Пожалуйста, для начала введите строку");
				getchar();
				system("cls");
				break;
			}
			else
			{
				printf("Исходная строка, состоящая из %d символов: %s\n", strlen(inp), inp);
				getchar();
				system("cls");
				break;
			}
		}
		case 4:
			break;
		}

	} while (punkt != 4);
	
	delete[] inp;

	_CrtDumpMemoryLeaks();
	return 0;
}


int menu()
{
	int punkt = 0;
	printf("Выберите пункт меню\n");
	printf("___________________\n\n");
	//_________________________________________________________________________

	printf("1. Ввод строки\n");
	printf("2. Вывод расширенной строки\n");
	printf("3. Вывод исходной строки\n");
	printf("4. Выход\n");

	//_________________________________________________________________________
	printf("___________________\n\n");
	do
	{
		char c = '\0';
		while (scanf_s("%d%c", &punkt, &c, 1) != 2 || c != '\n')
		{
			printf("The entered value is invalid. Please try again.\n");
			while (getchar() != '\n');
		}
	} while ((punkt < 1) || (punkt > 4));
	return punkt;
}

char * InputStrin(char* inp)
{
	printf("Пожалуйста, введите строку, первый и последний символы которой не являются пробелами\n");
	char string = '\0';
	scanf_s("%c", &string, 1);

	int leng = 1;

	char* str = new char[1];
	str[0] = string;

	while (string != '\0')
	{
		scanf_s("%c", &string, 1);
		char* tmpStr = new char[leng + 1];
		for (int i = 0; i < leng; i++)
		{
			tmpStr[i] = str[i];
		}

		if (string == '\n')
		{
			tmpStr[leng] = '\0';
			string = '\0';
		}
		else
		{
			tmpStr[leng] = string;
		}
		delete[] str;
		str = tmpStr;
		leng++;
	}
	return str;
}


int countOfGap(char* inp, int leng)
{
	char* proverka = new char[strlen(inp) + 1];
	strcpy_s(proverka, strlen(inp) + 1, inp);
	char* check = NULL;
	int countProbel = 0;
	int length = strlen(inp) + 1;

	do
	{
		for (int i = 1; i < length; i++)
		{
			if (proverka[i] == ' ')
			{
				if (proverka[i - 1] != ' ')
				{
					countProbel++;
				}
			}
		}
	} while (check != NULL);
	delete[] proverka;

	return countProbel;
}

int countOfGap1(char* inp, int leng)
{
	char* proverka = new char[strlen(inp) + 1];
	strcpy_s(proverka, strlen(inp) + 1, inp);
	char* check = NULL;
	int countProbel = 0;
	int length = strlen(inp) + 1;

	do
	{
		for (int i = 1; i < length; i++)
		{
			if (proverka[i] == ' ')
			{
					countProbel++;
			}
		}
	} while (check != NULL);
	delete[] proverka;

	return countProbel;
}



char** arrayWords(char** words, char* temp, int countProbel)
{
	const char s[2] = " ";
	char* token = NULL;

	int countToken = 0;
	token = strtok(temp, s);
	while (token != NULL)
	{
		words[countToken] = new char[strlen(token) + 1];
		strcpy(words[countToken], token);
		countToken++;
		token = strtok(NULL, s);
	}

	return words;
}


int countOfSymbols(int leng, int countProbel)
{
	int countOfSymbol = 0;
	do
	{
		printf("Количество символов во введенной строке равно %d. Пожалуйста, введите желаемое количество символов в строке: ", leng);
		char c = '\0';
		while (scanf_s("%d%c", &countOfSymbol, &c, 1) != 2 || c != '\n')
		{
			printf("The entered value is invalid. Please try again.\nКоличество символов во введенной строке равно %d. Пожалуйста, введите желаемое количество символов в строке: ", leng);
			while (getchar() != '\n');
		}
	} while ((countOfSymbol < leng) || (countOfSymbol > 300));

	return countOfSymbol;
}

char* Itog(char* strItog, int countProbel, int countOfSymbol, char** words, int chetnoe, int ostatok)
{
	strItog[0] = '\0';
	int checkcheck = -1;

	for (int i = 0; i < countProbel + 1; i++)
	{
		strcat_s(strItog, countOfSymbol + 1, words[i]);

		if (i == countProbel)
		{
			continue;
		}

		if (chetnoe != 0)
		{
			for (int j = 0; j < chetnoe; j++)
			{
				strcat_s(strItog, countOfSymbol + 1, " ");
			}
		}

		if ((ostatok > 0) && (checkcheck != i))
		{
			strcat_s(strItog, countOfSymbol + 1, " ");
			ostatok--;
			checkcheck = i;
		}

	}
	for (int i = 0; i < countProbel + 1; i++)
	{
		delete[] words[i];
	}
	delete[] words;
	return strItog;
}
