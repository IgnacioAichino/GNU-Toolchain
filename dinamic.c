#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dinamicStruct.h"


Datatypes data;

void setTypeFilesys(Datatypes *data){
    data->types_filesys=  getInfo("/proc/filesystems");
}

void setTotal(Datatypes *data){
    data->total_types= getTotalTypes("/proc/filesystems");
}

int getTotalTypes(const char *path){
    FILE* fp= NULL;
    char buffer[500];
    
	fp = fopen (path, "r");
    if(fp == NULL){
        printf("No se pudo abrir el archivo");
        exit(0);
    }

    int total=0;
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);
        total++;
    }

    fclose(fp);
    return total;
}

char** getInfo(const char *path){
    FILE* fp= NULL;
    char buffer[500];
    
	fp = fopen (path, "r");
    if(fp == NULL){
        printf("No se pudo abrir el archivo");
        exit(0);
    }

    char **words= (char **)malloc(50 * sizeof(char *));
    int i=0;
    while(fscanf(fp, "%s ", buffer) != EOF){
        char *temp= (char *)malloc(60);
        strcpy(temp, buffer);

        if(strcmp(temp, "nodev")){
            words[i]= (char*)malloc(60);
            strcpy(words[i], buffer);
            i++;
        }  
    }

    fclose(fp);
    return words;
}

void print_dinamicJson(){
    
    setTypeFilesys(&data);
    setTotal(&data);

    cJSON *object_json= cJSON_CreateObject();
    cJSON *filesystem_info= NULL;

    filesystem_info= cJSON_AddArrayToObject(object_json, "Filesystems types");

   
    //Set values for filesystem_info json
    cJSON *info= cJSON_CreateObject();
    for(int i=0; i<data.total_types; i++){
        cJSON_AddStringToObject(info, "type", data.types_filesys[i]);
    }

    cJSON_AddItemToArray(filesystem_info, info);

    fprintf(stdout, "%s\n", cJSON_Print(object_json));
    cJSON_Delete(object_json);
}




