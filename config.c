#include <string.h>
#include <stdio.h>
#include "config.h"
#include "fileoperation.h"

/*******************************/
/*
*这里不加static会有奇怪的bug，dbg函数会打印奇怪的数字
*之前下面两句写在fileoperation.c文件里，有上面的错误，现在不知道错误是否仍然存在
*如你所见，现在他移动到了config.c文件里并去掉了static修饰符
*/
char file_path[MAX_FILE_PATH_LEN] = "D://zbc//biancheng//Environment//my_environment//pwd//";
char file_name[100] = "pwd_data";
int Language = 0;
int SplitLineStyle = 0;
/*******************************/

ConfigList *read_config( void ){

    char *total_path = malloc( 200 * sizeof(char) );
    strcpy( total_path, file_path );
    total_path = strcat( total_path, "config.pwd" );

    FILE *fp = fopen( total_path, "r" );
    if( fp == NULL ){
        printf("config.pwd is not exited, please create one\n");
        fclose(fp);
        return NULL;
    }else{
        int line_num = 1;
        ConfigList *cp = malloc(sizeof(ConfigList)), *head = cp;
        while( !feof(fp) ){

            switch(line_num%2){
                case 1: {
                    cp->next = malloc(sizeof(ConfigList));
                    cp = cp->next;
                    fscanf( fp, "%s", cp->config ); break;
                }
                case 0: {fscanf( fp, "%s", cp->mode ); break;}
            }
            line_num ++;
        }
        cp->next = NULL;
        cp = head->next;
        free(head);
        fclose(fp);
        return cp;
    }
}

void list_config( ConfigList *cp ){
    while(cp!=NULL){
        printf("%s:", cp->config);
        printf("%s\n", cp->mode);
        cp = cp->next;
    }
}

void set_config( ConfigList *cp ){
    while(cp!=NULL){
        /*******************************/
        if( !strcmp((char*)(cp->config), "Language") ){
            if( !strcmp((char*)(cp->mode),"Chinese") ) Language = 0;
            if( !strcmp((char*)(cp->mode),"English") ) Language = 1;
        }
        if( !strcmp((char*)(cp->config), "SplitLineStyle") ){
            if( !strcmp((char*)(cp->mode),"---") ) SplitLineStyle = 0;
            if( !strcmp((char*)(cp->mode),"Number") ) SplitLineStyle = -1;
        }


        /*******************************/
        cp = cp->next;
    }
}

ConfigList *change_config( ConfigList *cp ){}
void save_config( ConfigList *cp ){}
void config_panel( void ){}