#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define TAM_MANO 52

struct Carta
{
    int num;
    char* palo;
};
typedef struct Carta Carta;

void menu(void);
void limpiar_pantalla(void);
void limpiar_stdin(void);
void liberar_carta(Carta* carta);

char* input_general(int opcion);    //si opcion es 1, se usará para elegir una opcion en el menu, si es 2 será para introducir una carta 
                                    //devuelve un char* reservado HACER FREE!!!

int input_carta(char* palabra);
int carta_existe(Carta* carta);
Carta* new_card(char* carta);

//1
void anadir_carta(void);

//2
void eliminar_carta(void);
void borrar_carta(Carta* carta);

//3
void ordenar_numero(void);

//4
void ordenar_palo(void);

//5
void mostrar_mano(void);

//6 
void barajar_mano(void);

//7
void liberar_mano(void);

//8
void guardar_cartas(void);
void cargar_cartas(void);
char* cartaAtexto(Carta* carta);

void print_n(void);