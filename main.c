//  gcc *.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o WarmingUp


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "textual.h"
#include "grafica.h"

int main (int argc, char * argv[])
{
    char * ficheiro1 = NULL;
    char * ficheiro2 = NULL;
    //UNICODE *v_paises=create_list();
    //UNICODE *v_cidades=create_list();
    int modo = obterParametros(argc,argv,&ficheiro1,&ficheiro2);
    //int anomax_paises = 0, anomin_paises = 0;
    //int anomax_cidades = 0, anomin_cidades = 0;

    //printf("%s\n", ficheiro1);

    if(modo == 0)
    {
        //leitura_dados_paises(v_paises, ficheiro1, &anomax_paises, &anomin_paises);
        //leitura_dados_cidades(v_cidades, ficheiro2, &anomax_cidades, &anomin_cidades);
        //printf("%d %d\n", anomax_paises, anomin_paises);
        //printf("%d %d\n", anomax_cidades, anomin_cidades);
        //TEXTUAL(&v_paises, &v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
        TEXTUAL(ficheiro1, ficheiro2);
        //printList(v_paises);
        //printf("\n\n\n");
        //printListCidades(v_cidades);
    }
    else if (modo == 1)
    {
        GRAFICO(ficheiro2);
    }


    /*
    free(v_paises);
    free(v_cidades);
    free(ficheiro1);
    free(ficheiro2);

	*/
    return EXIT_SUCCESS;
}








