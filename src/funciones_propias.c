#include "headers.h"

/**
 * @brief Mostra el missatge de benvinguda i els noms dels membres del grup
 */
void missatge_benvinguda ( void ) {
    printf(
        "#############################################################\n"
        "##  Us donem la benvinguda al joc de la Sopa de Lletres !  ##\n"
        "## Autors: Pablo Munoz, Luis Manuel Ocampo, Adria Montagut ##\n"
        "#############################################################\n"
    );
}

/**
 * @brief Carrega les paraules d'un fitxer donat a l'estructura principal del programa
 * @param sopa (E/S) Struct amb les dades del joc
 * @param nom_arxiu (E) Nom de l'arxiu que s'obrirà per aconseguir les paraules
 * @return true si s'han pogut carregar les paraules
 * @return false si hi ha hagut algun error en la càrrega de les paraules
 */
bool carregar_paraules ( struct Sopa_t * sopa, char nom_arxiu[] ) {
    FILE * arxiu = NULL;
    bool ok = false;
    int i = 0;

    arxiu = fopen( nom_arxiu, "r");
    if ( arxiu != NULL ) {
        do {
            /* Llegir paraules amb fscanf en comptes de fgets perquè cada línia sempre
            és una paraula única */
            fscanf(arxiu, "%s\n", sopa->paraules[i].contingut);
            sopa->paraules[i].encertada = false;
            i++;
        } while ( i < MAX_PARAULES && ! feof(arxiu) );
        /* Indicar el nombre de paraules llegides aprofitant el valor del contador i */
        sopa->n_paraules = i;
        ok = true;
    }
    fclose(arxiu);

    return ok;
}

/**
 * @brief Demanar mida de la sopa. Ha de ser entre [MIN_DIM, MAX_DIM]
 * @param sopa (E/S) Struct amb les dades del joc
 */
void demanar_mida ( struct Sopa_t * sopa ) {
    do {
        printf("Mida de la sopa[10..40]:");
        scanf("%d", &sopa->dim);
    } while ( sopa->dim < MIN_DIM || sopa->dim > MAX_DIM );
}

/**
 * @brief Mostra nombre de paraules i les propies paraules
 * @param sopa (E/S) Struct amb les dades del joc
 * @pre Les paraules estan carregades
 */
void mostrar_paraules ( struct Sopa_t * sopa ) {
    for ( int i = 0; i < sopa->n_paraules; i++ ) {
        if ( ! sopa->paraules[i].encertada ) {
            printf("%4s%-11s\n", "", sopa->paraules[i].contingut );
        }
    }
}

/**
 * @brief Mostra nombre de paraules i les propies paraules
 * @param sopa (E/S) Struct amb les dades del joc
 * @pre Les paraules estan carregades
 * @pre La mida de la sopa està inicialitzada
 */
void generar_sopa ( struct Sopa_t * sopa ) {
    /* x,y: són coordenades de la sopa. d: és direcció */
    int x, y, d, p_long;
	int i, aux, j;      //iterar i->palabras, aux->letras sopa, j->letras 1 palabra
	bool correcto;

    /* Iniciar aleatorietat */
	srand(time(NULL));

    /* Inicialitzar encerts (0), rendicio a false i crear taula de lletres i encerts */
    sopa->n_encerts  = 0;
    sopa->rendicio  = false;
    sopa->lletres    = malloc(sopa->dim * sopa->dim * sizeof(char));
    sopa->encertades = malloc(sopa->dim * sopa->dim * sizeof(char));

    /* Inicialitzem la taula lletres amb guions i a false la d'encerts */
    for (i = 0; i < sopa->dim * sopa->dim; i++) {
        sopa->encertades[i] = false;
        sopa->lletres[i]    = '-';
    }

    /* Per cada paraula, primer miro si la puc col·locar. Quan pugui la coloco */
	for (i = 0; i < sopa->n_paraules; i++) {
		p_long = strlen(sopa->paraules[i].contingut);   // Longitud de la paraula

        /* Generar parametres de col·locació CORRECTES */
		do {
			x = rand() % sopa->dim;		    // Genera x aleatoria
			y = rand() % sopa->dim;		    // Genera y aleatoria
			d = rand() % 2 + 1;				// Genera un d'aquests valors [-2,-1,1,2]
			d = (rand() % 2) ? -d : d;

            /* Comprova si cap la paraula dins dels límits */
            switch ( d ) {
                case 1:  correcto = (sopa->dim - x) >= p_long;  break;
                case 2:  correcto = (sopa->dim - y) >= p_long;  break;
                case -1: correcto = (x >= p_long);              break;
                case -2: correcto = (y >= p_long);              break;
            }

            /* Comprova que no hi hagi cap paraula enmig o que la lletra que es connecti sigui la mateixa */
            aux = 0;
            while ( abs(aux) < p_long && correcto ) {
                if ( abs(d) == 1 )
                    correcto = sopa->lletres[y*sopa->dim + (x+aux)] == '-' || sopa->lletres[y*sopa->dim + (x+aux)] == sopa->paraules[i].contingut[abs(aux)];
                else
                    correcto = sopa->lletres[(y+aux)*sopa->dim + x] == '-' || sopa->lletres[(y+aux)*sopa->dim + x] == sopa->paraules[i].contingut[abs(aux)];
                aux = ( d < 0 ) ? aux-1 : aux+1;
            }
        } while ( ! correcto );

        /* Guarda coordenades, direcció i longitud de la paraula per comprovar les solucions */
        sopa->solucions[i].x = x;
        sopa->solucions[i].y = y;
        sopa->solucions[i].dir = d;
        sopa->solucions[i].longitud = p_long;
        // printf("%8s -> %d %d %d\n", sopa->paraules[i].contingut,x,y,d);
        /* Coloca la paraula */
        for ( aux = j = 0; abs(aux) < p_long; j++ ) {
            if ( abs(d) == 1 )
                sopa->lletres[y*sopa->dim + (x+aux)] = sopa->paraules[i].contingut[j];
            else
                sopa->lletres[(y+aux)*sopa->dim + x] = sopa->paraules[i].contingut[j];
            aux = ( d < 0 ) ? aux-1 : aux+1;
        }
	}
    /* Generem una lletra aleatoriament en les caselles buides ( marcades amb guió ) */
    for (int i = 0; i < sopa->dim * sopa->dim; i++) {
       if (sopa->lletres[i] == '-') {
           sopa->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
       }
    }
}

/**
 * @brief Comprova l'estat de la partida
 * @param sopa (E) Struct amb les dades del joc
 * @return true si el jugador es rendeix o si ha encertat totes les paraules
 * @return false si el joc continua
 */
bool sopa_acabada ( struct Sopa_t * sopa ) {
    bool acabada;
    acabada = sopa->rendicio || (sopa->n_encerts == sopa->n_paraules);
    return acabada;
}

/**
 * @brief Demana i procesa la jugada
 * @param sopa (E/S) Struct amb les dades del joc
 */
void pedir_jugada ( struct Sopa_t * sopa ) {
    char paraula[100]; // Guardar la paraula RENDICIO
    int x, y, d;
    bool encertada;
    int i, aux;

    printf("\nRENDEIXES?:");
    getchar();
    fgets(paraula, 100, stdin);
    paraula[strcspn(paraula,"\n")] = '\0'; //Canviar salt de línia de fgets per null char

    /* Comprovar si l'usuari ha escrit "RENDICIO" */
    if ( strcmp( paraula, "RENDICIO") == 0 ) {
        rendicio(sopa, &x, &y, &d);
    } else {
        /* Supuestament ha trobat una paraula */
        /* Pedim Coordenades, direcció y comprovem que siguin vàlides */
        do {
            printf("Cord i Dir?:");
            scanf("%d %d %d", &x, &y, &d);
            // printf("x:%d\ny:%d\nd:%d\n", x, y, d);
        } while ( (x < 0 || x > MAX_DIM) || (y < 0 || y > MAX_DIM) || (abs(d) != 2 && abs(d) != 1) );

        /* Ajustar les coordenades del usuari per a usar-les */
        x = x - 1;
        y = y - 1;

        /* Comprobar si les coordenades i direcció es corresponen amb alguna paraula */
        encertada = false;
        for (i = 0; i < sopa->n_paraules && ! encertada; i++) {
            if ( x == sopa->solucions[i].x && y == sopa->solucions[i].y && d == sopa->solucions[i].dir ) {
                encertada = true;
                aux = i;
            }
        }

        /* Marcar-la si les dades són correctes i no ha sigut encertada abans */
        if ( encertada && ! sopa->paraules[aux].encertada ) {
            /* Bucle que marca la paraula */
            i = 0;
            while ( abs(i) < sopa->solucions[aux].longitud ) {
                if ( abs(d) == 1 )
                    sopa->encertades[y*sopa->dim + x+i] = true;
                 else
                    sopa->encertades[(y+i)*sopa->dim + x] = true;
                i = ( d < 0 ) ? i-1 : i+1;
            }

            /* Eliminar la paraula de la llista i sumar encerts */
            sopa->paraules[aux].encertada = true;
            sopa->n_encerts++;
        }
    }
}

/**
 * @brief Es marquen totes les paraules, o les que quedin per marcar
 * @param sopa (E/S) Struct amb les dades del joc
 * @param x (E/S) Coordenada x
 * @param y (E/S) Coordenada y
 * @param d (E/S) Direcció
 * @post Totes les paraules están marcades com encertades
 */
void rendicio ( struct Sopa_t * sopa, int *x, int *y, int *d) {
    int aux;

    sopa->rendicio = true;

    for ( int i = 0; i < sopa->n_paraules; i++) {
        if ( ! sopa->paraules[i].encertada ) {
            *x = sopa->solucions[i].x;
            *y = sopa->solucions[i].y;
            *d = sopa->solucions[i].dir;

            /* Bucle que marca la paraula */
            aux = 0;
            while ( abs(aux) < sopa->solucions[i].longitud ) {
                if ( abs(*d) == 1 )
                    sopa->encertades[(*y)*sopa->dim + (*x)+aux] = true;
                else
                    sopa->encertades[((*y)+aux)*sopa->dim + (*x)] = true;
                aux = ( *d < 0 ) ? aux-1 : aux+1;
            }
        }

        /* Eliminar-la de la llista o marcar-la com encertada */
        sopa->paraules[i].encertada = true;
    }
}

/**
 * @brief Allibera la memòria de les dues taules creades amb malloc()
 * @param sopa (E/S) Struct amb les dades del joc
 */
void tancar_sopa ( struct Sopa_t * sopa ) {
    free(sopa->lletres);
    free(sopa->encertades);
}
