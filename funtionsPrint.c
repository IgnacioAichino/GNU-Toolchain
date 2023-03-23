#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"



Data data;


void option_s(){
    printf("\n--------CPU--------\n");
    print_cpu();
    printf("\n-------MEMORY-------\n");
    print_memory();
}

void option_a(){
    printf("\n-----SO VERSION------\n");
    print_version();
}


void print_helpUser(){
    printf("Execute: ayuda de argumentos\n\n"
            "-h     Muestra las opciones del programa execute.\n"
		    "-s     Muestra: \n"
	        "           - Modelo de CPU.\n"
       	    "           - Cores de CPU.\n"
            "           - Hilos por core de CPU.\n"
            "-a     Muestra en MB: \n"
	        "           - Memoria total .\n"
       	    "           - Memoria libre\n"
            "           - Memoria disponible.\n"
            "           - Memoria swap ocupada.\n"
	        "-j      Muestra en formato JSON los valores de la opcion -s -a.\n"
	        "-d      Muestra los filesystems soportado por el kernel en formato JSON mediante libreria dinamica\n");
}


void print_cpu(){

    setValueCPU(&data);

    fprintf(stdout, "CPU model:  %s\n", data.cpu_model);
    fprintf(stdout, "CPU cores::  %s\n", data.cpu_cores);
    fprintf(stdout, "Threads per core:  %d\n", atoi(data.cpu_threads)/atoi(data.cpu_cores));
}

void print_memory(){

    setValueMemory(&data);

    fprintf(stdout, "Memory total:  %d MB\n", atoi(data.total)/1000);
    fprintf(stdout, "Memory available: %d MB\n", atoi(data.available)/1000);
    fprintf(stdout, "Memory free: %d MB\n", atoi(data.free)/1000);
    fprintf(stdout, "Swap in cache:  %d MB\n", atoi(data.swap)/1000);
}

void print_version(){
    
    setVersion(&data);
    fprintf(stdout, "%s\n", data.version);
}


void print_json(int flag_s, int flag_a){

    cJSON *object_json= cJSON_CreateObject();

    if(flag_s){
        setValueCPU(&data);
        setValueMemory(&data);
        cJSON *cpu_info= NULL;
        cJSON *mem_info= NULL;

        cpu_info= cJSON_AddArrayToObject(object_json, "CPU info");
        mem_info= cJSON_AddArrayToObject(object_json, "MEM info");

        //Set values for cpu_info json
        cJSON *info= cJSON_CreateObject();
        cJSON_AddStringToObject(info, "CPU model", data.cpu_model);
        cJSON_AddNumberToObject(info, "CPU cores", atoi(data.cpu_cores));
        cJSON_AddNumberToObject(info, "Threads per core", atoi(data.cpu_threads)/atoi(data.cpu_cores));
        cJSON_AddItemToArray(cpu_info, info);

        //Set values for mem_info
        cJSON *info2= cJSON_CreateObject();
        cJSON_AddNumberToObject(info2, "Memory total MB:", atoi(data.total)/1000);
        cJSON_AddNumberToObject(info2, "Memory available MB:", atoi(data.available)/1000);
        cJSON_AddNumberToObject(info2, "Memory free MB:", atoi(data.free)/1000);
        cJSON_AddNumberToObject(info2, "Swap in cache MB:", atoi(data.swap)/1000);
        cJSON_AddItemToArray(mem_info, info2);

    }   
    if(flag_a){
        setVersion(&data);
        cJSON *version_info= NULL;

        version_info= cJSON_AddArrayToObject(object_json, "VERSION info");
   
        //Set value for version
        cJSON *info= cJSON_CreateObject();
        cJSON_AddStringToObject(info, "Version", data.version);
        cJSON_AddItemToArray(version_info, info);
    }
    
    fprintf(stdout, "%s\n", cJSON_Print(object_json));
    cJSON_Delete(object_json);
}

