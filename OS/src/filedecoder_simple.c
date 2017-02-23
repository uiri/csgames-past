#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"
#include "filedecoder.h"
#include <dirent.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc < 2){
		printf("Usage: ./filedecoder file [-o outputfolder]\n");
		exit(1);
	}
	char* out = parse_out(argc, argv);
	if(strcmp(out, "out.coal") == 0) {
		out = "newdump";
	}
	sector_size = parse_sec(argc, argv);
	struct stat s;
	int ln = strlen(argv[1]);
	char* path = calloc(1, ln + 1);
	memcpy(path, argv[1], ln);
	if(!stat(argv[1], &s)) {
		if(S_ISDIR(s.st_mode) || S_ISREG(s.st_mode)) {
			parse_filesystem(path, out);
			printf("Successfully extracted data from %s\n", path);
		} else {
			printf("Bad argument %s, expected path to a file or a directory\n", path);
			free(path);
		}
	} else {
		printf("Error: syscall to stat failed, are you sure %s exists ?\n", path);
		free(path);
	}
}

void parse_filesystem(char *inpath, char* outpath)
{
	FILE* in = fopen(inpath, "r");
	partition* part = parse_part_info(in);
	dump_partition(part);
	// Forward to file hierarchy
	move_to_extent(in, 1, part);
	directory* dirs = parse_file_hierarchy(in, part);
	write_directory(in, dirs, part, outpath);
	fclose(in);
}

void decrypt_extent(char* ext, partition* part) {
	uint32_t enc_type = part->encryption_type;
	if(enc_type == 0x80) {
		ror_extent(ext, part);
	} else if(enc_type == 0x40) {
		xor_extent(ext, part);	
	}
}

// Does a ROR on every byte of the extent
void ror_extent(unsigned char* extent, partition* part)
{
	int i;
	int ext_sz = part->ext_size * sector_size;
	int ror_len = part->mask_data[0];
	for(i = 0; i < ext_sz; i++) {
		extent[i] = (extent[i] >> ror_len) | (extent[i] << (8 - ror_len));
	}
}

// XOR each byte of an extent with a char of the key
void xor_extent(char* extent, partition* part)
{
	int keylen = strlen(part->mask_data);
	int i;
	int ext_sz = part->ext_size * sector_size;
	for(i = 0; i < ext_sz; i++) {
		extent[i] = extent[i] ^ part->mask_data[i % keylen];
	}
}

partition* parse_part_info(FILE *in)
{
	partition* ret = malloc(sizeof(partition));
	char *buffer = calloc(sector_size, 1);
	fread(buffer, sector_size, 1, in);
	//ret->size = u64me_to_le(buffer);
	memcpy(&ret->size, buffer, 8);
	ret->ext_size = buffer[8];
	memcpy(&ret->volume_name, (buffer + 9), 40);
	//ret->hierarchy_size = u64be_to_le(buffer + 49);
	memcpy(&ret->hierarchy_size, buffer + 49, 8);
	ret->encryption_type = (*(buffer + 57)) & 0xF0;
	if(ret->encryption_type == 0x40) {
		int mask_sz = *(buffer + 58);
		char* mask_data = malloc(mask_sz);
		memcpy(mask_data, buffer + 59, mask_sz);
		ret->mask_sz = mask_sz;
		ret->mask_data = mask_data;
	} else if (ret->encryption_type == 0x80) {
		char* mask = malloc(1);
		mask[0] = (*(buffer + 57)) & 0x0F;
		ret->mask_data = mask;
	} else {
		ret->mask_sz = 0;
	}
	return ret;
}

directory* parse_file_hierarchy(FILE* in, partition* fsmeta)
{
	unsigned char* ext = malloc(fsmeta->ext_size * sector_size);
	fread(ext, fsmeta->ext_size, sector_size, in);
	decrypt_extent(ext, fsmeta);
	printf("First byte is %02x\n", ext[0]);
	if(ext[0] != 0x80) {
		printf("Error: Top entity is not a directory !\n");
		exit(-1);
	}
	if(ext[1] != 0x00) {
		printf("Error: First entity in file hierarchy must be a root directory with 0 as ID.\n");
		exit(-2);
	}
	dir_meta *root = malloc(sizeof(dir_meta));
	root->name = "root";
	root->id = 0;
	root->parent_id = 0;
	root->ext_location = 1;
	directory* rootdir = calloc(sizeof(directory), 1);
	rootdir->meta = root;
	int i;
	for(i = 0; i < (fsmeta->hierarchy_size - 1); i++) {
		move_to_extent(in, i + 2, fsmeta);
		fread(ext, fsmeta->ext_size, sector_size, in);
		decrypt_extent(ext, fsmeta);
		if(ext[0] == 0x40) {
			file_meta* fm = read_file_info(ext);
			directory* dir = find_dir_id(fm->parent_id, rootdir);
			if(dir == NULL) {
				printf("Error: Cannot find directory id %d in hierarchy", fm->parent_id);
				exit(-4);
			}
			add_child_file_to_dir(fm, dir);
			dump_filemeta(fm);
		} else if(ext[0] == 0x80) {
			dir_meta* dm = read_folder_info(ext);
			directory* dir = find_dir_id(dm->parent_id, rootdir);
			if(dir == NULL) {
				printf("Error: Cannot find directory id %d in hierarchy", dm->parent_id);
				exit(-4);
			}
			add_child_dir_to_dir(dm, dir);
			dump_dirmeta(dm);
		} else {
			printf("Bad data chunk.\n");
			exit(-3);
		}
	}
	print_hierarchy(rootdir);
	return rootdir;
}

dir_meta* read_folder_info(unsigned char* ext)
{
	dir_meta* ret = malloc(sizeof(dir_meta));
	//ret->id = u32be_to_le(ext + 1);
	memcpy(&ret->id, ext + 1, 4);
	//ret->parent_id = u32be_to_le(ext + 5);
	memcpy(&ret->parent_id, ext + 5, 4);
	ret->name = calloc(50, 1);
	memcpy(ret->name, ext + 9, 50);
	//ret->ext_location = u64me_to_le(ext + 59);
	memcpy(&ret->ext_location, ext + 59, 8);
	return ret;
}

file_meta* read_file_info(unsigned char* ext)
{
	file_meta* ret = malloc(sizeof(file_meta));
	ret->id = u32be_to_le(ext + 1);
	//ret->parent_id = u32be_to_le(ext + 5);
	memcpy(&ret->parent_id, ext + 5, 4);
	ret->name = calloc(50, 1);
	memcpy(ret->name, ext + 9, 50);
	//ret->ext_location = u64me_to_le(ext + 59);
	memcpy(&ret->ext_location, ext + 59, 8);
	//ret->ext_size = u64me_to_le(ext + 67);
	memcpy(&ret->ext_size, ext + 67, 8);
	//ret->byte_size = u64me_to_le(ext + 75);
	memcpy(&ret->byte_size, ext + 75, 8);
	return ret;
}

void write_directory(FILE* in, directory* dir, partition* part, char* outpath) {
	mkdir(outpath, S_IRWXU);
	int i;
	for(i = 0; i < dir->children_dirs_nb; i++) {
		char* dir_join[] = { outpath, dir->children_dirs[i]->meta->name };
		char* dirpath = join(dir_join, 2, "/");
		write_directory(in, dir->children_dirs[i], part, dirpath);
		free(dirpath);
	}
	for(i = 0; i < dir->children_files_nb; i++) {
		char* file_join[] = { outpath, dir->children_files[i]->name };
		char* filepath = join(file_join, 2, "/");
		write_file(in, dir->children_files[i], part, filepath);
		free(filepath);
	}
}

void write_file(FILE* in, file_meta* fm, partition* part, char* outpath) {
	FILE* out = fopen(outpath, "w");
	printf("Reading extent %ld for file %s\n", fm->ext_location, fm->name);
	int ext_id = fm->ext_location;
	move_to_extent(in, fm->ext_location, part);
	int ext_byte_size = part->ext_size * sector_size;
	char* ext = malloc(ext_byte_size);
	while(1) {
		fread(ext, ext_byte_size, 1, in);
		decrypt_extent(ext, part);
		uint32_t local_size = u32me_to_le(ext + 1);
		memcpy(&local_size, ext + 1, 4);
		printf("Reading chunk of %d bytes for file %s fm->name at offset %d\n", local_size, fm->name, ext_id);
		fwrite(ext + 5, local_size, 1, out);
		uint32_t nxt_id = u32be_to_le(ext + ext_byte_size - 4);
		memcpy(&nxt_id, ext + ext_byte_size - 4, 4);
		printf("Next extent id = %d\n", nxt_id);
		if(nxt_id == 0)
			break;
		move_to_extent(in, nxt_id, part);
		ext_id = nxt_id;
	}
	fclose(out);
}

void move_to_extent(FILE* in, uint64_t extent_id, partition* meta)
{
	fseek(in, meta->ext_size * sector_size * extent_id, SEEK_SET);
}

directory* find_dir_id(uint32_t id, directory* dir)
{
	int i = 0;
	if(dir->meta->id == id)
		return dir;
	for(i = 0; i < dir->children_dirs_nb; i++){
		directory* dirdir = dir->children_dirs[i];
		dir_meta* dirmet = dirdir->meta;
		if(dirmet->id == id)
			return dirdir;
		directory* retdir = find_dir_id(id, dirdir);
		if(retdir != NULL)
			return retdir;
	}
	return NULL;
}

void add_child_dir_to_dir(dir_meta* meta, directory* dir)
{
	int sz = ++dir->children_dirs_nb;
	directory* ndir = calloc(sizeof(directory), 1);
	ndir->meta = meta;
	directory** ndirs = calloc(sz, sizeof(void*));
	if(sz > 1) {
		memcpy(ndirs, dir->children_dirs, (sz - 1) * sizeof(void*));
		free(dir->children_dirs);
	}
	ndirs[sz - 1] = ndir;
	dir->children_dirs = ndirs;
}

void add_child_file_to_dir(file_meta* meta, directory* dir)
{
	int sz = ++dir->children_files_nb;
	file_meta** ndirs = calloc(sz, sizeof(void*));
	if(sz > 1) {
		memcpy(ndirs, dir->children_files, (sz - 1) * sizeof(void*));
		free(dir->children_files);
	}
	ndirs[sz - 1] = meta;
	dir->children_files = ndirs;
}

void dump_partition(partition* part) {
	printf("Partition %s:\n", part->volume_name);
	printf("- size: %lu\n", part->size);
	printf("- extent size: %hhu\n", part->ext_size);
	printf("- hierarchy size: %lu\n", part->hierarchy_size);
	unsigned char encryption = part->encryption_type & 0xF0;
	char* encryption_name;
	if(encryption == 0x40) {
		encryption_name = "XOR";
	} else if (encryption == 0x80) {
		encryption_name = "ROL";
	} else {
		encryption_name = "None";
	}
	printf("- encryption_type: %s\n", encryption_name);
	if(encryption == 0x40) {
		int mask_len = part->mask_sz;
		int i;
		printf("- encryption_mask: ");
		for(i = 0; i < mask_len; i ++) {
			printf("%2x", (unsigned char)(part->mask_data[i]));
		}
		printf("\n");
	} else if (encryption == 0x80) {
		printf("- encryption mask: %d\n", part->mask_data[0]);
	}
}

void dump_dirmeta(dir_meta *dir)
{
	printf("Dir meta dump:\n");
	printf("- ID: %d\n", dir->id);
	printf("- Parent ID: %d\n", dir->parent_id);
	printf("- Name: %s\n", dir->name);
	printf("- Extent: %ld\n", dir->ext_location);
}

void dump_filemeta(file_meta *file)
{
	printf("File meta dump:\n");
	printf("- ID: %d\n", file->id);
	printf("- Parent ID: %d\n", file->parent_id);
	printf("- Name: %s\n", file->name);
	printf("- Extent: %ld\n", file->ext_location);
	printf("- Extent Size: %ld\n", file->ext_size);
	printf("- Byte Size: %ld\n", file->byte_size);
}

void print_hierarchy(directory* dir) {
	int i;
	printf("Directory %d children files: \n", dir->meta->id);
	for(i = 0; i < dir->children_files_nb; i++) {
		printf("- File id %d\n", dir->children_files[i]->id);
	}
	printf("\n");
	printf("Directory %d children directories: \n", dir->meta->id);
	for(i = 0; i < dir->children_dirs_nb; i++) {
		printf("- Directory id %d\n", dir->children_dirs[i]->meta->id);
	}
	printf("\n");
	for(i = 0; i < dir->children_dirs_nb; i++) {
		directory* subdir = dir->children_dirs[i];
		print_hierarchy(subdir);
	}
}
