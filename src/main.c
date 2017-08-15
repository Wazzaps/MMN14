
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "util_funcs.h"
#include "parse_directives.h"
#include "parse_ops.h"
#include "errors.h"
#include "base4.h"
#include "constant_data.h"

#define DEBUG_MODE 1

int main (int argc, char* argv[]) {
	int iterator;
	int all_success = 1;

	/* Check that file arguments are valid */
	if (argc == 1) {
		fprintf(stderr, ERROR_NO_INPUT_FILES);
		return 1;
	}

	/* Open files */
	for (iterator = 1; iterator < argc; iterator++) {
		state_t state;
		char* file_name = file_add_extension(argv[iterator], ASM_EXT);
		int i;
		list* ptr;

		/* Create relevant tables - Setup state table */
		state.data_table = malloc(sizeof(cpu_word));
		state.data_counter = 0;
		state.code_table = malloc(sizeof(cpu_word));
		state.code_counter = 0;
		state.extern_table = NULL;
		state.entry_table = NULL;
		state.code_labels_table = NULL;
		state.data_labels_table = NULL;
		state.extern_refs_table = NULL;
		state.code_label_refs_table = NULL;

		state.current_file_name = argv[iterator];
		state.current_line_num = 0;
		state.failed = 0;

		/* Make sure the file exists */
		FILE* fp = fopen(file_name, "r");
		if (fp) {
			printf("Processing file: %s\n", file_name);
			state.current_file_ptr = fp;
		} else {
			fprintf(stderr, ERROR_CANNOT_READ, argv[iterator]);
			all_success = 0;
			continue;
		}

		/* Parse */
		parse_directives_and_labels(&state);
		parse_ops(&state);

		/* Close file */
		fclose(fp);

		// Add code size to all addresses in code which refers to data (ie. labels, matrices)
		for (i = 0; i < state.code_counter; i++) {
			if ((state.code_table[i] & 3) == RELOCATABLE) {
				state.code_table[i] += (state.code_counter + MEM_STARTS_AT) << 2;
			}
		}

		// Find and fill in all code label references in code
		ptr = state.code_label_refs_table;
		while (ptr) {
			ref_in_code* ref = ptr->data;
			state.code_table[ref->code_address] = find_code_label(&state, ref->name)->address << 2 | RELOCATABLE;
			ptr = ptr->next;
		}

		// Add data size to all labels
		list* curr_label = state.data_labels_table;
		while (curr_label != NULL) {
			((data_label*) (curr_label->data))->address += state.code_counter;
			curr_label = curr_label->next;
		}

		state.code_table = realloc(state.code_table, (state.code_counter + state.data_counter) * sizeof(cpu_word));
		if (state.code_table == NULL) {
			fprintf(stderr, ERROR_OUT_OF_MEMORY);
			exit(1);
		}
		memcpy(state.code_table + state.code_counter, state.data_table, state.data_counter * sizeof(cpu_word));

		// Go over all entry table to make sure all labels exist
		{
			list* entry_table_ptr = state.entry_table;
			while (entry_table_ptr) {
				data_label* my_data_label = find_data_label(&state, ((entry_with_line_num*) entry_table_ptr->data)->name);
				code_label* my_code_label = find_code_label(&state, ((entry_with_line_num*) entry_table_ptr->data)->name);
				if (!my_data_label && !my_code_label) {
					fprintf(stderr, ERROR_LABEL_DOESNT_EXIST, ((entry_with_line_num*) entry_table_ptr->data)->name, ((entry_with_line_num*) entry_table_ptr->data)->line_num, argv[iterator]);
					state.failed = 1;
					entry_table_ptr = entry_table_ptr->next;
					continue;
				}
				entry_table_ptr = entry_table_ptr->next;
			}
		}

		/* Write data to file */
		if (!state.failed) {
			char* output_ob_file_name = file_add_extension(argv[iterator], OBJ_EXT);
			FILE* output_ob_file = fopen(output_ob_file_name, "w");

			// Check that the file was opened
			if (!output_ob_file) {
				fprintf(stderr, ERROR_CANNOT_WRITE, output_ob_file_name);
				all_success = 0;
				continue;
			}



			// Write the file, with a 100 offset in address
			// TODO: Make more readable
			cpu_word* curr_word = state.code_table;
			for (i = 0; i < (state.code_counter + state.data_counter); i++) {
				char* base4_address = tobase4((i+MEM_STARTS_AT) & 1023, 4);
				char* base4_data = tobase4(curr_word[i] & 1023, 5);
				fprintf(output_ob_file, "%s\t%s\n", base4_address, base4_data);
				fprintf(stdout, "%d\t%s\t%s\n", i, base4_address, base4_data);
				free(base4_address);
				free(base4_data);
			}

			fclose(output_ob_file);
			free(output_ob_file_name);

			if (state.entry_table != NULL) {
				char* output_ent_file_name = file_add_extension(argv[iterator], ENT_EXT);
				FILE* output_ent_file = fopen(output_ent_file_name, "w");
				list* entry_table_ptr = state.entry_table;

				// Check that the file was opened
				if (!output_ent_file) {
					fprintf(stderr, ERROR_CANNOT_WRITE, output_ent_file_name);
					all_success = 0;
					continue;
				}

				// Go over all entry table to populate the ent file
				while (entry_table_ptr) {
					data_label* my_data_label;
					char* address_base4;

					my_data_label = find_data_label(&state, ((entry_with_line_num*) entry_table_ptr->data)->name);
					if (!my_data_label) {
						code_label* my_code_label = find_code_label(&state, ((entry_with_line_num*) entry_table_ptr->data)->name);

						address_base4 = tobase4(MEM_STARTS_AT + (my_code_label -> address), 4);
					} else
						address_base4 = tobase4(MEM_STARTS_AT + (my_data_label -> address), 4);

					fprintf(output_ent_file, "%s\t%s\n", ((entry_with_line_num*) entry_table_ptr->data)->name, address_base4);
					fprintf(stdout, "entry: %s\t%s\n", ((entry_with_line_num*) entry_table_ptr->data)->name, address_base4);
					free(address_base4);
					entry_table_ptr = entry_table_ptr->next;
				}

				fclose(output_ent_file);
				free(output_ent_file_name);
			}

			if (state.extern_table != NULL) {
				char* output_ext_file_name = file_add_extension(argv[iterator], EXT_EXT);
				FILE* output_ext_file = fopen(output_ext_file_name, "w");
				list* extern_refs_table_ptr = state.extern_refs_table;

				// Check that the file was opened
				if (!output_ext_file) {
					fprintf(stderr, ERROR_CANNOT_WRITE, output_ext_file_name);
					all_success = 0;
					continue;
				}

				// Go over all entry table
				while (extern_refs_table_ptr) {
					int address = MEM_STARTS_AT + ((ref_in_code*)extern_refs_table_ptr->data)->code_address;
					char* address_base4 = tobase4(address, 4);
					fprintf(output_ext_file, "%s\t%s\n", ((ref_in_code*)extern_refs_table_ptr->data)->name, address_base4);
					fprintf(stdout, "extern: %s\t%s\n", ((ref_in_code*)extern_refs_table_ptr->data)->name, address_base4);
					extern_refs_table_ptr = extern_refs_table_ptr->next;
					free(address_base4);
				}

				fclose(output_ext_file);
				free(output_ext_file_name);
			}
		}

		if (DEBUG_MODE) {
			printf("%s\n", state.failed ? "Fail!" : "Success!");
		}

		// Free everything
		free(state.data_table);
		free(state.code_table);
		//free_list(state.entry_table, free_);
		free_list(state.extern_table, free);
		free_list(state.extern_refs_table, free_extern_refs);
		free_list(state.data_labels_table, free_data_labels);
		free_list(state.code_labels_table, free_code_labels);
		free(file_name);

		all_success *= !state.failed;

	}

	return !all_success;
}