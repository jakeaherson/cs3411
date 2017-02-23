/* 	Jake Herson
 * 	7/9/2016
 * 
 * 	simplesh.sh
 * 	
 *
 * 	Compile: make
 *	Usage: ./simplesh
 */
 
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int pid = fork();
	
	if (pid == 0)
	{

		// function for redirection ( '<' , '>' )

		int fd0,fd1,i,in=0,out=0;
		char input[64],output[64];

		// finds where '<' or '>' occurs and make that argv[i] = NULL , to ensure that command wont't read that

		for(i=0;argv[i]!='\0';i++)
		{
			if(strcmp(argv[i],"<")==0)
			{        
				argv[i]=NULL;
				strcpy(input,argv[i+1]);
				in=2;           
			}               

			if(strcmp(argv[i],">")==0)
			{      
				argv[i]=NULL;
				strcpy(output,argv[i+1]);
				out=2;
			}         
		}

		//if '<' char was found in string inputted by user
		if(in)
		{   

			// fdo is file-descriptor
			int fd0;
			int O_RDONLY;
			if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
				perror("Couldn't open input file");
				exit(0);
			}           
			// dup2() copies content of fdo in input of preceeding file
			dup2(fd0, 0); // STDIN_FILENO here can be replaced by 0 

			close(fd0); // necessary
		}

		//if '>' char was found in string inputted by user 
		if (out)
		{

			int fd1 ;
			if ((fd1 = creat(output , 0644)) < 0) {
				perror("Couldn't open the output file");
				exit(0);
			}           

			dup2(fd1, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
			close(fd1);
		}

		execvp(*argv, argv);
		perror("execvp");
		_exit(1);

		// another syntax
		/*      if (!(execvp(*argv, argv) >= 0)) {     // execute the command  
				printf("*** ERROR: exec failed\n");
				exit(1);
		 */ 
	}


	else if(pid < 0)
	{     
		printf("fork() failed!\n");
		exit(1);
	}

	else 
	{   /* for the parent:      */
		int status;
		while (!(wait(&status) == pid)) ; // good coding to avoid race_conditions(errors) 
	}
}