#ifndef FILELOADER_H 
#define FILELOADER_H 

#include "infinitestructures.h"
#define ASM_EXTENSION ".as"

typedef struct single_file {
	char* file_name;
	infstring* contents;
} single_file;

infstring* load_file (char* _folder_name, char* file_name);

#endif