#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 516

void create_rrq_packets(char *filename,char *mode,char *request_packet){ // read request
    request_packet[0]=0;
    request_packet[1]=1;
    strcpy(request_packet+2,filename);
    strcat(request_packet+2+ strlen(filename)+1,mode);
}

void tftp_client(char *server_ip,int port,char *filename){
    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;

    if (getaddrinfo(server_ip,NULL,&hints,&res)!=0){
        perror("Error in the resolution of the server address");
        exit(EXIT_FAILURE);
    }

    // socket creation :
    sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if (sockfd<0){
        perror("Error in the creation of the socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    memcpy(&server_addr.sin_addr,&((struct sockaddr_in*)res->ai_addr)->sin_addr, sizeof(struct in_addr));

    char request_packet[MAX_BUFFER_SIZE];
    create_rrq_packets(filename,"octet",request_packet);


    // if error in "sendto", it returns -1, next we check if there is an error in sendto.
    if (sendto(sockfd,request_packet,MAX_BUFFER_SIZE,0,(struct sockaddr *)&server_addr, sizeof(server_addr))==-1){
        perror("Error sending rrq request");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char *argv[]){  // Processing command line arguments
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
        int port = 69;  // Default port
        char *filename = argv[2];
    } else {
        fprintf(stderr,"Usage: %s <server_ip> <port> <filename>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
}
