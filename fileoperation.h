#ifndef FILEOPERATION_H
#define FILEOPERATION_H


    #include "password.h"


    void dbg( char* tosay );
    void welcome( void );
    void show_file_operation( void );
    void my_exit( void );
    void list_file( void );

    void password_plus( void );
    void change_password_plus( void );
    char *get_file_path( void );
    FILE *create_file( FILE *file );
    void remove_file( void );
    void rename_file( void );
    FILE *select_file( FILE *file );
    Password *read_file( FILE *file );
    void save_file( Password *ppwd );
    FILE *file_panel( FILE *file );

#endif