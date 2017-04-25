#ifndef FILELOADER_H 
#define FILELOADER_H 

#define ASM_EXTENSION ".as"

typedef struct single_file_struct {
	char* file_name;
	char* contents;
} single_file;

single_file load_file (char* _folder_name, char* file_name);

#endif