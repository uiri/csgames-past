#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <string.h>

int verify_password(char *pass);
void print_flag();

int main(int argc, char **argv) {
	char pass[30];
	int size = 0;

	puts("Show me what you got !");
	puts("Enter the password Morty : ");
	size = read(0, pass, 29);
	pass[size] = '\0';

	if (verify_password(pass) == 0) {
		puts("There you go!");
		print_flag();
	} else {
		puts("Come on Morty, try harder");
	}

	return 0;
}

// Password is did_u_really_reverse_me
int verify_password(char *pass) {
	MD5_CTX c;
	unsigned char digest[16] = {
		0x87, 0xe0, 0xbe, 0x2f, 0x4f, 0x39, 0x86, 0x29, 
		0x5d, 0x86, 0xe3, 0x27, 0xaf, 0x53, 0xee, 0xd2
	};
	unsigned char pass_digest[16];
	int i;

	MD5_Init(&c);
	MD5_Update(&c, pass, strlen(pass));
	MD5_Final(pass_digest, &c);

	for (i = 0; i < 16; i++) {
		if (digest[i] != pass_digest[i]) {
			return -1;
		}
	}

	return 0;
}

void print_flag() {
	//char *flag = "T0_Jump_0r_N0t_T0_Jump_Th4t_1s_Th3_Qu3st10n";
	char flag[44] = {0x69, 0xa4, 0x2c, 0x67, 0x38, 0x50, 0xe4, 0x2c, 0x1d, 0x3f, 0x62, 0xda, 0x43, 0x59, 0x12, 0x69, 0xa4, 0x2c, 0x67, 0x38, 0x50, 0xe4, 0x2c, 0x79, 0x25, 0x09, 0xe0, 0x2c, 0x1c, 0x3e, 0x62, 0xc0, 0x1b, 0x1e, 0x12, 0x6c, 0xe1, 0x40, 0x5e, 0x39, 0x0c, 0xa4, 0x1d, 0x00};
	unsigned char xor[5] = {0x3d, 0x94, 0x73, 0x2d, 0x4d};
	int i;
	size_t len;

	len = strlen(flag);
	printf("UQAM{");
	for (i = 0; i < len; i++) {
		putchar(xor[i % 5] ^ flag[i]);
	}
	putchar('}');
	putchar('\n');
}


