#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"
#define DEBUG 0
/*-------------------------------------------------------------------------------------------*/
int main(){
    Password my_password[100];//my_pwd是一个struct password类型的数组 100为最大密码数，可以自行更改
    Password *ppwd = &my_password[0];
    char path[100] = "D://zbc//biancheng//Environment//my_environment//";
    char file_name[50] = "pwd_data.txt";

    // select file
    printf("please select file\n");
    scanf("%s",file_name);

    //读取文件里的内容

    //创建指向文件的指针
    FILE *file;
    if( (file=fopen( strcat( path, file_name ), "r+" )) == NULL ){
      printf("未找到文件%s,请自行创建\n", file_name);
      system("pause");
      exit(EXIT_FAILURE);
    }
    //按行读入文件到struct数组

    int line_num = 1;//行号

    while( !feof(file) ){ 
        switch( line_num % 5 ){
            case 1: {fscanf( file, "%s", ppwd->zhanghao );  break;}
            case 2: {fscanf( file, "%s", ppwd->zhanghu ); break;}
            case 3: {fscanf( file, "%s", ppwd->name ); break;}
            case 4: {fscanf( file, "%s", ppwd->pwd ); break;}
            case 0: {fscanf( file, "%s", ppwd->lnk ); ppwd ++; break;}
        }
        line_num ++;
    }
    int nums = line_num/5;//已有密码条数
    fclose( file );//关闭文件
    ppwd = my_password;//指向数组头部   
/*init words-----------------------------------------------------------------------*/
    printf("欢迎使用 @pwd@ 密码系统~\n");
    show_operation();
back:
    while(1){
        printf("-------------------------------------------------\n请选择操作:\n");
        int mode;
        scanf("%d",&mode);    
        switch( mode ){
            case 0: { printf("程序结束\n"); /*system("pause");*/ exit(EXIT_SUCCESS); }
            case 1: { list_all( my_password, nums ); break; }
            case 2: { search( my_password, nums ); break;}
            case 3: { store_password( my_password, nums ); nums++; break; }
            case 4: { change( my_password, nums ); break; }
            case 5: { my_delete( my_password, nums ); break; }
            case 8: { show_operation(); break; }
            case 9: { goto save; break; }
            default:{ printf("新功能开发中~(反正就是你非法输入了hhh)\n\n"); }
        } 
    }

save://文件指针作函数参数真不会用别骂了别骂了
    file=fopen( "D://zbc//biancheng//Environment//my_environment//pwd_data.txt", "w" );
    ppwd = my_password;//指向数组头部
    line_num = 1;
    while( *(ppwd->zhanghao)!='\0' ){ 
        // 这是没有实现的delete部分。。。菜菜菜
        // if( !strcmp("todelete",(char*)&(ppwd->zhanghao)) ){
        //   printf("zhixing");
        //   ppwd ++;
        //   // line_num ++;
        //   continue;
        // }
        switch( line_num % 5 ){
          case 1: {fprintf( file, "%s\n", ppwd->zhanghao ); break;}
          case 2: {fprintf( file, "%s\n", ppwd->zhanghu ); break;}
          case 3: {fprintf( file, "%s\n", ppwd->name ); break;}
          case 4: {fprintf( file, "%s\n", ppwd->pwd ); break;}
          case 0: {fprintf( file, "%s\n", ppwd->lnk ); ppwd ++; break;}
        }
        line_num ++;
    }
    fclose( file );
    printf("保存成功\n\n");
    goto back;  
    return 0;
}