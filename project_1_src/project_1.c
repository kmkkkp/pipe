#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
       	int fd_in = open("A", O_RDONLY);
	if(fd_in == -1){
		printf("Error! There is no file with name 'A' in same directory!\n");
		exit(1);
	}
	dup2(fd_in, 0);
	

     	int fd_out = open("B", O_CREAT|O_WRONLY|O_TRUNC, 0666);
	dup2(fd_out, 1);
	
	int pid=fork();
	if (pid == 0) {
		execlp("./P", "P", (char *)NULL);
	}
	else if(pid>0){
		wait(NULL);
	} 
}
