#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

int encode_file(FILE *fin, FILE *fout);
int decode_file(FILE *fin, FILE *fout);

int main(int argc, char **argv) {
	FILE *fin, *fout;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s file_in file_out\n", argv[0]);
		exit(1);
	}

	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Unable to open %s\n", argv[1]);
		exit(1);
	}

	if ((fout = fopen(argv[2], "w+")) == NULL) {
		fprintf(stderr, "Unable to open %s\n", argv[2]);
		exit(1);
	}

	encode_file(fin, fout);

	fclose(fin);
	fclose(fout);

	return 0;
}

int encode_file(FILE *fin, FILE *fout) {
	char current_char;
	char last_char;
	uint8_t counter = 1;
	int nb_read;
	
	if (fread(&current_char, sizeof(char), 1, fin) == 0) {
		return 0;
	}

	last_char = current_char;

	while (1) {
		nb_read = fread(&current_char, sizeof(char), 1, fin);

		if (current_char != last_char || nb_read == 0) {
			fwrite(&counter, sizeof(uint8_t), 1, fout);
			fwrite(&last_char, sizeof(char), 1, fout);
			if (nb_read == 0) break;
			last_char = current_char;
			counter = 1;
		} else {
			if (++counter == 0xff) {
				fwrite(&counter, sizeof(uint8_t), 1, fout);
				fwrite(&last_char, sizeof(char), 1, fout);
				counter = 1;
			}
		}
	}

	return 0;
}
