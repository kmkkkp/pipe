#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


#define MAXLINE 4096
#define MAXFNAME 30
#define WRMODE 2
#define MAXBUF MAXLINE+MAXFNAME+WRMODE+3
#define FIFO1 "/tmp/forclienttoserver"
#define FIFO2 "/tmp/forservertoclient"

int clientServer;
int serverClient;

typedef struct request{
    char fileName[MAXFNAME];
    char rwmode[WRMODE];
    char var[MAXLINE];
}request;

request separateData(char input[]){//divide data to use
    request data;
    strcpy(data.fileName, strtok(input, "\n"));
    strcpy(data.rwmode, strtok(NULL, "\n"));
    strcpy(data.var, strtok(NULL, "\0"));
    return data;
}

int main(void){
    char receiveData[MAXBUF];
    pid_t pid = -1; 
    
    unlink(FIFO1);
    unlink(FIFO2);

    if(mkfifo(FIFO1, 0666)<0||mkfifo(FIFO2, 0666)<0){
        printf("Cannot make pipe!\n");
        exit(1);
    }
    clientServer = open(FIFO1, O_RDONLY);//make named pipe to read from client
    serverClient = open(FIFO2, O_WRONLY);//make named pipe to write to client

    while(1){
        read(clientServer, receiveData, MAXBUF);//read client
        pid = fork();
        if(pid==-1){
            printf("Can't fork\n");
        }
        else if(pid == 0){
            request useData = separateData(receiveData);//data dividing
            if(strcmp(useData.rwmode, "r")==0){ //readmode
                char buffer[MAXBUF] = { };
                int readfd = open(useData.fileName, O_RDONLY);
                if(readfd<0){
                    printf("File name error\n");
                    strcpy(buffer, "File name error");
                }
                else{
                    printf("Client read success\n");
                    read(readfd, buffer, atoi(useData.var));
                    close(readfd);
                }
                write(serverClient, buffer, MAXBUF);//send to client after work
            }
            else if(strcmp(useData.rwmode, "w")==0) {//writemode
                char buffer[MAXBUF] = { };
                int note;
                int writefd = open(useData.fileName, O_CREAT|O_WRONLY|O_TRUNC, 0666);
                if(writefd<0){
                    printf("can't write\n");
                    strcpy(buffer, "can't write");
                }
                else{
                    note = write(writefd, useData.var, (int)strlen(useData.var));
                    printf("Write success\n");
                    sprintf(buffer, "Write success\nWriten bytes: %d", note);
                    close(writefd);
                }
                write(serverClient, buffer, MAXBUF);//send to client after work
            }
        }
        else{
            waitpid(pid, NULL, 0);
        }
        memset(receiveData, 0, sizeof(receiveData));
    }
    close(clientServer);
    close(serverClient);
    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}
