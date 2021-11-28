#include <stdio.h>
#include <stdlib.h>

typedef struct{
  char zhanghao[30];
  char zhanghu[30];
  char name[30];
  char pwd[30];
  char lnk[2];
} Password;//用Password代替struct类型

void show( Password *p, int nums );
void list_all( Password *p, int nums );
void store_password( Password *p, int nums );
void change( Password *p, int nums );
void my_delete( Password *p, int nums );

void search_by_lnk( char *input, Password *p, int nums );
void search_by_zhanghao( char *input, Password *p, int nums );
void search_by_zhanghu( char *input, Password *p, int nums );
void search_by_name( char *input, Password *p, int nums );
void search( Password *p, int nums );