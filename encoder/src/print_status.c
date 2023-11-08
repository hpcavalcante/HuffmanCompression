#include "encoder.h"

void	print_status_decoder(t_shm *shm)
{
	printf ("\n\tWaiting for decoder...\n");
	while (shm->time_to_decode == -1)
		;
	printf("\n\tDecompressed data: %s\n", shm->decompress_data);
	printf("\n\tFile original size: %2.f bytes\n", g_data->initial_size);
	printf("\tFile size compressed: %2.f bytes\n", shm->c_bytes);
	printf("\tFile size decompressed: %2.f bytes\n", shm->t_bytes);
	printf("\tCompression rate: %.2f%%\n", (g_data->initial_size - shm->c_bytes) / g_data->initial_size * 100);
	printf("\tTime to decode: %d ms\n", shm->time_to_decode);
}

void	print_status_encoder()
{
	long int	passed_time;

	printf("Done!\n");
	passed_time = get_time() - g_data->time;
	printf ("\tCompression time: %ld ms\n", passed_time);
}