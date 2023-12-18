#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_BUFFER_SIZE 516

void create_wrq_packets(char *filename,char *mode,char *request_packet){
    short opcode = htons(2);

    memcpy(request_packet,&opcode,sizeof(short));

    strcpy(request_packet+ sizeof(short),filename);
    strcpy(request_packet+ sizeof(short)+ strlen(filename),mode);
}

void tftp_put_client(char *server_ip,int port,char *filename){
    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;

    if (getaddrinfo(server_ip,NULL,&hints,&res)!=0){
        perror("Error in the resolution of the server address");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if (sockfd<0){
        perror("Error in the creation of the socket");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    memcpy(&server_addr.sin_addr,&((struct sockaddr_in*)res->ai_addr)->sin_addr, sizeof(struct in_addr));

    char request_packet[MAX_BUFFER_SIZE];
    create_wrq_packets(filename,"octet",request_packet);

    if(sendto(sockfd,request_packet,MAX_BUFFER_SIZE,0,(struct sockaddr *)&server_addr, sizeof(server_addr))==-1){
        perror("Error sending WRQ request");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    FILE *file=fopen(filename,"rb");
    if(file==NULL){
        perror("Error opening the file for reading");
        fclose(file);
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_response_addr;
    socklen_t server_response_len = sizeof(server_response_addr);

    char buffer[MAX_BUFFER_SIZE];
    short next_block_number=1;

    while(1){
        ssize_t read_size= fread(buffer+4,1,MAX_BUFFER_SIZE-1,file);

        short opcode=htons(3);
        short block_number = htons(next_block_number);
        memcpy(buffer,&opcode, sizeof(short));
        memcpy(buffer+2,&block_number,sizeof(short));

        sendto(sockfd,buffer,4+read_size,0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        recvfrom(sockfd,buffer,MAX_BUFFER_SIZE,0,(struct sockaddr *)&server_response_addr, &server_response_len);

        short received_opcode;
        memcpy(&received_opcode,buffer,sizeof(short));
        received_opcode=ntohs(received_opcode);

        if (received_opcode==4){
            short received_block_number;
            memcpy(&received_block_number,buffer,sizeof(short));

            if (received_block_number== next_block_number){
                next_block_number++;

                if (read_size<block_number){
                    break;
                }
            }
        }
    }
    fclose(file);
    close(sockfd);
    freeaddrinfo(res);
}
int main(int argc,char *argv[]){
    if(argc==4){
        char *server_ip=argv[1];
        int port;
        if (atoi(argv[2])==0){  // if there isn't the port, return failure
            fprintf(stderr,"Port format doesn't match");
            exit(EXIT_FAILURE);
        } else {  // else return the port
            port = atoi(argv[2]);
        }
        char *filename = argv[3];
        tftp_put_client(server_ip,port, filename);
        exit(EXIT_SUCCESS);
    } else if(argc==3){
        char *server_ip=argv[1];
        int port = 69;
        char *filename = argv[2];
        tftp_put_client(server_ip,port, filename);
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr,"Usage: %s <server_ip> <port> <filename>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
}