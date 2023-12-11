#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_BUFFER_SIZE 516

void tftp_put_client(char *server_ip,int port,char *filename){
    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;

    if (getaddrinfo(server_ip,NULL,&hints,&res)!=0){
        perror("Error in the resolution of the server address");
    }

    sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if (sockfd<0){
        perror("Error in the creation of the socket");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    memcpy(&server_addr.sin_addr,&((struct sockaddr_in*)res->ai_addr)->sin_addr, sizeof(struct in_addr));
}
int main(int argc,char *argv[]){
    if(argc==4){
        char *server_ip=argv[1];
        if (atoi(argv[2])==0){
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