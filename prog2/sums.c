/*===========================================================================
	USAGE: sums inputFile outputFile
	-lcrypto parameter to gcc accesses library with MD5 routine
============================================================================*/
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MD5_LENGTH 16
#define NUM_HASHES 4
#define EXPECTED_SIZE 10

/*============================================================================
- lineSums takes as input the names of two files.
If the first file does not exist, returns zero (NULL ptr)
immediately.
If the second file does not exist, it will be created; if it does
exist, it will be truncated.
- Computes an MD5 hash over each line of the input file
A line ends with a newline character or EOF
Any newline character in a line is removed before taking the sum
- Allocates and fills in an array of character pointers that each point
to the MD5 hash values in the following format:
Each line in the output array is LINEx:SUMx
where LINEx is input line number x and
SUMx is the MD5 hash value over LINEx
- Writes each entry of the array to the output file separated by a newline
- Returns a pointer to the array
It is the responsibility of the caller to deallocate the returned array
of string pointers and strings. This routine should "leak" no other memory
============================================================================*/ 

char **lineSums(char *inp, char *outp)
{
	unsigned char output[MD5_LENGTH];
	unsigned char *sumPtr;
	int i = 0;
	int j;
	int done = 0;
	char *word;
	char oneByte[3];
	char **entries = {""};
	size_t wordLen;
	size_t lineLen;
	size_t nbytes = EXPECTED_SIZE;
	FILE *inFile;
	FILE *outFile;
	
	inFile = fopen(inp,"r");
	outFile = fopen(outp,"w+");
	
	while (done == 0) {
		entries = malloc(10*sizeof(char));
		wordLen = EXPECTED_SIZE;
		word = malloc(wordLen);
		if(word == (char *)0 && entries != NULL) {
			free(word);
			free(sumPtr);
			return(entries);
		} //spread out
		lineLen = getline(&word, &nbytes, inFile);
		if(lineLen < 0) { 
			done = 1;
			break; 
		}
		#ifdef DEBUG
		printf("line <%s> lineLength <%d> buf size <%d>\n", word, lineLen, wordLen);
		#endif
		/* MD5 produces 16 byte value */
		output = malloc(MD5_LENGTH);
		sumPtr = MD5((const unsigned char*)word, strlen(word), output);
		entries[i] = malloc(lineLen + 1 + 127);
		strcat(entries[i], word);
		strcat(entries[i], ":");
		for(j=0; j < MD5_LENGTH; j++) {
			sprintf(oneByte, "%02x", sumPtr[j]);
			strcat(entries[i], oneByte);
		}
		fprintf(outFile,"%s\n", entries[i]);
		#ifdef DEBUG
			printf("Entry %d <%s>\n", i, entries[i]);
		#endif
		printf("\n");
	}
	return(entries);
}
/*============================================================================
Demonstrate lineSums.
USAGE: sums inputFile outputFile
Prints out returned array values. Should match contents of output file exactly.
Deallocates all memory associated with the returned sums
*============================================================================*/

int main(int argc, char *argv[])
{
	char **theSums;
	int i = 0;
	theSums = lineSums(argv[1], argv[2]);

	#ifdef DEBUG
		printf("Writing out returned values:\n");
	#endif
	
	for (i=0; theSums[i]!=(char *)0; i++) {
		printf("%d %s\n", i, theSums[i]);
	}
	
	#ifdef DEBUG
		printf("Done main\n");
	#endif
	
	free(theSums);
}