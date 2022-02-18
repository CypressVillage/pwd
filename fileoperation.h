#ifndef FILEOPERATION_H
#define FILEOPERATION_H

    #include <stdio.h>
    #include <stdlib.h>
    #include "password.h"

    #define MAX_FILE_PATH_LEN 100


    void dbg( char* tosay );
    void welcome( void );
    void show_file_operation( void );
    void my_exit( void );
    void list_file( void );

    FILE *create_file( FILE *file );
    FILE *select_file( FILE *file );
    Password *read_file( FILE *file );
    void save_file( Password *ppwd );
    FILE *file_panel( FILE *file );

#endif