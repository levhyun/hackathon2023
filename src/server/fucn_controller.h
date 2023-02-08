/* func */
// utils-server.h
void push_data(char *table, char *list) {
    // printf("Table name : |%s|\nlist value : |%s|\n", table, list);

    struct {
        char name[256];
        char value[256];
    } propertyInfo[256];

    struct {
        char str[256];
    } property[256];
    int count = 0;
    int pre = 0;

    for(int i = 0; i < strlen(list); i++){
        if(list[i] == '^') {
            pre = 0;
            count++;
        } else {
            property[count].str[pre++] = list[i];
        }
    }

    // for(int i = 0; i < count; i++){
    //     printf("str : %s\n", property[i].str);
    // }
    
    int bool = 0;
    for(int i = 0; i < count; i++){
        for(int j = 0; j < strlen(property[i].str); j++){
            if(bool == 1) {
                propertyInfo[i].value[j] = property[i].str[j];
            } else {
                if(property[i].str[j] == ',') {
                    bool+=1;
                } else {
                    propertyInfo[i].name[j] = property[i].str[j];
                }
            }
        }
        bool = 0;
    }

    // for(int i = 0; i < count; i++){
    //     printf("name : ");
    //     for(int j = 0; j < strlen(property[i].str); j++){
    //         printf("%c", propertyInfo[i].name[j]);
    //     }
    //     printf(", value : ");
    //     for(int j = 0; j < strlen(property[i].str); j++){
    //         printf("%c", propertyInfo[i].value[j]);
    //     }
    //     printf("\n");
    // }

    FILE *fileHandle;
    for(int i = 0; i < count; i++){
        char command[1024];
        sprintf(command, "./../database/%s/%s.txt", table, propertyInfo[i].name);            
        // printf("command : %s\n", command);
        if (fileHandle = fopen(command, "w+")) {
            for(int j = 2; j < strlen(property[i].str); j++){
                fputc(propertyInfo[i].value[j], fileHandle);
            }
            fclose(fileHandle);
        }
    }
}

void rm_rf(char *table) {
    char *tableData = get_table_data(table);

    struct {
        char name[256];
    } propertyInfo[256];

    struct {
        char str[256];
    } property[256];
    int count = 0;
    int pre = 0;

    for(int i = 0; i < strlen(tableData); i++){
        if(tableData[i] == '^') {
            pre = 0;
            count++;
        } else {
            property[count].str[pre++] = tableData[i];
        }
    }
    
    int bool = 0;
    for(int i = 0; i < count; i++){
        for(int j = 0; j < strlen(property[i].str); j++){
            if(bool == 0) {
               if(property[i].str[j] == ',') {
                    bool+=1;
                } else {
                    propertyInfo[i].name[j] = property[i].str[j];
                }
            }
        }
        bool = 0;
    }

    // for(int i = 0; i < count; i++){
    //     printf("name : %s|\n", propertyInfo[i].name);
    // }

    FILE *fileHandle;
    for(int i = 0; i <= count; i++){
        char command[1024];
        sprintf(command, "./../database/%s/%s.txt", table, propertyInfo[i].name);            
        if (fileHandle = fopen(command, "w+")) {
            fputs(" ", fileHandle);
            fclose(fileHandle);
        }
    }
}

int check(char *table, char *file) {
    char *list = get_table_data(table);

    struct {
        char name[256];
        char value[256];
    } propertyInfo[256];

    struct {
        char str[256];
    } property[256];
    int count = 0;
    int pre = 0;

    for(int i = 0; i < strlen(list); i++){
        if(list[i] == '^') {
            pre = 0;
            count++;
        } else {
            property[count].str[pre++] = list[i];
        }
    }
    
    int bool = 0;
    for(int i = 0; i < count; i++){
        for(int j = 0; j < strlen(property[i].str); j++){
            if(bool == 1) {
                propertyInfo[i].value[j] = property[i].str[j];
            } else {
                if(property[i].str[j] == ',') {
                    bool+=1;
                } else {
                    propertyInfo[i].name[j] = property[i].str[j];
                }
            }
        }
        bool = 0;
    }

    for(int i = 0; i <= count; i++) {
        if(!strcmp(file, propertyInfo[i].name)){
            if(propertyInfo[i].value[2] == ' '){
                return 0;
            } else { 
                return 1;
            }
        }
    }
}

void start_create(char *option1, char *option2) {

    printf("[+] create 명령 시작\n");
    // printf("[+] run create command \noption1 : %s, optino2 : %s\n\n",option1, option2 );
    char mkdir[256];
    
    
    sprintf(mkdir, "mkdir ./../database/%s", option1);
    system(mkdir);

    struct optionStruct {
        char option[256];
    } optionList[256];

    int cnt = 0; 
    int index = 0;

    for (int i = 0; i < strlen(option2); i++) {
        if (option2[i] == ',') {
            index = 0;
            cnt++;
        } else {
            optionList[cnt].option[index++] = option2[i]; 
        }
    }   

    
    
    for(int i = 0; i <= cnt; i++) {
        char str[256];
        char *p = str;
        for (int j = 0; j < strlen(optionList[i].option); j++) {
            str[j] = optionList[i].option[j];
        }
        char  touch[BUF_SIZE];
        sprintf(touch, "touch ./../database/%s/%s.txt", option1, p);
        
        system(touch); 
        sprintf(touch, "./../database/%s/%s.txt", option1, p);
        FILE * fp;
        if(fp = fopen(touch, "w+") ) {
            fputs(" ", fp);
        }
        fclose(fp);
    }

    

    char config_command[256];
    
    FILE * config_file = fopen("config.txt","w");
    if(config_file == NULL) 
    {
        puts("[-] config 파일을 생성할 수 없습니다.");
    }
    else 
    {
        puts("[+] config 파일을 생성합니다.");
    }
    
    for(int i = 0; i < cnt; ++i) {
        fputs(optionList[i].option, config_file);
        fputs(",", config_file);
    }
        fputs(optionList[cnt].option, config_file);

    fclose(config_file);

    sprintf(mkdir, "mv config.txt ./../database/%s/", option1);
    system(mkdir);
    printf("[+] create 명령 완료\n");
}   

/* 테이블을 생성한 뒤, config 파일을 명세합니다. */
// A,0,1,2,3,4,5,X,7,8,9^B,0,1,2,3,4,5,6,7,8,9^C,0,1,2,3,4,5,6,7,8,9^
void start_insert(char *table, char *command) {

    // printf("Table name : |%s|\ncommand : |%s|\n", table, command);

    struct { // 원래 구조체
        char name[256];
        char value[256];
    } propertyInfo[256];

    struct {
        char str[256];
    } property[256];
    int count = 0;
    int pre = 0;

    for(int i = 0; i < strlen(command); i++){
        if(command[i] == ',') {
            pre = 0;
            count++;
        } else {
            property[count].str[pre++] = command[i];
        }
    }

    // for(int i = 0; i <= count; i++){
    //     printf("str : %s\n", property[i].str);
    // }
    
    int bool = 0;
    for(int i = 0; i <= count; i++){
        for(int j = 0; j < strlen(property[i].str); j++){
            if(bool == 1) {
                propertyInfo[i].value[j] = property[i].str[j];
            } else {
                if(property[i].str[j] == ':') {
                    bool+=1;
                } else {
                    propertyInfo[i].name[j] = property[i].str[j];
                }
            }
        }
        bool = 0;
    }

    // for(int i = 0; i <= count; i++){
    //     printf("name : ");
    //     for(int j = 0; j < strlen(property[i].str); j++){
    //         printf("%c", propertyInfo[i].name[j]);
    //     }
    //     printf(", value : ");
    //     for(int j = 0; j < strlen(property[i].str); j++){
    //         printf("%c", propertyInfo[i].value[j]);
    //     }
    //     printf("\n");
    // }

    FILE *fileHandle;
    for(int i = 0; i <= count; i++){
        char command[1024];
        sprintf(command, "./../database/%s/%s.txt", table, propertyInfo[i].name);            
        // printf("command : %s\n", command);
        if(check(table, propertyInfo[i].name)) {
            fileHandle = fopen(command, "a");
            for(int j = 2; j < strlen(property[i].str); j++){
                fputc(',', fileHandle);
                fputc(propertyInfo[i].value[j], fileHandle);
            }
            fclose(fileHandle);
        }else {
            fileHandle = fopen(command, "w+");
            for(int j = 2; j < strlen(property[i].str); j++){
                fputc(propertyInfo[i].value[j], fileHandle);
            }
            fclose(fileHandle);
        }
    }
    


    

}

void start_delete(char *option1, char *option2) {
    

    if(same_str(option2, "*")) { /* delete {"table"} ["*"] */
        rm_rf(option1);
    } 

    else { /* select {"table"} ["index"]*/
        // 구현부
    }

}

void start_select(char *option1, char *option2) {

    char *list = get_table_data(option1);
    // printf("%s", list);

    if(same_str(option2, "*")) { /* select {"table"} ["*"] */
        trasmit_to_clnt_by_gui(delete_space(list));
    } 

    else { /* select {"table"} ["index"]*/
        // 구현부
    }
    
}

void start_update(char *option1, char *option2) {
    char command[1024];
    sprintf(command, "mv ./../database/%s ./../database/%s", option1, option2);
    system(command);
}
/* main */
void choose_funcs(char *command, char *option) {
    
    char *option1 = get_option1(option);
    char *option2 = get_option2(option);

    // printf("[t] option1 : %s, optino2 : %s\n", option1, option2);

    if(same_str(command, "create"))
        start_create(option1, option2);

    else if(same_str(command, "insert"))
        start_insert(option1, option2);

    else if(same_str(command, "update"))
        start_update(option1, option2);


    else if(same_str(command, "delete"))
        start_delete(option1, option2);

    else if(same_str(command, "select"))
        start_select(option1, option2);

}

