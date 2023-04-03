#include <stdio.h>
#include "headers.h"

/* Procediment que mostra missatge de benvinguda i els noms del membresdel grup*/
void missatge_benvinguda ( void ) {
    printf(
        "#############################################################\n"
        "##  Us donem la benvinguda al joc de la Sopa de Lletres !  ##\n"
        "## Autors: Pablo Munoz, Luis Manuel Ocampo, Adria Montagut ##\n"
        "#############################################################\n"
    );
}

/* Carrega les paraules d'un fitxer donat a l'estructura principal del programa: sopa*/
void carregar_paraules ( struct Sopa_t * sopa, FILE * arxiu ) {
    /* Un contador. De hecho se puede usar sopa->n_paraules como contador pero usando
    la variable i el codigo es mas claro
    */
    int i = 0;
    do {
        /* Leer palabras con fscanf en vez de fgets pk cada linea siempre
        es una palabra unica
        */
        fscanf(arxiu, "%s\n", sopa->paraules[i].contingut);
        i++;
    } while ( i < MAX_PARAULES && ! feof(arxiu) );
    /* Indicar el numero de palabras leidas aprovechando el valor del contador i */
    sopa->n_paraules = i;
}

/* Mostra nombre de paraules i les propies paraules */
void mostrar_paraules ( struct Sopa_t * sopa ) {
    int i;
    printf("Hi ha un total de %d paraules:\n", sopa->n_paraules );
    for ( i = 0; i < sopa->n_paraules; i++ ) {
        printf("%4s%-11s\n", "",sopa->paraules[i].contingut );
    }
}
