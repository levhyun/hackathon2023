#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <string.h>

int clnt_sock;

#include "./../../head/define.h"
#include "./../../head/untils-server.h"

#include "error.h"
#include "fucn_controller.h"

/* 함수 원형 */
void *recv_to_clnt(void *arg);

/* MAIN */
int main(int argc, char* argv[]) {

    int serv_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    if(argc != 2) {
        printf("%s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1) 
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    if(listen(serv_sock, 5) == -1) 
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1) 
        error_handling("accept() error");

    printf("[ 🗔 ] Server Log\n");
    printf("[ ✔️ ] Server Start!a\n");
    printf("[ ✔️ ] 사용자 연결 완료 connect clint ip %s\n", inet_ntoa(clnt_addr.sin_addr));
    
    char command[BUF_SIZE];
    char table[BUF_SIZE], option[BUF_SIZE];
    int str_len;
    while(1) {
        
        str_len = read(clnt_sock, command, sizeof(command) - 1);      
        if(str_len == -1)
            error_handling("read() error");
            /* Command Filter */
            

            /* 에러 처리 코드 삽입*/

        choose_funcs(get_command(command), get_option(command));
    }
    close(serv_sock);
    close(clnt_sock);
    return 0;

}



