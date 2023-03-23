# GNU Toolchain y Linux Software #
## SOI - FCEFyN - UNC - 2022 ## 

## Compilacion
*Para la compilacion de este proyecto debera utilizar GCC*

Dentro de este repositorio se encuentra el archivo *Makefile* que le permitira compilar.

Comandos necesarios:

*Compilacion*
- make (Realiza la compilacion)

Este comando genera un ejecutable llamado **execute**

#### 1. Command line arguments
*Ejecucion*

Este proyecto tiene como objetivo implementación de librerías estáticas y dinámicas.
Podra ejecutar el programa pasando distinto tipos de argumentos para visualizar determinadas salidas.
- ./execute -arg (Ejecuta el programa)

Dispone de la opcion _./execute -h_ para conocer las argumentos disponibles.

 1. Si se ejecuta con la opción -s 
 
 Podra obtener:
 
    - Obtener información referida al CPU, a partir del archivo /proc/cpuinfo:
    - Obtener la *memoria ram total*, *libre* y *disponible* en Megabytes. A partir del archivo /proc/meminfo. 
    - Obtener la memoria *Swap Ocupada*. A partir del archivo /proc/meminfo.
 
 2. Si se ejecuta con la opción -a 
 
 Podra obtener:
 
    - Obtener informacion de la version del archivo  /proc/version

#### 2. Static Library
Se implemento la libreria cJSON a partir del siguiente repositorio:
cJSON, https://github.com/DaveGamble/cJSON
- ./execute -arg (Ejecuta el programa)
1. Si se ejecuta con la opción -j a las opciones anteriores podra visualizar la informacion del item 1 ya mencionado en formato json por pantalla.
La implentacion de una libreria estatica esta declarada en el Makefile de este proyecto.

Se conusltaron varias fuentes para la implentacion, una de ellas es: https://www.geeksforgeeks.org/static-vs-dynamic-libraries/


#### 3. Dynamic Library
Se implemento la libreria cJSON a partir del siguiente repositorio:
cJSON, https://github.com/DaveGamble/cJSON
- ./execute -arg (Ejecuta el programa)
1. Si se ejecuta con la opción -d podra visualizar la informacion sobre los filesystems soportado por el kernel en uso: /proc/filesystems en formato json por pantalla. Ademas la libreria se cargara de manera dinamica en tiempo de ejecucion. 

Se conusltaron varias fuentes para la implentacion, una de ellas es: https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html

Para utilizar dinamicamente la carga de la libreria se utilizo la libreria   #include <dlfcn.h>
https://man7.org/linux/man-pages/man3/dlopen.3.html

Para un error conocido en la llamada de mi libreria pude resolverlo por este link: https://stackoverflow.com/questions/14134245/iso-c-void-and-function-pointers

#### 4. Cuestionario
1. ¿Cuáles son los tipos de type descriptors que podemos encontrar en /proc/<id>/fd?

    El directorio /proc está organizado en directorios virtuales y subdirectorios. los directorios con nombre numérico /proc/<id> representan a los procesos en ejecución. 
    /proc/<id>/fd: Contiene los descriptores de archivo para el proceso, mostrando cuáles archivos o dispositivos lo están usando. Cada entrada es un enlace simbólico al archivo o dispositivo abierto en ese descriptor de archivo. Puede escribir o leer desde estos enlaces simbólicos.

2. Suponiendo que un usuario está ejecutando el proceso pid 1212, ¿Es válida la ejecución del siguiente comando desde una terminal nueva?
% echo “Hello, world.” >> /proc/1212/fd/1

   Los file descriptros 0,1,2 son incializados como entrada, salida y error. Por lo que el comando anterior permite escribir.
   Tambien hay que tener en cuenta que los file descriptors se pueden abrir por medio del inode para el pipe o socket en cuestion de un proceso. Este pipe nos permite un canal unidireccional para poder escribir y leer. 

3. Qué diferencia hay entre hard y soft limits?

    Soft limits son los limites que tiene asignado un procesos o aplicacion de usuario. En cambio, Hard limits es simplmente un valor mayor que soft limits que va indicar el maximo de limit que puede asignarse para un proceso. Solo un usuario con permisos de root podra modificar estos valores.
    _(soft limits <= hard limit)_
