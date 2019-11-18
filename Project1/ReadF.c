#include"ReadF.h"

int read_file_lines_number()
{
	FILE* file;
	int line = 0;
	char ch = 'a';
	file = fopen("file.txt", "r");

	while (!feof(file))
	{
		ch = fgetc(file);
		if (ch == '\n' || ch == EOF)
			line++;
	}
	fclose(file);
	return line;
}

void read_file_data_to_arrays(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, char *key[])
{
	FILE *file;
	file = fopen("file.txt", "r");
	int array_index_A = 0;
	int array_index_B = 0;
	int array_index_C = 0;
	int array_index_D = 0;
	int line = 0;
	int counter = 0;
	char ch = 'a';
	int nameMoved = 0;
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
			nameMoved = 0;
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
						nameMoved = 1;
						while (char_array_A[line][array_index_B] != '\0')
						{
							char_array_B[line][array_index_B] = char_array_A[line][array_index_B];
							array_index_B++;
						}						
						char_array_A[line][0] = '\0';
						counter++;
					}
				}
				if(nameMoved == 0)
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

void print_char_arrays(char **char_array_A, char **char_array_B, char **char_array_C, char **char_array_D, int line)
{
	printf("\n\t\tTABLICA INSTRUKCJI\n\n ");
	for (int i = 0; i < line; i++)
	{
		printf("\t%s\t ", char_array_A[i]);
		printf("%s\t ", char_array_B[i]);
		printf("%s\t ", char_array_C[i]);
		printf("%s\n ", char_array_D[i]);
	}
	printf("\n ");
}
