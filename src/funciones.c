#include "headers.h"

/* Mostra la sopa de lletres pel terminal */
/* En principi, NO HAURIEU DE MODIFICAR AQUEST CODI */
void mostrar_sopa (struct Sopa_t * sopa) {
    int i, j;
    int p;
    // Mostrem els numeros de columna
    // printf("\033[0;31m");   // Color
    printf("  ");
    for (i = 10; i < sopa->dim + 1; i+=10) {
        for (j=0; j < 18; j++)
            printf(" ");
        printf(" %d", i/10);
    }

    printf("\n  ");
    for (i = 0; i < sopa->dim; i++) {
        p = (i % 10) + 1;
        p != 10 ? printf(" %d", p) : printf(" 0");
    }

    printf("\n");
    // printf("\033[0m");  // Tornem al color per defecte

    // Mostrem les lletres. Cada lletra ocupa dos espais:
    // Si correspon a un encert, es marca
    for (i = 0; i < sopa->dim ; i++) {
        // printf("\033[0;31m");   // Color
        printf("%-2d", i + 1);  // Mostrar numero de linia
        // printf("\033[0m");  // Tornem al color per defecte

        for (j = 0; j < sopa->dim; j++) {
            if (sopa->encertades[i * sopa->dim + j]) {
                // printf("\033[1;32m");   // Color verd de fons
                printf(" %c", sopa->lletres[i * sopa->dim + j]);
                // printf("\033[0m");  // Tornem al color per defecte
            } else {
                printf(" %c", sopa->lletres[i * sopa->dim + j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    if ( ! sopa_acabada(sopa) ) {
        printf("Portes %d encerts.\n", sopa->n_encerts);
        printf("Paraules per trobar: %d\n", sopa->n_paraules - sopa->n_encerts);
    } else {
        ( sopa->rendicio ) ? printf("## T'HAS RENDIT ##\n") : printf("## HAS GUANYAT ##\n");
        printf("Encerts: %d\n", sopa->n_encerts);
        printf("Paraules Restants: %d\n", sopa->n_paraules - sopa->n_encerts);
    }
    mostrar_paraules(sopa);
}
