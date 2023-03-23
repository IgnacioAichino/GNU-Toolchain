#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"



typedef struct Data{

    //Data for /proc/cpuinfo
    char *cpu_model;
    char *cpu_cores;
    char *cpu_threads;

    //Data for /proc/meminfo
    char *total;
    char *available;
    char *free;
    char *swap;

    //Data for /proc/version
    char *version;   
} Data;


//funtions in optionData.c
void setValueCPU(Data *data);
void setValueMemory(Data *data);
void setVersion(Data *data);
char* getInfoFile(const char *path, const char *characterist);
char* getVersion(const char *path);


//funtions in funtionsPrint.c
void option_a();
void option_s();
void print_cpu();
void print_memory();
void print_version();
void print_json(int flag_s, int flag_a);
void print_helpUser();


