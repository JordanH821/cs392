#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <signal.h>
#include "my.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char* nameBuff = malloc(1025);
    char* message = malloc(1025);
    char* serverMessage = malloc(2053);
    if (argc < 3) {
       my_str("Usage: ./client <host> <port>");
       exit(0);
    }
    memset(nameBuff, '\0',1025);
    my_str("Please enter a username: ");
    read(0, nameBuff, 1024);
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }
    n = write(sockfd, nameBuff, my_strlen(nameBuff));
    free(nameBuff);
    nameBuff = NULL;
    if (n < 0) 
         error("ERROR writing to socket");
    pid_t pid;
    if((pid = fork()) < 0){
        error("Fork failed");
    } else if(pid == 0){//child used to read
        while(1){
            bzero(serverMessage, 2053);
            read(sockfd, serverMessage, 2053);
            my_str(serverMessage);
        }
    } else {//parent used to write
        while(1){
            memset(message, '\0', 1025);
            read(0, message, 1024);
            if(my_strncmp(message, "/exit", 5) == 0){
                write(sockfd, message, my_strlen(message));
                kill(pid, SIGKILL);
                close(sockfd);
                exit(0);
            }
            n = write(sockfd, message, my_strlen(message));
            //need to check for special commands and then kill child on exit
            //close sockets
        }
    }
    close(sockfd);
    return 0;
}