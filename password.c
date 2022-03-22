#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "password.h"
#include "fileoperation.h"
#include "config.h"
#include "language.h"

extern int password_num;

void split_line( void ){
  if(!strcmp(SplitLineStyle, "---")) printf("----------------------------------------------------------------------\n");
  if(!strcmp(SplitLineStyle, "num")) printf("1234567890123456789012345678901234567890123456789012345678901234567890\n");
  if(!strcmp(SplitLineStyle, "nul")) printf("\n");
}


void show_operation( void ){
  switch(Language){
    case 0:{
      printf("密码列表: 1\t查找密码: 2\t新建密码: 3\n修改密码: 4\t删除密码: 5\t");
      printf("保存更改: 8\n查看操作: 9\t退出系统: 0\t返回上级: -\n");
      break;
    }
    case 1:{
      printf("%-20s","1: list password");
      printf("%-20s","2: search password");
      printf("%-20s","3: create password");
      printf("\n");
      printf("%-20s","4: change password");
      printf("%-20s","5: delete password");
      printf("%-20s","8: save password");
      printf("\n");
      printf("%-20s","9: show operation");
      printf("%-20s","0: exit");
      printf("%-20s","-: return");
      printf("\n");
      break;
    }
  }
}


void show( Password *p, int i ){
  switch(Language){
    case 0:{
      printf("账号%d:%s\n",i+1,p->account);
      printf("账户:%s\n",p->account_num);
      printf("昵称:%s\n",p->name);
      if(IsShowPassword){
        printf("密码:%s\n",p->pwd);
      }else{
        printf("密码:**********\n");
      }
      printf("快捷方式:%s\n\n",p->lnk);
      break;
    }
    case 1:{
      printf("account %d:%s\n",i+1,p->account);
      printf("account number:%s\n",p->account_num);
      printf("name:%s\n",p->name);
      if(IsShowPassword){
        printf("password:%s\n",p->pwd);
      }else{
        printf("password:**********\n");
      }
      printf("lnk:%s\n\n",p->lnk);
      break;
    }
  }

}


void list_all( Password *p ){
  for( int i=0; i<password_num; ++i ){
    show( p, i );
    p++;
  }
}


void new_password( Password *p ){
  
    language_1_new_password("请输入账号:",1);
    scanf("%s",&((p+password_num)->account));

    language_1_new_password("请输入账户:",2);
    scanf("%s",&((p+password_num)->account_num));   

    language_1_new_password("请输入昵称:",3);
    scanf("%s",&((p+password_num)->name));  

    language_1_new_password("请输入密码:",4);
    scanf("%s",&((p+password_num)->pwd));   

    language_1_new_password("请输入快捷数字:",5);
    scanf("%s",&((p+password_num)->lnk));   
    
    language_1_new_password("创建完成，记得保存哦~\n\n",6);
}


void search( Password *p ){
    language_1_search("请选择搜索类型:\n",1);
    language_1_search("快捷搜索: 1\t账号搜索: 2\n账户搜索: 3\t昵称搜索: 4\n",2);
    int search_mode;
    scanf("%d",&search_mode);

    language_1_search("请输入数据:",3);
    char input[30];
    scanf("%s",input);
    printf("\n");

    int flag = 0, is_find = 0;
    for( int i=0; i<password_num; ++i ){
        is_find = 0;
        switch(search_mode){
            case 1: { is_find = !strcmp(input,(char*)&(p->lnk)); break; }
            case 2: { is_find = !strcmp(input,(char*)&(p->account)); break; }
            case 3: { is_find = !strcmp(input,(char*)&(p->account_num)); break; }
            case 4: { is_find = !strcmp(input,(char*)&(p->name)); break; }
            default: printf("搜索模式不匹配\n\n");
        }
        if( is_find ){
          show( p, i );
          flag ++;
        }
        p++;
    }
    if(flag){
        printf("共找到%d条结果\n\n",flag);
    }else{
        printf("未找到结果\n\n");
    }   
}


void change( Password *p ){
    printf("请选择想要修改的账号\n");
    char input[30];
    scanf("%s",input);
    int flag = 0;//是否找到
    Password *q;//储存p
    for( int i=0; i<password_num; ++i ){
        if( !strcmp(input,(char*)&(p->account)) ){
            show( p, i );
            q = p;
            flag ++;
        }
        p++;
    }

    if(flag){
        printf("请选择要修改的内容:\n");
        printf("账号: 1\t账户: 2\n昵称: 3\t密码: 4\n快捷方式: 5\n");
        int mode;
        scanf("%d",&mode);
        printf("请输入修改后的内容:\n");
        switch( mode ){
            case 1: { scanf("%s",&(q->account)); break; }
            case 2: { scanf("%s",&(q->account_num)); break; }
            case 3: { scanf("%s",&(q->name)); break; }
            case 4: { scanf("%s",&(q->pwd)); break; }
            case 5: { scanf("%s",&(q->lnk)); break; }
            default: { printf("非法输入!\n"); }
        }
        printf("修改完毕，记得保存哦~\n\n");
    }else{
        printf("未找到结果\n\n");
    }

}


void my_delete( Password *p ){
    printf("请选择想要删除的账号\n");
    char input[30];
    scanf("%s",input);
    int flag = 0;//是否找到
    Password *q;//储存p
    for( int i=0; i<password_num; ++i ){
        if( !strcmp(input,(char*)&(p->account)) ){
            show( p, i );
            q = p;
            flag ++;
        }
        p++;
    }

    if(flag){
        strcpy(q->account,"todelete");
        printf("删除完毕，记得保存哦~\n\n");
    }else{
        printf("未找到结果\n\n");
    }
}


int addPasswordIntoClipboard( int pwdnum, Password *p ){
  int contentSize = strlen(p[pwdnum-1].pwd) + 1;
  HGLOBAL hMemory;
  LPTSTR lpMemory;
  if(!OpenClipboard(NULL)) return 0;
  if(!EmptyClipboard()) return 0;
  if(!(hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize))) return 0;
  if(!(lpMemory = (LPTSTR)GlobalLock(hMemory))) return 0;
  memcpy_s(lpMemory, contentSize, p[pwdnum-1].pwd, contentSize);
  GlobalUnlock(hMemory);
  if(!SetClipboardData(CF_TEXT, hMemory)) return 0;
  CloseClipboard();
  if(Language==0) printf("password copied\n");
  if(Language==1) printf("已复制\n");
  return 1;
}


void password_panel( Password *p_pwd ){
    if(IsCls) system("cls");
    printf("密码本: %s.txt\n", file_name);
    split_line();
    show_operation();
    Password *my_password = p_pwd;
    char mode = 0;
    while(1){
        fflush(stdin);
        split_line();
        // switch(Language)
        printf("请选择操作:\n");
        scanf("\n");
        scanf("%c",&mode);
        switch( mode ){
            case '1': { list_all( my_password ); break; }
            case '2': { search( my_password ); break;}
            case '3': { new_password( my_password ); password_num++; break; }
            case '4': { change( my_password ); break; }
            case '5': { my_delete( my_password ); break; }
            case '8': { save_file( my_password ); break; }
            case '9': { show_operation(); break; }
            case '0': { save_file( my_password ); my_exit(); break; }
            case '-': { FILE *file = NULL; file_panel( file ); break; }
            case 'c': { addPasswordIntoClipboard(getchar()-'0', my_password); break; }
            default:{ printf("新功能开发中~(反正就是你非法输入了hhh)\n\n"); }
        } 
    }
}