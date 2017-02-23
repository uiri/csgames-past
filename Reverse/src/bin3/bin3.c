#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>

#define PASS_LEN 44

int validate_password(char *password);

void __attribute__ ((constructor)) __init() {
	pid_t pid;

	if (ptrace(PTRACE_TRACEME, pid, NULL, NULL) != 0) {
		exit(0);
	}
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

// UQAM{4nt1_D3bugg3rs_4r3nt_So_B4d_Aft3r_All_R1ght?}
int validate_password(char *password) {
	char c[2] = "\x00\x00";
	char pass[2] = "\x00\x00";
	char xor_bytes[3] = {0xd1, 0xee, 0xd9};
	int cipher[44] = {
		0xe5, 0x80, 0xad, 0xe0, 0xb1, 0x9d, 0xe2, 0x8c, 0xac, 0xb6, 0x89, 0xea, 0xa3, 0x9d, 0x86, 0xe5,
		0x9c, 0xea, 0xbf, 0x9a, 0x86, 0x82, 0x81, 0x86, 0x93, 0xda, 0xbd, 0x8e, 0xaf, 0xbf, 0xa5, 0xdd,
		0xab, 0x8e, 0xaf, 0xb5, 0xbd, 0xb1, 0x8b, 0xe0, 0x89, 0xb1, 0xa5, 0xd1,
	};

	if (PASS_LEN != strlen(password)) {
		return -1;
	}

	for (int i = 0; i < PASS_LEN; i++) {
		c[0] = password[i];
		pass[0] = cipher[i] ^ xor_bytes[i % 3];

		if (strcmp(c, pass) != 0) {
			return -1;
		}
	}

	return 0;
}
