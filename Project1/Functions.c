#include "Functions.h"

void push(int **arr, int *plus_size, int *size) 
{
	// ZWIÊKSZAMY ROZMIAR TABLICY O PODANY WYMIAR
	*size = *size + *plus_size; 
	printf(" array size = %d\n ", *size );
	*arr = realloc(*arr, sizeof(int) * *size ); 
	return size;
}

int DS(char **char_array_A, char **char_array_C, char **char_array_D, int *arr, int line, int *arr_size, int *plus_size)
{ 
	int i = 0;
	*plus_size = 0;
	_itoa(*arr_size, char_array_D[line], 10);
	if(char_array_C[line][0] == 'I')	*plus_size = 1;
	else
	{
			*plus_size = atoi(char_array_C[line]);
	}
	push(&arr, plus_size, arr_size);
	for (i = *arr_size - *plus_size; i < *arr_size; i++) arr[i] = 0;
	return arr;
}

int DC(char **char_array_A, char **char_array_C, char **char_array_D, int* arr, int line, int* arr_size, int* plus_size)
{
	printf("DC: ");
	int char_index_C = 0;
	int value_place, i;
	*plus_size = 0;
	_itoa(*arr_size, char_array_D[line], 10);
	if (char_array_C[line][0] == 'I')	*plus_size = 1;
	else
	{
		*plus_size = atoi(char_array_C[line]);
	}
	push(&arr, plus_size, arr_size);
	for (i = *arr_size - *plus_size; i < *arr_size; i++) arr[i] = 0;
	
	while (char_array_C[line][char_index_C] != '\n ') // WPISUJEMY PODAN¥ WARTOŒÆ DO ZADEKLAROWANEJ CZÊŒCI TABLICY
	{
		if (char_array_C[line][char_index_C] == '(')
		{
			char_index_C++;
			value_place = char_index_C;
			for (int i = *arr_size - *plus_size; i < *arr_size; i++)
			{
				while (char_array_C[line][char_index_C] != ')')
				{
					arr[i] *= 10;
					arr[i] += char_array_C[line][char_index_C] - '0';
					char_index_C++;
				}		
				char_index_C = value_place;
				char_array_C[line][char_index_C - 1] = '\0';
			}
			break;
		}
		char_index_C++;	
	}
	printf("ARRAY[%d] : ARRAY[%d] = %d \n ", *arr_size - *plus_size, *arr_size - 1, arr[*arr_size - 1]);
	return arr;
}

void L(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *arr, int *pointer)
{ 
	int char_index_D = 0;
	int p = 0, i = 0;
	int value_place;

	while (char_array_D[line][char_index_D] != '\0')
	{
		if (char_array_D[line][char_index_D] == '(')
		{
			value_place = char_index_D;
			char_index_D++;
			while (char_array_D[line][char_index_D] != ')')
			{
				p *= 10;
				p += char_array_D[line][char_index_D] - '0';
				char_index_D++;
			}
			char_array_D[line][value_place] = '\0';
			pointer = reg[p];
			break;
		}
		char_index_D++;
	}
	while (strcmp(char_array_D[line], char_array_A[i]) != 0 && i != line) { i++; }
	if (i == line) pointer = (int*)((char*)pointer + atoi(char_array_D[line]));
	else pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	reg[atoi(char_array_C[line])] = *pointer;
	printf("L : REGISTER[%s] = %d \n ", char_array_C[line], reg[atoi(char_array_C[line])]);
}

void LA(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int* arr, int *pointer)
{
	int char_index_D = 0;
	int p = 0, i = 0;
	int value_place;


	while (char_array_D[line][char_index_D] != '\0')
	{
		if (char_array_D[line][char_index_D] == '(')
		{
			value_place = char_index_D;
			char_index_D++;
			while (char_array_D[line][char_index_D] != ')')
			{
				p *= 10;
				p += char_array_D[line][char_index_D] - '0';
				char_index_D++;
			}
			char_array_D[line][value_place] = '\0';
			pointer = reg[p];
			break;
		}
		char_index_D++;
	}
	while (strcmp(char_array_D[line], char_array_A[i]) != 0 && i != line) { i++; }
	if (i == line) pointer = (int*)((char*)pointer + atoi(char_array_D[line]));
	else pointer = (int*)((char*)pointer + atoi(char_array_D[i]) * 4);
	reg[atoi(char_array_C[line])] = pointer;
	printf("LA: REGISTER[%s] = %p \n ", char_array_C[line], reg[atoi(char_array_C[line])]);
}


void LR(int *reg, char  **char_array_C, char  **char_array_D, int line)
{
	printf("LR: ");
	reg[atoi(char_array_C[line])] = reg[atoi(char_array_D[line])];
	printf("REGISTER[%s] = %d \n ", char_array_C[line], reg[atoi(char_array_C[line])]);
}

void dzialanie_arytmetyczne(char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int znak_dzialania, int *reg, int *arr)
{
	int i = 0;
	while (strcmp(char_array_D[line], char_array_A[i]) != 0) i++;
	if (znak_dzialania == 1) reg[atoi(char_array_C[line])] += arr[atoi(char_array_D[i])];
	else if (znak_dzialania == 2) reg[atoi(char_array_C[line])] -= arr[atoi(char_array_D[i])];
	else if (znak_dzialania == 3) reg[atoi(char_array_C[line])] *= arr[atoi(char_array_D[i])];
	else if (znak_dzialania == 4) reg[atoi(char_array_C[line])] /= arr[atoi(char_array_D[i])];
	printf("REGISTER[%s] = %d\n ", char_array_C[line], reg[atoi(char_array_C[line])]);
}

void dzialanie_arytmetyczne_R(char  **char_array_C, char  **char_array_D, int line, int znak_dzialania, int *reg, int *arr)
{
	if(znak_dzialania == 1) reg[atoi(char_array_C[line])] += reg[atoi(char_array_D[line])];
	else if(znak_dzialania == 2) reg[atoi(char_array_C[line])] -= reg[atoi(char_array_D[line])];
	else if (znak_dzialania == 3) reg[atoi(char_array_C[line])] *= reg[atoi(char_array_D[line])];
	else if (znak_dzialania == 4) reg[atoi(char_array_C[line])] /= reg[atoi(char_array_D[line])];
	printf("REGISTER[%s] = %d\n ", char_array_C[line], reg[atoi(char_array_C[line])]);
}

void C(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *arr)
{
	int i = 0;
	while (strcmp(char_array_D[line], char_array_A[i]) != 0) i++;
	reg[16] = reg[atoi(char_array_C[line])] - arr[atoi(char_array_D[i])];
	printf("C : %d\n ", reg[15]);
}

void CR(int *reg, char  **char_array_C, char  **char_array_D, int line, int *arr)
{
	reg[16] = reg[atoi(char_array_C[line])] - reg[atoi(char_array_D[line])];
	printf("CR: %d\n ", reg[16]);
}

int J(int *reg, char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	printf("J : %s\n ", char_array_C[line]);
	while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
	return instruction_index - 1;
}

int JP(int* reg, char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	if (reg[16] > 0)
	{
		printf("JP: %s\n ", char_array_C[line]);
		while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
		return instruction_index - 1;
	}
	else return line;
}
int JZ(int* reg, char  **char_array_A, char  **char_array_C, int line)
{
	int instruction_index = 0;
	if (reg[16] == 0)
	{
		printf("JZ: %s\n ", char_array_C[line]);
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
		printf("JN: %s\n ", char_array_C[line]);
		while (strcmp(char_array_C[line], char_array_A[instruction_index]) != 0) instruction_index++;
		return instruction_index - 1;
	}
	else return line;
}

void ST(int* reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int* arr)
{
	int i = 0;
	while (strcmp(char_array_D[line], char_array_A[i]) != 0) i++;
	arr[atoi(char_array_D[i])] = reg[atoi(char_array_C[line])];
	printf("ST: arr[%s] = %d \n ", char_array_D[i], arr[atoi(char_array_D[i])]);
}