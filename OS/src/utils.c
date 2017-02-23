#include "utils.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Checks if option '-o' is used, defaults to "out"
char* parse_out(int argc, char** argv)
{
	int i;
	for(i = 1; i < (argc - 1); i++) {
		if(!strcmp(argv[i], "-o")){
			return argv[i + 1];
		}
	}
	return "out.coal";
}

// Write the 16 bits of `data` to `buffer` in big-endian form
void u16le_to_be(uint16_t data, unsigned char* buffer) {
	int i = 0;
	uint8_t d;
	for(i = 0; i < 2; i++) {
		d = (data & (0xFFl << (8 * i))) >> (8 * i);
		buffer[1 - i] = d;
	}
}

// Write the 32 bits of `data` to `buffer` in big-endian form
void u32le_to_be(uint32_t data, unsigned char* buffer) {
	int i = 0;
	uint8_t d;
	for(i = 0; i < 4; i++) {
		d = (data & (0xFFl << (8 * i))) >> (8 * i);
		buffer[3 - i] = d;
	}
	//printf("Written hex for %d in BE form is ", data);
	//for(i = 0; i < 4; i ++) {
	//	printf("0x%02x ", buffer[i]);
	//}
	//printf("\n");
}

// Write the 32 bits of `data` to `buffer` in middle-endian form
void u32le_to_me(uint32_t data, unsigned char* buffer)
{
	uint16_t p1 = (data & 0xFFFF0000) >> 16;
	memcpy(buffer, &p1, 2);
	p1 = data & 0xFFFF;
	memcpy(buffer + 2, &p1, 2);
}

// Write the 64 bits of `data` to `buffer` in middle-endian form
void u64le_to_me(uint64_t data, unsigned char* buffer)
{
	uint32_t p1 = (data & 0xFFFFFFFF00000000) >> 32;
	memcpy(buffer, &p1, 4);
	p1 = data & 0xFFFFFFFF;
	memcpy(buffer + 4, &p1, 4);
}

// Write the 64 bits of `data` to `buf` in big-endian form
void u64le_to_be(uint64_t data, unsigned char* buf)
{
	int i = 0;
	uint8_t d;
	for(i = 0; i < 8; i++) {
		d = (data & (0xFFl << (8 * i))) >> (8 * i);
		buf[7 - i] = d;
	}
}

// Joins an array of strings using `sep`
char* join(char** strings, int len, char* sep)
{
	int i;
	if(len == 0) return "";
	int endlen = 0;
	for(i = 0; i < len; i++) {
		endlen += strlen(strings[i]);
	}
	endlen += strlen(sep) * (len - 1);
	char* endstr = calloc(endlen + 1, 1);
	strcat(endstr, strings[0]);
	for(i = 1; i < len; i++) {
		strcat(endstr, sep);
		strcat(endstr, strings[i]);
	}
	//printf("Allocating path at address %p\n", endstr);
	return endstr;
}

uint64_t u64be_to_le(unsigned char* b)
{
	uint64_t ret = 0x00;
	int i;
	for(i = 0; i < 8; i ++) {
		ret |= ((uint64_t)b[i]) << ((7 - i) * 8);
	}
	return ret;
}

uint64_t u64me_to_le(unsigned char* b)
{
	uint64_t ret = 0x00;
	int i;
	uint64_t hi32 = (uint64_t)(*((uint32_t*)b));
	uint64_t low32 = (uint64_t)(*((uint32_t*)(b + 4)));
	ret |= low32;
	ret |= (hi32 << 32);
	return ret;
}

uint32_t u32be_to_le(unsigned char* b)
{
	uint32_t ret = 0;
	int i;
	for(i = 0; i < 4; i++) {
		ret |= ((uint32_t)b[i]) << ((3 - i) * 8);
	}
	return ret;
}

uint32_t u32me_to_le(unsigned char* b)
{
	uint32_t ret = 0;
	uint32_t hi16 = (uint32_t)(*((uint16_t*)b));
	uint32_t low16 = (uint32_t)(*((uint16_t*)(b + 2)));
	ret |= low16;
	ret |= (hi16 << 16);
	return ret;
}

uint16_t u16be_to_le(unsigned char* b)
{
	uint16_t ret;
	int i;
	for(i = 0; i < 2; i++) {
		ret |= ((uint16_t)b[i]) << ((1 - i) * 8);
	}
	return ret;
}

// Checks if option '-s' is used, defaults to 512
int parse_sec(int argc, char** argv)
{
	int i = 0;
	for(i = 1; i < (argc - 1); i++) {
		if(!strcmp(argv[i], "-s")) {
			return atoi(argv[i + 1]);
		}
	}
	return 512;
}
