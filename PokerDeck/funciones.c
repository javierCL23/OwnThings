#include "funciones.h"

char* numeros[]={"1","2","3","4","5","6","7","8","9","10","11","12"};
char* palos[]={"bastos","espadas","copas","oros"};
Carta* mano[TAM_MANO]={0};
int n;
int n_max;


void print_n(void){
    printf("N=%i\n",n);
}

void menu(void){
    printf("1. Añadir una carta\n");
    printf("2. Eliminar una carta\n");
    printf("3. Ordenar por numero\n");
    printf("4. Ordenar por palo\n");
    printf("5. Mostrar mano actual\n");
    printf("6. Barajar mano actual\n");
    printf("7. Descartar mano actual\n");
    printf("8. Salir\n\n");
}

void limpiar_pantalla(void){
    int espera;
    switch (fork())
    {
    case -1:
        printf("Something went wrong\n");
        exit(EXIT_FAILURE);
    case 0:
        execl("/bin/clear","clear",NULL);
    default:
        wait(&espera);
        if (WEXITSTATUS(espera)!=0){
            printf("Something went wrong\n");
            exit(EXIT_FAILURE);
        }
        break;
    };
}

void liberar_carta(Carta* carta){
    free(carta->palo);
    free(carta);
}

void limpiar_stdin(void){
    int c;
	while ((c = getchar()) != '\n' && c != EOF) {
	}
}

char* input_general(int opcion){
    int max_len=3;
    char* salto_lin;
    if (opcion==2){
        max_len=12; //el length maximo para una carta es de 9 "(10,11,12)-espadas + \n + \0"
    }
    char* buffer=(char*) malloc(max_len*sizeof(char));
    printf(">");
    if (fgets(buffer,max_len,stdin)==NULL){
        fprintf(stderr,"UPS, algo ha ido mal, intentalo de nuevo\n");
        free(buffer);
    }
    salto_lin=strchr(buffer,'\n');
    if (salto_lin==NULL){
        fprintf(stderr,"ERROR, input demasiado largo\n");
        limpiar_stdin();
        free(buffer);
        return NULL;
    }
    *salto_lin='\0';
    return buffer;
}

void anadir_carta(void){
    char* carta;
    Carta* nueva_carta;
    int i;
    if(n==TAM_MANO){
        printf("No se pueden añadir más cartas, ya están todas\n");
        return;
    }
    carta=input_general(2);
    if (carta==NULL){
        return;
    }
    if (input_carta(carta)){
        nueva_carta=new_card(carta);
        if(carta_existe(nueva_carta)==-1){
            for (i=0;i<TAM_MANO;i++){
                if(mano[i]==NULL){
                    mano[i]=nueva_carta;
                    break;
                }
            }
            n++;
            if (n>n_max){
                n_max=n;
            }
        }
        else{
            printf("Esa carta ya está en tu mano\n");
            liberar_carta(nueva_carta);
        }
    }
    free(carta);
}

int input_carta(char* palabra){
    int i;
    int j;
    char* input=strdup(palabra);
    char* parteIz;
    char* parteDer=strchr(input,'-');
    if (parteDer==NULL){
        fprintf(stderr,"Formato no válido: \"num-palo\"\n");
        free(input);
        return 0;   
    }
    parteIz=input;
    *parteDer='\0';
    parteDer++;
    for(i=0;i<12;i++){
        if(strcmp(parteIz,numeros[i])==0){
            for(j=0;j<4;j++){
                if(strcmp(parteDer,palos[j])==0){
                    free(input);
                    return 1;
                }
            }
        }
    }
    fprintf(stderr,"Formato no válido: \"num-palo\"\n");
    free(input);
    return 0;
}

int carta_existe(Carta* carta){
    int i;
    for (i=0;i<n_max;i++){
        if (mano[i]!=NULL){
            if (carta->num==mano[i]->num && strcmp(carta->palo,mano[i]->palo)==0){
                return i;
            }
        }
    }
    return -1;
}

Carta* new_card(char* carta){
    char* izq;
    char* der;
    Carta* nueva_carta=(Carta*)malloc(sizeof(Carta));
    izq=carta;
    der=strchr(carta,'-');
    *der='\0';
    der++;
    nueva_carta->num=atoi(izq);
    nueva_carta->palo=strdup(der);
    return nueva_carta;
}

void eliminar_carta(void){
    char* carta;
    Carta* nueva_carta;
    int posicion;
    if(n==0){
        printf("No se pueden eliminar más cartas,no hay\n");
        return;
    }
    carta=input_general(2);
    if (carta==NULL){
        return;
    }
    if (input_carta(carta)){
        nueva_carta=new_card(carta);
        posicion=carta_existe(nueva_carta);
        if(posicion!=-1){
            liberar_carta(mano[posicion]);
            mano[posicion]=NULL;
            n--;
        }
        else{
            printf("Esa carta no está en tu mano\n");
        }
        liberar_carta(nueva_carta);
    }
    free(carta);
}

void ordenar_numero(void){
    int i;
    int j;
    int k;
    int hay_carta=0;

    if (n==0){
        printf("La mano está vacía, no hay cartas para ordenar\n");
        return;
    }
    for(i=0;i<12;i++){
        for (j=0;j<4;j++){
            for (k=0;k<n_max;k++){
                if(mano[k]!=NULL){
                    if (mano[k]->num == i+1 && strcmp(mano[k]->palo,palos[j])==0){
                        printf("%i-%s\n",mano[k]->num,mano[k]->palo);
                        hay_carta=1;
                    }
                }
            }
        }
        if (hay_carta){
            printf("\n");
            hay_carta=0;
        }
    }
}

void ordenar_palo(void){
    int i;
    int j;
    int k;
    int hay_carta=0;

    if (n==0){
        printf("La mano está vacía, no hay cartas para ordenar\n");
        return;
    }
    for(j=0;j<4;j++){
        for (i=0;i<12;i++){
            for (k=0;k<n_max;k++){
                if(mano[k]!=NULL){
                    if (mano[k]->num == i+1 && strcmp(mano[k]->palo,palos[j])==0){
                        printf("%i-%s\n",mano[k]->num,mano[k]->palo);
                        hay_carta=1;
                    }
                }
            }
        }
        if (hay_carta){
            printf("\n");
            hay_carta=0;
        }
    }
}

void mostrar_mano(void){
    int i;
    if (n==0){
        printf("No hay cartas que mostrar\n");
    }
    for(i=0;i<n_max;i++){
        if (mano[i]!=NULL){
            printf("%i-%s\n",mano[i]->num,mano[i]->palo);
        }
    }
    printf("\n");
}
void liberar_mano(void){
    int i;
    for (i=0;n>0;i++){
        if (mano[i]!=NULL){
            liberar_carta(mano[i]);
            mano[i]=NULL;
            n--;
        }
    }
    n_max=0;
}

void barajar_mano(void){
    srand(time(0));
    if (n==0){
        fprintf(stderr,"No hay cartas que barajar\n");
        return;
    }
    Carta* temporal;
    int i;
    int j;
    for (i=n_max-1;i>0;i--){
        j= rand() % (i + 1);
        temporal=mano[i];
        mano[i]=mano[j];
        mano[j]=temporal;
    }
    printf("La mano ha sido barajada correctamente\n");
}

void cargar_cartas(void){
    FILE* archivo;
    int tam_max=12;
    char linea[12];
    char* salto_linea;
    Carta* nueva_carta;
    int max_attemps=0;
    int i;
    archivo=fopen("/tmp/cartas_guardado.txt","r");
    if (archivo==NULL){
        return;
    }
    while(fgets(linea,tam_max,archivo)){
        salto_linea=strchr(linea,'\n');
        if (salto_linea!=NULL){
            *salto_linea='\0';
        }
        if (!input_carta(linea)){
            fprintf(stderr,"ERROR, something went wrong with the save-file\n");
            liberar_mano();
            fclose(archivo);
            return;
        }
    
        nueva_carta=new_card(linea);
        if (carta_existe(nueva_carta)!=-1){
            fprintf(stderr,"ERROR, something went wrong with the save-file (carta repetida)\n");
            liberar_mano();
            liberar_carta(nueva_carta);
            fclose(archivo);
            return;
        }
        for (i=0;i<TAM_MANO;i++){
                if(mano[i]==NULL){
                    mano[i]=nueva_carta;
                    break;
                }
        }
        n++;
        if (n>n_max){
            n_max=n;
        }
    }
    do
    {
        max_attemps++;
    } while (fclose(archivo)!=0 && max_attemps>5);

}

void guardar_cartas(void){
    FILE* archivo;
    int max_attemps=0;
    int i;
    char* linea;
    do{
        archivo = fopen("/tmp/cartas_guardado.txt", "w");
        max_attemps++;
    }while (archivo==NULL && max_attemps<5);
    if (archivo==NULL){
        fprintf(stderr,"ERROR,No se pudo guardar el contenido del save-file\n");
        return;
    }
    for (i=0;i<n_max;i++){
        if (mano[i]!=NULL){
            linea=cartaAtexto(mano[i]);
            fprintf(archivo,"%s",linea);
            free(linea);
        }
    }
    max_attemps=0;
    do
    {
        max_attemps++;
    } while (fclose(archivo)!=0 && max_attemps>5);
    
}

char* cartaAtexto(Carta* carta){
    char* text=(char*)malloc(12*sizeof(char));
    sprintf(text,"%i-%s\n",carta->num,carta->palo);
    return text;
}