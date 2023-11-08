#include "encoder.h"

void	create_list(t_list *list)
{
	printf("\n\tCreating ordened list... ");
	list->start = NULL;
	list->size = 0;
	fill_list(g_data->freq_tab, list);
}

void	list_insert(t_list *list, t_node *node)
{
	t_node *aux;

	if (list->start == NULL)
		list->start = node;
	else if (node->freq < list->start->freq)
	{
		node->next = list->start;
		list->start = node;
	}
	else
	{
		aux = list->start;
		while (aux->next && aux->next->freq <= node->freq)
			aux = aux->next;
		node->next = aux->next;
		aux->next = node;
	}
	list->size++;
}

void	fill_list(unsigned int *tab, t_list *list)
{
	t_node *new;

	for (int i = 0; i < SIZE; i++)
		if(tab[i] >  0)
		{
			new = malloc(sizeof(t_node));
			if (new == NULL)
			{
				printf("Error at malloc in 'fill_list' function\n");
				exit(1);
			}
			new->c = i;
			new->freq = tab[i];
			new->right = NULL;
			new->left = NULL;
			new->next = NULL;
			list_insert(list, new);
		}
}

void	print_list(t_list *list)
{
	t_node *aux = list->start;

	printf("\n\t Lista ordenada: | Tamanho: %d\n\n", list->size);
	while (aux)
	{
		printf("\n\t Caracter: %c | Frequência: %d\n\n", aux->c, aux->freq);
		aux = aux->next;
	}
}
