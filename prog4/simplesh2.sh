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

	if (pid == -1) {
		perror("fork");
	} else if (pid == 0) {   

		if (in) { //if '<' char was found in string inputted by user
			int fd0 = open(input, O_RDONLY, 0);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
			in = 0;
		}

		if (out) { //if '>' was found in string inputted by user
			int fd1 = creat(output, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
			out = 0;
		}  
	
		execvp(res[0], res);
		perror("execvp");
		_exit(1);
	
	} else {
		waitpid(pid, 0, 0);
		free(res);
	}
}