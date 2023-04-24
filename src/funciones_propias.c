#include <stdio.h>
#include <stdbool.h>
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
bool carregar_paraules ( struct Sopa_t * sopa, char nom_arxiu[] ) {
    bool ok = false;
    FILE * arxiu = NULL;
    int i = 0;
    /* Un contador. De hecho se puede usar sopa->n_paraules como contador pero usando
    la variable i el codigo es mas claro
    */

    arxiu = fopen( nom_arxiu, "r");
    if ( arxiu != NULL ) {
        ok = true;
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

    fclose(arxiu);
    return ok;
}

/* Demanar mida de la sopa. Ha de ser entre [10, 40] */
void demanar_mida ( struct Sopa_t * sopa ) {
    do {
        printf("Mida de la sopa[10..40]:");
        scanf("%d", &sopa->dim);
    } while ( sopa->dim < 10 || sopa->dim > 40 );
}

/* Mostra nombre de paraules i les propies paraules */
void mostrar_paraules ( struct Sopa_t * sopa ) {
    int i;
    printf("Hi ha un total de %d paraules:\n", sopa->n_paraules );
    for ( i = 0; i < sopa->n_paraules; i++ ) {
        printf("%4s%-11s\n", "",sopa->paraules[i].contingut );
    }
}

void generar_sopa ( struct Sopa_t * sopa )
{
	int aux, p_long;
	int x, y, d;	// x i y son coordenadas de la sopa, d es direccion
	bool correcto;
	srand(time(NULL));

    sopa->n_encerts  = 0;
    sopa->lletres    = malloc(sopa->dim * sopa->dim * sizeof(char));   // Espai per a les lletres
    sopa->encertades = malloc(sopa->dim * sopa->dim * sizeof(char));   // Per saber si una lletra correspon a encert
    for (int i = 0; i < sopa->dim * sopa->dim; i++)
    {
        sopa->encertades[i] = false;
        // Inicializamos la tabla con guiones
        sopa->lletres[i] = '-';
    }

	for (int i = 0; i < sopa->n_paraules; i++)
	{
		p_long = strlen(sopa->paraules[i].contingut);   // Longitud de la palabra
		do
		{
			x = rand() % sopa->dim;		// Genera x aleatoria
			y = rand() % sopa->dim;		// Genera y aleatoria
			d = rand() % 4;				// Genera dirección aleatoria
			// d = rand() % 2 + 2;				// Genera dirección aleatoria
			if (d == 0) // HORIZONTAL PALANTE
			{
				correcto = (sopa->dim - x >= p_long);     // Comprueba si cabe la palabra dentro de los limites
				aux = 0;
				while(aux < p_long && correcto)
				{
					correcto = (sopa->lletres[ y *sopa->dim+(x+aux)] == '-');		// Comprueba que no haya ninguna palabra en medio (i*N + j)
					aux++;
				}
			} else if (d == 1) { // VERTICAL PALANTE
                correcto = (sopa->dim - y >= p_long);     // Comprueba si cabe la palabra dentro de los limites
                aux = 0;
                while(aux < p_long && correcto)
                {
                    correcto = (sopa->lletres[(y+aux)*sopa->dim+x] == '-');		    // Comprueba que no haya ninguna palabra en medio (i*N + j)
                    aux++;
                }
            }else if (d == 2) { // HORIZONTAL PATRAS
                correcto = (x >= p_long);                 // Comprueba si cabe la palabra dentro de los limites
                aux = 0;
                while(aux < p_long && correcto)
				{
					correcto = (sopa->lletres[ y *sopa->dim+(x-aux)] == '-');		// Comprueba que no haya ninguna palabra en medio (i*N + j)
					aux++;
				}
            } else {// VERTICAL patras
                correcto = (y >= p_long);                 // Comprueba si cabe la palabra dentro de los limites
                aux = 0;
                while(aux < p_long && correcto)
                {
                    correcto = (sopa->lletres[(y-aux)*sopa->dim+x] == '-');		    // Comprueba que no haya ninguna palabra en medio (i*N + j)
                    aux++;
                }
            }
		}
		while ( ! correcto);

        sopa->solucions[i].x = x;                   //
        sopa->solucions[i].y = y;                   // Guarda las coordenadas y la longitud de la palabra para comprobar las soluciones
        sopa->solucions[i].longitud = p_long;       //
		if (d == 0)
		{
			for (int j = 0; j < p_long; j++)
			{
				sopa->lletres[y*sopa->dim + (x+j)] = sopa->paraules[i].contingut[j];    // Escribe la palabra
			}
            sopa->solucions[i].dir = 1;             // Guarda la direccion
		} else if (d == 1) {
            for (int j = 0; j < p_long; j++)
            {
                sopa->lletres[(y+j)*sopa->dim + x] = sopa->paraules[i].contingut[j];    // Escribe la palabra
            }
            sopa->solucions[i].dir = 2;             // Guarda la direccion
        } else if (d == 2) {
            for (int j = 0; j < p_long; j++)
			{
				sopa->lletres[y*sopa->dim + (x-j)] = sopa->paraules[i].contingut[j];    // Escribe la palabra
			}
            sopa->solucions[i].dir = -1;            // Guarda la direccion
        } else
		{
            for (int j = 0; j < p_long; j++)
            {
                sopa->lletres[(y-j)*sopa->dim + x] = sopa->paraules[i].contingut[j];    // Escribe la palabra
            }
            sopa->solucions[i].dir = -2;            // Guarda la direccion
		}
	}
    for (int i = 0; i < sopa->dim * sopa->dim; i++)
    {
        // Generamos una letra aleatoriamente en las casillas en las que no haya letras aun
		if (sopa->lletres[i] == '-')
        {
			sopa->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
        }
    }
}
