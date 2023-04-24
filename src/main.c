#include "headers.h"

int main ( int argc, char * argv[] ) {
    struct Sopa_t sopa;

    /* Mostrar Missatge de Benvinguda XD*/
    //missatge_benvinguda();

    if ( argv[1] == NULL || argc > 2 ) {
        /* Missatge d'error si no s'indica el fitxer*/
        printf("ERROR. S'ha d'especificar l'arxiu que conte les paraules.\nSortint de programa");
    } else {
        /* Aqui es comencen a fer coses */
        /* Obro l'arxiu, carrego les paralues a sopa.paraules, i tanco fitxer */
        // arxiu_obert = carregar_paraules( &sopa, argv[1]) );
        if ( ! carregar_paraules( &sopa, argv[1]) ) {
            printf("ERROR. No s'ha pogut obrir el fitxer %s.", argv[1]);
        } else {
            /* Ordeno les paraules a sopa.paraules */
            ordenar_paraules( &sopa );

            /* Mostro les paraules a sopa.paraules */
            mostrar_paraules( &sopa );

            demanar_mida( &sopa );

            /* Generar Sopa */
            generar_sopa(&sopa);
            mostrar_sopa(&sopa);

            /* ESQUEMA BUCLE JUEGO
            while (! sacabao(&sopa) ) {
                pedir_jugada(&sopa)
                mostrar_sopa(&sopa)
            }
            */
        }
    }

    return 0;
}
