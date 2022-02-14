#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"

void show_operation( void ){
  printf("密码列表: 1\t查找密码: 2\t新建密码: 3\n修改密码: 4\t删除密码: 5\t");
  printf("查看操作: 8\n保存更改: 9\t退出系统: 0\n");
}

void show( Password *p, int i ){
  printf("账号%d：%s\n",i+1,p->zhanghao);
    printf("账户：%s\n",p->zhanghu);
    printf("昵称：%s\n",p->name);
    printf("密码：%s\n",p->pwd);
    printf("快捷方式：%s\n\n",p->lnk);
}

void list_all( Password *p, int nums ){
  for( int i=0; i<nums; ++i ){
    show( p, i );
    p++;
  }
}

void store_password( Password *p ,int nums ){
  
  printf("请输入账号:");
  scanf("%s",&((p+nums)->zhanghao));

  printf("请输入账户:");
  scanf("%s",&((p+nums)->zhanghu));

  printf("请输入昵称:");
  scanf("%s",&((p+nums)->name));

  printf("请输入密码:");
  scanf("%s",&((p+nums)->pwd));

  printf("请输入快捷数字:");
  scanf("%s",&((p+nums)->lnk));

  printf("创建完成，记得保存哦~\n\n");
}

void search_by_lnk( char *input, Password *p, int nums ){
  int flag = 0;
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->lnk)) ){
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

void search_by_zhanghao( char *input, Password *p, int nums ){
  int flag = 0;
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->zhanghao)) ){
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

void search_by_zhanghu( char *input, Password *p, int nums ){
  int flag = 0;
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->zhanghu)) ){
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

void search_by_name( char *input, Password *p, int nums ){
  int flag = 0;
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->name)) ){
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

void search( Password *p, int nums ){
  printf("请选择搜索类型:\n");
  printf("快捷搜索: 1\t账号搜索: 2\n账户搜索: 3\t昵称搜索: 4\n");

  int search_mode;
  scanf("%d",&search_mode);
  printf("请输入数据:");
  char input[30];
  scanf("%s",input);
  printf("\n");

  switch(search_mode){
    case 1: { search_by_lnk( input, p, nums ); break; }
    case 2: { search_by_zhanghao( input, p, nums ); break; }
    case 3: { search_by_zhanghu( input, p, nums ); break; }
    case 4: { search_by_name( input, p, nums ); break; }
    default: printf("搜索模式不匹配\n\n");
  }
}

void change( Password *p, int nums ){
change_1:
  printf("请选择想要修改的账号\n");
  char input[30];
  scanf("%s",input);
  int flag = 0;//是否找到
  Password *q;//储存p
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->zhanghao)) ){
      show( p, i );
      q = p;
      flag ++;
    }
    p++;
  }

  if(!flag){
    printf("未找到结果\n\n");
    goto change_1;
  }

  printf("请选择要修改的内容:\n");
  printf("账号: 1\t账户: 2\n昵称: 3\t密码: 4\n快捷方式: 5\n");

  int mode;

select_mode:

  scanf("%d",&mode);
  printf("请输入修改后的内容:\n");
  switch( mode ){
    case 1: { scanf("%s",&(q->zhanghao)); break; }
    case 2: { scanf("%s",&(q->zhanghu)); break; }
    case 3: { scanf("%s",&(q->name)); break; }
    case 4: { scanf("%s",&(q->pwd)); break; }
    case 5: { scanf("%s",&(q->lnk)); break; }
    default: { printf("非法输入!\n请选择要修改的内容:\n"); goto select_mode; }
  }
  printf("修改完毕，记得保存哦~\n\n");
}

void my_delete( Password *p, int nums ){
  del_1:
  printf("请选择想要删除的账号\n");
  char input[30];
  scanf("%s",input);
  int flag = 0;//是否找到
  Password *q;//储存p
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->zhanghao)) ){
      show( p, i );
      q = p;
      flag ++;
    }
    p++;
  }

  if(!flag){
    printf("未找到结果\n\n");
    goto del_1;
  }
  strcpy(q->zhanghao,"todelete");

  printf("删除完毕，记得保存哦~\n\n");
}

// void password_panel( Password *p_pwd ){
//   while(1){
//         printf("-------------------------------------------------\n请选择操作:\n");
//         int mode;
//         scanf("%d",&mode);    
//         switch( mode ){
//             case 0: { printf("程序结束\n"); /*system("pause");*/ exit(EXIT_SUCCESS); }
//             case 1: { list_all( my_password, nums ); break; }
//             case 2: { search( my_password, nums ); break;}
//             case 3: { store_password( my_password, nums ); nums++; break; }
//             case 4: { change( my_password, nums ); break; }
//             case 5: { my_delete( my_password, nums ); break; }
//             case 8: { show_operation(); break; }
//             case 9: { goto save; break; }
//             default:{ printf("新功能开发中~(反正就是你非法输入了hhh)\n\n"); }
//         } 
//     }
// }