#include "Instructions.h"
#include "Functions.h"

void check_instructions(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, int line, char *key[])
{
	char ch = 'a';
	int arr_size = 0, plus_size;
	int reg[17];
	int *arr = malloc(arr_size * sizeof(int));
	int** pointer = &arr;
	
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < 20; j++)
			if (strcmp(key[j], char_array_B[i]) == 0)
				switch (j)
				{
				case 0:
					printf("DS: ");
					arr = DS(char_array_A, char_array_C, char_array_D, arr, i, &arr_size, &plus_size);
					j = 20; break;
				case 1:
					arr = DC(char_array_A, char_array_C, char_array_D, arr, i, &arr_size, &plus_size);
					j = 20; break;
				case 2:
					L(reg, char_array_A, char_array_C, char_array_D, i, arr, *pointer);
					j = 20; break;
				case 3:
					LA(reg, char_array_A, char_array_C, char_array_D, i, arr, *pointer);
					j = 20; break;
				case 4:
					LR(reg, char_array_C, char_array_D, i);
					j = 20;  break;
				case 5:
					printf("A:  ");
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 1, reg, arr);
					j = 20; break;
				case 6:
					printf("AR: ");
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 1, reg, *arr);
					j = 20; break;
				case 7:
					printf("S:  ");
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 2, reg, *arr);
					j = 20; break;
				case 8:
					printf("SR: ");
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 2, reg, *arr);
					j = 20; break;
				case 9:
					printf("M:  ");
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 3, reg, *arr);
					j = 20; break;
				case 10:
					printf("MR: ");
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 3, reg, *arr);
					j = 20; break;
				case 11:
					printf("D:  ");
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 4, reg, *arr);
					j = 20; break;
				case 12:
					printf("DR: ");
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 4, reg, *arr);
					j = 20; break;
				case 13:
					C(reg, char_array_A, char_array_C, char_array_D, i, arr);
					j = 20; break;
				case 14:
					CR(reg, char_array_C, char_array_D, i, arr);
					j = 20; break;
				case 15:
					i = J(reg, char_array_A, char_array_C, i);
					j = 20; break;
				case 16:
					i = JP(reg, char_array_A, char_array_C, i);
					j = 20; break;
				case 17:
					i = JZ(reg, char_array_A, char_array_C, i);
					j = 20; break;
				case 18:
					i = JN(reg, char_array_A, char_array_C, i);
					j = 20; break;
				case 19:
					ST(reg, char_array_A, char_array_C, char_array_D, i, arr);
					j = 20; break;
				}
		if (ch != 's') ch = getch();
	}
	*pointer = NULL;
	free(arr);
}