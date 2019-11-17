#include<stdio.h>
#include<stdlib.h>

int DS(char **char_array_A, char **char_array_C, char **char_array_D, int *arr, int line, int *arr_size, int *plus_size);

int DC(char **char_array_A, char **char_array_C, char **char_array_D, int *arr, int line, int *arr_size, int* plus_size);

void L(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *arr, int *pointer);

void LA(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int* arr, int *pointer);

void LR(int *reg, char  **char_array_C, char  **char_array_D, int line);
	
void dzialanie_arytmetyczne(char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int znak_dzialania, int *reg, int *arr);

void dzialanie_arytmetyczne_R(char  **char_array_C, char  **char_array_D, int line, int znak_dzialania, int *reg, int *arr);

void C(int *reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int *arr);

void CR(int *reg, char  **char_array_C, char  **char_array_D, int line, int *arr);

int J(int *reg, char  **char_array_A, char  **char_array_C, int line);

int JP(int* reg, char  **char_array_A, char  **char_array_C, int line);

int JZ(int* reg, char  **char_array_A, char  **char_array_C, int line);

int JN(int* reg, char  **char_array_A, char  **char_array_C, int line);

void ST(int* reg, char  **char_array_A, char  **char_array_C, char  **char_array_D, int line, int* arr);
