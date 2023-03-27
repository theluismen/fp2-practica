#include <stdbool.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */
struct Paraula_t{
    char ll[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool enc;   // La paraula s'ha encertat
};

struct Sopa_t{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    struct Paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
};

extern void missatge_benvinguda( void );
