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

#define SIZE_MAX 1000000

typedef struct s_node {
	int				freq;
	unsigned char 	c;

	struct s_node *left, *right, *next;

} t_node;

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