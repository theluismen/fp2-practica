#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers.h"

/* Mostra la sopa de lletres pel terminal */
/* En principi, NO HAURIEU DE MODIFICAR AQUEST CODI */
void mostrar_sopa (struct Sopa_t * sopa) {
    // Mostrem els numeros de columna
    // printf("\033[0;31m");   // Color
    printf("  ");
    for (int i = 10; i < sopa->dim + 1; i+=10) {
        for (int j=0; j < 18; j++)
            printf(" ");
        printf(" %d", i/10);
    }

    printf("\n  ");
    for (int i = 0; i < sopa->dim; i++) {
        int p = (i % 10) + 1;
        p != 10 ? printf(" %d", p) : printf(" 0");
    }

    printf("\n");
    // printf("\033[0m");  // Tornem al color per defecte


    // Mostrem les lletres. Cada lletra ocupa dos espais:
    // Si correspon a un encert, es marca
    for (int i = 0; i < sopa->dim ; i++) {
        // printf("\033[0;31m");   // Color
        printf("%-2d", i + 1);  // Mostrar numero de linia
        // printf("\033[0m");  // Tornem al color per defecte

        for (int j = 0; j < sopa->dim; j++) {
            if (sopa->encertades[i * sopa->dim + j]) {
                // printf("\033[0;42m");   // Color verd de fons
                printf(" %c", sopa->lletres[i * sopa->dim + j]);
                // printf("\033[0m");  // Tornem al color per defecte
            } else {
                printf(" %c", sopa->lletres[i * sopa->dim + j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Portes %d encerts.\n", sopa->n_encerts);
    printf("Paraules a trobar: %d\n", sopa->n_paraules - sopa->n_encerts);
    for (int i = 0; i < sopa->n_paraules; i++) {
        if ( ! sopa->paraules[i].encertada ) {
            printf("%s\n", sopa->paraules[i].contingut);
        }
    }
}
