#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <errno.h>
#include "my.h"

void sendToAllClients(struct pollfd clients[], char* name, char* message, int size){
    char formattedMessage[2048];
    memset(formattedMessage, '\0', 2048);
    my_strncpy(formattedMessage, name, my_strlen(name) - 1);
    my_strcat(formattedMessage, " : ");
    my_strcat(formattedMessage, message);
    for(int c = 1; c < size; c++){
        send(clients[c].fd, formattedMessage, my_strlen(formattedMessage), 0);
    }
}

int main(int argc, char* argv[]){

    if(argc != 2){
        my_str("Usage: ./server <port>");
        exit(1);
    }
    int rc, on = 1;
    int listen_sd = -1, new_sd = -1;
    int end_server = 0, compress_array = 0; //0 being false
    int close_conn;
    char* message = malloc(2048);
    struct sockaddr_in addr;
    struct pollfd fds[10];
    char names[10][1024]; //allocate memory for the user names
    memset(names, '\0', 1024 * 10);
    //struct pollfd fds[] = (struct pollfd*)malloc(10 * sizeof(int)); //mallocs memory for 10 client file descriptors
    int nfds = 1, current_size = 0, i, j;

    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sd < 0){
        perror("initial socket failed - ln26");
        exit(1);
    }

    rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if(rc < 0){
        perror("setsockopt() failed - ln31");
        close(listen_sd);
        exit(1);
    }

    rc = ioctl(listen_sd, FIONBIO, (char *)&on);
    if(rc < 0){
        perror("ioctl() failed - ln37");
        close(listen_sd);
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));
    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
    if(rc < 0){
        my_int(atoi(argv[1]));
        perror("bind() failed - ln54");
        close(listen_sd);
        exit(1);
    }

    rc = listen(listen_sd, 32);
    if(rc < 0){
        perror("listen() failed - ln61");
        close(listen_sd);
        exit(1);
    }

    memset(fds, 0, sizeof(fds));

    fds[0].fd = listen_sd;
    fds[0].events = POLLIN;

    do {
        rc =  poll(fds, nfds, -1);//poll waits until it recieves an event
        if(rc < 0){
            perror("poll failed - ln 74");
            break;
        } else if(rc == 0){// cant happen since poll is set to -1
            my_str("polling timed out");
        }

        current_size = nfds;
        for(i = 0; i < current_size; i++){
            if(fds[i].revents == 0){
                continue;
            }

            if(fds[i].revents != POLLIN){
                my_str("Error: Server got scared");
                end_server = 1; //set end_server to true
                break;
            }

            if(fds[i].fd == listen_sd){
                my_str("new client(s) connecting");
                do{
                    new_sd = accept(listen_sd, NULL, NULL);
                    if(new_sd <  0){
                        if(errno != EWOULDBLOCK){
                            perror("accept() failed - ln99");
                            end_server = 1;
                        }
                        break;
                    }
                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                } while(new_sd != -1);
            } else {
                my_str("reading from fds > 0");
                close_conn = 0; //set to false
                memset(message, '\0', 1024);
                rc = recv(fds[i].fd, message, sizeof(message), 0);
                if(rc < 0){
                    if(errno != EWOULDBLOCK){
                        perror("recv() failed - ln112");
                        close_conn = 1;
                    }
                    break;
                }
                if(rc == 0){
                    my_str("Connection closed");
                    close_conn = 1;
                    break;
                }
                my_str("HELP");
                if(my_strncmp(names[i], "\0", 1) == 0){//name not set
                    my_strcpy(names[i], message);
                } else {
                    sendToAllClients(fds, names[i], message, nfds);
                }

                if(close_conn){
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = 1;
                }
            }
        }
        if(compress_array){
            compress_array = 0; //set array to false
            for(i = 0; i < nfds; i++){
                if(fds[i].fd == -1){
                    for(j = i; j < nfds; j++){
                        fds[j].fd = fds[j+1].fd;
                    }
                    nfds--;
                }
            }
        }
    } while(end_server == 0);
    for(i = 0; i < nfds; i++){
        if(fds[i].fd >= 0){
            close(fds[i].fd);
        }
    }
}
