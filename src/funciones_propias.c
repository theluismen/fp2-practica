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
    FILE * arxiu = NULL;
    bool ok = false;
    int i = 0;

    arxiu = fopen( nom_arxiu, "r");
    if ( arxiu != NULL ) {
        do {
            /* Leer palabras con fscanf en vez de fgets pk cada linea siempre
            es una palabra unica */
            fscanf(arxiu, "%s\n", sopa->paraules[i].contingut);
            i++;
        } while ( i < MAX_PARAULES && ! feof(arxiu) );
        /* Indicar el numero de palabras leidas aprovechando el valor del contador i */
        sopa->n_paraules = i;
        ok = true;
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

/* Procediment que genera icoloca les paraules a la sopa de lletres */
void generar_sopa ( struct Sopa_t * sopa ) {
    /* x,y: son coordenadas de la sopa. d: es direccion*/
    int x, y, d, p_long;
	int i, aux, j; //iterar i->palabras, aux->letras sopa, j->letras 1 palabra
	bool correcto;

    /* Iniciar aleatoriedad */
	srand(time(NULL));

    /* Inicializar aciertos (0) i crear tabla de letras i aciertos */
    sopa->n_encerts  = 0;
    sopa->lletres    = malloc(sopa->dim * sopa->dim * sizeof(char));
    sopa->encertades = malloc(sopa->dim * sopa->dim * sizeof(char));

    /* Inicializamos la tabla letras con guiones y a falso la de aciertos */
    for (i = 0; i < sopa->dim * sopa->dim; i++) {
        sopa->encertades[i] = false;
        sopa->lletres[i]    = '-';
    }

    /* Para cada palabras, primero miro si la puedo colocar. Cuando pueda la coloco */
	for (i = 0; i < sopa->n_paraules; i++) {
		p_long = strlen(sopa->paraules[i].contingut);   // Longitud de la palabra

        /* Generar parametros de colocacion CORRECTOS */
		do {
			x = rand() % sopa->dim;		    // Genera x aleatoria
			y = rand() % sopa->dim;		    // Genera y aleatoria
			d = rand() % 2 + 1;				// Genera uno de estos valores [-2,-1,1,2]
			d = (rand() % 2) ? -d : d;

            /* Comprueba si cabe la palabra dentro de los limites */
            switch ( d ) {
                case 1:  correcto = (sopa->dim - x) >= p_long;  break;
                case 2:  correcto = (sopa->dim - y) >= p_long;  break;
                case -1: correcto = (x >= p_long);              break;
                case -2: correcto = (y >= p_long);              break;
            }

            /* Comprueba que no haya ninguna palabra en medio */
            aux = 0;
            while ( abs(aux) < p_long && correcto ) {
                if ( abs(d) == 1 )
                    correcto = sopa->lletres[y*sopa->dim + (x+aux)] == '-';
                else
                    correcto = sopa->lletres[(y+aux)*sopa->dim + x] == '-';
                aux = ( d < 0 ) ? aux-1 : aux+1;
            }
        } while ( ! correcto );

        /* Guarda las coordenadas, direccion y longitud de la palabra para comprobar las soluciones */
        sopa->solucions[i].x = x;
        sopa->solucions[i].y = y;
        sopa->solucions[i].dir = d;
        sopa->solucions[i].longitud = p_long;

        /* Coloca la palabra */
        for ( aux = j = 0; abs(aux) < p_long; j++ ) {
            if ( abs(d) == 1 )
                sopa->lletres[y*sopa->dim + (x+aux)] = sopa->paraules[i].contingut[j];
            else
                sopa->lletres[(y+aux)*sopa->dim + x] = sopa->paraules[i].contingut[j];
            aux = ( d < 0 ) ? aux-1 : aux+1;
        }
	}
    /* Generamos una letra aleatoriamente en las casillas vacias( marcadas con guion ) */
    for (int i = 0; i < sopa->dim * sopa->dim; i++) {
		if (sopa->lletres[i] == '-') {
			sopa->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
        }
    }
}

/* No ESTA FET*/
void pedir_jugada ( struct Sopa_t * sopa ) {
    int x, y, d, p_long;

    printf("Trobes?:");
    // scanf("", );
}
