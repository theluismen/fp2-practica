#include <stdbool.h>
#include <stdio.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */
struct Paraula_t{
    char contingut[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool encertada;   // La paraula s'ha encertat
};

struct Sopa_t{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    struct Paraula_t paraules[MAX_PARAULES];    // Les paraules
    int n_paraules;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
};

/* PROTOTIPOS FUNCIONES */
extern void missatge_benvinguda( void );

extern void carregar_paraules ( struct Sopa_t * sopa, FILE * arxiu );

extern void mostrar_paraules ( struct Sopa_t * sopa );

extern bool estan_ordenades ( char str1[], char str2[], int * diff, int * desp);

extern void ordenar_paraules ( struct Sopa_t * sopa );
