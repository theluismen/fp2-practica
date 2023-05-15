#include "headers.h"

/* Funcion que devuelve:
        true  -> si str1 i str2 NO estan ordenadas alfabeticamente
        false -> si str1 i str2 estan ordenadas alfabeticamente
    Sirve para comparar mas tarde las palabras de la sopa en
    la funcion ordenar_paraules().
    Recibe por referencia diff y desp que indican la diferencia cuando
    se encuentran letras distintas y el numero de desplazamientos realizados
    para encontrar letras distintas.
*/
/**
 * @brief Determina si dos strings estan ordenats
 * @param str1 (E) Primera paraula
 * @param str2 (E) Segona paraula
 * @param diff (S) La diferencia quan es troben lletres diferents
 * @param desp (S) El nombre de desplaçaments realitzats per trobar lletres diferents
 * @return true si str1 i str2 NO estan ordenades alfabèticament
 * @return false si str1 i str2 estan ordenades alfabèticament
 */
bool estan_ordenades ( char str1[], char str2[], int * diff, int * desp) {
    bool swap = false;
    int k;

    *diff = 0;
    *desp = 0;
    /* Recorro los strings mientras pueda i no encuentre letras distintas */
    for ( k = 0; str1[k] != '\0' && str2[k] != '\0' && *diff == 0; k++ ) {
        *diff = str1[k] - str2[k];
    }
    /* k representa los desplazamientos*/
    *desp = k;
    /* Si la diferencia es positiva quiere decir que una letra de la str1
    era mayor alfabeticamente que una de str2, por lo tanto true pk estan
    desordenadas.
    Mismo caso si el str2 se acaba y he comparado mismas
    letras. Ej: de ARBOLEDA y ARBOL va antes ARBOL*/
    if ( *diff > 0 || ( str1[k] != '\0' && str2[k] == '\0' ) ) {
        swap = true;
    }
    return swap;
}

/* El algoritmo es una especie de ordenacion por seleccion adaptado a strings */
/**
 * @brief Ordena les cadenes de caracters de la llista de paraules
 * @param sopa (E/S) Struct amb les dades del joc
 * @pre Hi ha alguna paraula en la llista
 * @post La llista de paraules està ordenada alfabèticament
 */
void ordenar_paraules ( struct Sopa_t * sopa ) {
    int diff, desp,                 /* Variables para guardar informacion */
        min_diff,                   /*  de los strings comparados y */
        min_desp,                   /*  candidatos a intercambio */
        ind_min_diff;
    char aux[MAX_LLETRES + 1];      /* String auxiliar para intercambio */
    int i, j;                       /* Indices */

    for ( i = 0; i < sopa->n_paraules - 1; i++ ) {
        ind_min_diff = -1;
        min_diff = 0;
        min_desp = MAX_LLETRES;
        /* Basicamente decidir cual del resto de palabras tengo que cambiar,
        si es necesario*/
        for ( j = i + 1; j < sopa->n_paraules; j++ ) {
            if ( estan_ordenades(sopa->paraules[i].contingut, sopa->paraules[j].contingut, &diff, &desp) ) {
                if ( desp < min_desp || ( desp == min_desp && diff > min_diff ) ) {
                    min_diff = diff;
                    ind_min_diff = j;
                    min_desp = desp;
                } else if ( desp == min_desp && diff == min_diff && estan_ordenades(sopa->paraules[ind_min_diff].contingut, sopa->paraules[j].contingut, &diff, &desp) ) {
                    ind_min_diff = j;
                }
            }
        }
        /* SI ES NECESARIO, Cambio palabras */
        if ( ind_min_diff != -1 ) {
            strcpy(aux, sopa->paraules[i].contingut);
            strcpy(sopa->paraules[i].contingut, sopa->paraules[ind_min_diff].contingut);
            strcpy(sopa->paraules[ind_min_diff].contingut, aux);
        }
    }
}
