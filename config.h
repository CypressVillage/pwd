#ifndef CONFIG_H
#define CONFIG_H
    // #include "cJSON.h"

    #define MAX_CONFIG_LENGTH 50
    #define MAX_FILE_PATH_LEN 100


    /*config list*/
    extern char file_path[MAX_FILE_PATH_LEN];
    extern char file_name[100];
    extern char *PasswordPlus;
    extern int IsEnablePasswordPlus;
    extern int Language;
    extern char *SplitLineStyle;
    extern int IsDeveloperMode;
    extern int IsCls;

    typedef struct configList{
        char config[MAX_CONFIG_LENGTH];
        char mode[MAX_CONFIG_LENGTH];
        struct configList *next;
    } ConfigList;

    void show_config_operation( void );
    void show_all_config(void);
    ConfigList *read_config( void );
    void list_config( ConfigList *cp );
    void set_config( ConfigList *cp );
    ConfigList *change_config( ConfigList *cp );
    ConfigList *refresh_config_list( void );
    void save_config( ConfigList *cp );
    void config_panel( ConfigList *cp );


#endif