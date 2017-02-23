#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

typedef struct coords {
	int x_from;
	int x_to;
} coords;

typedef struct play_gol_structs {
	char*** matrices;
	int matln;
	int iters;
	coords* chunk;
	pthread_barrier_t* barr;
} play_gol_structs;

int neighbours(char** matrix, int x, int y, int matsz)
{
	int yup = y - 1;
	if(yup < 0) yup = matsz - 1;
	int ydown = y + 1;
	if(ydown == matsz) ydown = 0;
	int xlft = x - 1;
	if(xlft < 0) xlft = matsz - 1;
	int xrgt = x + 1;
	if(xrgt == matsz) xrgt = 0;
	int nei = 0;
	nei += matrix[x][yup];
	nei += matrix[xlft][yup];
	nei += matrix[xrgt][yup];
	nei += matrix[x][ydown];
	nei += matrix[xlft][ydown];
	nei += matrix[xrgt][ydown];
	nei += matrix[xlft][y];
	nei += matrix[xrgt][y];
	return nei;
}

void make_iter(char** src_matrix, char** dst_matrix, int matln, coords* chunk)
{
	int i, j;
	for(i = chunk->x_from; i <= chunk->x_to; i++) {
		for(j = 0; j < matln; j++) {
			int n = neighbours(src_matrix, i, j, matln);
			if(n < 2) dst_matrix[i][j] = 0;
			else if(n == 2) dst_matrix[i][j] = src_matrix[i][j];
			else if(n == 3) dst_matrix[i][j] = 1;
			else dst_matrix[i][j] = 0;
		}
	}
}

// (char ***matrices, int matln, int iters, coords* chunk, pthread_barrier_t** barrs)
void* play_gol_on(void* nargs)
{
	play_gol_structs* args = (play_gol_structs*) nargs;
	char ***matrices = args->matrices;
	int matln = args->matln;
	int iters = args->iters;
	coords* chunk = args->chunk;
	pthread_barrier_t* barr = args->barr;
	int i;
	char** matrix[2] = {matrices[0], matrices[1]};
	int matid[2] = {0, 1};
	for(i = 0; i < iters; i++) {
		//printf("Starting iteration %d\n", i);
		make_iter(matrix[matid[0]], matrix[matid[1]], matln, chunk);
		matid[0] ^= 1;
		matid[1] ^= 1;
		//printf("Finished iteration %i, waiting at barrier\n", i);
		pthread_barrier_wait(barr);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc < 3) {
		printf("Usage: ./gol file.in iters [--check]\n");
		exit(1);
	}
	int iters = atoi(argv[2]);
	FILE* fin = fopen(argv[1], "r");
	if(fin == NULL) {
		printf("Cannot open file %s, are you sure it exists ?\n", argv[1]);
		exit(2);
	}
	int matsz;
	int rd = fscanf(fin, "%d\n", &matsz);
	//printf("Matrix size = %d\n", matsz);
	int i, j;
	char** matrix = calloc(matsz, sizeof(char*));
	char* lndata = calloc(matsz + 1, 1);
	for(i = 0; i < matsz; i++) {
		char* ln = calloc(matsz, 1);
		int ret = fread(lndata, matsz + 1, 1, fin);
		for(j = 0; j < matsz; j++) {
			ln[j] = lndata[j] - '0';
		}
		matrix[i] = ln;
	}
	free(lndata);
	char** nmat = calloc(matsz, sizeof(char*));
	for(i = 0; i < matsz; i++) {
		char* ln = calloc(matsz, 1);
		memcpy(ln, matrix[i], matsz);
		nmat[i] = ln;
	}
	fclose(fin);
	char** mats[2] = {matrix, nmat};
	//int idx[2] = {0, 1};
	int nb_threads = sysconf( _SC_NPROCESSORS_ONLN );
	if(nb_threads & 1 == 1) {
		printf("Unsupported configuration, nb_threads is not even\n");
		exit(3);
	}
	// Prepare threads
	pthread_t *threads = calloc(nb_threads, sizeof(pthread_t));
	play_gol_structs *th_args = calloc(nb_threads, sizeof(play_gol_structs));
	pthread_barrier_t *barr = calloc(1, sizeof(pthread_barrier_t));
	pthread_barrier_init(barr, NULL, 4);
	int chunksz = matsz / 4;
	for(i = 0; i < nb_threads; i++) {
		coords* th_coords = calloc(1, sizeof(th_coords));
		th_coords->x_from = i * chunksz;
		th_coords->x_to = (i + 1) * chunksz - 1;
		play_gol_structs* arg = &th_args[i];
		arg->matrices = mats;
		arg->matln = matsz;
		arg->iters = iters;
		arg->chunk = th_coords;
		arg->barr = barr;
		//printf("Thread %d works on chunk from x = %d to x = %d\n", i, th_coords->x_from, th_coords->x_to);
	}
	for(i = 0; i < nb_threads; i++) {
		int ret = pthread_create(&threads[i], NULL, play_gol_on, &th_args[i]);
		if(ret != 0) {
			printf("Error creating pthread: \"%s\"\n", strerror(errno));
			exit(4);
		}
	}
	for(i = 0; i < nb_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	if(argc == 4) {
		char** finmat = mats[iters % 2];
		for(i = 0; i < matsz; i++) {
			for(j = 0; j < matsz; j++) {
				printf("%d", finmat[i][j]);
			}
			printf("\n");
		}
	}
	free(barr);
	for(i = 0; i < nb_threads; i++) {
		free(th_args[i].chunk);
	}
	free(th_args);
	free(threads);
	for(i = 0; i < matsz; i++) {
		free(matrix[i]);
		free(nmat[i]);
	}
	free(matrix);
	free(nmat);
}
