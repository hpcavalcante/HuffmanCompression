#include "encoder.h"

t_node *remove_from_start(t_list *list)
{
	t_node *aux = NULL;

	if(list->start) 
	{
		aux = list->start;
		list->start = aux->next;
		aux->next = NULL;
		list->size--;
	}
	return (aux);
}

void	print_tree(t_node *root, int size)
{
	if (root->left == NULL && root->right == NULL)
		printf("\n\t Folha: %c\tAltura: %d\n", root->c, size);
	else
	{
		print_tree(root->left, size + 1);
		print_tree(root->right, size + 1);
	}
}

t_node *create_tree(t_list *list)
{
	t_node *first, *second, *new;

	printf("\n\tCreating Huffman Tree...");
	while (list->size > 1)
	{
		first = remove_from_start(list);
		second = remove_from_start(list);
		new = malloc(sizeof(t_node));
		if (new == NULL)
		{
			printf("Error at malloc in 'create_tree' function\n");
			exit (1);
		}
		new->freq = (first->freq + second->freq);
		new->left = first;
		new->right = second;
		new->next = NULL;
		list_insert(list, new);
	}
	g_data->height = tree_size(list->start);
	return (list->start);
}
