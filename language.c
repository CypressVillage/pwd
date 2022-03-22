#include <stdio.h>
#include "language.h"
#include "config.h"

void language_1_new_password(char *pre, int num){
    if( Language == 0 ) printf("%s",pre);

    if( Language == 1 ){
        switch(num){
            case 1: printf("please input your account:"); break;
            case 2: printf("please input your account number:"); break;
            case 3: printf("please input your nickname:"); break;
            case 4: printf("please input your password:"); break;
            case 5: printf("please input your lnk:"); break;
            case 6: printf("create finished, remember to save it!\n\n:"); break;
        }
    }
}

void language_1_search(char *pre, int num){
    if( Language == 0 ) printf("%s",pre);

    if( Language == 1 ){
        switch(num){
            case 1: printf("please input the search mode:\n"); break;
            case 2: 
                printf("%-20s","1: lnk");
                printf("%-20s","2: account");
                printf("\n");
                printf("%-20s","3: account number");
                printf("%-20s","4: nickname");
                printf("\n");
                break;
            case 3: printf("please input you want to search:"); break;
            case 4: printf("\n"); break;
            case 5: printf("\n"); break;
            case 6: printf("\n"); break;
        }
    }
}
