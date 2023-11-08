#include "encoder.h"

int	sizeof_string(char **dic, unsigned char *text)
{
	int i;
	int	size;

	i = 0;
	size = 0;
	while (text[i] != '\0')
	{
		size += strlen(dic[text[i]]);
		i++;
	}
	return (size);
}

void	encoder()
{
	int	i;
	int	size;

	printf("\n\tEncoding... ");
	size = sizeof_string(g_data->dict, g_data->text);
	char	*cod = calloc(size + 1,sizeof(char));
	i = 0;
	while (g_data->text[i] != '\0')
	{
		strcat(cod, g_data->dict[g_data->text[i]]);
		i++;
	}
	g_data->encoded = (unsigned char *)cod;
	//return ((unsigned char *)cod);
}