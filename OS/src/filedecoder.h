static int sector_size = 512;

typedef struct partition {
	uint64_t size;
	unsigned char ext_size;
	unsigned char volume_name[40];
	uint64_t hierarchy_size;
	unsigned char encryption_type;
	unsigned char mask_sz;
	unsigned char* mask_data;
} partition;

typedef struct dir_meta {
	uint32_t id;
	uint32_t parent_id;
	unsigned char* name;
	uint64_t ext_location;
} dir_meta;

typedef struct file_meta {
	uint32_t id;
	uint32_t parent_id;
	unsigned char* name;
	uint64_t ext_location;
	uint64_t ext_size;
	uint64_t byte_size;
} file_meta;

typedef struct directory directory;
typedef struct directory {
	dir_meta* meta;
	int children_dirs_nb;
	directory** children_dirs;
	int children_files_nb;
	file_meta** children_files;
} directory;

void parse_filesystem(char *inpath, char* outpath);
partition* parse_part_info(FILE *in);
void add_child_dir_to_dir(dir_meta*, directory*);
void add_child_file_to_dir(file_meta*, directory*);
directory* parse_file_hierarchy(FILE* in, partition* fsmeta);
void move_to_extent(FILE* in, uint64_t extent_id, partition* meta);
directory* find_dir_id(uint32_t id, directory* dir);
dir_meta* read_folder_info(unsigned char* ext);
file_meta* read_file_info(unsigned char* ext);
void print_hierarchy(directory* dir);
void write_directory(FILE* in, directory* dir, partition* part, char* outpath);
void write_file(FILE* in, file_meta* fm, partition* part, char* outpath);
void ror_extent(unsigned char* extent, partition* part);
void xor_extent(char* extent, partition* part);

// Debug functions
// Prints the contents of `part`
void dump_partition(partition *part);
// Prints the contents of `part`
void dump_dirmeta(dir_meta *part);
// Prints the contents of `part`
void dump_filemeta(file_meta *part);
