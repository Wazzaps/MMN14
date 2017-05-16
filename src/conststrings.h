#ifndef CONSTSTRINGS_H 
#define CONSTSTRINGS_H 

/* INFOS */
#define STR_INF_SELECTED_OUTPUT_FOLDER "Selected output folder: %s\n"
#define STR_INF_SELECTED_INPUT_FOLDER "Selected input folder: %s\n"
#define STR_INF_PROG_USAGE "\
Usage:\n\
  mycompiler file1 [file2 file3 ... fileN] [flags]\n\
Flags:\n\
  --outputfolder (-o) - If specified, files are outputted in the specified path instead of current folder\n\
  --inputfolder  (-i) - If specified, files taken from the specified path instead of current folder\n\
  --verbose      (-v) - Outputs debug information\n\
  --help         (-h) - This text\n\
"

/* ERRORS */
#define STR_ERR_MISSING_ARGUMENTS "Missing arguments.\n"
#define STR_ERR_MISSING_FLAG_ARGUMENTS "Missing arguments after flag %s.\n"
#define STR_ERR_ERROR_OPENING_FILE_FOR_WRITING "Error opening file `%s%s` for writing!\n"
#define STR_ERR_ERROR_OPENING_FILE_FOR_READING "Error opening file `%s%s` for reading!\n"
#define STR_ERR_MAX_FILES_REACHED "Maximum amount of input files (%d) reached.\n"

#endif