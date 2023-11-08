#include "encoder.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	file_size(char *argv)
{
	FILE *file = fopen(argv, "r");
	int	size;

	size = 0;
	if (file)
	{
		while (fgetc(file) != -1)
			size++;
	}
	else
	{
		printf("Error at open/read file at file_size\n");
		exit (0);
	}
	return (size);
}

char	*read_file(char *file_name)
{
	FILE *file = fopen(file_name, "r");
	char	c;
	int		i = 0;
	char	*text;

	text = calloc(g_data->file_size, sizeof(char *));
	if (file)
	{
		while(!feof(file))
		{
			c = fgetc(file);
			if (c != -1)
			{
				text[i] = c;
				i++;
			}
		}
		fclose (file);
		return (text);
	}
	else 
		printf("\n Error at open file to read\n");
	exit (1);
}