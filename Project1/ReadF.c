#include"ReadF.h"

void set_color(int foreground, int background);

int read_file_lines_number(char filename[20])
{
	FILE* file;
	int line = 0;
	char ch = 'a';
	file = fopen(filename, "r");

	while (!feof(file))
	{
		ch = fgetc(file);
		if (ch == '\n' || ch == EOF)
			line++;
	}
	fclose(file);
	return line;
}

void read_file_data_to_arrays(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, char *key[] ,char filename[20])
{
	FILE *file;
	file = fopen(filename, "r");
	int array_index_A = 0;
	int array_index_B = 0;
	int array_index_C = 0;
	int array_index_D = 0;
	int line = 0;
	int counter = 0;
	char ch = 'a';
	int name_moved = 0;
	while (ch != EOF)
	{
		ch = fgetc(file);
		// JEŒLI SPOTKAMY PRZECINEK, SPACJÊ ALBO TABULATOR TO COUNTER ROŒNIE
		if (ch == ',' || ch == ' ' || ch == '\t') counter++;
		// DODATKOWO JEŒLI SPOTKAMY KONIEC LINII TO "LINIA ROŒNIE" I ZERUJEMY INDEXY TABLIC
		else if (ch == '\n' || ch == EOF)
		{
			char_array_B[line][array_index_B] = '\0';
			char_array_C[line][array_index_C] = '\0';
			char_array_D[line][array_index_D] = '\0';

			counter = 0;
			name_moved = 0;
			line++;
			array_index_A = 0;
			array_index_B = 0;
			array_index_C = 0;
			array_index_D = 0;
		}
		else
		{
			// SPRAWDZAMY MODULO COUNTERA I DOPASOWUJEMY DO KTÓREJ TABLICY WPISYWAÆ
			if (counter % 4 == 0)
			{
				char_array_A[line][array_index_A] = ch;
				array_index_A++;
			}
			if ( (counter % 4 == 1) && (array_index_B == 0) ) 
			{
				char_array_A[line][array_index_A] = '\0';
				for (int j = 0; j < 20; j++)
				{
					if (strcmp(key[j], char_array_A[line]) == 0)
					{
						name_moved = 1;
						while (char_array_A[line][array_index_B] != '\0')
						{
							char_array_B[line][array_index_B] = char_array_A[line][array_index_B];
							array_index_B++;
						}						
						char_array_A[line][0] = '\0';
						counter++;
					}
				}
				if(name_moved == 0)
				{
					char_array_B[line][array_index_B] = ch;
					array_index_B++;
				}
			}
			else if (counter % 4 == 1)
			{
				char_array_B[line][array_index_B] = ch;
				array_index_B++;
			}
			if (counter % 4 == 2)
			{
				char_array_C[line][array_index_C] = ch;
				array_index_C++;
			}
			if (counter % 4 == 3)
			{
				char_array_D[line][array_index_D] = ch;
				array_index_D++;
			}
		}
	}
	fclose(file);
}

void print_char_arrays(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, int line, int current_line, COORD coord)
{
	int i;
	coord.X = 0;
	coord.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("NACISNIJ \"ENTER\" ZEBY PRZEJSC DO NASTEPNEJ INSTRUKCJI\nNACISNIJ \"f\" ZEBY WYKONAC CALY PROGRAM\nNACISNIJ \"q\" ZEBY WYJSC Z PROGRAMU\n ");
	printf("\n\tTABLICA INSTRUKCJI\n\n ");
	for (i = 0; i < line; i++)
	{
		if (current_line == i + 1) set_color(2, 0);
		printf("%d. %15s\t", i, char_array_A[i]);
		printf("%2s\t", char_array_B[i]);
		printf("%-8s\t ", char_array_C[i]);
		printf("%-6s\n ", char_array_D[i]);
		set_color(15, 0);
	}
	printf("\n ");
}

void print_registers_array(char **char_array_C, char **char_array_D, COORD coord, int* reg, int current_line, int instruction_code)
{
	int i;
	coord.X = 70;
	coord.Y = 5;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("  TABLICA REJESTROW\n\n ");
	for (i = 0; i < 17; i++)
	{
		if ((instruction_code == 22 || instruction_code == 23) && (i == atoi(char_array_C[current_line])))  set_color(1, 0);
		if ((instruction_code == 22) && (i == atoi(char_array_D[current_line])))  set_color(5, 0);
			coord.Y = i + 7;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 14 || i == 15) printf("RG[%d] = %2p\n ", i, reg[i]);
		else printf("RG[%d] = %-8d\n ", i, reg[i]);
		set_color(15, 0);
	}
}

void print_values_array(char** char_array_A, char** char_array_D, COORD coord, int arr_size, int* arr, int line, int instruction_code, int* pointer, int* reg)
{
	int i = 0, j, k = 0;
	int char_index_D = 0;
	char c = ' ';

	while (char_array_D[line][char_index_D] != '\0')
	{
		if (char_array_D[line][char_index_D] == '(')
		{
			char_index_D++;
			while (char_array_D[line][char_index_D] != ')')
			{
				k *= 10;
				k += char_array_D[line][char_index_D] - '0';
				char_index_D++;
			}
			if (reg[k] < 40000) pointer = (int*)((char*)pointer + reg[k]); // SPRAWDZAMY CZY W REJESTRZE JEST CA£Y ADRES CZY PRZESUNIÊCIE 
			else pointer = reg[k];
			break;
		}
		char_index_D++;
	}
	while (strcmp(char_array_D[line], char_array_A[i]) != 0 && i != line) { i++; }
	if (i == line) pointer = (int*)((char*)pointer + atoi(char_array_D[line]));
	else pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	
	coord.X = 160;
	coord.Y = 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("PAMIEC\n\n ");

	for (j = 0; j < arr_size; j++)
	{
		if (instruction_code == 23)
		{
			if ((((int)pointer - (int)reg[14]) / 4) == j) set_color(5, 0);
		}
		if (j % 3 == 0)
		{
			coord.X = 100;
			coord.Y = (j / 3) + 7;
		}
		else if (j % 3 == 1) coord.X = 140;
		else  coord.X = 180;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (instruction_code == 21 && j == atoi(char_array_D[line]))
			printf("%15s", char_array_A[line]);
		else
		{
			coord.X += 15;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
		printf("[%d] = %-10d\n ", j, arr[j]);
		set_color(15, 0);
	}
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int foreground, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + 16 * background);
}