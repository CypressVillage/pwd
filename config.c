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
char *PasswordPlus = "1";
int IsEnablePasswordPlus = 0;
int Language = 0;
char *SplitLineStyle = "---";
int IsDeveloperMode = 0;
int IsCls = 0;
/*******************************/

void show_config_operation( void ){
    switch (Language){
        case 0:
            printf("%-20s","1: 查看设置");
            printf("%-20s","2: 更改设置");
            printf("%-20s","3: 恢复出厂");
            printf("\n");
            printf("%-20s","6: 更新设置");
            printf("%-20s","7: 应用设置");
            printf("%-20s","8: 保存设置");
            printf("\n");
            printf("%-20s","9: 查看操作");
            printf("%-20s","0: 退出系统");
            printf("%-20s","-: 返回上级");
            printf("\n");

            if(IsDeveloperMode){
                printf("%-16s","l: list config");
                printf("%-16s","p: show path");
                printf("%-16s","c: change password plus");
                printf("\n");
            }
            break;

        default:
            break;
    }
}


void show_all_config(void){
    printf("语言:");
    if(Language){printf("英文\n");} else{printf("中文\n");}
    printf("分割线样式:");
    if(!strcmp(SplitLineStyle, "---")) printf("---\n");
    if(!strcmp(SplitLineStyle, "num")) printf("数字\n");
}


ConfigList *read_config( void ){

    char *total_path = strcat( get_file_path(), "config.pwd" );

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
        /*****************************************************************************/
        if( !strcmp(cp->config, "Language") ){
            if( !strcmp(cp->mode,"Chinese") ) Language = 0;
            if( !strcmp(cp->mode,"English") ) Language = 1;
        }
        if( !strcmp(cp->config, "SplitLineStyle") ){
            if( !strcmp(cp->mode,"---") ) SplitLineStyle = "---";
            if( !strcmp(cp->mode,"Number") ) SplitLineStyle = "num";
        }
        if( !strcmp(cp->config, "IsEnablePasswordPlus") ){
            if( !strcmp(cp->mode,"false") ) IsEnablePasswordPlus = 0;
            if( !strcmp(cp->mode,"true") ) IsEnablePasswordPlus = 1;
        }
        if( !strcmp(cp->config, "PasswordPlus") ){
            PasswordPlus = malloc( 100 * sizeof(char) );
            strcpy( PasswordPlus, cp->mode );
        }
        if( !strcmp(cp->config, "IsCls") ){
            if( !strcmp(cp->mode,"false") ) IsCls = 0;
            if( !strcmp(cp->mode,"true") ) IsCls = 1;
        }
        /*****************************************************************************/
        cp = cp->next;
    }
}


/*a panel to user, to change global vars*/
ConfigList *change_config( ConfigList *cp ){}


/*read global vars, create a new config list*/
ConfigList *refresh_config_list( void ){
    ConfigList *cp;
    if(Language != 0){
        cp->next = malloc(sizeof(ConfigList));
        strcpy(cp->config,"Languange");
        if(Language==1){
            strcpy(cp->mode,"Chinese");
        }
    }
    if(IsEnablePasswordPlus != 0){
        cp->next = malloc(sizeof(ConfigList));
        cp = cp->next;
        strcpy(cp->config,"IsEnablePasswordPlus");
        strcpy(cp->mode,"true");
    }
}


/*read config list into file*/
void save_config( ConfigList *cp ){
    char *total_path = strcat( get_file_path(), "config.pwd" );
    FILE *file = fopen( total_path, "w" );

    int line_num = 1;
    while( cp!=NULL ){

        switch( line_num % 2 ){
            case 1: {fprintf( file, "%s\n", cp->config ); break;}
            case 0: {fprintf( file, "%s\n", cp->mode ); cp=cp->next; break;}
        }

        line_num ++;
    }

    fclose( file );
    printf("保存成功\n");
}


void config_panel( ConfigList *cp ){
    if(IsCls) system("cls");
    printf("设置:\n");
    split_line();
    show_config_operation();

    int mode = 0;
    while(1){
        fflush(stdin);
        split_line();
        printf("请选择操作:\n");

        scanf("%c", &mode);
        switch(mode){
            case '1':{ show_all_config(); break;}
            case '2':{  break;}
            case '3':{  break;}
            case '4':{  break;}
            case '7':{ set_config(cp); break;}
            case '8':{ save_config(cp); break;}
            case '9':{ show_config_operation(); break;}
            case '0':{ my_exit(); break;}
            case '-':{ FILE *file = NULL; file_panel( file ); break;}
            case '`':{ IsDeveloperMode = 1; break;}
            case 'l':{ if(IsDeveloperMode) list_config(cp); break;}
            case 'p':{ if(IsDeveloperMode) {printf(get_file_path()); printf("\n");}break;}
            case 'c':{ if(IsDeveloperMode) change_password_plus(); break;}
            default: break;
        }

    }

}