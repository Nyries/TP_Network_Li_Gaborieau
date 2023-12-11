#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 516

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
