#include <stdio.h>
#include <stdlib.h>

#ifndef PASSWORD_H
#define PASSWORD_H
  typedef struct password{
    char account[30];
    char account_num[30];
    char name[30];
    char pwd[30];
    char lnk[2];
  } Password;//用Password代替struct类型
  
  void split_line( void );
  void show_operation( void );
  void show( Password *p, int nums );
  void list_all( Password *p );
  void new_password( Password *p );
  void change( Password *p );
  void my_delete( Password *p );
  void search( Password *p );
  int addPasswordIntoClipboard( int pwdnum, Password *p );
  void password_panel( Password *p_pwd );

#endif