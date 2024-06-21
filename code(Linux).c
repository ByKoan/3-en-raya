#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_NAME 0xff

typedef struct Jugador  // Estructura que usaremos para almacenar el nombre del jugador y su simbolo
{
    char *nombre;  
    char  simbolo; 
} Jugador;

char * crear_tablero(); // Funcion que creara el tablero
char * print_tablero(char * tablero);  // Funcion que printa el tablero
void colocarposicion(char *tablero, Jugador jugador);  // Funcion que colocara la posicion que elija el jugador
int comprobar_victoria(char *tablero, char simbolo);  // Funcion que comprobara la victoria mediante las posiciones en el tablero
void limpiar_consola();  // Funcion que usaremos para limpiar la consola


int main() {  // Funcion principal del programa

    printf("\n 3 En Raya Made By Koan \n \n");

    Jugador jugador1 = {  //Estructura para jugador 1
        .nombre  = (char *)malloc(sizeof(char) * MAX_LEN_NAME),  // Reservaremos memoria en funcion de la longitud del nombre
        .simbolo = 0,  // Declaramos el simbolo como 0 para posteriormente remplazarlo por "x" u "o"
    };
    
    Jugador jugador2 = {  //Estructura para jugador 2
        .nombre  = (char *)malloc(sizeof(char) * MAX_LEN_NAME),  // Reservaremos memoria en funcion de la longitud del nombre
        .simbolo = 0,  // Declaramos el simbolo como 0 para posteriormente remplazarlo por "x" u "o"
    };

    memset(jugador1.nombre, 0, MAX_LEN_NAME);  // La memoria que hemos reservado la ponemos a 0
    memset(jugador2.nombre, 0, MAX_LEN_NAME);  // La memoria que hemos reservado la ponemos a 0

    printf("Nombre del jugador 1: ");  
    fgets(jugador1.nombre, MAX_LEN_NAME, stdin);  // Pedimos al jugador 1 que nos ingrese su nombre
    jugador1.nombre[strcspn(jugador1.nombre, "\n")] = 0;  // Eliminamos el caracter \n que fgets nos añade

    printf("Nombre del jugador 2: ");
    fgets(jugador2.nombre, MAX_LEN_NAME, stdin);  // Pedimos al jugador 2 que nos ingrese su nombre
    jugador2.nombre[strcspn(jugador2.nombre, "\n")] = 0;  // Eliminamos el caracter \n que fgets nos añade


    printf("Simbolo del jugador 1 (x u o): "); 
    scanf(" %c", &(jugador1.simbolo));  // Pedimos al jugador 1 que nos ingrese su simbolo con el que va a jugar
    printf("Simbolo del jugador 2 (x u o): ");
    scanf(" %c", &(jugador2.simbolo));  // Pedimos al jugador 2 que nos ingrese su simbolo con el que va a jugar

    if ((jugador1.simbolo == 'x' && jugador2.simbolo == 'o') ||   (jugador1.simbolo == 'o' && jugador2.simbolo == 'x')) { //Con este if estamos comprobando que nos hayan introducido el simbolo correctamente
        printf("Con simbolo %c, jugador %s\n", jugador1.simbolo, jugador1.nombre);
        printf("Con simbolo %c, jugador %s\n", jugador2.simbolo, jugador2.nombre);
    } else {
        printf("Selecciona entre x/o para ambos jugadores.\n");
        return EXIT_FAILURE;
    }
    

    char * tablero = crear_tablero();  // Llamamos a la funcion crear_tablero para inicializarlo 

    int turno = 0; // Creamos la variable turno la cual si es = 0 es el turno del jugador 1, si es = 1 es el turno del jugador 2
    for (int i = 0; i < 9; i++) { // Bucle que ira recorriendo desde la posicion 0 hasta la 9
        limpiar_consola();
        print_tablero(tablero); // Imprimimos el tablero
        if (turno == 0) {
            colocarposicion(tablero, jugador1); // Funcion que colocara la posicion para el jugador 1
            if (comprobar_victoria(tablero, jugador1.simbolo)) {  
                limpiar_consola();
                print_tablero(tablero);
                printf("\n%s ha ganado!", jugador1.nombre);
                free(tablero); // Liberamos la memoria del tablero y la memoria de los 2 jugadores
                free(jugador1.nombre);
                free(jugador2.nombre);
                return EXIT_SUCCESS;
            }
            turno = 1;
        } else {
            colocarposicion(tablero, jugador2);  // Funcion que colocara la posicion para el jugador 1
            if (comprobar_victoria(tablero, jugador2.simbolo)) {
                limpiar_consola();
                print_tablero(tablero);
                printf("\n%s ha ganado!", jugador2.nombre);
                free(tablero);  // Liberamos la memoria del tablero y la memoria de los 2 jugadores
                free(jugador1.nombre);
                free(jugador2.nombre);
                return EXIT_SUCCESS;
            }
            turno = 0;
        }
    }

    limpiar_consola();
    print_tablero(tablero); 
    printf("\nEs un empate!");
    free(tablero);  // Liberamos la memoria del tablero y la memoria de los 2 jugadores
    free(jugador1.nombre);
    free(jugador2.nombre);



    return EXIT_SUCCESS;
}

char * crear_tablero () {
    char * ptr_malloc = (char *)malloc(9 * sizeof(char));  // Reservamos memoria para las 9 posiciones
    for (int i = 0; i < 9; i++) {  // Con este for inicializaremos el tablero con las 9 posiciones con espacios en blanco
        ptr_malloc[i] = ' ';
    }
    return ptr_malloc;  // Retornamos el puntero de malloc
}

char * print_tablero (char * tablero) {
    printf(
            " ____________________\n"
            "|   %c  |   %c  |   %c  |\n"
            "|------|------|------|\n"
            "|   %c  |   %c  |   %c  |\n"
            "|------|------|------|\n"
            "|   %c  |   %c  |   %c  |\n"
            "|------|------|------|", tablero[0], tablero[1], tablero[2], tablero[3], tablero[4], tablero[5], tablero[6], tablero[7], tablero[8]);  // Funcion la cual nos imprimira el tablero con las 9 posiciones
}

void colocarposicion(char *tablero, Jugador jugador) {
    int posicion;  // Crearemos la variable posicion que posteriormente nos ingresaran el valor mediante el scanf
    printf("Turno de %s. Ingresa una posicion (1-9): ", jugador.nombre);
    scanf("%d", &posicion);

    while (posicion < 1 || posicion > 9 || tablero[posicion - 1] != ' ') {  // Bucle que se encarga de validar y asegurar que la posicion ingresada sea valida
        printf("Posicion invalida. Intenta de nuevo: ");
        scanf("%d", &posicion);
    }

    tablero[posicion - 1] = jugador.simbolo;  // Actualizara el tablero con el simbolo del jugador en la posicion especificada
}

int comprobar_victoria(char *tablero, char simbolo) {
    // Verificar filas y columnas
    for (int i = 0; i < 3; i++) {
        if ((tablero[i*3] == simbolo && tablero[i*3 + 1] == simbolo && tablero[i*3 + 2] == simbolo) || // Filas
            (tablero[i] == simbolo && tablero[i + 3] == simbolo && tablero[i + 6] == simbolo)) {      // Columnas
            return 1;
        }
    }
    // Verificar diagonales
    if ((tablero[0] == simbolo && tablero[4] == simbolo && tablero[8] == simbolo) ||
        (tablero[2] == simbolo && tablero[4] == simbolo && tablero[6] == simbolo)) {
        return 1;
    }
    return 0;
}

void limpiar_consola() {
    system("clear");
}
