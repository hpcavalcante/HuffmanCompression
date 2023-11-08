#include "encoder.h"

void	free_tree(t_node *tree)
{
	if (tree == NULL)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free(data->text);
	free(data->freq_tab);
	for (int i = 0; i < data->height; i++)
		free(data->dict[i]);
	free(data->dict);
	free(data->encoded);
	free(data->file_out);
	free(data);
}
