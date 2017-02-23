#include <dirent.h>

// Size of a sector
static int sector_size;

// Size of an extent (default to 8 sectors)
static int extent_size;

// Encryption method
// 0x40 for XOR
// 0x80 for ROLx
static int encryption;

// Key for XOR
static char* xor_key;

// Bytes to ROL
static int rol_len;

// File metadata
typedef struct filemeta {
	// Identifier of the file
	uint32_t file_id;
	// Parent directory id, unsigned 32 bits
	uint32_t parent_dir;
	// File name in UTF-8
	char filename[50];
	// Location of the file in extents
	uint64_t data_location;
	// File size in extents
	uint64_t ext_size;
	// File size in bytes
	uint64_t byte_size;
	// Path to source file
	char* src_path;
} filemeta;

// A File partition
typedef struct filepart {
	// Size of the volume in extents (maximum 8 bytes)
	uint64_t size_of_the_volume;
	// Size of an extent
	int ext_size;
	// Version of the volume
	char version[7];
	// Name of the volume
	char name[40];
	// Size of the file_hierarchy (in extents)
	uint64_t file_hierarchy_sz;
	// Type of encoding for the data
	char data_enc;
	// Length of the mask (if necessary)
	char masklen;
	// Mask data (length is known with masklen)
	char* mask;
} filepart;

typedef struct metalist metalist;

typedef struct metalist {
	// Magic number, 0x80 is a dirmeta, 0x40 is a filemeta
	uint8_t magic;
	// Pointer to metadata, if magic is 0x80 then cast to dirmeta, else cast to filemeta
	void* metadata;
	// Pointer to the next entity
	metalist* next;
} metalist;

// Directory metadata
typedef struct dirmeta {
	// Identifier of directory in memory
	uint32_t dir_id;
	// Parent directory's id
	uint32_t parent_dir;
	// Name of the directory, must be null-terminated
	char dir_name[50];
	// Location of the data in extents
	uint64_t data_location;
	// Children data
	metalist* children;
	// Path to source directory
	char* src_path;
} dirmeta;

typedef struct writedef {
	// Is the data a dirmeta or a filemeta ? 0x80 for dir, 0x40 for file
	uint8_t magic;
	// Metadata, can infer type with magic
	void* meta;
	// Next extent to write at, 0x00 if all was written
	int next_extent;
} writedef;

typedef struct filewrite {
	// Source of the file
	int position_in_src;
	// Remaining bytes to write
	int remaining;
	// Metadata for the file
	filemeta* metadata;
} filewrite;

typedef struct dirwrite {
	// Directory metadata
	dirmeta* dir;
	// List of children to write to disk
	metalist* children;
} dirwrite;

typedef struct writequeue writequeue;

typedef struct writequeue {
	// The definition to write
	writedef* definition;
	// The next element to write
	writequeue* next;
} writequeue;


int parse_ext(int argc, char** argv);
void parse_enc(int argc, char** argv);
void make_filesystem(char* root_path, char* out_path);
int in_byte_size(char* parent_path, char* inpath);
int in_file_byte_size(char* parent_path, char* in);
int in_dir_byte_size(char* parent_path, char* in_path);
dirmeta* build_hierarchy(char* top_path);
int add_file_to(char* path, dirmeta* d, int next);
int add_folder_to(char* path, dirmeta* d, int next);
uint32_t file_byte_to_extent_size(long byte_size);
void append_meta_to_list(metalist* lst, metalist* node);
void write_fs_to(dirmeta* d, char* out_path);
int hierarchy_size(dirmeta* d);
int data_size(dirmeta* d);
void write_fs_info(filepart* fs, FILE* out);
void write_hierarchy_to(dirmeta* d, FILE* out, char* extent);
void write_filemeta_to(filemeta* f, FILE* out, char* extent);
int count_children(dirmeta* d);
int write_dirdata_to(dirmeta* d, FILE* out, char* extent, int current_ext, int next_cont);
int write_filedata_to(filemeta* f, FILE* out, char* extent, int current_ext, int next_cont);
writequeue* build_writequeue(dirmeta* d);
void append_to_writequeue(writequeue* list, writequeue* node);
void add_dir_to_queue(dirmeta* d, writequeue* w);
writequeue* make_dirnode(dirmeta* d);
writequeue* make_filenode(filemeta* f);
void commit_data_to_disk(writequeue* wq, FILE* out, char* extent);
writequeue* write_dir_chunk(writequeue* wq, FILE* out, char* extent);
writequeue* write_file_chunk(writequeue* wq, FILE* out, char* extent);
void debug_writequeue(writequeue* w);
void rol_extent(unsigned char* extent);
void xor_extent(char* extent);
void encrypt_extent(char* extent);
