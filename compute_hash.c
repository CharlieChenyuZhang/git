#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Hash manipulation functions in hash_functions.c
void hash(char *hash_val, long block_size);
int check_hash(const char *hash1, const char *hash2, long block_size);

#ifndef MAX_BLOCK_SIZE
    #define MAX_BLOCK_SIZE 1024
#endif

/* Converts hexstr, a string of hexadecimal digits, into hash_val, an an 
 * array of char.  Each pair of digits in hexstr is converted to its 
 * numeric 8-bit value and stored in an element of hash_val.
 * Preconditions: 
 *    - hash_val must have enough space to store block_size elements
 *    - hexstr must be block_size * 2 characters in length
 */

void xstr_to_hash(char *hash_val, char *hexstr, int block_size) {
    for(int i = 0; i < block_size*2; i += 2) {
        char str[3];
        str[0] = hexstr[i];
        str[1] = hexstr[i + 1];
        str[2] = '\0';
        hash_val[i/2] = strtol(str, NULL, 16);
    }
}

// Print the values of hash_val in hex
void show_hash(char *hash_val, long block_size) {
    for(int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}


int main(int argc, char **argv) {
	// given block
   char hash_val[MAX_BLOCK_SIZE] = {'\0'};
   long block_size;
    
	// first task: update it to handle two command line arguments
	// check whether the user provided too many inputs
	int valid_input_size = 1;
	
	if (argc > 3 || argc == 1){
		valid_input_size = 0;
	}
	
	int valid_input = 1;
	// check the value provided as the first argument
	for (int i = 0; i < strlen(argv[1]); i++) {
		if (isdigit(argv[1][i]) == 0) {
			valid_input = 0;
			break;
		}
	}
	if (valid_input != 0){
		// if the input is an digit, check whether it is a positive digit and less than MAX_BLOCK_SIZE
		long i;
		i = strtol(argv[1], NULL, 10);		
		if (i <= 0 || i > MAX_BLOCK_SIZE){
			valid_input = 0;		
		}
	}
	
	// check after all, whether the valid input n valid input size are 0s or not
	if (valid_input == 0 || valid_input_size == 0){
		if (valid_input == 0){
			printf("The block size should be a positive integer less than %d.", MAX_BLOCK_SIZE);
			printf("\n");
		} 
		if (valid_input_size == 0){
			// input size
			printf("Usage: compute_hash BLOCK_SIZE [ COMPARISON_HASH ]");
			printf("\n");
		}
		// terminate the program
		exit(EXIT_FAILURE);
	}else {
		// assign the value to block_size
		block_size = strtol(argv[1], NULL, 10);	
	}

	// part2, call the hash function
	hash(hash_val, block_size);
	printf("\n");
	show_hash(hash_val, block_size);
	
	// part 3
	// initialize the expected value array
	char expected_value[MAX_BLOCK_SIZE] = {'\0'};
	for (int i = 0; i < block_size; i++) {
		expected_value[i] = '\0';
	}
	// check whether the second command line is provided or not
	if (argc == 3) {
		// convert the string into an array of char
		xstr_to_hash(expected_value, argv[2], block_size);
		printf("%d", check_hash(hash_val, expected_value, block_size));
		printf("\n");	
	}
	
   return 0;
}

