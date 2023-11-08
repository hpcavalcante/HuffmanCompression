#include "encoder.h"

t_data	*g_data;

void	check_args(int argc, char **argv)
{
	struct stat	sb;

	if (strcmp("-f", argv[1]) == 0)
	{
		for (int i = 2; i < argc; i++)
			g_data->file_size += file_size(argv[i]);
		g_data->text = calloc(g_data->file_size + 2, sizeof(unsigned char));
		for (int i = 2; i < argc; i++)
		{
			strcat((char *)g_data->text, read_file(argv[i]));
			stat(argv[i], &sb);
			g_data->initial_size += sb.st_size;
		}
		g_data->file_name = (unsigned char *)argv[2];
	}
	else
	{
		for (int i = 1; i < argc; i++)
			g_data->file_size += strlen(argv[i]);
		g_data->text = calloc(g_data->file_size + 1, sizeof(unsigned char));
		for (int i = 1; i < argc; i++)
		{
			strcat((char *)g_data->text, argv[i]);
			if (i < argc - 1)
				strcat((char *)g_data->text, " ");
		}
		g_data->initial_size = strlen((char *)g_data->text);
		g_data->file_name = (unsigned char *)argv[1];
	}
	g_data->file_out = calloc(strlen((char *)g_data->file_name) + 4,\
	sizeof(unsigned char *));
	strcat((char *)g_data->file_out, (char *)g_data->file_name);
	strcat((char *)g_data->file_out, ".hf");
}

void	init_g_data(int argc, char **argv)
{
	g_data = malloc(sizeof(t_data));
	g_data->freq_tab = (unsigned int *)calloc(SIZE, sizeof(int));
	g_data->text = NULL;
	g_data->file_size = 0;
	g_data->initial_size = 0;
	g_data->file_out = NULL;
	check_args(argc, argv);
	if ((strlen((char *)g_data->text) > SIZE_MAX))
		printf(WARNING);
	g_data->time = get_time();
	g_data->dict = NULL;
}

void	tree_to_array(t_node *root, long int *tree, int *index)
{
	if (root == NULL) {
		tree[(*index)++] = -1;
		return ;
	}
	tree[(*index)++] = root->c;
	tree_to_array(root->left, tree, index);
	tree_to_array(root->right, tree, index);
	tree_to_array(root->next, tree, index);
}

t_shm* create_shared_memory() 
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(t_shm), 0666 | IPC_CREAT);
    t_shm* shared_memory = (t_shm*)shmat(shmid, NULL, 0);
	bzero(shared_memory, sizeof(t_shm));

	return (shared_memory);
}

void	sharing_memory(t_node *tree, t_shm *shm)
{
	int i = 0;
	
	tree_to_array(tree, shm->tree, &i);
	shm->time_to_decode = -1;
	strcpy(shm->file_out, (char *)g_data->file_out);
	strcpy((char *)shm->compress_data, (char *)g_data->compressed_data);
	shm->text_size = strlen((char *)g_data->text);
}

int	main(int argc, char **argv)
{
	t_list 		list;
	t_node 		*tree;

	t_shm *shm = create_shared_memory();
	setlocale(LC_ALL, "C.UTF-8");
	init_g_data(argc, argv);
	fill_table();
	create_list(&list);
	tree = create_tree(&list);
	create_dict(tree, "");
	encoder();
	compress();
	sharing_memory(tree, shm);
	print_status_encoder();
	print_status_decoder(shm);
	shmdt(shm);
	free_data(g_data);
	free_tree(tree);
	return (0);
}
