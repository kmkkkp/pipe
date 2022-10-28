#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 4096
#define MAXFNAME 30
#define WRMODE 2
#define MAXBUF MAXLINE+MAXFNAME+WRMODE+3
#define FIFO1 "/tmp/forclienttoserver"
#define FIFO2 "/tmp/forservertoclient"

typedef struct requestFromClient{
    char fileName[MAXFNAME];
    char rwMode[WRMODE];
    char var[MAXLINE];
}request; //data struct for sending

request data;
char dataSend[MAXBUF];//if read, use like receiving, if write, use like sending

int main(){

    int clientServer = open(FIFO1, O_WRONLY);//open pipe to write(client->server)
    int serverClient = open(FIFO2, O_RDONLY);//open pipe to read(server->client)


        printf("Enter File Name: ");
        scanf("%s", data.fileName);//get File name
        getchar();//delete buffer
        
        while(1){
            printf("Enter File Mode[r|w]: ");//get File mode (write or read)
            scanf("%s", data.rwMode);
            getchar();//delete buffer
            if(data.rwMode[0] == 'r'){//read
                printf("Enter Bytes to read: ");
                scanf("%s", data.var);
                getchar();//delte buffer
                break;
            }
            else if(data.rwMode[0]=='w'){//write
                printf("Enter String: ");
                scanf("%s", data.var);
                getchar();//delte buffer
                break;
            }
            else;
        }
        strcat(dataSend, data.fileName);
        strcat(dataSend, "\n");
        strcat(dataSend, data.rwMode);
        strcat(dataSend, "\n");
        strcat(dataSend, data.var);//data combine to send         

        if(write(clientServer, dataSend, MAXBUF)<0){//send to server
            printf("Write error\n");
        }
        if(read(serverClient, dataSend, MAXBUF)<0){//read from server
            printf("Read error\n");
        }
        printf("-------------------------\n");
        printf("After work\n");
        printf("FileName: %s\n", data.fileName);
        printf("FileMode: %s\n", data.rwMode);
        printf("Data: ");
        if(data.rwMode[0]=='r'){
            printf("%s\n", dataSend);
        }
        else if(data.rwMode[0]=='w'){
            printf("%s\n", dataSend);
        }


    close(clientServer);//close pipe
    close(serverClient);//close pipe
    return 0;
}