#include "encoder.h"

void	fill_table()
{
	unsigned int j;

	printf("\n\tCreating frequency table... ");
	for (int i = 0; g_data->text[i] != '\0'; i++)
	{
		j = g_data->text[i];
		g_data->freq_tab[j]++;
	}
}

void	print_table(unsigned int *tab)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (tab[i] != 0)
			printf("\n \t%d = %u = %c\n", i, tab[i], i);
	}
}