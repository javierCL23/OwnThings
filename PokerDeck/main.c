#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "funciones.h"

// main
int main (int argc, char* argv[]){
    int salir=0;
    char* opcion;
    cargar_cartas();
    while(!salir){
        print_n();
        menu();
        opcion=input_general(1);
        if (opcion!=NULL){
            switch (*opcion) {
                case '1':
                    limpiar_pantalla();
                    anadir_carta();
                    break;
                case '2':
                    limpiar_pantalla();
                    eliminar_carta();
                    break;
                case '3':
                    limpiar_pantalla();
                    ordenar_numero();
                    break;
                case '4':
                    limpiar_pantalla();
                    ordenar_palo();
                    break;
                case '5':
                    limpiar_pantalla();
                    mostrar_mano();
                    break;
                case '6':
                    limpiar_pantalla();
                    barajar_mano();
                    break;
                case '7':
                    limpiar_pantalla();
                    liberar_mano();
                    printf("La mano ha sido completamente descartada\n");
                    break;
                case '8':
                    salir=1;
                    guardar_cartas();
                    printf("Saliendo del programa\n");
                    liberar_mano();
                    break;
                
                default:
                    printf("Opcion no válida\n");
                    break;
            }
            free(opcion);
        }
        else{
            limpiar_pantalla();
            fprintf(stderr,"ERROR, input demasiado largo\n");
        }
    }
    exit(EXIT_SUCCESS);
}
