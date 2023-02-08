// #include "./../../head/define.h"
// char command[BUF_SIZE] = " ";
// char option[BUF_SIZE] = " ";

// char strCut(int startIndex, char *argCommand) {
//     for(int i = startIndex; i < strlen(argCommand); i++) {
//         option[i-6] = argCommand[i];
//     }
// }

// char *error(char *argCommand, char *return_command, char *return_option) {

//     argCommand = delete_space(argCommand);
//     // printf("error.h : argCommand : %s\n", argCommand);
//     // 문자열 처리
//     for(int i = 0; i < strlen(argCommand); i++){
//         if(i == strlen(argCommand)-1) {
//             return "[-0]command error";
//         }
//         if(argCommand[i] == '{') {
//             strCut(i, argCommand);
//             break;
//         } else {
//             command[i] = argCommand[i];
//         }
//     }

//     // printf("command : %s\noption : %s\n", command, option);

//     // 명령어 에러
//     char *commandList[5] = {"create","insert","select","update","delete"};
//     for(int i = 0; i < 5; i++) {
        
//         if(!strcmp(command,commandList[i])) {
//             //printf("command success\n");
//             break;
//         } else {
//             if(i == 4) return "[-1]command error";
//             // printf("%s != %s\n", command, commandList[i]);
//         }
//     }

//     // 명령어 구조에러
//     char list[BUF_SIZE] = "";
//     int top = -1;

//     for(int i = 0; i < strlen(option); i++){
//         if(option[i] == '{' || option[i] == '}' || option[i] == '[' || option[i] == ']') {
//             top++;
//             list[top] = option[i];
//         }
//     }

//     // printf("option fatch : %s\n", list);

//     if(!strcmp(list, "{}[]")) {
//         // printf("commend struct success\n");
//     } else {
//         return "[-2]error\n";
//     }

//     // printf("error : %p %p\n", command, option);
   
    
//     return "True";
// }




