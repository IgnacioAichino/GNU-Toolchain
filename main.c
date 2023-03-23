#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <dlfcn.h>
#include "structures.h"
#include "dinamicStruct.h"
   
const char* const short_options = "sajdh";

const struct option long_option[]= {
		{ "s_option", 0, NULL, 's' },
		{ "a_option", 0, NULL, 'a' },
		{ "j_option", 0, NULL, 'j' },
		{ "d_option", 0, NULL, 'd' },
        { "h_option", 0, NULL, 'h' },
		{ NULL,	0, NULL, 0	} };


int main(int argc, char *argv[]){

    if(argc == 1){
        printf("Ingrese la opcion -h para obtener informacion\n");
        exit(0);
    }

    int option_user= 0;
    int flag_j= 0;
    int flag_s= 0;
    int flag_a= 0;

    while((option_user= getopt_long(argc, argv, short_options, long_option, NULL)) != -1){
        
        switch(option_user){          
            case 's':
                flag_s= 1;
                break;

            case 'a':
                flag_a= 1;
                break;
        
            case 'j':
                flag_j= 1;
                break;

            case 'd':
                printf("\n-----DINAMIC LIB------\n");
                void *libhandle= dlopen("./libdinamica.so", RTLD_LAZY);
                if(libhandle==NULL){
                    printf("Error al cargar lib dinamica");
                }
                else{
                    void(*funtion)();
                    *(void **)(&funtion)= dlsym(libhandle, "print_dinamicJson");
                    (*funtion)();
                    dlclose(libhandle);
                }
                break;

            case 'h':
                print_helpUser();
                break;
                
            default:
                exit(0);
                break;
        }
    }
    
    if(flag_j && (flag_s || flag_a)){
        print_json(flag_s, flag_a);
    }
    else{
        if(flag_a){
            option_a();
        }
        if(flag_s){
            option_s();
        }
    }

   
    return 0;

}
