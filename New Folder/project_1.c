#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
       	int fd_in = open("A", O_RDONLY);
	printf("%d", fd_in);
	dup2(fd_in, 0);

     	int fd_out = open("B", O_CREAT|O_WRONLY|O_TRUNC, 0666);
	printf("%d", fd_out);
	dup2(fd_out, 1);
	
	int pid=fork();
	if (pid == 0) {
		execlp("./P", "P", NULL);
	}
	else if(pid>0){
		wait(NULL);
	}
	 
}
