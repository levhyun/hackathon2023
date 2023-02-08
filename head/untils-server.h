#ifndef UNTILS_H
# define UNTILS_H

/* 함수 원형 */
void error_handling(char *message);
char *delete_space(char *arg_str);
char *get_command(char *argCommand);
char *get_option(char *argCommand);

// 다음의 함수는 func_controll에서 사용합니다. 
    int same_str(char *str1, char *str2);
    void trasmit_to_clnt_by_gui(char *str);
    char *get_option1(char *option);
    char *get_option2(char *option);    
    void clean_char_arr(char *str);
    char *get_index_option2(char *option2, int get_index);
    char *get_table_data(char *table);
    char *convert_gui(char *list);  
    void push_data(char *table, char *list);


/* 함수 구현부 */
void error_handling(char *message){
	
    // stderr : 표준에러장치
	fputs(message, stderr);
    fputc('\n', stderr);
    
    exit(1);
}

char *delete_space(char *arg_str) {
    char *str = (char *)malloc(sizeof(char) * strlen(arg_str));
    int i, k = 0;
    
    for(i = 0; i < strlen(arg_str); i++)
        if(arg_str[i] != ' ') str[k++] = arg_str[i]; 

    str[k] = '\0';
    return str;
}

char *get_command(char *argCommand) {
    argCommand = delete_space(argCommand);

    static char local_command[256];

    for(int i = 0; i < 256; ++i) 
        local_command[i] = '\0';

    for(int i = 0; i < strlen(argCommand); i++){
        if(argCommand[i] == '{') {
            break;
        } else {
            local_command[i] = argCommand[i];
        }
    }
    return local_command;
}

char *get_option(char *argCommand) {
    argCommand = delete_space(argCommand);

    static char local_option[256];

    for(int i = 0; i < 256; ++i) 
        local_option[i] = '\0';

    for(int i = 0; i < strlen(argCommand); i++){
        if(argCommand[i] == '{') {
            for(int j = i; j < strlen(argCommand); j++) {
                local_option[j-6] = argCommand[j];
            }
            break;
        }
    }
    return local_option;
}




/* func */
int same_str(char *str1, char *str2) {
    return !(strcmp(str1, str2));
}

void trasmit_to_clnt_by_gui(char *str) {
    

    printf("[+] trasmit to client by gui\n");
    write(clnt_sock, str, sizeof(long) * strlen(str));

}

char *get_option1(char *option) {
    static char option1[256];
    int option_idx = 0;
    for(int i = 0; i < 256; ++i) 
        option1[i] = '\0';
    
   

    for(int i = 2;; ++i) {
        if(option[i] == '"') break;
        option1[option_idx++] = option[i]; 
    }

    return option1;
}

char *get_option2(char *option) {

    static char option2[256];

    int option_idx = 0;
    int start_idx = 0;
 
        for(int i = 0; i < 256; ++i) 
        option2[i] = '\0';
    
  
    for(int i = 1;;++i) {
        if(option[i] == '}') {
            start_idx = i+2;
            break;
        } 
    }

    for(int i = start_idx;; ++i) {
        if((option[i] == '"' && option[i+1] == ']')  == 1) {
            // option2[option_idx] = ';';
            break;
        }
        if(option[i] == '"') continue;
        option2[option_idx++] = option[i];

    }

    return option2;
}

void clean_char_arr(char *str) {
    int strlen_str = strlen(str);
    for(int i = 0; i < strlen_str; ++i) {
        str[i] = '\0';
    } 
}

char *get_index_option2(char *option2, int get_index) {
    static char word[256];

    for(int i = 0; i < 256; ++i) 
        word[i] = '\0';

    int go_cnt = 0;
    int start_index = 0;
    int cnt_index = 0;
        for(int i = 0;;++i) {
            if(go_cnt == get_index) break;
            if(option2[i] == ',') go_cnt++;
            start_index++;

        }

    for(int i = start_index;;++i) {
        if(option2[i] == ',' || option2[i] == ';') break;
        word[cnt_index++] = option2[i];
    }
    
    return word;
}

char *get_table_data(char *table) {
    // printf("[get_table_data(\"%s\")]\n", table);

    struct{
        char fileName[256];
    }fileList[256];
    int pre = 0;
    int fileCount = 0;

    FILE *fileHandle;
    char readFile[256];
    char fileValue[1024];

    sprintf(readFile, "./../database/%s/config.txt", table);
                       
    if (fileHandle = fopen(readFile, "r")) {
        fgets(fileValue, sizeof(fileValue), fileHandle);
        fclose(fileHandle);
    }
    // printf( "read config.txt : %s|\n", fileValue);

    //////////////////////////////////////////////////////////

    for(int i = 0; i < strlen(fileValue); i++){
        if(fileValue[i] == ',') {
            fileCount++;
            pre = 0;
        } else {
            fileList[fileCount].fileName[pre++] = fileValue[i];
        }
    }

    // printf("file name list fatch : |");
    // for(int i = 0; i <= fileCount; i++) {
    //     printf("%s|", fileList[i].fileName);
    // }
    // printf("\n");

    ////////////////////////////////////////////////////////////

    static char list[256] = "";
    for(int i = 0; i < 256; ++i) list[i] ='\0';
    for(int i = 0; i <= fileCount; i++){
        char command[512];
        sprintf(command, "./../database/%s/%s.txt", table, fileList[i].fileName);
        // printf("%s| : ", command);
                           
        char value[512];
        if (fileHandle = fopen(command, "r")) {
            fgets(value, sizeof(value), fileHandle);
            fclose(fileHandle);
        }
        // printf("%s|\n", value);

        char push[1024];
        if(value) {
            sprintf(push, "%s,%s^", fileList[i].fileName, value);
            strcat(list,push);
        } else {
            sprintf(push, "%s,^", fileList[i].fileName);
            strcat(list,push);
        }
    }

    // printf("final list : %s\n", list);

    return list;
}

char *convert_gui(char *list) {
    static char return_str[256/*속성*/][256/*원소*/];
    // A,1,2,3^B,1,2,3^C,1,2,3,4,4,5^

    for(int i = 0; i < 256; ++i) {
        for(int j = 0; j < 256; ++j) {
            return_str[i][j] = '\0';
        }
    }

    int attr_idx = 0; // i
    int elet_idx = 0; // j

    for (int i = 0; i < strlen(list); ++i) {

        if(list[i] == '^') {
            attr_idx ++;
            elet_idx = 0;
        } else 

        if(list[i] != ',') {
            return_str[attr_idx][elet_idx++] = list[i];
        }
    }

    // for(int i = 0; i < 10; ++i) {
    //     for(int j = 0; j < 10; ++j) {
    //         printf("%c ", return_str[j][i]);
    //     }
    //     printf("\n");
    // }
    return (char *) return_str;
}



#endif
