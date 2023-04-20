#include <stdio.h>
#include "headers.h"

int main ( int argc, char * argv[] ) {
    FILE * arxiu = NULL;
    struct Sopa_t sopa;

    /* Mostrar Missatge de Benvinguda XD*/
    //missatge_benvinguda();

    if ( argv[1] == NULL || argc > 2) {
        /* Missatge d'error si no s'indica el fitxer*/
        printf("ERROR. S'ha d'especificar l'arxiu que conte les paraules.\nSortint de programa");
    } else {
        /* Aqui es comencen a fer coses */
        /* Obro l'arxiu, carrego les paralues a sopa.paraules, i tanco fitxer */
        arxiu = fopen( argv[1], "r");
        carregar_paraules( &sopa, arxiu );
        fclose(arxiu);

        /* Ordeno les paraules a sopa.paraules */
        ordenar_paraules( &sopa );

        /* Mostro les paraules a sopa.paraules */
        mostrar_paraules( &sopa );

        /* Pedir mida de la sopa */
        do {
            printf("Mida de la sopa[10..40]:");
            scanf("%d", &sopa.dim);
        } while ( sopa.dim < 10 || sopa.dim > 40 );

        /* Generar Sopa */
		generar_sopa(&sopa);
		mostrar_sopa(&sopa);
    }

    return 0;
}
