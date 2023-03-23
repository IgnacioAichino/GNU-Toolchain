#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "structures.h"


void setValueCPU(Data *data){
    data->cpu_model= getInfoFile("/proc/cpuinfo", "model name");
    data->cpu_cores= getInfoFile("/proc/cpuinfo", "cpu cores");
    data->cpu_threads= getInfoFile("/proc/cpuinfo", "siblings");
}

void setValueMemory(Data *data){
    data->total= getInfoFile("/proc/meminfo", "MemTotal");
    data->available= getInfoFile("/proc/meminfo", "MemAvailable");
    data->free= getInfoFile("/proc/meminfo", "MemFree");
    data->swap= getInfoFile("/proc/meminfo", "SwapCached");
}

void setVersion(Data *data){
    data->version= getVersion("/proc/version");
}

char* getInfoFile(const char *path, const char *characterist){
    //File pointer
    FILE* fp= NULL;
    char buffer[500];

    fp= fopen(path, "r");
    if(fp == NULL){
        printf("No se pudo abrir el archivo");
        exit(0);
    }

    fgets(buffer, sizeof(buffer), fp);
    while(!strstr(buffer, characterist)){
        fgets(buffer, sizeof(buffer), fp);

        if(feof(fp)){
            printf("No matcheo substring en %s", path);
            break;
        }
    }

    //Get value of characteristc
    char* match= strtok(buffer, ":");
    while(match != NULL){
        strcpy(buffer, match);
        match= strtok(NULL, ":");
    }

    //Delete \n of buffer
    if(strstr(buffer, "\n")){
        strcpy(buffer, strtok(buffer, "\n"));
    }

    fclose(fp);
    return strdup(buffer);
}

char* getVersion(const char *path){
    //Dinamic mem
    FILE* fp= NULL;
    size_t SIZE= 1024;
    char* word= malloc(sizeof(char) * SIZE);

    if(word == NULL){
        printf("Fail malloc");
        exit(0);
    }

    fp= fopen(path, "r");
    if(fp == NULL){
        printf("No se pudo abrir el archivo");
        exit(0);
    }

    if(fgets(word, SIZE, fp) == NULL){
        printf("Fail fgets\n");
        exit(0);
    }
    fclose(fp);

    for(size_t i=0; i<strlen(word); i++){
        word[i]=  toupper(word[i]);
    }
    
    return word;
    
}