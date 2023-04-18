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

void generar_sopa(struct Sopa_t *s)
{
	int aux, p_length;
	int x, y, d;	// x i y son coordenadas de la sopa, d es dirección
	bool correcto;
	srand(time(NULL));

    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        s->encertades[i] = false;
        // Inicialitzem la taula amb guions
        s->lletres[i] = '-';
    }

	for (int i = 0; i < s->n_paraules; i++)
	{
		p_length = strlen(s->paraules[i].contingut);
		do
		{
			x = rand() % s->dim;		// Genera x aleatoria
			y = rand() % s->dim;		// Genera y aleatoria
			d = rand() % 2;				// Genera dirección aleatoria
			if (d == 0)
			{
				correcto = (s->dim - x >= p_length);
				aux = 0;
				while(aux < p_length && correcto)
				{
					correcto = (s->lletres[y*s->dim+(x+aux)] == '-');		// i*N + j
					aux++;
				}
			}
			else
			{
				correcto = (s->dim - y >= p_length);
				aux = 0;
				while(aux < p_length && correcto)
				{
					correcto = (s->lletres[(y+aux)*s->dim+x] == '-');		// i*N + j
					aux++;
				}
			}
		}
		while (!correcto);

		if (d == 0)
		{
			for (int j = 0; j < p_length; j++)
			{
				s->lletres[y*s->dim + (x+j)] = s->paraules[i].contingut[j];
			}
		}
		else
		{
			for (int j = 0; j < p_length; j++)
			{
				s->lletres[(y+j)*s->dim + x] = s->paraules[i].contingut[j];
			}
		}
	}
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        s->encertades[i] = false;
        // Generem una lletra aleatoriament
		if (s->lletres[i] == '-')
		{
			s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
		}
    }
}
