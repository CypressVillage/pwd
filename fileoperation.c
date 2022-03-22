#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include "fileoperation.h"
#include "password.h"
#include "config.h"


extern char file_path[MAX_FILE_PATH_LEN];
extern char file_name[100];
int password_num; // the num include passwords to delete

void dbg( char* tosay ){
    static int debugtime = 1;
    printf("debug:(%d)->%s\n",debugtime,tosay);
    debugtime ++;
}


void show_file_operation( void ){
    
    switch(Language){
        case 0:{
            printf("1: 文件列表\t");
            printf("2: 选择文件\t");
            printf("3: 新建文件\t");
            printf("\n");
            printf("4: 文件更名\t");
            printf("5: 删除文件\t");
            printf("8: 程序设置\t");
            printf("\n");
            printf("9: 查看操作\t");
            printf("0: 退出系统\t");
            printf("\n");
            break;
        }
        case 1:{
            printf("%-20s","1:list file");
            printf("%-20s","2:select file");
            printf("%-20s","3:create file");
            printf("\n");
            printf("%-20s","5:delete file");
            printf("%-20s","8:settings");
            printf("%-20s","9:show operation");
            printf("\n");
            printf("%-20s","0:exit");
            printf("\n");
            break;
        }
    }


}


void my_exit( void ){
    system("title 命令提示符");
    system("chcp 936 > nul");
    exit(EXIT_SUCCESS);
}


void welcome( void ){
    switch (Language){
        case 0: printf("欢迎使用 @pwd@ 密码系统~\n"); break;
        case 1: printf("welcom to use @pwd@~\n"); break;
    }
}


void list_file( void ){
    printf("\n");

    char *f_path = strcat( get_file_path(), "*.txt" );
    // system("for &i in (*.txt) do echo &i");
    __int64 Handle;
    int txt_num = 1;
    struct __finddata64_t FileInfo;
    if( (Handle = _findfirst64( f_path, &FileInfo)) == -1L ){
        printf("没有找到文件\n");
    }else{
        printf("%s\n", FileInfo.name);
        while( _findnext64(Handle, &FileInfo) == 0 ){
            txt_num ++;
            printf("%s\n", FileInfo.name);
        }
        _findclose(Handle);
        printf("\n共找到%d条结果\n", txt_num);
    }

    getchar();
}


void password_plus( void ){
    printf("please enter your password:\n");
    char *input = malloc( 100 * sizeof(char) );
    scanf("%s", input);
    if(strcmp( input, PasswordPlus ))
        my_exit();
}


void change_password_plus( void ){
    printf("please enter the new password:\n");
    scanf("%s",PasswordPlus);
}


char *get_file_path( void ){
    char *total_path = malloc( MAX_FILE_PATH_LEN * sizeof(char) );
    strcpy( total_path, file_path );
    return total_path;
}


FILE *create_file( FILE *file ){

    printf("请输入文件名:");
    scanf("%s",file_name);

    char *total_path = strcat( strcat( get_file_path(), file_name ), ".txt" );

    file=fopen( total_path , "w+" );
    printf("创建成功!\n");
    return file;
}


void remove_file( void ){
    // printf("please input the filename youwant to remove:\n");
    printf("请选择要删除的文件:\n");
    scanf("%s", file_name);

    char *total_path = strcat( strcat( get_file_path(), file_name ), ".txt");

    if( !remove(total_path) ){
        // printf("file removed!\n");
        printf("文件已删除!\n");
    }else{
        // printf("file not exit\n");
        printf("文件不存在\n");
    }
}


void rename_file( void ){
    // printf("please input the filename youwant to remove:\n");
    printf("请选择要更改的文件:\n");
    char *total_path = strcat( strcat( get_file_path(), file_name ), ".txt");
    scanf("%s", file_name);

    printf("请选择新的文件名:\n");
    char *name_to_change = malloc(_MAX_FNAME);
    scanf("%s", name_to_change);
    char *new_file_path = strcat( strcat( get_file_path(), name_to_change ), ".txt");

    if( !rename(total_path, new_file_path) ){
        // printf("file changed!\n");
        printf("更改成功!\n");
    }else{
        // printf("file not exit\n");
        printf("文件不存在\n");
    }
}


/*
    after this function, the file is opening
    close is in function "read_file"
*/
FILE *select_file( FILE *file ){

    // printf("please select file\n");
    printf("请选择文件:\n");
    scanf("%s",file_name);

    char *total_path = strcat( strcat( get_file_path(), file_name ), ".txt");

    if( (file=fopen( total_path, "r+" )) == NULL ){
        printf("文件%s.txt不存在,是否创建? (y&n)\n", file_name);
        // printf("file\"%s.txt\"is not exit, make one? (y&n)\n", file_name);

        char isCreate = 'y';
        scanf("\n");// clean the buffer, but I don't know why it must be write here
        scanf("%c", &isCreate );
        if( isCreate == 'y' ){
            file=fopen( total_path , "w+" );
            printf("创建成功!\n");
            return file;
        }else if ( isCreate == 'n' ){
            return NULL;
        }else{
            printf("undefined input\n");
            return NULL;
        }
        
    }else{
        printf("打开成功!\n");
        return file;
    }
}


Password *read_file( FILE *file ){
    Password *pwd = malloc( 100 * sizeof(Password) ), *ppwd = pwd;
    int line_num = 1;//行号
    while( !feof(file) ){ 
        switch( line_num % 5 ){
            case 1: {fscanf( file, "%s", ppwd->account ); break;}
            case 2: {fscanf( file, "%s", ppwd->account_num ); break;}
            case 3: {fscanf( file, "%s", ppwd->name ); break;}
            case 4: {fscanf( file, "%s", ppwd->pwd ); break;}
            case 0: {fscanf( file, "%s", ppwd->lnk ); ppwd++; break;}
        }
        line_num ++;
    }
    password_num = line_num/5;//已有密码条数
    fclose( file );
    return pwd;
}


void save_file( Password *ppwd ){

    char *total_path = strcat( strcat( get_file_path(), file_name ), ".txt");
    FILE *file = fopen( total_path, "w" );

    int f_num = password_num, line_num = 1;
    while( f_num ){

        // delete
        if( !strcmp( ppwd->account, "todelete" ) ){
            ppwd ++;
            f_num --;
            continue;
        }

        switch( line_num % 5 ){
          case 1: {fprintf( file, "%s\n", ppwd->account ); break;}
          case 2: {fprintf( file, "%s\n", ppwd->account_num ); break;}
          case 3: {fprintf( file, "%s\n", ppwd->name ); break;}
          case 4: {fprintf( file, "%s\n", ppwd->pwd ); break;}
          case 0: {fprintf( file, "%s\n", ppwd->lnk ); ppwd ++; f_num--; break;}
        }

        line_num ++;
    }

    fclose( file );
    printf("保存成功\n");
}


FILE *file_panel( FILE *file ){
    if(IsCls) system("cls");
    welcome();
    split_line();
    show_file_operation();
    
    int mode = 0;
    while(1){
        fflush(stdin);
        split_line();
        // printf("please select mode:\n");
        printf("请选择操作:\n");

        scanf("%d", &mode);
        switch ( mode ){
            case 1: { list_file(); break;}
            case 2: {
                file = select_file( file );
                if(file==NULL) break;
                Password *p = read_file(file);
                password_panel( p );
                break;
            }
            case 3: {
                file = create_file(file);
                Password *p = read_file(file);
                password_panel( p );
                break;
            }
            case 4: {rename_file(); break;}
            case 5: {remove_file(); break;}
            case 8: {ConfigList *cp = read_config(); config_panel(cp); break;}
            case 9: {show_file_operation(); break;}
            case 0: {my_exit(); break;}
            default:{printf("undefined mode\n"); break;}
        }

    }
    
}