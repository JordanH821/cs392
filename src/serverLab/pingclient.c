/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

#include "my.h"

int seed = 123456789;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   srand(seed);
   int sock, length, n;
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];

   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   char* dummyBuff = malloc(10);
   read(0, dummyBuff, 10);

   //start
   n = sendto(sock,"Ping",4,
                  0,(struct sockaddr *)&from,fromlen);
   if (n  < 0) error("sendto");

   //ping pong loop
   while (1) {
       n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) error("recvfrom");
       write(1,"Received a datagram: ",21);
       write(1,buf,n);
       if(my_strcmp(buf, "LOST") == 0){
          my_str("Win");
          return 0;
       }
       int random = rand() % 10;
       if(random != 1){
            n = sendto(sock,"Ping",4,
                0,(struct sockaddr *)&from,fromlen);
            if (n  < 0) error("sendto");
        } else {
            n = sendto(sock,"LOST",4,
                0,(struct sockaddr *)&from,fromlen);
            if (n  < 0) error("sendto");
            return 0;
        }
   }
   return 0;
 }
