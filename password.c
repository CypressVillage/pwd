#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"

void show( Password *p, int i ){
  printf("�˺�%d��%s\n",i+1,p->zhanghao);
    printf("�˻���%s\n",p->zhanghu);
    printf("�ǳƣ�%s\n",p->name);
    printf("���룺%s\n",p->pwd);
    printf("��ݷ�ʽ��%s\n\n",p->lnk);
}

void list_all( Password *p, int nums ){
  for( int i=0; i<nums; ++i ){
    show( p, i );
    p++;
  }
}

void store_password( Password *p ,int nums ){
  
  printf("�������˺�:");
  scanf("%s",&((p+nums)->zhanghao));

  printf("�������˻�:");
  scanf("%s",&((p+nums)->zhanghu));

  printf("�������ǳ�:");
  scanf("%s",&((p+nums)->name));

  printf("����������:");
  scanf("%s",&((p+nums)->pwd));

  printf("������������:");
  scanf("%s",&((p+nums)->lnk));

  printf("������ɣ��ǵñ���Ŷ~\n\n");
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
    printf("���ҵ�%d�����\n\n",flag);
  }else{
    printf("δ�ҵ����\n\n");
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
    printf("���ҵ�%d�����\n\n",flag);
  }else{
    printf("δ�ҵ����\n\n");
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
    printf("���ҵ�%d�����\n\n",flag);
  }else{
    printf("δ�ҵ����\n\n");
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
    printf("���ҵ�%d�����\n\n",flag);
  }else{
    printf("δ�ҵ����\n\n");
  }
}

void search( Password *p, int nums ){
  printf("��ѡ����������:\n");
  printf("�������: 1\t�˺�����: 2\n�˻�����: 3\t�ǳ�����: 4\n");

  int search_mode;
  scanf("%d",&search_mode);
  printf("����������:");
  char input[30];
  scanf("%s",input);
  printf("\n");

  switch(search_mode){
    case 1: { search_by_lnk( input, p, nums ); break; }
    case 2: { search_by_zhanghao( input, p, nums ); break; }
    case 3: { search_by_zhanghu( input, p, nums ); break; }
    case 4: { search_by_name( input, p, nums ); break; }
    default: printf("����ģʽ��ƥ��\n\n");
  }
}

void change( Password *p, int nums ){
change_1:
  printf("��ѡ����Ҫ�޸ĵ��˺�\n");
  char input[30];
  scanf("%s",input);
  int flag = 0;//�Ƿ��ҵ�
  Password *q;//����p
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->zhanghao)) ){
      show( p, i );
      q = p;
      flag ++;
    }
    p++;
  }

  if(!flag){
    printf("δ�ҵ����\n\n");
    goto change_1;
  }

  printf("��ѡ��Ҫ�޸ĵ�����:\n");
  printf("�˺�: 1\t�˻�: 2\n�ǳ�: 3\t����: 4\n��ݷ�ʽ: 5\n");

  int mode;

select_mode:

  scanf("%d",&mode);
  printf("�������޸ĺ������:\n");
  switch( mode ){
    case 1: { scanf("%s",&(q->zhanghao)); break; }
    case 2: { scanf("%s",&(q->zhanghu)); break; }
    case 3: { scanf("%s",&(q->name)); break; }
    case 4: { scanf("%s",&(q->pwd)); break; }
    case 5: { scanf("%s",&(q->lnk)); break; }
    default: { printf("�Ƿ�����!\n��ѡ��Ҫ�޸ĵ�����:\n"); goto select_mode; }
  }
  printf("�޸���ϣ��ǵñ���Ŷ~\n\n");
}

void my_delete( Password *p, int nums ){
  del_1:
  printf("��ѡ����Ҫɾ�����˺�\n");
  char input[30];
  scanf("%s",input);
  int flag = 0;//�Ƿ��ҵ�
  Password *q;//����p
  for( int i=0; i<nums; ++i ){
    if( !strcmp(input,(char*)&(p->zhanghao)) ){
      show( p, i );
      q = p;
      flag ++;
    }
    p++;
  }

  if(!flag){
    printf("δ�ҵ����\n\n");
    goto del_1;
  }
  strcpy(q->zhanghao,"todelete");

  printf("ɾ����ϣ��ǵñ���Ŷ~\n\n");
}