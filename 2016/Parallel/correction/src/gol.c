#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void make_iter(char** src_matrix, char** dst_matrix, int matln)
{
	int i, j;
	for(i = 0; i < matln; i++) {
		for(j = 0; j < matln; j++) {
			int n = neighbours(src_matrix, i, j, matln);
			if(n < 2) dst_matrix[i][j] = 0;
			else if(n == 2) dst_matrix[i][j] = src_matrix[i][j];
			else if(n == 3) dst_matrix[i][j] = 1;
			else dst_matrix[i][j] = 0;
		}
	}
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
	char** matrs[2] = {matrix, nmat};
	int idx[2] = {0, 1};
	for(i = 0; i < iters; i++) {
		make_iter(matrs[idx[0]], matrs[idx[1]], matsz);
		idx[0] ^= 1;
		idx[1] ^= 1;
	}
	if(argc == 4) {
		char** finmat = matrs[iters % 2];
		for(i = 0; i < matsz; i++) {
			for(j = 0; j < matsz; j++) {
				printf("%d", finmat[i][j]);
			}
			printf("\n");
		}
	}
	for(i = 0; i < matsz; i++) {
		free(matrix[i]);
		free(nmat[i]);
	}
	free(matrix);
	free(nmat);
}
