#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

typedef struct Datatypes
{
    char **types_filesys;
    int total_types;

} Datatypes;


void setTotal(Datatypes *data);
void setTypeFilesys(Datatypes *data);
char** getInfo(const char *path);
int getTotalTypes(const char *path);
void print_dinamicJson();

