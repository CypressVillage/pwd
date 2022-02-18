#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileoperation.h"
#include "password.h"
// #include "config.h"


/*
这里不加static会有奇怪的bug，dbg函数会打印奇怪的数字
*/
static char file_path[MAX_FILE_PATH_LEN] = "D://zbc//biancheng//Environment//my_environment//pwd//";
static char file_name[100] = "pwd_data";
int file_num;


void dbg( char* tosay ){
    static int debugtime = 1;
    printf("debug:(%d)->%s\n",debugtime,tosay);
    debugtime ++;
}


void show_file_operation( void ){
    
    printf("文件列表: 1\t");
    printf("选择文件: 2\t");
    printf("新建文件: 3\n");
    printf("删除文件: 5\t");
    printf("查看操作: 9\t");
    printf("退出系统: 0\n");

    // printf("1:list file\n");
    // printf("2:select file\n");
    // printf("3:delete file\n");
    // printf("9:show file operation\n");
    // printf("0:exit\n");
}


void my_exit( void ){
    system("title 命令提示符");
    system("chcp 936 > nul");
    exit(EXIT_SUCCESS);
}


void welcome( void ){
    // printf("welcom to use @pwd@~\n\n");
    printf("欢迎使用 @pwd@ 密码系统~\n\n");
}


void list_file( void ){
    system("for &i in *.txt do echo &i");
}


FILE *create_file( FILE *file ){
    char *f_path = malloc( MAX_FILE_PATH_LEN * sizeof(char) );
    strcpy( f_path, file_path );

    printf("请输入文件名:");
    scanf("%s",file_name);

    char *total_path = malloc( 200 * sizeof(char) );
    total_path = (char*)strcat( strcat( f_path, file_name ), ".txt");

    file=fopen( total_path , "w+" );
    printf("创建成功!\n");
    return file;
}


/*
    after this function, the file is opening
    close is in function "read_file"
*/
FILE *select_file( FILE *file ){

    // we can't change file_path
    char *f_path = malloc( MAX_FILE_PATH_LEN * sizeof(char) );
    strcpy( f_path, file_path );

    // printf("please select file\n");
    printf("请选择文件:\n");
    scanf("%s",file_name);

    char *total_path = malloc( 200 * sizeof(char) );
    total_path = (char*)strcat( strcat( f_path, file_name ), ".txt");

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
            case 1: {fscanf( file, "%s", ppwd->zhanghao ); break;}
            case 2: {fscanf( file, "%s", ppwd->zhanghu ); break;}
            case 3: {fscanf( file, "%s", ppwd->name ); break;}
            case 4: {fscanf( file, "%s", ppwd->pwd ); break;}
            case 0: {fscanf( file, "%s", ppwd->lnk ); ppwd++; break;}
        }
        line_num ++;
    }
    file_num = line_num/5;//已有密码条数
    fclose( file );
    return pwd;
}


// nums include to delete
void save_file( Password *ppwd ){
    char *f_path = malloc( MAX_FILE_PATH_LEN * sizeof(char) );
    strcpy( f_path, file_path );

    char *total_path = malloc( MAX_FILE_PATH_LEN * sizeof(char) );
    total_path = (char*)strcat( strcat( f_path, file_name ), ".txt");
    FILE *file = fopen( total_path, "w" );

    int f_num = file_num, line_num = 1;
    while( f_num ){

        // delete
        if( !strcmp( ppwd->zhanghao, "todelete" ) ){
            ppwd ++;
            f_num --;
            continue;
        }

        switch( line_num % 5 ){
          case 1: {fprintf( file, "%s\n", ppwd->zhanghao ); break;}
          case 2: {fprintf( file, "%s\n", ppwd->zhanghu ); break;}
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
    split_line();
    show_file_operation();
    
    int mode = 0;
    while(1){
        split_line();
        // printf("please select mode:\n");
        printf("请选择操作:\n");

        scanf("%d", &mode);
        switch ( mode ){
            case 1: { break;}
            case 2: {
                do{
                    file = select_file( file );
                }while( file == NULL );
                Password *p = read_file(file);
                password_panel( p );
                break;
            }
            case 3: {
                file = create_file(file);
                Password *p = read_file(file);
                password_panel( p );
            }
            case 5: {break;}
            case 9: {show_file_operation(); break;}
            case 0: {my_exit(); break;}
            default:{printf("undefined mode\n"); break;}
        }

    }
    
}