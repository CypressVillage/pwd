#include <stdlib.h>
#include "password.h"
#include "fileoperation.h"
#include "config.h"
#define DEBUG 0


// gcc main.c password.c password.h fileoperation.h fileoperation.c config.h config.c language.h language.c
int main(){
    system("chcp 65001 > nul");
    system("title pwd");

    ConfigList *cp = read_config();
    set_config(cp);
    free(cp);

    if(IsEnablePasswordPlus) password_plus();

    FILE *file = NULL;
    file_panel(file);
 
    return 0;
}