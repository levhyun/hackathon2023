
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "./../../head/define.h"
#include "./../../head/untils-client.h"


void *recv_to_serv(void *arg) {
    int conn_sock = *((int*) arg);
    int str_len;
    char command[256];
    while(1) {
        str_len = read(conn_sock, command, sizeof(command) - 1);
        if(str_len == -1)
            error_handling("read() error");
        
        printf("KessDB > ");
        printf("%s\n", command);
        
    }
}

int main(int argc, char *argv[]) {
    int conn_sock;
    struct sockaddr_in serv_addr;

    if(argc != 3) {
        printf("%s <ip> <port>", argv[0]);
        exit(1);
    }

    conn_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(conn_sock == -1) 
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(conn_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1) //2번
        error_handling("connect() error");
        
    /* ** ** ** */
    pthread_t tid;
    pthread_create(&tid, NULL, recv_to_serv, (void *)&conn_sock);

    char command[256];
    // tramit to server
    while(1) {
    
        scanf(" %[^\n]s", command);
        sleep(1);
        write(conn_sock, command, sizeof(command));
        
    }
        close(conn_sock);
        return 0;
}