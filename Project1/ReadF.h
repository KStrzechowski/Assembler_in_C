#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

int read_file_lines_number(char filename[20]);

void read_file_data_to_arrays(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, char *key[], char filename[20]);

void print_char_arrays(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, int line, int current_line, COORD coord);

void print_registers_array(char **char_array_C, char **char_array_D, COORD coord, int* reg, int i, int j);

void print_values_array(char **char_array_A, char **char_array_D, COORD coord, int arr_size, int* arr, int line, int k, int *pointer, int *reg);