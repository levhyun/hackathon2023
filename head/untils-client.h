#ifndef UNTILS_H
# define UNTILS_H

/* 함수 원형 */
void error_handling(char *message);


/* 함수 구현부 */
void error_handling(char *message){
	
    // stderr : 표준에러장치
	fputs(message, stderr);
    fputc('\n', stderr);
    
    exit(1);
}

int same_str(char *str1, char *str2) {
    return !(strcmp(str1, str2));
}

#endif