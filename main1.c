#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "listops.h"
#include "functions.h"

//sufficient for 512 + 1 characters
#define TEMP_STRING_LEN 513
#define HOLDING_STR_LEN 128

int
main(int argc, char *argv[]) {

	FILE* input_file;
	FILE* output_file;
	
	//holding the str from input file for processing
	char temp_str[TEMP_STRING_LEN];

	list_t* street_list;

	//list data variables
	int footpath_id;
	char address[HOLDING_STR_LEN + 1];
	char clue_sa[HOLDING_STR_LEN + 1];
	char asset_type[HOLDING_STR_LEN + 1];
	double deltaz, distance, grade1in;
	double mcc_id, mccid_int; //will be int in struct, double for easier scanning
	double rlmax, rlmin;
	char segside[HOLDING_STR_LEN + 1];
	double statusid, streetid, street_group; //will be int in struct, double for easier scanning
	double start_lat, start_lon, end_lat, end_lon;

	//get the file name to open
	input_file = fopen(argv[2], "r");
	assert(input_file);

	output_file = fopen(argv[3], "w");
	assert(output_file);

	//list created
	street_list = make_empty_list();

	//begin scanning in data
	//skip header
	fgets(temp_str, TEMP_STRING_LEN, input_file);

	//scans row by row and save values
	while (fgets(temp_str, TEMP_STRING_LEN, input_file) != NULL) {

		int has_quotes = 0;
		int str_len = strlen(temp_str);

		//check whether the string contains <""> quotation marks
		//if so, replace commas within quotes for easier scanning
		has_quotes = replace_commas(temp_str, str_len);

		scan_values(temp_str, &footpath_id, address, clue_sa, asset_type, &deltaz, &distance, &grade1in, 
		&mcc_id, &mccid_int, &rlmax, &rlmin, segside, &statusid, &streetid, &street_group, &start_lat, 
		&start_lon, &end_lat, &end_lon, str_len);


		//revert the "changed commas" within quotes and remove quotations marks
		if (has_quotes != 0) {
			
			change_asterik_remove_quotes(address);
			change_asterik_remove_quotes(clue_sa);
			change_asterik_remove_quotes(asset_type);
			change_asterik_remove_quotes(segside);
		}

		//insert node into list
		street_list = insert_at_foot(street_list, footpath_id, address, clue_sa, asset_type, deltaz, 
		distance, grade1in, mcc_id, mccid_int, rlmax, rlmin, segside, statusid, streetid, street_group, 
		start_lat, start_lon, end_lat, end_lon);
	}

	//linked list complete, now to accept input from stdin and search for matches

	while (fgets(temp_str, HOLDING_STR_LEN, stdin) != NULL) {

		//get rid of the \n that is read by fgets()
		int str_len = strlen(temp_str);
		temp_str[str_len - 1] = '\0';

		//search for matches and write them into file, and output total num of matches
		list_str_search(temp_str, street_list, output_file);
	}

	free_list(street_list);	

	fclose(input_file);
	fclose(output_file);
}	
