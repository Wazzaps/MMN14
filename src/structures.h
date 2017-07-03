#ifndef STRUCTURES_H 
#define STRUCTURES_H 

#define MAX_STRING_LENGTH 300

typedef char string[MAX_STRING_LENGTH+1];

typedef struct entry_list {
	string name;
	unsigned int line_num;
	struct entry_list* next;
} entry_list;

typedef struct extern_list {
	string name;
	unsigned int line_num;
	struct extern_list* next;
} extern_list;

typedef struct label_list {
	string name;
	struct label_list* next;
} label_list;

typedef struct {
	unsigned int instruction_id;
	unsigned int label_id;
    unsigned int line_num;
	/* Mode values: 0 = Constant, 1 = Label ID, 2 = Register num, 3 = Matrix access */
	/* Matrix access bits: sizeof(int) = n/8  ==>  0..(matrix label num)..n-16..(register A num)..n-8..(register B num)..n */
	unsigned int a1_mode:2;
	unsigned int a2_mode:2;
	unsigned int a3_mode:2;
	unsigned int a1_value;
	unsigned int a2_value;
	unsigned int a3_value;
    struct code_line* next;
} code_line;

#endif