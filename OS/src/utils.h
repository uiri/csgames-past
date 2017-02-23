#include <stdint.h>

void u64le_to_be(uint64_t data, unsigned char* b);
void u64le_to_me(uint64_t data, unsigned char* b);
void u32le_to_be(uint32_t data, unsigned char* b);
void u32le_to_me(uint32_t data, unsigned char* b);
void u16le_to_be(uint16_t data, unsigned char* b);
char* join(char** strings, int len, char* sep);
uint64_t u64be_to_le(unsigned char* b);
uint64_t u64me_to_le(unsigned char* b);
uint32_t u32be_to_le(unsigned char* b);
uint32_t u32me_to_le(unsigned char* b);
uint16_t u16be_to_le(unsigned char* b);
char* parse_out(int argc, char** argv);
int parse_sec(int argc, char** argv);
