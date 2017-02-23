#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i = 1;
	int first;
	int length;
	
	first = atoi(argv[1]);
	if(first < 1 || first > 100) {
		printf("First argument does not meet requirements.\n");
		exit(0);
	}
	
	length = strlen(argv[2]);
	if(length != 5) {
		printf("Second argument should be exactly 5 characters.\n");
		exit(0);
	}
	
	printf("%d\n", argc);
	for (i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	
	return 0;
}