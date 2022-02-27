#ifndef CONFIG_H
#define CONFIG_H


    #define MAX_CONFIG_LENGTH 50
    #define MAX_FILE_PATH_LEN 100


    /************************************/
    extern char file_path[MAX_FILE_PATH_LEN];
    extern char file_name[100];
    extern int Language;
    extern int SplitLineStyle;
    /************************************/

    typedef struct configList{
        char config[MAX_CONFIG_LENGTH];
        char mode[MAX_CONFIG_LENGTH];
        struct configList *next;
    } ConfigList;

    ConfigList *read_config( void );
    void list_config( ConfigList *cp );
    void set_config( ConfigList *cp );
    ConfigList *change_config( ConfigList *cp );
    void save_config( ConfigList *cp );
    void config_panel( void );


#endif