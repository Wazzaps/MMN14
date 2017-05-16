#ifndef FILEWRITER_H 
#define FILEWRITER_H 

#include "../src/infinitestructures.h"

#define OBJ_EXTENSION ".ob"
#define ENT_EXTENSION ".ent"
#define EXT_EXTENSION ".ext"

void write_file (char* _folder_name, char* _file_name, char* extension, infstring* contents);

#endif