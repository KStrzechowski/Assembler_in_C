#include<stdlib.h>
#include<stdio.h>
#include <conio.h>
#include<Windows.h>
#include"ReadF.h"
#include"Instructions.h"
#include"Functions.h" 
void MaximizeOutputWindow(void)
{
	HWND console_window = GetConsoleWindow(); 
	ShowWindow(console_window, SW_MAXIMIZE); 
}

main(int argc, char* argv[])
{
	FILE* file;
	COORD coord;
	char filename[20];
	char* key[20] = {"DS", "DC", "L", "LA", "LR", "A", "AR", "S", "SR", "M", "MR", "D", "DR", "C", "CR", "J", "JP", "JZ", "JN", "ST" };
	char** char_array_A;
	char** char_array_B;
	char** char_array_C;
	char** char_array_D;
	int line, i;
	MaximizeOutputWindow();
	coord.X = 0;
	coord.Y = 0;
	printf("PODAJ NAZWE PLIKU: ");
	scanf("%s", filename);


	line = read_file_lines_number(filename);
	char_array_A = (char**) malloc(line * sizeof(char*));
	char_array_B = (char**) malloc(line * sizeof(char*));
	char_array_C = (char**) malloc(line * sizeof(char*));
	char_array_D = (char**) malloc(line * sizeof(char*));
	for (i = 0; i < line; i++)
	{
		char_array_A[i] = (char*) malloc(20 * sizeof(char));
		char_array_B[i] = (char*) malloc(3  * sizeof(char));
		char_array_C[i] = (char*) malloc(20 * sizeof(char));
		char_array_D[i] = (char*) malloc(20 * sizeof(char));
	}
	read_file_data_to_arrays(char_array_A, char_array_B, char_array_C, char_array_D, key, filename);
	print_char_arrays(char_array_A, char_array_B, char_array_C, char_array_D, line, 0, coord);
	check_instructions(char_array_A, char_array_B, char_array_C, char_array_D, line, key);

	for (i = 0; i < line; i++) free(char_array_A[i], char_array_B[i], char_array_C[i], char_array_D[i]);
	free(char_array_A, char_array_B, char_array_C, char_array_D);
	
	return 0;
} 