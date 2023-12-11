#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>

#define MAX_BUFFER_SIZE 516

void tftp_client(char *server_ip,int port,char *filename){
    struct addrinfo hints, *res;

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;

    if (getaddrinfo(server_ip,NULL,&hints,&res)!=0){
        perror("Error in the resolution of the server address");
    }
}

int main(int argc,char *argv[]){
    if(argc==4){  // gettftp ; server ; port; file
        char *server_ip=argv[1];
        if (atoi(argv[2])==0){  // if there isnt the port, return failure
            fprintf(stderr,"Port format doesn't match");
            exit(EXIT_FAILURE);
        } else {
            int port = atoi(argv[2]);
        }
        char *filename = argv[3];
    } else if(argc==3){
        char *server_ip=argv[1];
        int port = 69;
        char *filename = argv[2];
    } else {
        fprintf(stderr,"Usage: %s <server_ip> <port> <filename>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
}
