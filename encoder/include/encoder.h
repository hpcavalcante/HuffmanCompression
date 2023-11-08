#ifndef ENCODER_H
# define ENCODER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 256
#define SIZE_MAX 1000000
#define WARNING "\n\033[31m\033[1mWarning!\033[0m Very large texts may exhibit unexpected behavior. Texts with more than 1M characters may not be printed in their entirety on the terminal, check out the decompressed file with the diff command.\n"

typedef struct s_node {
	int				freq;
	unsigned char 	c;

	struct s_node *left, *right, *next;

} t_node;

typedef struct s_list {
	int		size;
	t_node 	*start;
} t_list;

typedef struct s_shm {
	
	unsigned char	compress_data[SIZE_MAX];
	unsigned char	decompress_data[SIZE_MAX];
	int	time_to_decode;
	float	t_bytes;
	float	c_bytes;
	long int tree[SIZE_MAX];
	int	text_size;
	char	file_out[50];

} t_shm;

typedef struct s_data
{
	unsigned char 	*text;
	unsigned int 	*freq_tab;
	int				height;
	char			**dict;
	unsigned char	*encoded;
	char			*decod;
	unsigned char	*file_name;
	int				file_size;
	unsigned char	*file_out;
	long int		time;
	float			initial_size;
	float			final_size;
	char			*compressed_data;

} t_data;

/* Frequency Table */
void	fill_table();

/*  Ordened List */
void	create_list(t_list *list);
void	list_insert(t_list *list, t_node *node);
void	fill_list(unsigned int *tab, t_list *list);

/* Huffman Tree */
t_node *remove_from_start(t_list *list);
t_node *create_tree(t_list *list);

/* Dictionary */
int		tree_size(t_node *root);
char 	**init_dict();
void	create_dict(t_node *root, char *path);

/* Debbug */
void	print_table(unsigned int *tab);
void	print_list(t_list *list);
void	print_tree(t_node *root, int size);
void	print_dict(char **dic);

/* Encoder */
void	encoder();
int		sizeof_string(char **dic, unsigned char *text);

/* Compress */
void	compress();

/* Status */
void	print_status_encoder();
void	print_status_decoder(t_shm *shm);

/* Free */
void	free_tree(t_node *tree);
void	free_data(t_data *data);

/* Utils */
long	get_time(void);
int		file_size(char *argv);
char	*read_file(char *file_name);

extern t_data	*g_data;

#endif