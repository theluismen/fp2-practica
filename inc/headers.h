#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */
struct Paraula_t{
    char contingut[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool encertada;   // La paraula s'ha encertat
};

struct Coords_t{
    int x;          // Coordenada x de la palabra
    int y;          // Coordenada y de la palabra
    int dir;        // Dirección de la palabra (1 = horizontal palante, 2 = vertical palante, -1 = horizontal patras, -2 = vertical patras)
    int longitud;     // longitud palabra
};

struct Sopa_t{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    struct Paraula_t paraules[MAX_PARAULES];    // Les paraules
    int n_paraules;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
    struct Coords_t solucions[MAX_PARAULES];    // Coordenades de les paraules
};

/* PROTOTIPOS FUNCIONES */
extern void missatge_benvinguda( void );

extern bool carregar_paraules ( struct Sopa_t * sopa, char nom_arxiu[] );

extern void mostrar_paraules ( struct Sopa_t * sopa );

extern bool estan_ordenades ( char str1[], char str2[], int * diff, int * desp);

extern void demanar_mida ( struct Sopa_t * sopa );

extern void ordenar_paraules ( struct Sopa_t * sopa );

extern void generar_sopa ( struct Sopa_t * sopa);

extern void mostrar_sopa ( struct Sopa_t * sopa);
