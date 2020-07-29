#include "Functions.h"
void set_color(int foreground, int background);

void push(int **arr, int *plus_size, int *size) 
{
	// ZWIÊKSZAMY ROZMIAR TABLICY O PODANY WYMIAR
	*size = *size + *plus_size; 
	*arr = realloc(*arr, sizeof(int) * *size ); 
	return size;
}

int DS(char **char_array_A, char **char_array_C, char **char_array_D, int *arr, int line, int *arr_size, int *plus_size)
{ 
	int i = 0;
	*plus_size = 0;
	_itoa(*arr_size, char_array_D[line], 10);
	if(char_array_C[line][0] == 'I')	*plus_size = 1;
	else *plus_size = atoi(char_array_C[line]);
	
	push(&arr, plus_size, arr_size);
	for (i = *arr_size - *plus_size; i < *arr_size; i++) arr[i] = i;
	return arr;
}

int DC(char **char_array_A, char **char_array_C, char **char_array_D, int* arr, int line, int* arr_size, int* plus_size)
{
	int char_index_C = 0;
	int value_place, i;
	*plus_size = 0;
	_itoa(*arr_size, char_array_D[line], 10);
	if (char_array_C[line][0] == 'I')	*plus_size = 1;
	else *plus_size = atoi(char_array_C[line]);
	
	push(&arr, plus_size, arr_size);
	for (i = *arr_size - *plus_size; i < *arr_size; i++) arr[i] = 0;

	// WPISUJEMY PODAN¥ WARTOŒÆ DO ZADEKLAROWANEJ CZÊŒCI TABLICY
	while (char_array_C[line][char_index_C] != '\n ') 
	{
		if (char_array_C[line][char_index_C] == '(')
		{
			char_index_C++;
			for (int i = *arr_size - *plus_size; i < *arr_size; i++)
				while (char_array_C[line][char_index_C] != ')')
				{
					arr[i] *= 10;
					arr[i] += char_array_C[line][char_index_C] - '0';
					char_index_C++;
				}		
			break;
		}
		char_index_C++;	
	}
	return arr;
}

void L(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *pointer)
{ 
	int char_index_D = 0;
	int p = 0, i = 0;

	while (char_array_D[line][char_index_D] != '\0')
	{
		if (char_array_D[line][char_index_D] == '(')
		{
			char_index_D++;
			while (char_array_D[line][char_index_D] != ')')
			{
				p *= 10;
				p += char_array_D[line][char_index_D] - '0';
				char_index_D++;
			}
			if (reg[p] < 40000) pointer = (int*)((char*)pointer + reg[p]); // SPRAWDZAMY CZY W REJESTRZE JEST CA£Y ADRES CZY PRZESUNIÊCIE 
			else pointer = reg[p];
			break;
		}
		char_index_D++;
	}
	while (strcmp(char_array_D[line], char_array_A[i]) != 0 && i != line) { i++; }
	if (i == line) pointer = (int*)((char*)pointer + atoi(char_array_D[line]));
	else pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	reg[atoi(char_array_C[line])] = *pointer;
}

void LA(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *pointer)
{
	int char_index_D = 0;
	int p = 0, i = 0;

	while (char_array_D[line][char_index_D] != '\0')
	{
		if (char_array_D[line][char_index_D] == '(')
		{
			char_index_D++;
			while (char_array_D[line][char_index_D] != ')')
			{
				p *= 10;
				p += char_array_D[line][char_index_D] - '0';
				char_index_D++;
			}
			if (reg[p] < 40000) pointer = (int*)((char*)pointer + reg[p]); // SPRAWDZAMY CZY W REJESTRZE JEST CA£Y ADRES CZY PRZESUNIÊCIE
			else pointer = (int*)reg[p];
			break;
		}
		char_index_D++;
	}
	while (strcmp(char_array_D[line], char_array_A[i]) != 0 && i != line) { i++; }
	if (i == line) pointer = (int*)((char*)pointer + atoi(char_array_D[line]));
	else pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	reg[atoi(char_array_C[line])] = pointer;
}

void LR(int *reg, char  **char_array_C, char  **char_array_D, int line)
{
	reg[atoi(char_array_C[line])] = reg[atoi(char_array_D[line])];
}

void dzialanie_arytmetyczne(char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int znak_dzialania, int *reg, int *arr, int *pointer)
{
	int i = 0;
	while (strcmp(char_array_D[line], char_array_A[i]) != 0) { i++; }
	pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);

	while (strcmp(char_array_D[line], char_array_A[i]) != 0) i++;
	if (znak_dzialania == 1) reg[atoi(char_array_C[line])] += *pointer;
	else if (znak_dzialania == 2) reg[atoi(char_array_C[line])] -= *pointer;
	else if (znak_dzialania == 3) reg[atoi(char_array_C[line])] *= *pointer;
	else if (znak_dzialania == 4) reg[atoi(char_array_C[line])] /= *pointer;
}

void dzialanie_arytmetyczne_R(char  **char_array_C, char  **char_array_D, int line, int znak_dzialania, int *reg, int *arr)
{
	if(znak_dzialania == 1) reg[atoi(char_array_C[line])] += reg[atoi(char_array_D[line])];
	else if(znak_dzialania == 2) reg[atoi(char_array_C[line])] -= reg[atoi(char_array_D[line])];
	else if (znak_dzialania == 3) reg[atoi(char_array_C[line])] *= reg[atoi(char_array_D[line])];
	else if (znak_dzialania == 4) reg[atoi(char_array_C[line])] /= reg[atoi(char_array_D[line])];
}

void C(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *arr, int *pointer)
{
	int i = 0;
	while (strcmp(char_array_D[line], char_array_A[i]) != 0) { i++; }
	pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	
	while (strcmp(char_array_D[line], char_array_A[i]) != 0) i++;
	(int)reg[16] = (int)(reg[atoi(char_array_C[line])] - *pointer);
}

void CR(int *reg, char  **char_array_C, char  **char_array_D, int line)
{
	reg[16] = reg[atoi(char_array_C[line])] - reg[atoi(char_array_D[line])];
}

int J( char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
	return instruction_index - 1;
}

int JP(int* reg, char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	if (reg[16] > 0)
	{
		while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
		return instruction_index - 1;
	}
	return line;
}
int JZ(int* reg, char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	if (reg[16] == 0)
	{
		while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
		return instruction_index - 1;
	}
	return line;
}

int JN(int* reg, char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	if (reg[16] < 0)
	{
		while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
		return instruction_index - 1;
	}
	return line;
}

void ST(int* reg, char** char_array_A, char** char_array_C, char** char_array_D, int line, int* pointer)
{
	int char_index_D = 0;
	int p = 0, i = 0;

	while (char_array_D[line][char_index_D] != '\0')
	{
		if (char_array_D[line][char_index_D] == '(')
		{
			char_index_D++;
			while (char_array_D[line][char_index_D] != ')')
			{
				p *= 10;
				p += char_array_D[line][char_index_D] - '0';
				char_index_D++;
			}
			if (reg[p] < 40000) pointer = (int*)((char*)pointer + reg[p]); // SPRAWDZAMY CZY W REJESTRZE JEST CA£Y ADRES CZY PRZESUNIÊCIE
			else pointer = (int*)reg[p];
			break;
		}
		char_index_D++;
	}
	while (strcmp(char_array_D[line], char_array_A[i]) != 0 && i != line) { i++; }
	if (i == line) pointer = (int*)((char*)pointer + atoi(char_array_D[line]));
	else pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	*pointer = reg[atoi(char_array_C[line])];
}