#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"
#define DEBUG 0
/*-------------------------------------------------------------------------------------------*/
int main(){
  Password my_password[100];//my_pwd��һ��struct password���͵����� 100Ϊ������������������и���
  Password *ppwd = &my_password[0];
  //��ȡ�ļ��������

  //����ָ���ļ���ָ��
  FILE *file;
  if( (file=fopen( "D://zbc//biancheng//Environment//my_environment//pwd_data.txt", "r+" )) == NULL ){
    printf("δ�ҵ��ļ�pwd_data.txt,�����д���\n");
    system("pause");
    exit(EXIT_FAILURE);
  }
  //���ж����ļ���struct����
  
  int line_num = 1;//�к�
  
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
  int nums = line_num/5;//������������
  fclose( file );//�ر��ļ�
  ppwd = my_password;//ָ������ͷ��

/*init words-----------------------------------------------------------------------*/
  printf("��ӭʹ�� @pwd@ ����ϵͳ~\n");
  printf("�����б�: 1\t��������: 2\t�½�����: 3\n�޸�����: 4\tɾ������: 5\t");
  printf("�鿴����: 8\n�������: 9\t�˳�ϵͳ: 0\n");

back:
  while(1){
    printf("-------------------------------------------------\n��ѡ�����:\n");
    int mode;
    scanf("%d",&mode);

    switch( mode ){
      case 0: { printf("�������\n"); /*system("pause");*/ exit(EXIT_SUCCESS); }
      case 1: { list_all( my_password, nums ); break; }
      case 2: { search( my_password, nums ); break;}
      case 3: { store_password( my_password, nums ); nums++; break; }
      case 4: { change( my_password, nums ); break; }
      case 5: { my_delete( my_password, nums ); break; }
      case 8: { printf("�����б�: 1\t��������: 2\t�½�����: 3\n�޸�����: 4\tɾ������: 5\t");
                printf("�鿴����: 8\n�������: 9\t�˳�ϵͳ: 0\n"); break; }
      case 9: { goto save; break; }
      default:{ printf("�¹��ܿ�����~(����������Ƿ�������hhh)\n\n"); }
    }

  }

save://�ļ�ָ�������������治���ñ����˱�����
  file=fopen( "D://zbc//biancheng//Environment//my_environment//pwd_data.txt", "r+" );
  ppwd = my_password;//ָ������ͷ��
  line_num = 1;
  while( *(ppwd->zhanghao)!='\0' ){ 
    // ����û��ʵ�ֵ�delete���֡������˲˲�
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
  printf("����ɹ�\n\n");
  goto back;

  return 0;
}