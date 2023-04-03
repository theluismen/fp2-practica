#include <stdio.h>

#include "headers.h"

int main ( int argc, char * argv[] ) {
    FILE * arxiu = NULL;
    struct Sopa_t sopa;

    /* Mostrar Missatge de Benvinguda XD*/
    //missatge_benvinguda();

    if ( argv[1] == NULL ) {
        /* Missatge d'error si no s'indica el fitxer*/
        printf("ERROR. S'ha d'especificar l'arxiu que conté les paraules.\nSortint de programa");
    } else {
        /* Aqui es comencen a fer coses */
        arxiu = fopen( argv[1], "r");
        carregar_paraules( &sopa, arxiu );
        fclose(arxiu);
        ordenar_paraules( &sopa );
        mostrar_paraules( &sopa );

        /* Pedir mida de la sopa */
        do {
            printf("Mida de la sopa[10..40]:");
            scanf("%d", &sopa.dim);
        } while ( sopa.dim < 10 || sopa.dim > 40 );

        /* Generar Sopa */

    }

    return 0;
}
