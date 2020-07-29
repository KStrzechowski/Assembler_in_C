#include "Instructions.h"
#include "Functions.h"

void check_instructions(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, int line, char *key[])
{
	char ch = 'a';
	int arr_size = 0, plus_size, i, j;
	int reg[17];
	int *arr = malloc(arr_size * sizeof(int));
	int** pointer = &arr;
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	for (i = 0; i < 17; i++) reg[i] = 0;
	reg[15] = *char_array_A;

	for (i = 0; i < line; i++)
	{
		if (ch != 'f') ch = 'a';
		while (ch != '\r' && ch != 'f' && ch != 'q')	 ch = _getch();
		if (ch == 'q') break;
		if (ch != 'f' || i == line) print_char_arrays(char_array_A, char_array_B, char_array_C, char_array_D, line, i + 1, coord);

		for (j = 0; j < 20; j++)
			if (strcmp(key[j], char_array_B[i]) == 0)
				switch (j)
				{
				case 0:
					arr = DS(char_array_A, char_array_C, char_array_D, arr, i, &arr_size, &plus_size);
					reg[14] = *pointer;
					j = 20; break;
				case 1:
					arr = DC(char_array_A, char_array_C, char_array_D, arr, i, &arr_size, &plus_size);
					reg[14] = *pointer;
					j = 20; break;
				case 2:
					L(reg, char_array_A, char_array_C, char_array_D, i, *pointer);
					j = 22; break;
				case 3:
					LA(reg, char_array_A, char_array_C, char_array_D, i, *pointer);
					j = 22; break;
				case 4:
					LR(reg, char_array_C, char_array_D, i);
					j = 21;  break;
				case 5:
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 1, reg, arr, *pointer);	//A
					j = 22; break;
				case 6:
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 1, reg, arr);	//AR
					j = 21; break;
				case 7:
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 2, reg, arr, *pointer);	//S
					j = 22; break;
				case 8:
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 2, reg, arr);	//SR	
					j = 21; break;
				case 9:
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 3, reg, arr, *pointer);	//M
					j = 22; break;
				case 10:
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 3, reg, arr);	//MR	
					j = 21; break;
				case 11:
					dzialanie_arytmetyczne(char_array_A, char_array_C, char_array_D, i, j = 4, reg, arr, *pointer);	//D
					j = 22; break;
				case 12:
					dzialanie_arytmetyczne_R(char_array_C, char_array_D, i, j = 4, reg, arr);	//DR
					j = 21; break;
				case 13:
					C(reg, char_array_A, char_array_C, char_array_D, i, arr, *pointer);
					j = 22; break;
				case 14:
					CR(reg, char_array_C, char_array_D, i);
					j = 21; break;
				case 15:
					i = J( char_array_A, char_array_C, i);
					j = 30; break;
				case 16:
					i = JP(reg, char_array_A, char_array_C, i);
					j = 30; break;
				case 17:
					i = JZ(reg, char_array_A, char_array_C, i);
					j = 30; break;
				case 18:
					i = JN(reg, char_array_A, char_array_C, i);
					j = 30; break;
				case 19:
					ST(reg, char_array_A, char_array_C, char_array_D, i, *pointer);
					j = 22; break;
				}
		if (ch != 'f' || i == line)
		{
			print_registers_array(char_array_C, char_array_D, coord, reg, i, j);
			print_values_array(char_array_A, char_array_D, coord, arr_size, arr, i, j, *pointer, reg);
		}
		if (i == line - 1)
		{
			print_values_array(char_array_A, char_array_D, coord, arr_size, arr, i, j, *pointer, reg);
			print_registers_array(char_array_C, char_array_D, coord, reg, i, j);
		}
	}
	
	coord.X = 1;
	coord.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    _getch();

	*pointer = NULL;
	free(arr);
}