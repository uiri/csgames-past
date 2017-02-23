#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <time.h>

#define PASS_LEN 50
#define MAX_TIME_DELTA 1

time_t base_time;
int validate_password(char *password);

void __attribute__ ((constructor)) __init() {
	pid_t pid;

	if (ptrace(PTRACE_TRACEME, pid, NULL, NULL) != 0) {
		exit(0);
	}
}

void __attribute__ ((constructor)) __check() {
    base_time = time(NULL);
}

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("Usage : %s password\n", argv[0]);
		exit(0);
	}

	if (validate_password(argv[1]) == 0) {
		printf("UQAM{%s}\n", argv[1]);
	} else {
		puts("You're not allowed in here !");
	}

	return 0;
}

// UQAM{I_W1sh_I_H4d_IDA_inst4lled_But_Wh0_C4n_4ff0rd_Th4t}
int validate_password(char *password) {
    time_t now;
    char pass = '\xd1';
    char xor_bytes[50] = {
        0x98, 0x16, 0x08, 0x66, 0x42, 0x1b, 0x37, 0x16, 0x16, 0x17, 0x7c, 0x50, 0x3b, 0x16, 0x0d, 0x05,
        0x1e, 0x36, 0x07, 0x1d, 0x07, 0x40, 0x58, 0x00, 0x09, 0x01, 0x3b, 0x1d, 0x37, 0x01, 0x2b, 0x08,
        0x3f, 0x58, 0x6f, 0x1c, 0x77, 0x5a, 0x31, 0x6b, 0x52, 0x00, 0x56, 0x42, 0x16, 0x3b, 0x0b, 0x3c,
        0x5c, 0x40,
    };

	if (PASS_LEN != strlen(password)) {
		return -1;
	}

	for (int i = 0; i < PASS_LEN; i++) {
		pass ^= xor_bytes[i];

		if ((time(NULL) -  base_time) > MAX_TIME_DELTA
                || pass != password[i]) {
			return -1;
		}
	}

	return 0;
}
