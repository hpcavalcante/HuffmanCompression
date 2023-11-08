#include "../include/decoder.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned int	is_positive_bit(unsigned char byte, int i)
{
	unsigned char mask = (1 << i);
	return (byte & mask);
}

unsigned char	*decompress(t_node *root, char *file_name, int size, char *compressed)
{
	FILE *file = fopen(file_name, "rb");
	FILE *file_out = fopen("decompressed", "w");
	unsigned char	byte = 0;
	t_node 			*aux = root;

	compressed = calloc(SIZE_MAX, sizeof(char *));
	if (file)
	{
		while(fread(&byte, sizeof(unsigned char), 1, file))
		{
			for (int i = 7; i >= 0; i--)
			{
				aux = is_positive_bit(byte, i) ? aux->right : aux->left;
				if (aux->left == NULL && aux->right == NULL)
				{
					if (size == 0)
						break;
					fputc(aux->c, file_out);
					char c = (char)aux->c;
					strncat(compressed, &c, 1);
					size--;
					aux = root;
				}
			}
		}
		fclose(file);
		fclose(file_out);
	}
	else
		printf("\nError at open/read file.\n");
	return ((unsigned char *)compressed);
}

t_node *array_to_tree(long int *tree, int *index) {
    if (tree[*index] == -1) {
        (*index)++;
        return NULL;
    }
    t_node *root = (t_node *)malloc(sizeof(t_node));
    
	root->c = tree[(*index)++];
    root->left = array_to_tree(tree, index);
    root->right = array_to_tree(tree, index);
	root->next = array_to_tree(tree, index);
    
	return (root);
}

t_shm* create_shared_memory() 
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(t_shm), 0666 | IPC_CREAT);
    t_shm* shared_memory = (t_shm*)shmat(shmid, NULL, 0);

    return (shared_memory);
}


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	unsigned char	*decoded_data;
	long int		initial_time;
	struct stat 	sb;

	t_shm *shm = create_shared_memory();
	int i = 0;
	t_node *tree = array_to_tree(shm->tree, &i);
	initial_time = get_time();
	printf("\tDecoding... ");
	decoded_data = decompress(tree, shm->file_out, shm->text_size, (char *)shm->compress_data);
	strcpy((char *)shm->decompress_data, (char *)decoded_data);
	stat(shm->file_out, &sb);
	shm->c_bytes = sb.st_size;
	stat("decompressed", &sb);
	shm->t_bytes = sb.st_size;
	shm->time_to_decode = get_time() - initial_time;
	printf("Done!\n");
	free(decoded_data);
	shmdt(shm);
	return (0);
}
