#include "encoder.h"

void compress()
{
	printf("\n\tCompressing to shared memory:... ");
	FILE	*file_compress = fopen((char *)g_data->file_out, "wb");
	if (!file_compress)
		printf("\nError: fail to compresses file");
	unsigned char mask, byte = 0;
	int j = 7;
	int c_index = 0;
	int i;
	
	g_data->compressed_data = calloc(SIZE_MAX, sizeof(char *));
	for (i = 0; g_data->encoded[i]; i++){
		mask = 1;
		if  (g_data->encoded[i] == '1'){
			mask = mask << j;
			byte = byte | mask;
		}
		j--;
		if (j < 0) {
			g_data->compressed_data[c_index] = byte;
			c_index++;
			byte = 0;
			j = 7;
		}
	}
	for (int i = 0; i < c_index; i++)
		fwrite(&g_data->compressed_data[i], sizeof(unsigned char), 1, file_compress);
	if (j != 7){
		g_data->compressed_data[c_index] = byte;
		fwrite(&g_data->compressed_data[c_index], sizeof(unsigned char), 1, file_compress);
	}
	fclose(file_compress);
}