#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 516

void create_rrq_packets(char *filename,char *mode,char *request_packet){
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

    if (sendto(sockfd,request_packet,MAX_BUFFER_SIZE,0,(struct sockaddr *)&server_addr, sizeof(server_addr))==-1){
        perror("Error sending rrq request");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    FILE *file=fopen(filename,"wb");
    if(file==NULL){
        perror("Error opening th file");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_response_addr;
    socklen_t server_response_len = sizeof(server_response_addr);

    while(1){
        char buffer[MAX_BUFFER_SIZE];
        ssize_t recv_size = recvfrom(sockfd,buffer,MAX_BUFFER_SIZE,0,(struct sockaddr *)&server_response_addr,&server_response_len);

        if (recv_size==-1){
            perror("Error in the reception of datas");
            fclose(file);
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        short opcode;
        memcpy(&opcode,buffer, sizeof(short));
        opcode = ntohs(opcode);

        if (opcode==3){
            fwrite(buffer + 4,1,recv_size-4,file);

            char ack_packet[4];
            ack_packet[0]=0;
            ack_packet[1]=4;
            short block_number;
            memcpy(&block_number,buffer+2, sizeof(short));
            block_number = ntohs(block_number);
            memcpy((ack_packet +2, &block_number, sizeof(short)));

            sendto(sockfd,ack_packet,4,0,(struct sockaddr *)&server_response_addr, server_response_len);
        }
        if (recv_size<MAX_BUFFER_SIZE-4){
            break;
        }
    }
    fclose(file);
    close(sockfd);
    freeaddrinfo(res);
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
