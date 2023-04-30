#include "headers.h"

/* Procediment que mostra missatge de benvinguda i els noms del membres del grup*/
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
            sopa->paraules[i].encertada = false;
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
    } while ( sopa->dim < MIN_DIM || sopa->dim > MAX_DIM );
}

/* Mostra nombre de paraules i les propies paraules */
void mostrar_paraules ( struct Sopa_t * sopa ) {
    for ( int i = 0; i < sopa->n_paraules; i++ ) {
        if ( ! sopa->paraules[i].encertada ) {
            printf("%4s%-11s\n", "", sopa->paraules[i].contingut );
        }
    }
}

/* Procediment que genera icoloca les paraules a la sopa de lletres */
void generar_sopa ( struct Sopa_t * sopa ) {
    /* x,y: son coordenadas de la sopa. d: es direccion */
    int x, y, d, p_long;
	int i, aux, j; //iterar i->palabras, aux->letras sopa, j->letras 1 palabra
	bool correcto;

    /* Iniciar aleatoriedad */
	srand(time(NULL));

    /* Inicializar aciertos (0), rendicio a false i crear tabla de letras i aciertos */
    sopa->n_encerts  = 0;
    sopa->rendicio  = false;
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

        /* Guarda coordenadas, direccion y longitud de la palabra para comprobar las soluciones */
        sopa->solucions[i].x = x;
        sopa->solucions[i].y = y;
        sopa->solucions[i].dir = d;
        sopa->solucions[i].longitud = p_long;
        // printf("%8s -> %d %d %d\n", sopa->paraules[i].contingut,x,y,d);
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
    // for (int i = 0; i < sopa->dim * sopa->dim; i++) {
	// 	if (sopa->lletres[i] == '-') {
	// 		sopa->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
    //     }
    // }
}

/* Funcion que devuelve true si */
bool sopa_acabada ( struct Sopa_t * sopa ) {
    bool acabada;
    acabada = sopa->rendicio || (sopa->n_encerts == sopa->n_paraules);
    return acabada;
}

/* No ESTA FET */
void pedir_jugada ( struct Sopa_t * sopa ) {
    char paraula[100]; // Guardar la paraula RENDICIO
    int x, y, d;
    bool encertada;
    int i, aux;

    /* */
    printf("\nRENDEIXES?:");
    getchar();
    fgets(paraula, 100, stdin);
    paraula[strcspn(paraula,"\n")] = '\0'; //Cambiar salto de linea de fgets por null char

    /* Comprovar si l'usuari ha escrit "RENDICIO" */
    if ( strcmp( paraula, "RENDICIO") == 0 ) {
        /* Si es rendeix s'han de marcar totes les paraules, o les que quedin per marcar */
        sopa->rendicio = true;
        for ( i = 0; i < sopa->n_paraules; i++) {
            if ( ! sopa->paraules[i].encertada ) {
                x = sopa->solucions[i].x;
                y = sopa->solucions[i].y;
                d = sopa->solucions[i].dir;

                /* Bucle que marca la paraula */
                aux = 0;
                while ( abs(aux) < sopa->solucions[i].longitud ) {
                    if ( abs(d) == 1 )
                        sopa->encertades[y*sopa->dim + x+aux] = true;
                    else
                        sopa->encertades[(y+aux)*sopa->dim + x] = true;
                    aux = ( d < 0 ) ? aux-1 : aux+1;
                }
            }

            /* Eliminar-la de la llista o marcar-la com encertada */
            sopa->paraules[i].encertada = true;
        }
    } else {
        /* Supuestamente ha encontrado una palabra */
        /* Pedimos Coordenadas, direccion y comprovamos que sean validas */
        do {
            printf("Cord i Dir?:");
            scanf("%d %d %d", &x, &y, &d);
            // printf("x:%d\ny:%d\nd:%d\n", x, y, d);
        } while ( (x < 0 || x > MAX_DIM) || (y < 0 || y > MAX_DIM) || (abs(d) != 2 && abs(d) != 1) );

        /* Ajustar les coordenades del usuari per a usar-les */
        x = x - 1;
        y = y - 1;

        /* Comprobar si les coordenades i direccio es corresponen amb alguna paraula */
        encertada = false;
        for (i = 0; i < sopa->n_paraules && ! encertada; i++) {
            if ( x == sopa->solucions[i].x && y == sopa->solucions[i].y && d == sopa->solucions[i].dir ) {
                encertada = true;
                aux = i;
            }
        }

        /* Marcarla si les dades son correctes i no ha sigut encertada abans */
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

/* Procediment que allibera les dues taules (lletres, encertades) de l'struct sopa,
    creades previament amb malloc() */
void tancar_sopa ( struct Sopa_t * sopa ) {
    free(sopa->lletres);
    free(sopa->encertades);
}
