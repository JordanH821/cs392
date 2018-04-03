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

int main(int argc, char* argv[]){

    if(argc != 2){
        my_str("Usage: ./server <port>");
        exit(1);
    }
    int len, rc, on = 1;
    int listen_sd = -1, new_sd = -1;
    int desc_ready, end_server = 0, compress_array = 0; //0 being false
    int close_conn;
    char* message = malloc(2048);
    struct sockaddr_in addr;
    int timeout;
    struct pollfd fds[] = malloc(10 * sizeof(int)); //mallocs memory for 10 client file descriptors
    int nfds = 1, current_size = 0, i, j;

    list_sd = socket(AF_INET, SOCK_STREAM, 0);
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
    addr.sin_port = htons(argv[1]);
    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
    if(rc < 0){
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

    while(1){
        rc =  poll(fds, nfds, -1);//poll waits until it recieves an event
        if(rc < 0){
            perror("poll failed - ln 74");
            break;
        } else if(rc == 0){// cant happen since poll is set to -1
            my_str("polling timed out");
        }

        current_size = ndfs;
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
                while()
            }
        }
    }

}