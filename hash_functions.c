#include <stdio.h>

// Complete these two functions according to the assignment specifications


void hash(char *hash_val, long block_size) {
	// initialize hash_val
	for (int i = 0; i < block_size; i++) {
		hash_val[i] = '\0';
	}
	// read the input one at a time and apply xor operation to replace the position
	// at hash_val accordingly until the input ended
	// initialize the char
	char c;
	int counter = 0;
	while (scanf("%c", &c) != EOF) {
		// if not read the EOF, we xor the char with the value at the counter position
		hash_val[counter] = (hash_val[counter] ^ c);
		// prepare for the next counter
		counter ++;
		if (counter == block_size) {
			counter = 0;
		}
	}
}


int check_hash(const char *hash1, const char *hash2, long block_size) {
	// check the char in the array one by one, return the index if they do not match
	for (int i = 0; i < block_size; i++) {
		if (hash1[i] != hash2[i]) {
			return i;
		}	
	}
	// otherwise, return block_size
   return block_size;
}
