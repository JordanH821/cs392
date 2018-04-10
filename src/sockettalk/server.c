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

void sendToAllClients(struct pollfd clients[], char* name, char* message, int size, int meBit){
    char formattedMessage[2053];
    memset(formattedMessage, '\0', 2053);
    my_strncpy(formattedMessage, name, my_strlen(name));
    if(meBit){
        my_strcat(formattedMessage, " ");
        my_strcat(formattedMessage, &message[4]);
        if(message[4] == '\0'){
            my_strcat(formattedMessage, "\n");
        }
    } else {
        my_strcat(formattedMessage, " : ");
        my_strcat(formattedMessage, message);
    }
    my_str(formattedMessage);
    my_str("\n");
    for(int c = 1; c < size; c++){
        send(clients[c].fd, formattedMessage, my_strlen(formattedMessage), 0);
    }
}

char* nameCleaner(char* name){
    char* cleanName = (char*)malloc(my_strlen(name) + 1);
    int j = 0;
    char* illegal = " \n\t";
    for(int i = 0; i < my_strlen(name); i++){
        if(my_strfind(illegal, name[i]) == NULL){
            cleanName[j] = name[i];
            j++;
        }
    }
    cleanName[j+1] = '\0';
    return cleanName;
}

void reallocHelp(struct pollfd* fds, char** names, int userLimit){
    for(int i = (userLimit / 2); i < userLimit; i++){
        names[i] = (char*)malloc(1025);
        memset(names[i], '\0', 1025);
    }
    memset(&fds[userLimit/2 + 1], 0, sizeof(fds[userLimit/2 + 1]));
}

int main(int argc, char* argv[]){

    if(argc != 2){
        my_str("Usage: ./server <port>");
        exit(1);
    }
    int rc, on = 1;
    int listen_sd = -1, new_sd = -1;
    int end_server = 0, compress_array = 0; //0 being false
    //int close_conn;
    char* message = malloc(2053);
    struct sockaddr_in addr;
    struct pollfd* fds = malloc(sizeof(int) * 3);
    char** names; //allocate memory for the user names
    names = malloc(3 * sizeof(char*));
    for(int i = 0; i < 3; i++){
        names[i] = (char*)malloc(1025);
        memset(names[i], '\0', 1025);
    }
    //memset(names, '\0', 1025 * 10);
    int userLimit = 3;
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

    memset(fds, 0, sizeof(*fds));

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

            if(fds[i].fd == -1){
                continue;
            }
            if(fds[i].revents == 0){
                continue;
            }

            if(fds[i].revents != POLLIN){
                my_str("Error: Server got scared");
                end_server = 1; //set end_server to true
                break;
            }

            if(fds[i].fd == listen_sd){
                my_str("new client(s) connecting\n");
                do{
                    new_sd = accept(listen_sd, NULL, NULL);
                    if(new_sd <  0){
                        if(errno != EWOULDBLOCK){
                            perror("accept() failed - ln99");
                            end_server = 1;
                        }
                        break;
                    }
                    if(nfds >= userLimit - 1){
                        my_str("User limit reached, reallocing memory\n");
                        userLimit *= 2;
                        names = realloc(names, userLimit * sizeof(char*));
                        fds = realloc(fds, userLimit * sizeof(int));
                        reallocHelp(fds, names, userLimit);
                    }
                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                } while(new_sd != -1);
            } else {
                my_str("reading from fds > 0\n");
                //close_conn = 0; //set to false
                memset(message, '\0', 1025);
                rc = recv(fds[i].fd, message, 1024, 0);
                my_str("\n");
                my_str(message);
                my_str("\n");
                if(rc < 0){
                    if(errno != EWOULDBLOCK){
                        perror("recv() failed - ln112");
                        //close_conn = 1;

                    }
                    break;
                }
                if(rc == 0){
                    my_str("Connection closed\n");
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = 1;
                    continue;
                }
                if(my_strncmp(names[i], "\0", 1) == 0){//name not set
                    char* cleanName = nameCleaner(message);
                    if(my_strlen(cleanName) == 0){
                        my_strcpy(names[i], "BlankName");
                        char* blankNameError = "You have entered a username of just white space. Update with \'/me <new name>\'.\n";
                        send(fds[i].fd, blankNameError, my_strlen(blankNameError), 0);
                    } else{
                        my_strcpy(names[i], nameCleaner(message));
                    }
                } else if(my_strncmp(message, "/me", 3) == 0){
                    sendToAllClients(fds, names[i], message, nfds, 1);
                } else if(my_strncmp(message, "/nick", 5) == 0){
                    memset(names[i], '\0', 1025);
                    my_strcpy(names[i], nameCleaner(&message[6]));//NEED TO FORMAT USERNAME
                } else if(my_strncmp(message, "/exit", 5) == 0){
                    my_str("Connection closed with ");
                    my_str(names[i]);
                    my_str("\n");
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = 1;
                    continue;
                } else if(my_strncmp(message, "/", 1) == 0){
                    my_str(names[i]);
                    my_str(" used an invalid special command.\n");
                    char* errorMessage = "That is an invalid special command.\n";
                    send(fds[i].fd, errorMessage, my_strlen(errorMessage), 0);
                } else {
                    sendToAllClients(fds, names[i], message, nfds, 0);
                }

                // if(close_conn){
                //     close(fds[i].fd);
                //     fds[i].fd = -1;
                //     compress_array = 1;
                // }
            }
        }
        if(compress_array){
            compress_array = 0; //set array to false
            for(i = 0; i < nfds; i++){
                if(fds[i].fd == -1){
                    for(j = i; j < nfds; j++){
                        fds[j].fd = fds[j+1].fd;
                        memset(names[j], '\0', 1025);
                        my_strcpy(names[j], names[j+1]);
                        memset(names[j+1], '\0', 1025);
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
