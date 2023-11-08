#include "encoder.h"

int	tree_size(t_node *root)
{
	int	left, right;

	if (root == NULL)
		return (-1);
	else
	{
		left = tree_size(root->left) + 1;
		right = tree_size(root->right) + 1;
		if (left > right)
			return left;
		else
			return right;
	}
}

char **init_dict()
{
	char 	**dict;

	dict = malloc(sizeof(char *) * SIZE + 1);
	for (int i = 0; i < SIZE; i++)
		dict[i] = calloc((g_data->height + i), sizeof(char));
	return (dict);
}

void	create_dict(t_node *root, char *path)
{
	char right[g_data->height];
	char left[g_data->height];

	if (g_data->dict == NULL)
		g_data->dict = init_dict();
	if (root->left == NULL && root->right == NULL)
		strcpy(g_data->dict[root->c], path);
	else
	{
		strcpy(left, path);
		strcpy(right, path);
		strcat(left, "0");
		strcat(right, "1");
		create_dict(root->left, left);
		create_dict(root->right, right);
	}
}

void	print_dict(char **dic)
{
	printf("\n\t Dicionário: \n");
	for (int i = 0; i < SIZE; i++)
	{
		if (strlen(dic[i]) > 0)
			printf("\t%3d: %s\n", i, dic[i]);
	}
}