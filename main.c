#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.h"
#include "fileoperation.h"
#define DEBUG 0


// gcc main.c password.c password.h fileoperation.h fileoperation.c
int main(){
    system("chcp 65001 > nul");
    system("title pwd");
    welcome();
    
    FILE *file = NULL;
    file_panel(file);
 
    return 0;
}