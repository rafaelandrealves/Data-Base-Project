#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textual.h"

#define MAX_SIZE 200


/*  =========================================================
                    MODO TEXTUAL
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void TEXTUAL(char * ficheiro1, char * ficheiro2)
{
    UNICODE *v_paises=create_list();
    UNICODE *v_cidades=create_list();
    UNICODE * vetorLista[2019] = {NULL};

    int anomax_paises = 0, anomin_paises = 0;
    int anomax_cidades = 0, anomin_cidades = 0;



    leitura_dados_paises(v_paises,vetorLista, ficheiro1, &anomax_paises, &anomin_paises);
    //printList(v_paises);
    leitura_dados_cidades(v_cidades, ficheiro2, &anomax_cidades, &anomin_cidades);
    //printf("%d %d\n", anomax_paises, anomin_paises);
	//printf("%d %d\n", anomax_cidades, anomin_cidades);
    menu1(&v_paises, &v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    //printList(v_paises);
	printf("\n\n\n");
	//printListCidades(v_cidades);

    printList(v_paises);

    /*UNICODE * aux = v_paises;
    while(v_paises!= NULL)
    {
		free(aux->payload);
		aux = v_paises;
		v_paises = v_paises->next;
		free(aux);
	}*/

    free(v_paises);
    free(v_cidades);
    free(ficheiro1);
    free(ficheiro2);
}


/*  =========================================================
                    MENU PRINCIPAL
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1(UNICODE **v_paises, UNICODE ** v_cidades,UNICODE *vetorLista[2019], int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char * ficheiro1, char * ficheiro2)
{
    int aux = 0, check = 0;
    char buffer[MAX_SIZE];

    printf("=========================================================================\n\t\t\tMENU PRINCIPAL\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("0/ENTER. Sair da aplicação\n1. Filtragem de dados\n2. Historico de temperaturas\n3. Analise de temperaturas por ano\n4. Analise da temperatura global\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("0/ENTER. Sair da aplicação\n1. Filtragem de dados\n2. Historico de temperaturas\n3. Analise de temperaturas por ano\n4. Analise da temperatura global\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }
    switch (aux)
    {
        case 0:
            printf("=========================================================================\n\t\t\tAPLICAÇÃO FECHADA\n=========================================================================\n");
            break;
        case 1:
            // Filtragem de dados
            menu1_1(v_paises,v_cidades,vetorLista,anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            // Histórico de temperatura
            menu1_2(*v_paises,*v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            // Análise de temperatura para um ano
            menu1_3(*v_paises,*v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 4:
            // Análise da temperaura global - Moving Average
            menu1_4(*v_paises, *v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades,ficheiro1,ficheiro2);
            menu1(v_paises,v_cidades,vetorLista,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }



}


/*  =========================================================
                    FILTRAGEM DE DADOS
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1(UNICODE **v_paises, UNICODE ** v_cidades,UNICODE *vetorLista[2019], int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char * ficheiro1, char * ficheiro2)
{
    int aux = 0, check = 0;
    char buffer[MAX_SIZE];
    printf("=========================================================================\n\t\t\tFILTRAGEM DE DADOS\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Limpa critérios\n\t2. Escolhe intervalo para análise\n\t3. Escolhe mês para analise\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Limpa critérios\n\t2. Escolhe intervalo para análise\n\t3. Escolhe mês para analise\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }

    switch(aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            // FUNÇÃO PARA LIMPAR CRITÉRIOS
            menu1_1_1(v_paises, v_cidades,vetorLista, ficheiro1, ficheiro2);
            menu1(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            // FUNÇÃO PARA INTERVALO PARA ANÁLISE
            menu1_1_2(v_paises, v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades);
            menu1(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            // FUNÇÃO PARA ANALISAR MÊS
            menu1_1_3(v_paises, v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades);
            menu1(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }

}



/*  =========================================================
                HISTÓRICO DE TEMPERATURAS
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_2(UNICODE *v_paises, UNICODE * v_cidades,UNICODE *vetorLista[2019], int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char * ficheiro1, char * ficheiro2)
{
    int aux = 0, check = 0;
    char buffer[MAX_SIZE];

    printf("=========================================================================\n\t\t\tHISTÓRICO DE TEMPERATURAS\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Global: aplica-se a todos os paises\n\t2. Por pais: aplica-se a um unico pais\n\t3. Por cidade: aplica-se a uma unica cidade\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Global: aplica-se a todos os paises\n\t2. Por pais: aplica-se a um unico pais\n\t3. Por cidade: aplica-se a uma unica cidade\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }

    switch (aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            //GLOBAL
            menu1_2_1(v_paises, anomax_paises, anomin_paises);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            //POR PAIS
            menu1_2_2(v_paises, anomax_paises, anomin_paises);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            // POR CIDADE
            menu1_2_3(v_cidades, anomax_cidades, anomin_cidades);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_2(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }
}


/*  =========================================================
                ANÁLISE DE TEMPERATURA POR ANO
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_3(UNICODE *v_paises, UNICODE * v_cidades,UNICODE *vetorLista[2019], int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char * ficheiro1, char * ficheiro2)
{
    int aux = 0, check = 0,ano = 0;
    char buffer[MAX_SIZE];

    printf("=========================================================================\n\t\t\tANÁLISE DE TEMPERATURA POR ANO\n=========================================================================\n");
    printf("Escolha o ano que deseja estudar [%d;%d]: ", anomin_paises, anomax_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &ano);
    while(check != 1 || ano>anomax_paises || ano<anomin_paises)
    {
        printf("Ano inválido! Volte a introduzir o ano que deseja estudar [%d;%d]: ", anomin_paises, anomax_paises);
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &ano);
    }
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Analisa por pais\n\t2. ANalisa por cidade\n\t3. Por cidade: aplica-se a uma unica cidade\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Analisa por pais\n\t2. Analisa por cidade\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }



    switch(aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            // ANÁLISE POR PAIS
            menu1_3_1(v_paises, anomax_paises, anomin_paises, ano);
            menu1(&v_paises, &v_cidades,vetorLista,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            //ANÁLISE POR CIDADE
            menu1_3_2(v_cidades, anomax_cidades, anomin_cidades,ano);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_3(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }

}


/*  =========================================================
        ANÁLISE DA TEMPERATURA GLOBAL - MOVING AVERAGE
----------------------------------------------------------------------------------------------------------------------------------------
    =========================================================*/
void menu1_4(UNICODE *v_paises, UNICODE * v_cidades,UNICODE *vetorLista[2019], int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char * ficheiro1, char * ficheiro2)
{
    char buffer[MAX_SIZE];
    int aux=0;
    int check = 0;
    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA GLOBAL - MOVING AVERAGE\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Análise Global\n\t2. Análise por pais\n\t3.Análise por cidade\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    while (check != 1 || aux > 3 || aux < 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Análise Global\n\t2. Análise por pais\n\t3.Análise por cidade\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }


    switch(aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            // ANÁLISE GLOBAL
            menu1_4_1(v_paises, anomin_paises);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            //ANÁLISE POR PAIS
            menu1_4_2(v_paises, anomin_paises);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            menu1_4_3(v_cidades, anomin_paises);
            menu1(&v_paises,&v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
            //ANALISE POR CIDADE
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_4(v_paises,v_cidades,vetorLista, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }

}

void menu1_4_1(UNICODE *copia,float minficheiro){


    int intervalo=0,i=0;
    float minimo=100.0f;
    float maximo=-100.0f;
    float diferencamax=0.0f;
    int vetoranalise[6]={1860,1910,1960,1990,2013};
    char buffer[100]={'\0'};
    int check=0;

    printf("Introduza o intervalo que pretenda:\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while(check!=1 ||intervalo > 12 || intervalo<1)
    {
        printf("Volte a introduzir o número do intervalo  [1;12]:");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &intervalo);
    }


    while(i<5){
        minimo=100.0f;
        maximo=-100.0f;
        movingAverageG(copia->next->next,&maximo,&minimo,minficheiro,intervalo,vetoranalise[i]);
        diferencamax=maximo-minimo;
        if(maximo!=-100.0f && minimo!=100.0f){
            printf("O max para %d é %f\n",vetoranalise[i],maximo);
            printf("O min para %d é  %f\n",vetoranalise[i],minimo);
            printf("A diferença é %f\n",diferencamax);}
        i++;
        }


    }


void menu1_4_2(UNICODE *copia,float minficheiro){
    int vetoranalise[6]={1860,1910,1960,1990,2013};
    int check=0, intervalo=0;
    char pais[100]={'\0'};
    float minimo=100.0f;
    float maximo=-100.0f;
    float diferencamax=0.0f;
    char buffer[100]={'\0'};
    int i=0;

    printf("Introduza o intervalo que pretenda:\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while(check!=1 ||intervalo > 12 || intervalo<1)
    {
        printf("Volte a introduzir o número do inertvalo  [1;12]:");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &intervalo);
    }
    printf("Introduza o pais para o cálculo: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%s", pais);
    while(check!=1)
    {
        printf("Volte a introduzir o pais\n ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%s", pais);
    }
    pais[strlen(pais)]='\0';
        while(i<5){
        minimo=100.0f;
        maximo=-100.0f;
        movingAveragePais(copia->next->next,&maximo,&minimo,pais,minficheiro,intervalo,vetoranalise[i]);
        diferencamax=maximo-minimo;
        if(maximo!=-100.0f && minimo!=100.0f){
        printf("O max para %d é %f\n",vetoranalise[i],maximo);
        printf("O min para %d é  %f\n",vetoranalise[i],minimo);
        printf("A diferença é %f\n",diferencamax);}
        i++;
        }


}

void menu1_4_3(UNICODE *copia,float minficheiro){
    int vetoranalise[6]={1860,1910,1960,1990,2013};
    int check=0, intervalo=0;
    float minimo=100.0f;
    float maximo=-100.0f;
    float diferencamax=0.0f;
    char cidade[100]={'\0'};
    char buffer[100]={'\0'};
    int i=0;

    printf("Introduza o intervalo que pretenda:\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while(check!=1 ||intervalo > 12 || intervalo< 1)
    {
        printf("Volte a introduzir o número do inertvalo  [1;12]:");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &intervalo);
    }
    printf("Introduza a cidade para o cálculo: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%s", cidade);
    while(check!=1)
    {
        printf("Volte a introduzir o cidade\n ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%s", cidade);
    }
    cidade[strlen(cidade)]='\0';
        while(i<5){
        minimo=100.0f;
        maximo=-100.0f;
        movingAverage_cidade(copia->next->next,&maximo,&minimo,cidade,minficheiro,intervalo,vetoranalise[i]);
        diferencamax=maximo-minimo;
        if(maximo!=-100.0f && minimo!=100.0f){
        printf("O max para %d é %f\n",vetoranalise[i],maximo);
        printf("O min para %d é  %f\n",vetoranalise[i],minimo);
        printf("A diferença é %f\n",diferencamax);}

        i++;
        }


}










/*  =========================================================
                    LIMPAR CRITÉRIOS
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1_1(UNICODE **v_paises, UNICODE ** v_cidades,UNICODE *vetorLista[2019], char * ficheiro1, char * ficheiro2)
{
    printf("=========================================================================\n\t\t\tLIMPAR CRITÉRIOS\n=========================================================================\n");
    int anomin_lixo_paises = 0;
    int anomax_lixo_paises = 0;
    int anomin_lixo_cidades = 0;
    int anomax_lixo_cidades = 0;
    //UNICODE * auxiliar_paises = NULL;
    //UNICODE * auxiliar_cidades = NULL;
    /*
    if(*v_aux_paises != v_paises)
    {
        auxiliar_paises = *v_aux_paises;
        *v_aux_paises = v_paises;
        free(auxiliar_paises);
    }
    if(*v_aux_cidades != v_cidades)
    {
        auxiliar_cidades = *v_aux_cidades;
        *v_aux_cidades = v_cidades;
        free(auxiliar_cidades);
    }*/


	clearList(v_paises);
	clearList(v_cidades);

    leitura_dados_paises(*v_paises,vetorLista, ficheiro1, &anomax_lixo_paises, &anomin_lixo_paises);
    //printList(*v_paises);
    leitura_dados_cidades(*v_cidades, ficheiro2, &anomax_lixo_cidades, &anomin_lixo_cidades);
	//printListCidades(*v_cidades);
    printf("=========================================================================\n\t\t\tCRITÉRIOS LIMPOS\n=========================================================================\n");
}


/*  =========================================================
                ESCOLHE INTERVALO PARA ANÁLISE
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1_2(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades)
{
    printf("=========================================================================\n\t\tESCOLHA DE INTERVALO PARA ANÁLISE\n=========================================================================\n");

    char buffer[MAX_SIZE]={'\0'};
    int check=0;
    int mes_paises,ano_paises=0, mes_cidades = 0, ano_cidades = 0;

    // OS VALORES SÃO PEDIDOS PARA OS PAISES E PARA AS CIDADES POIS PODEM NÃO TER OS MESMOS ANOS

    printf("PARA OS PAISES: Insira o mês e ano que deseja fixar segundo a forma mês:ano. Mes:[1;12]. Ano:[%d;%d]\n", anomin_paises, anomax_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d:%d", &mes_paises,&ano_paises);
    while((check != 2) || (mes_paises>12 || mes_paises<1) || (ano_paises<anomin_paises || ano_paises>anomax_paises))
    {
        printf("A data não foi bem introduzida! Volte a introduzir a data: \n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d:%d", &mes_paises,&ano_paises);
    }
    printf("PARA AS CIDADES: Insira o mês e ano que deseja fixar segundo a forma mês:ano. Mes:[1;12]. Ano:[%d;%d]\n", anomin_cidades, anomax_cidades);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d:%d", &mes_cidades,&ano_cidades);
    while((check != 2) || (mes_cidades>12 || mes_cidades<1) || (ano_cidades<anomin_cidades || ano_cidades>anomax_cidades))
    {
        printf("A data não foi bem introduzida! Volte a introduzir a data: \n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d:%d", &mes_cidades,&ano_cidades);
    }

    *v_paises = limparintervalo(v_paises, anomax_paises, anomin_paises, mes_paises, ano_paises);
    *v_cidades = limparintervalo(v_cidades, anomax_cidades, anomin_cidades, mes_cidades, ano_cidades);
    //printList(*v_paises);
    //printListCidades(*v_cidades);



    printf("=========================================================================\n\t\t\tCRITÉRIO APLICADO\n=========================================================================\n\n");
}


/*  =========================================================
                ESCOLHE MÊS PARA ANÁLISE
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1_3(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades)
{
    char buffer[200]={'\0'};
    int check=0;
    int mesinicial,mesfinal=0;

    printf("=========================================================================\n\t\t\tESCOLHA DE MÊS PARA ANÁLISE\n=========================================================================\n");
    printf("Insira o mês inicial e final que deseja fixar segundo a forma mêsinicial:mêsfinal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d:%d", &mesinicial,&mesfinal);
    while((check != 2) || (mesinicial>12 || mesinicial<1 || mesfinal<1 || mesfinal>12) || mesfinal == mesinicial)
    {
        printf("Volte a introduzir os números\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d:%d", &mesinicial,&mesfinal);
    }


    *v_paises = limpaMeses(v_paises, anomax_paises, anomin_paises, mesinicial, mesfinal);
    //printList(*v_paises);
    *v_cidades = limpaMeses(v_cidades, anomax_cidades, anomin_cidades, mesinicial, mesfinal);
    //printListCidades(*v_cidades);



    printf("=========================================================================\n\t\t\tCRITÉRIO APLICADO\n=========================================================================\n\n");
}


/*  =========================================================
                ANÁLISE GLOBAL DA TEMPERATURA
    \param v_paises: lista dos paises
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    =========================================================*/
void menu1_2_1(UNICODE *v_paises, int anomax_paises, int anomin_paises)
{
    float min = 500.0f, max = -50.0f, med = 0.0f, soma = 0.0f;
    int num = 0, anoFinal = 0, numLinhas = 0, valDados = -1;
    UNICODE * aux = v_paises->next;
    UNICODE * tmp;
    char comando=0;
    char buffer[MAX_SIZE];
    int intervalo = 0, check = 0;
    printf("=========================================================================\n\t\t\tANÁLISE GLOBAL DA TEMPERATURA\n=========================================================================\n");

    printf("Introduza o tempo de intervalo para análise [1, %d]: ", anomax_paises-anomin_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while (check == 0 || intervalo <= 0 || intervalo > anomax_paises-anomin_paises)
    {
        printf("O valor não é valido! Volte a introduzir um intervalo de tempo para análise: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &intervalo);
    }

    while(aux->next != NULL)
    {
        min = 500.0f;
        max = -50.0f;
        med = 0.0f;
        soma = 0.0f;
        num = 0;
        comando = 0;
        anoFinal = aux->payload->dt.ano + intervalo - 1;
        tmp = aux;
        do
        {
            soma += (tmp->payload->temperatura);
            num++;
            if(tmp->payload->temperatura > max) max = tmp->payload->temperatura;
            if(tmp->payload->temperatura < min) min = tmp->payload->temperatura;
            valDados = 1;
            tmp = tmp->next;
        }while((tmp->next != NULL) && (tmp->payload->dt.ano<=anoFinal));
        med = soma/num;
        if(anoFinal >= anomax_paises) // para no intervalo não aparecer um ano superior ao ano máximo
        {
            if(valDados == 1 && !(max == 0 && min == 0 && med == 0)) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anomax_paises, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anomax_paises);
        }
        else
        {
            if(valDados == 1 && !(max == 0 && min == 0 && med == 0)) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        }
        valDados = 0;
        while(aux->next != NULL && aux->payload->dt.ano <= anoFinal)
        {
            aux = aux->next;
        }
        if(numLinhas == 20)
        {
            scanf("%c", &comando);
            if(comando == 97 && comando != 0)
            {
                numLinhas = 0;
                comando = 0;
            }
            else if(comando == 113 && comando != 0)
            {
                getchar();
                return;
            }
            getchar(); // vai buscar o \n
        }
        numLinhas++;
    }
}


/*  =========================================================
                ANÁLISE DA TEMPERATURA DE UM PAIS
    \param v_paises: lista dos paises
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    =========================================================*/
void menu1_2_2(UNICODE *v_paises, int anomax_paises, int anomin_paises)
{
    char nome_pais[MAX_SIZE];
    char buffer[MAX_SIZE];
    int i = 0, num = 0, anoFinal = 0, numLinhas = 0, valDados = -1;
    float min = 500.0f, max = -50.0f, med = 0.0f, soma = 0.0f;
    UNICODE * aux = v_paises->next;
    UNICODE * tmp;
    int check = 0, intervalo = 0;
    char comando = 0;

    printf("=========================================================================\n\t\t\tANÁLISE DA TEMPERATURA DE UM PAIS\n=========================================================================\n");
    printf("Introduza o tempo de intervalo para análise [1, %d]: ", anomax_paises-anomin_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while (check == 0 || intervalo <= 0 || intervalo > anomax_paises-anomin_paises)
    {
        printf("O valor não é valido! Volte a introduzir um intervalo de tempo para análise: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &intervalo);
    }
    printf("Introduza o nome de um pais: ");
    fgets(nome_pais, MAX_SIZE, stdin);
    for(i = strlen(nome_pais)-1; i < MAX_SIZE; i++)
    {
        nome_pais[i] = '\0';
    }
    aux = v_paises->next;
    while(aux->next != NULL)
    {
        min = 500.0f;
        max = -50.0f;
        med = 0.0f;
        soma = 0.0f;
        num = 0;
        comando = 0;
        anoFinal = aux->payload->dt.ano + intervalo - 1;
        tmp = aux;
        do
        {
            if(strstr(tmp->payload->pais, nome_pais) != NULL)
            {
                soma += (tmp->payload->temperatura);
                num++;
                if(tmp->payload->temperatura > max) max = tmp->payload->temperatura;
                if(tmp->payload->temperatura < min) min = tmp->payload->temperatura;
                valDados = 1;
            }
            tmp = tmp->next;
        }while((tmp->next != NULL) && (tmp->payload->dt.ano<=anoFinal));
        med = soma/num;
        if(anoFinal > anomax_paises) // para no intervalo não aparecer um ano superior ao ano máximo
        {
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anomax_paises, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anomax_paises);
        }
        else
        {
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        }
        //if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
        //else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        valDados = 0;
        while(aux->next != NULL && aux->payload->dt.ano <= anoFinal)
        {
            aux = aux->next;
        }
        if(numLinhas == 20)
        {
            scanf("%c", &comando);
            if(comando == 97 && comando != 0)
            {
                numLinhas = 0;
                comando = 0;
            }
            else if(comando == 113 && comando != 0)
            {
                getchar();
                return;
            }
            getchar();
        }
		numLinhas++;

    }
}


/*  =========================================================
            ANÁLISE DA TEMPERATURA DE UMA CIDADE
    \param v_cidades: lista das cidades
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    =========================================================*/
void menu1_2_3(UNICODE * v_cidades, int anomax_cidades, int anomin_cidades)
{
    char nome_cidade[MAX_SIZE];
    char buffer[MAX_SIZE];
    int i = 0, num = 0, anoFinal = 0, numLinhas = 0, valDados = -1;
    float min = 500.0f, max = -50.0f, med = 0.0f, soma = 0.0f;
    int intervalo = 0, check = 0;
    UNICODE * tmp;
    UNICODE * aux = v_cidades->next;
    char comando = 0;

    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA DE UMA CIDADE\n=========================================================================\n");
    printf("Introduza o tempo de intervalo para análise [1, %d]: ", anomax_cidades-anomin_cidades);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while (check == 0 || intervalo <= 0 || intervalo > anomax_cidades-anomin_cidades)
    {
        printf("O valor não é valido! Volte a introduzir um intervalo de tempo para análise: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &intervalo);
    }

    printf("Introduza o nome de uma cidade: ");
    fgets(nome_cidade, MAX_SIZE, stdin);
    for(i = strlen(nome_cidade)-1; i < MAX_SIZE; i++)
    {
        nome_cidade[i] = '\0';
    }
    aux = v_cidades->next;
    while(aux->next != NULL)
    {
        min = 500.0f;
        max = -50.0f;
        med = 0.0f;
        soma = 0.0f;
        num = 0;
        comando = 0;
        anoFinal = aux->payload->dt.ano + intervalo - 1;
        tmp = aux;
        do
        {
            if(strstr(tmp->payload->cidade, nome_cidade) != NULL)
            {
                soma += (tmp->payload->temperatura);
                num++;
                if(tmp->payload->temperatura > max) max = tmp->payload->temperatura;
                if(tmp->payload->temperatura < min) min = tmp->payload->temperatura;
                valDados = 1;
            }
            tmp = tmp->next;
        }
        while((tmp->next != NULL) && (tmp->payload->dt.ano<=anoFinal));

        med = soma/num;
        if(anoFinal > anomax_cidades) // para no intervalo não aparecer um ano superior ao ano máximo
        {
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anomax_cidades, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anomax_cidades);
        }
        else
        {
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        }
        //if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
        //else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        valDados = 0;
        while(aux->next != NULL && aux->payload->dt.ano <= anoFinal)
        {
            aux = aux->next;
        }
        if(numLinhas == 20)
        {
            scanf("%c", &comando);
            if(comando == 97 && comando != 0)
            {
                numLinhas = 0;
                comando = 0;
            }
            else if(comando == 113 && comando != 0)
            {
                getchar();
                return;
            }
            getchar();
        }
        numLinhas++;

    }
}


/*  =========================================================
            ANÁLISE DA TEMPERATURA POR ANO POR PAIS
-----------------------------------------------------------------------------------------------------------------------------
    =========================================================*/
void menu1_3_1(UNICODE *v, int anomax, int anomin, int ano)
{
    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA POR ANO POR PAIS\n=========================================================================\n");
       int check=0;
    char buffer[100]={'\0'};
    int numPaises=0;
    printf("Qual o número de paises que pretende ver para cada critério? [1;20]: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &numPaises);
    while(check!=1 || numPaises > 20 || numPaises< 1)
    {
        printf("Volte a introduzir o número de paises para cada critério [1;20]: ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &numPaises);
    }



    analise_da_temperatura_ano_pais(v->next->next,numPaises, ano);

}


/*  =========================================================
            ANÁLISE DA TEMPERATURA POR ANO POR CIDADE
            -----------------------------------------------------------------------------------------------------
    =========================================================*/
void menu1_3_2(UNICODE * v_cidades, int anomax_paises, int anomin_cidades,int ano)
{      int check=0;
    char buffer[100]={'\0'};
    int numCidades=0;

    printf("Qual o número de cidades que pretende ver para cada critério? [1;20]: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &numCidades);
    while(check!=1 || numCidades > 20 || numCidades < 1)
    {
        printf("Volte a introduzir o número de paises para cada critério [1;20]: ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &numCidades);
    }

    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA POR ANO POR CIDADE\n=========================================================================\n");
    analise_da_temperatura_ano_cidade(v_cidades->next->next,numCidades, ano);
}


/*  =========================================================
            LER OS PARAMETROS DE EXECUÇÃO DO PROGRAMA
    \param argc: número de argumentos introduzidos
    \param argv[]: argumentos introduzidos no terminal na execução do programa
    \param ficheiron1: nome do ficheiro dos paises
    \param ficheiron2: nome do ficheiro das cidades
    \return: retorna 1 caso seja modo gráfico; retorna 0 para modo textual
    =========================================================*/
int obterParametros(int argc,char* argv[], char** ficheiron1,char ** ficheiron2)
{
    char * ficheiro1 = NULL;
    char * ficheiro2 = NULL;
    int fich1 = -1, fich2 = -1;
    int varmodo = -1;
    int erro=0;

    if(argc != 6)
    {
        printf("Parâmetros de inicialização inválidos!!!\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < argc; i++)
    {
        //printf("%s\t",argv[i]);
        //printf("%d\n",(int)strlen(argv[i]));
        if(strstr(argv[i], "-f1") != NULL)
        {
            fich1 = i;
            erro++;
        }
        if(strstr(argv[i], "-f2") != NULL)
        {
            fich2 = i;
            erro++;
        }
        if((strstr(argv[i], "-g") != NULL) || (strstr(argv[i], "-t") != NULL))
        {
            varmodo = i;
            erro++;
        }
    }

    if(erro != 3)
    {
        printf("Os argumentos introduzidos não estão corretos!\n");
        exit(EXIT_FAILURE);
    }

    ficheiro1 = (char *) checkedMalloc((strlen(argv[fich1+1] + 1)) * sizeof(char));
    strcpy(ficheiro1, argv[fich1+1]);
    *ficheiron1=ficheiro1;
    //printf("%s\n", ficheiro1);
    ficheiro2 = (char *) checkedMalloc((strlen(argv[fich2+1] + 1)) * sizeof(char));
    strcpy(ficheiro2, argv[fich2+1]);
    //printf("%s\n", ficheiro2);
    *ficheiron2=ficheiro2;

    if(strcmp(argv[varmodo], "-g") == 0)
    {
        return 1;
    }
    else if (strcmp(argv[varmodo], "-t") == 0)
    {
        return 0;
    }
	printf("Erro na introdução dos parametros");
	exit(EXIT_FAILURE);

}


/*  =========================================================
            LEITURA DE DADOS DO FICHEIRO DE PAISES
    \param v_paises: lista dos paises
    \param ficheiro1: ficheiro para os paises
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    =========================================================*/
void leitura_dados_paises(UNICODE *v_paises,UNICODE *vetorLista[2019],char *ficheiro1, int* anomax_paises, int* anomin_paises)
{
    FILE * fp = NULL;
    int check=0;
    char buffer[MAX_SIZE]={'\0'};

    //    dados_temp *auxv;
    dados_temp *vect = NULL;

    char nome[MAX_SIZE]={'\0'};
    int data_ano=0;
    int data_mes=0;
    int data_dia=0;
    float temperatura=0.0f;
    float incerteza=0.0f;
    int _anomax = 0000;
    int _anomin = 5000;
    fp=checkedFile(ficheiro1,"r");


    listvector(vetorLista);
    while(fgets(buffer,MAX_SIZE,fp)!=NULL)
    {

        check = sscanf(buffer,"%d-%d-%d,%f,%f,%[^\n]",&data_ano,&data_mes,&data_dia,&temperatura,&incerteza,nome);

        if(check==6)
        {
            vect = (dados_temp*) checkedMalloc(sizeof(dados_temp));
			if(data_ano > _anomax) _anomax = data_ano;
			if(data_ano < _anomin) _anomin = data_ano;
			vect->dt.ano=data_ano;
			vect->dt.mes=data_mes;
			vect->dt.dia=data_dia;
			vect->temperatura=temperatura;
			vect->incerteza=incerteza;
			strcpy(vect->pais,nome);
			//printf("%d-%d-%d,%f,%f,%s\n",vect[i].dt.ano,vect[i].dt.mes,vect[i].dt.dia,vect[i].temperatura,vect[i].incerteza,vect[i].pais);
			//insert_node(*v, &vect[i]);
			insert_sorted(vect, vetorLista[vect->dt.ano]);
        }

    }
    *anomax_paises = _anomax;
    *anomin_paises = _anomin;
    v_paises->next = juntarlista(vetorLista, *anomax_paises, *anomin_paises);
    fclose(fp);
    for (int i = 0; i<2019; i++) free(vetorLista[i]);



}


/*  =========================================================
                        CRIAR UMA LISTA
    \return: retorna um ponteiro para o dummy node
    =========================================================*/
UNICODE * create_list ()
{
    dados_temp auxiliar; // conteúdo indiferente para o DAMMY NODE

    return create_node(&auxiliar);
}


/*  =========================================================
                    CRIAR UM NOVO NÓ DA LISTA
    \param _payload: apontador para o conteudo para adicionar ao nó da lista
    \return: retorna um ponteiro para o novo elemento
    =========================================================*/
UNICODE * create_node(dados_temp * _payload)
{
    UNICODE * aux = NULL;

    aux = (UNICODE *) checkedMalloc(sizeof(UNICODE));

    aux->next = NULL;
    aux->prev = NULL;
    aux->payload = _payload;
    return aux;
}


/*  =========================================================
                    INSERIR UM NOVO NÓ DA LISTA
    \param _head: apontador para a cabeça da lista
    \param _payload: apontador para o conteudo a adicionar
    =========================================================*/
void insert_node(UNICODE * _head, dados_temp * _payload)
{
    UNICODE *new_node = create_node(_payload);

    new_node->prev = _head;
    new_node->next = _head->next;
    _head->next =new_node;
    if(new_node->next != NULL)
       new_node->next->prev=new_node;
}


/*  =========================================================
                IMPRIMIR A LISTA DOS PAISES
    \param head: ponteiro para a cabeça da lista a imprimir
    =========================================================*/
void printList(UNICODE * head)
{
    UNICODE * aux = NULL;
    FILE * fp = NULL;

    fp = fopen("outpaises.txt", "w");


    aux = head->next;
    while(aux != NULL)
    {
        fprintf(fp, "%d-%d-%d,%f,%f,%s\n",aux->payload->dt.ano,aux->payload->dt.mes,aux->payload->dt.dia,aux->payload->temperatura,aux->payload->incerteza,aux->payload->pais);
        aux=aux->next;
    }
    fclose(fp);

}


/*  =========================================================
                INSERÇÃO ORDENADA POR DATA
    \param _payload: apontador para o conteudo a inserir na lista
    \param vectList: lista dos paises para inserir o novo nó
    =========================================================*/
void insert_sorted(dados_temp * _payload, UNICODE * vectList)
{
    UNICODE *aux=NULL;
    UNICODE * new_node = create_node(_payload);
    int colocou=0;
    aux=vectList;
    do
    {
        if(aux->next!= NULL && new_node->payload->dt.mes < aux->next->payload->dt.mes)
        {
            new_node->prev = aux;
            new_node->next = aux->next;
            aux->next = new_node;
            if(new_node->next != NULL)
                new_node->next->prev=new_node;
            colocou=1;
            //vectList = new_node->next;
            return;
        }
     aux=aux->next;
    }while(aux != NULL);

    if(colocou==0){//insert_tail
            new_node=insert_tail(vectList,_payload);
            vectList = new_node;
        }
}


/*  =========================================================
                    INSERIR UM NÓ NA CAUDA
    \param _head: cabeça da lista a inserir o nó
    \param _payload: apontador para o conteúdo a inserir
    \return: retorna um apontador para o elemento que foi adicionado
    =========================================================*/
UNICODE * insert_tail(UNICODE *_head,dados_temp *_payload)
{

    UNICODE *aux = NULL;
    UNICODE *new_elem = NULL;
    new_elem = create_node(_payload);
    if(_head->next==NULL) // se a lista estiver vazia
    {
        _head->next = new_elem;//aponto a head para o novo elemento;
        new_elem->prev = _head;
        new_elem->next = NULL;
        return new_elem;
    }
    aux=_head;
    while(aux->next!=NULL){//encontrar o ultimo elemento
        aux=aux->next;
    }

    aux->next=new_elem;
    new_elem->prev=aux;
    return new_elem;
}


/*  =========================================================
                    REMOÇÃO DE UM NÓ DA LISTA
    \param _head: endereço da cabeça da lista
    \return: retorna 0 caso tenha sido removido e -1 se a lista estiver vazia
    =========================================================*/
int remove_nodes(UNICODE **_head)
{
    UNICODE *aux=NULL;
    if(*_head== NULL)
    {
    return -1;// empty list return now
    }
    aux=*_head;
    if((*_head)->next != NULL)
        (*_head)->next->prev = (*_head)->prev; //NÃO SEI SE ESTÁ BEM
    (*_head)->prev->next=(*_head)->next;
    //free(aux->payload);
    free(aux);

    return 0;

}


/*  =========================================================
                ELIMINAÇÃO DE TODA A LISTA
    =========================================================*/
void clearList(UNICODE **_head)
{
    UNICODE *aux=NULL;
    aux=(*_head)->next;
    while(remove_nodes(&aux) != -1)
    {
        if(aux->next!=NULL)
        {
            aux=aux->next;
        }
        else
        {
            return;
        }
    }
}

/*  =========================================================
    COLOCA EM CADA POSIÇÃO DO VETOR UM APONTADOR PARA O DUMMY NODE DE UMA LISTA QUE VAI SER CRIADA NESTE FUNÇÃO
    \param vetor[2019]: vetor que contém apontadores para uma lista com dados do ano igual à posição no vetor
    =========================================================*/
void listvector(UNICODE *vetor[2019])
{
    int i=0;

    //colocar num vetor cada ano com as linhas desorganizadas e depois organizar
    while(i<2019)
    {
       vetor[i] = create_list(); // todas as listas têm um dammy node
        i++;
    }
}


/*  =========================================================
    JUNÇÃO DAS LISTAS QUE CONTÉM DADOS DE UM ANO ORGANIZADOS
    \param vetor[2019]: vetor que contém apontadores para uma lista com dados do ano igual à posição no vetor
    \param anomax: ano maximo do vetor de listas
    \param anomin: ano minimo do vetor de listas
    =========================================================*/
UNICODE* juntarlista(UNICODE *vetor[2019], int anomax, int anomin)
{
    int i=0;
    UNICODE *aux=NULL;
    UNICODE *tmp=NULL;
    UNICODE *retorna=NULL;
    int check=0;
    int check1=0;
    for(i=anomin+1;i<anomax+1;i++)
    {
        if((check==0) && (vetor[i-1] != NULL))
        {
            retorna=vetor[i-1]->next;
        }
        check = 1;

        aux = vetor[i-1];
        while(aux->next != NULL)
        {
            aux = aux->next;
            check1=1;
            tmp = aux;
        }
        if(check1 && vetor[i]->next != NULL)
        {
            if(vetor[i]->next != NULL)//tem dados
            {
                tmp->next = vetor[i]->next;
                vetor[i]->next->prev = tmp;
                //printf("dn+ apagado, linha:: %d\n", i);
            }
            check1=0;
        //printList(vetor[i]);
        }

        //vetor[i-1]->next = vetor[i];
        //vetor[i]->prev = vetor[i-1];
        /*if(vetor[i] != NULL)
        {

            aux=vetor[i]->next;
            while(aux!=NULL)
            {
                aux=aux->next;
            }
            if(aux->next != NULL && vetor[i+1]->next != NULL)
            {
                aux=vetor[i+1]->next;
                vetor[i+1]->next->prev=aux;
            }
            check=1;
        }*/
    }
    if(retorna->next == NULL) printf("é null!! \n");

    //printList(retorna);
    return retorna;
}


/*  =========================================================
    REMOÇÃO DE NÓS ANTERIORES À DATA DEFINIDA PELO UTILIZADOR
    \param v: lista(dos paises ou das cidades) na qual vão ser removidos os dados que não cumpram os critérios definidos pelo utilizador
    \param anomax: ano maximo do vetor de listas
    \param anomin: ano minimo do vetor de listas
    \param mes: mes definido pelo utilizador
    \param ano: ano definido pelo utilizador
    \return: retorna o apontados para o primeiro elemento da nova lista
    =========================================================*/
UNICODE* limparintervalo(UNICODE **v,int anomax, int anomin, int mes, int ano)
{
    UNICODE *temp=NULL;
    //UNICODE *copia=create_list();
    UNICODE *auxiliar;
    temp=(*v)->next;
    //dados_temp *vector;
    //dados_temp *auxv=NULL;               //ATENÇÃO:: ALOCAR MEMÓRIA
    int head=0;
    //int i=ano;
    //int check=0;


    while(head == 0)
    {
        if(temp->payload->dt.ano>=ano && temp->payload->dt.mes>=mes)
        {
            head = 1;
        }
        else
        {
            remove_nodes(&temp);
            temp=temp->next;
        }
    }
    auxiliar = temp;
    /*
    while(i <= anomax && temp->next != NULL)
    {
        vector = temp->payload;
        insert_tail(copia,vector);
        temp=temp->next;
        if(temp->prev->payload->dt.ano != temp->payload->dt.ano)
        {
            i++;
        }
    }
    auxiliar=copia;*/

    return auxiliar;
}


/*  =========================================================
    REMOÇÃO DE NÓS QUE NÃO ESTEJAM ENTRE OS MESES DEFINIDOS PELO UTILIZADOR
    \param v: lista(dos paises ou das cidades) na qual vão ser removidos os dados que não cumpram os critérios definidos pelo utilizador
    \param anomax: ano maximo do vetor de listas
    \param anomin: ano minimo do vetor de listas
    \param mesinicial: mes inicial definido pelo utilizador
    \param mesfinal: mes final defnio pelo utilizador
    \return: retorna o apontador para o inicio da nova lista
    =========================================================*/
UNICODE * limpaMeses(UNICODE **v, int anomax, int anomin, int mesinicial, int mesfinal)
{
    //UNICODE * nova_lista = create_list();
    UNICODE * aux = (*v)->next;
    UNICODE * retorna = NULL;
	int check = 0;
    int anosDiferentes = (mesinicial>mesfinal ? 1 : 0);


    if(anosDiferentes == 0) // os meses pertencem ao mesmo ano, ou seja não é necessário mudar de ano
    {
        while(aux != NULL)
        {
            if((aux->payload->dt.mes >= mesinicial && aux->payload->dt.mes <= mesfinal) && aux->next != NULL)
            {
                //insert_tail(nova_lista, aux->payload);
                if(check == 0)
                {
					retorna = aux;
					check = 1;
				}
                aux = aux->next;
            }
            else
            {
                remove_nodes(&aux);
                aux = aux->next;
            }
        }
    }
    else if(anosDiferentes == 1) // os meses pertencem a anos diferentes
    {
        while(aux != NULL)
        {
            if((aux->payload->dt.mes >= mesinicial || aux->payload->dt.mes <= mesfinal) && aux->next != NULL)
            {
                //insert_tail(nova_lista, aux->payload);
                if(check == 0)
                {
					retorna = aux;
					check = 1;
				}
				aux = aux->next;
            }
            else
            {
                remove_nodes(&aux);
                aux = aux->next;
            }
        }
    }


    /*
    while(aux != NULL)
    {
        while(aux->payload->dt.mes < mesinicial && aux->next != NULL)
        {
            aux = aux->next;
            printf("\t1---%d\n", aux->payload->dt.mes);
        }
        if(anosDiferentes == 0) // os meses estão todos no mesmo ano
        {
            while(aux->payload->dt.mes <= mesfinal && aux->next != NULL)
            {
                insert_tail(nova_lista, aux->payload);
                aux = aux->next;
            }
            aux->
        }
        else if(anosDiferentes == 1) // os meses estão em anos diferentes
        {
            while(aux->payload->dt.mes <= 12 && aux->next != NULL)
            {
                insert_tail(nova_lista, aux->payload);
                aux = aux->next;
            }
            while(aux->payload->dt.mes <= mesfinal && aux->next != NULL)
            {
                insert_tail(nova_lista, aux->payload);
                aux = aux->next;
            }
        }
        aux = aux->next;

    }
    */
    return retorna;

}

/*  =========================================================
    LEITURA DO FICHEIRO DAS CIDADES
    \param v_cidades: lista das cidades
    \param ficheiro2: nome do ficheiro das cidades
    \param anomax_cidades: ano maximo das cidades para retornar para outras funções
    \param anomin_cidades: ano minimo das cidades para retornar para outras funções
    =========================================================*/
void leitura_dados_cidades(UNICODE *v_cidades,char *ficheiro2, int *anomax_cidades, int *anomin_cidades)
{
    FILE * fp = NULL;
    dados_temp * payload;
    UNICODE * vetorLista[2019] = {NULL};

    char buffer[MAX_SIZE];
    char pais[MAX_SIZE];
    char cidade[MAX_SIZE];
    int ano = 0, mes = 0, dia = 0, check = 0, anomax = 0000, anomin = 5000;
    float temperatura = 0.0f, incerteza = 0.0f, nlatitude = 0.0f, nlongitude = 0.0f;
    char clongitude, clatitude;
    char *lixo = NULL;
    fp = checkedFile(ficheiro2, "r");

    listvector(vetorLista);

    while( fgets(buffer, MAX_SIZE, fp) != NULL)
    {
        check = sscanf(buffer, "%d-%d-%d,%f,%f,%[^,],%[^,],%f%c,%f%c%[^\n]",&ano, &mes, &dia,
                &temperatura, &incerteza, cidade, pais, &nlatitude,
                &clatitude, &nlongitude, &clongitude, lixo );

        if(check == 11)
        {
            payload = (dados_temp *) checkedMalloc(sizeof(dados_temp));
			if(ano > anomax) anomax = ano;
			if(ano < anomin) anomin = ano;
			payload->dt.ano = ano;
			payload->dt.mes = mes;
			payload->dt.dia = dia;
			payload->temperatura = temperatura;
			payload->incerteza = incerteza;
			strcpy(payload->pais, pais);
			strcpy(payload->cidade, cidade);
			payload->latitude.angular = nlatitude;
			payload->longitude.angular = nlongitude;
			payload->latitude.direcao = (strcmp(&clatitude, "N") == 0 ? NORTE : SUL);
			payload->longitude.direcao = (strcmp(&clongitude, "W") == 0 ? OESTE : ESTE);

			//printf("%d-%d-%d,%f,%f,%s,%s,%f %c,%f %c\n",ano, mes, dia, temperatura, incerteza, pais, cidade, nlatitude, clatitude, nlongitude, clongitude);
			//insert_tail(v_cidades, payload);
			insert_sorted(payload, vetorLista[payload->dt.ano]);
        }
    }
    *anomax_cidades = anomax;
    *anomin_cidades = anomin;
    v_cidades->next = juntarlista(vetorLista, *anomax_cidades, *anomin_cidades);
    fclose(fp);
    for (int i = 0; i < 2019; i++) free(vetorLista[i]);
}


/*  =========================================================
                IMPRIMIR A LISTA DAS CIDADES
    \param head: ponteiro para a cabeça da lista a imprimir
    =========================================================*/
void printListCidades(UNICODE * head)
{
    UNICODE * aux = head->next;
    //FILE * fp = fopen("outcidades.txt", "w");


    while(aux != NULL)
    {
        printf("%d-%d-%d,%f,%f,%s,%s,%f %d,%f %d\n",aux->payload->dt.ano, aux->payload->dt.mes, aux->payload->dt.dia,
        aux->payload->temperatura, aux->payload->incerteza, aux->payload->cidade, aux->payload->pais,
        aux->payload->latitude.angular, aux->payload->latitude.direcao, aux->payload->longitude.angular,
        aux->payload->longitude.direcao);
        aux = aux->next;
    }

    //fclose(fp);
}


/*  =========================================================
        FUNÇÃO QUE FAZ MALLOC E REALIZA A VERIFICAÇÃO
    \param size: tamanho da memória a alocar
    \return: retorna um ponteiro para esse espaço de memória alocado
    =========================================================*/
void * checkedMalloc(size_t size)
{
	void *mem = malloc(size);
    if(mem == NULL)
    {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return mem;
}


/*  =========================================================
        FUNÇÃO QUE ABRE UM FICHEIRO E RETORNA UM APONTADOR PARA O MESMO.
        FAZ A VERIFICAÇÃO DE VALIDADE DE ABERTURA
    \param fich: nome do ficheiro
    \param modo: modo de abertura do ficheiro: "r", "w", ...
    \return: retorna um ponteiro para o ficheiro aberto
    =========================================================*/
FILE * checkedFile(char * fich, char * modo)
{
	FILE * aux = fopen(fich, modo);
	if (aux == NULL)
	{
		printf("Falha na abertura do ficheiro %s", fich);
		exit(EXIT_FAILURE);
	}
	return aux;
}


void analise_da_temperatura_ano_pais(UNICODE *copia,int numeropaises,int ano)
{
    int i=0;
    int numerodeelementos=0;
    UNICODE *vetor[2019]={NULL};
    Paises *vetorpaises[1000];
    Amplitude *ampvetorpaises[1000]={NULL};
    Paises *vetorfinal[20]={NULL};
    Paises *vetormin[20]={NULL};
    Amplitude *vetoramp[20]={NULL};
    UNICODE *vetoraux[2019]={NULL};


    listvector(vetor);
    listvector(vetoraux);

    organizapaises(copia,&numerodeelementos,ano,vetor);
    organizapaises(copia,&numerodeelementos,ano,vetoraux);
    calculamedia(vetor,numerodeelementos,vetorpaises);
    calculaamplitude(vetoraux,numerodeelementos,ampvetorpaises);
    insertcountries(vetorpaises,vetorfinal,numerodeelementos,numeropaises);
    insertcountriesminimo(vetorpaises,vetormin,numerodeelementos,numeropaises);
    insertcountriesAmplitude(ampvetorpaises,vetoramp,numerodeelementos,numeropaises);

    printf("----------MAXIMO---------\n");

    while(i<numeropaises)
    {
        printf(" Com a temperatura maxima media %f é %s \n",vetorfinal[i]->media,vetorfinal[i]->pais);
        i++;
    }
    i=0;
    printf("----------MINIMO---------\n");
    while(i<numeropaises)
    {
        printf(" Com a temperatura minima media %f é %s \n",vetormin[i]->media,vetormin[i]->pais);
        i++;
    }

    i=0;
    printf("----------AMPLITUDE---------\n");
    while(i<numeropaises)
    {
        printf(" Com a maior amplitude media %s é %f \n",vetoramp[i]->pais, vetoramp[i]->dif);
        i++;
    }


}


void insertcountriesAmplitude(Amplitude *vetor[1000],Amplitude *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {
            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if((vetor[i]->dif) > vetorfinal[j]->dif)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }

        }
    }
}

void calculaamplitude(UNICODE *vetor[2019], int numerodedados,Amplitude *vetorpaises[1000])
{

    float maximo=-10.0f;
    float minimo=100.0f;
    float diferenca=0.0f;
    int i=0;
    int check=1;
    Amplitude *auxv=NULL;

    while(i<numerodedados)
    {
        maximo=-10.0f;
        minimo=100.0f;
        diferenca=0.0f;
        check=0;
        while(vetor[i]->next!=NULL)
        {
            auxv=(Amplitude*)realloc(vetorpaises[i],(i+1)*sizeof(Amplitude));
            vetorpaises[i]=auxv;
            if(vetor[i]->next->payload->temperatura > maximo)
            {
                maximo=vetor[i]->next->payload->temperatura;
                printf("teste\n");
                fflush(stdout);
            }
            if(vetor[i]->next->payload->temperatura<minimo)
            {
                minimo=vetor[i]->next->payload->temperatura;
                printf("teste2\n");
                fflush(stdout);
            }
            vetor[i]=vetor[i]->next;
            check=1;
        }
        if(check==1)
        {
            printf("Max---%f---\n",maximo);
            printf("Min---%f---\n",minimo);
            fflush(stdout);
            diferenca=((maximo-minimo)*2)/2;
            vetorpaises[i]->dif=diferenca;
            strcpy(vetorpaises[i]->pais,vetor[i]->payload->pais);
        }
        i++;
   }
}

void insertcountriesminimo(Paises *vetor[1000],Paises *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {
            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media < vetorfinal[j]->media)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }
        }
    }
}

void organizacidades(UNICODE *copia, int *numerocidades,int ano,UNICODE *vetor[2019])
{

    int numerodeelementos=0;
    int i=0;
    dados_temp *vect[2000];
    while(copia->payload->dt.ano != ano)
    {
        copia=copia->next;
    }


    do
    {
        i=0;
        while( i<200)
        {
            if(vetor[i]->next==NULL)
            {
                /*vect[i].dt.ano=copia->payload.dt.ano;
                vect[i].dt.mes=copia->payload.dt.mes;
                vect[i].dt.dia=copia->payload.dt.dia;
                vect[i].temperatura=copia->payload.temperatura;
                vect[i].incerteza=copia->payload.incerteza;
                strcpy(vect[i].pais,copia->payload.pais);*/
                vect[i] = (copia->payload);
                insert_node(vetor[i],vect[i]);
                break;
            }
            else if(strstr(copia->payload->cidade,vetor[i]->next->payload->cidade)!=NULL)//CRIAR DUAS FUNÇÕES UMA PARA CIDADES E OUTRA PARA PAISES
            {
                    /*vect[i].dt.ano=copia->payload.dt.ano;
                    vect[i].dt.mes=copia->payload.dt.mes;
                    vect[i].dt.dia=copia->payload.dt.dia;
                    vect[i].temperatura=copia->payload.temperatura;
                    vect[i].incerteza=copia->payload.incerteza;
                    strcpy(vect[i].pais,copia->payload.pais);*/
                    vect[i] = (copia->payload);
                    insert_node(vetor[i],vect[i]);
                    break;
            }

            i++;
        }


        copia=copia->next;
    }
    while( copia!=NULL && copia->payload->dt.ano==ano);
    i=0;
    do
    {
        if(vetor[i]->next->next!=NULL)
        {
            numerodeelementos++;
        }

        i++;
    }
    while(vetor[i]->next!=NULL);

    printf("-------------%d-------\n",numerodeelementos);
    *numerocidades=numerodeelementos;

}
void organizapaises(UNICODE *copia, int *numeropaises,int ano,UNICODE *vetor[2019])
{

    int numerodeelementos=0;
    int i=0;
    dados_temp *vect[2000];
    UNICODE *aux=NULL;
    aux=copia;
    printf("%d\n",copia->next->payload->dt.ano);
    fflush(stdout);

    while(copia->next->payload->dt.ano != ano)
    {
        copia=copia->next;
        if(copia->next==NULL){
           return;
    }
    }


    do
    {
        i=0;
        while( i<500)
        {
            if(vetor[i]->next==NULL)
            {
                /*vect[i].dt.ano=copia->payload.dt.ano;
                vect[i].dt.mes=copia->payload.dt.mes;
                vect[i].dt.dia=copia->payload.dt.dia;
                vect[i].temperatura=copia->payload.temperatura;
                vect[i].incerteza=copia->payload.incerteza;
                strcpy(vect[i].pais,copia->payload.pais);*/
                vect[i] = (copia->payload);
                insert_node(vetor[i],vect[i]);
                break;
            }
            else if(strstr(copia->payload->pais,vetor[i]->next->payload->pais)!=NULL)//CRIAR DUAS FUNÇÕES UMA PARA CIDADES E OUTRA PARA PAISES
            {
                    /*vect[i].dt.ano=copia->payload.dt.ano;
                    vect[i].dt.mes=copia->payload.dt.mes;
                    vect[i].dt.dia=copia->payload.dt.dia;
                    vect[i].temperatura=copia->payload.temperatura;
                    vect[i].incerteza=copia->payload.incerteza;
                    strcpy(vect[i].pais,copia->payload.pais);*/
                    vect[i] = (copia->payload);
                    insert_node(vetor[i],vect[i]);
                    break;
            }

            i++;
        }


        copia=copia->next;
    }
    while( copia!=NULL && copia->payload->dt.ano==ano);
    i=0;
    do
    {
        if(vetor[i]->next->next!=NULL)
        {
            numerodeelementos++;
        }

        i++;
    }
    while(vetor[i]->next!=NULL);

    printf("-------------%d-------\n",numerodeelementos);
    *numeropaises=numerodeelementos;
    copia=aux;

}

void calculamedia(UNICODE *vetor[2019], int numerodedados,Paises *vetorpaises[1000])
{

    float soma=0;
    int i=0;
    int numerodeinfo=0;
    Paises *auxv=NULL;

   while(i<numerodedados){
        numerodeinfo=0;
        soma=0;
        while(vetor[i]->next!=NULL)
        {
            auxv=(Paises*)realloc(vetorpaises[i],(i+1)*sizeof(Paises));
            vetorpaises[i]=auxv;
            soma+=vetor[i]->next->payload->temperatura;
            numerodeinfo++;
            vetor[i]=vetor[i]->next;
        }
        printf("---%f---\n",soma/numerodeinfo);
        printf("---%d---\n",numerodeinfo);

        vetorpaises[i]->media=soma/numerodeinfo;
        strcpy(vetorpaises[i]->pais,vetor[i]->payload->pais);
        i++;
   }
}


void insertcountries(Paises *vetor[1000],Paises *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {


            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media > vetorfinal[j]->media)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];

                }
                vetorfinal[j]=vetor[i];
                break;
            }

        }
    }
}


void analise_da_temperatura_ano_cidade(UNICODE *copia,int numerocidades,int ano){
    int i=0;
    int numerodeelementos=0;
    UNICODE *vetor[2019]={NULL};
    UNICODE *vetoraux[2019]={NULL};
    cidades *vetorcidades[1000];
    AmpCidades *ampvetorcidades[1000]={NULL};
    cidades *vetorfinal[20]={NULL};
    cidades *vetormin[20]={NULL};
    AmpCidades *vetoramp[20]={NULL};

    listvector(vetor);
    listvector(vetoraux);
    organizacidades(copia,&numerodeelementos,ano,vetor);
    organizacidades(copia,&numerodeelementos,ano,vetoraux);
    calculamediacidades(vetor,numerodeelementos,vetorcidades);
    calculaamplitudeCidades(vetoraux,numerodeelementos,ampvetorcidades);
    insertcidade(vetorcidades,vetorfinal,numerodeelementos,numerocidades);
    insertcountriesminimocidade(vetorcidades,vetormin,numerodeelementos,numerocidades);
    insertcountriesAmplitudeCidades(ampvetorcidades,vetoramp,numerodeelementos,numerocidades);

    printf("----------MAXIMO---------\n");

    while(i<numerocidades){
        printf(" Com a temperatura maxima media %f é %s \n",vetorfinal[i]->media,vetorfinal[i]->cidade);
        i++;
    }
    i=0;
    printf("----------MINIMO---------\n");
    while(i<numerocidades){
        printf(" Com a temperatura minima media %f é %s \n",vetormin[i]->media,vetormin[i]->cidade);
        i++;
    }

    i=0;
    printf("----------AMPLITUDE---------\n");
    while(i<numerocidades){
        printf(" Com a maior amplitude media %s é %f \n",vetoramp[i]->cidade, vetoramp[i]->dif);
        i++;
    }


}

void insertcidade(cidades *vetor[1000],cidades *vetorfinal[20],int numerodedados,int numeroinserido){
    printf("---_%d\n",numerodedados);
    for(int i=0;i<numerodedados;i++){
        for(int j=0;j<numeroinserido;j++){


            if(vetorfinal[j]==NULL) {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media > vetorfinal[j]->media){
                for(int k=numeroinserido-2;k>=j;k--){
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];

                }
                vetorfinal[j]=vetor[i];
                break;}

        }
    }
}
void insertcountriesminimocidade(cidades *vetor[1000],cidades *vetorfinal[20],int numerodedados,int numeroinserido){
    for(int i=0;i<numerodedados;i++){
        for(int j=0;j<numeroinserido;j++){


            if(vetorfinal[j]==NULL) {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media < vetorfinal[j]->media){
                for(int k=numeroinserido-2;k>=j;k--){
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];

                }
                vetorfinal[j]=vetor[i];
                break;}

        }
    }
}

void calculaamplitudeCidades(UNICODE *vetor[2019], int numerodedados,AmpCidades *vetorcidades[1000]){

    float maximo=-10.0f;
    float minimo=100.0f;
    float diferenca=0.0f;
    int i=0;
    int check=1;
    AmpCidades *auxv=NULL;


   while(i<numerodedados){
        maximo=-10.0f;
        minimo=100.0f;
        diferenca=0.0f;
        check=0;
        while(vetor[i]->next!=NULL){//alterar!!!!!!
            auxv=(AmpCidades*)realloc(vetorcidades[i],(i+1)*sizeof(AmpCidades));
            vetorcidades[i]=auxv;
            if(vetor[i]->next->payload->temperatura > maximo){
                maximo=vetor[i]->next->payload->temperatura;
            }
            if(vetor[i]->next->payload->temperatura<minimo){
                minimo=vetor[i]->next->payload->temperatura;
            }
            vetor[i]=vetor[i]->next;
            check=1;
        }
        if(check==1){
        //printf("O pais %s tem o máximo %f e min %f---\n",vetor[i]->payload->cidade,maximo,minimo);
        fflush(stdout);
        diferenca=((maximo-minimo)*2)/2;//para ser positivo
        vetorcidades[i]->dif=diferenca;
        strcpy(vetorcidades[i]->cidade,vetor[i]->payload->cidade);}
        i++;
   }

    }

void insertcountriesAmplitudeCidades(AmpCidades *vetor[1000],AmpCidades *vetorfinal[20],int numerodedados,int numeroinserido){
    for(int i=0;i<numerodedados;i++){
        for(int j=0;j<numeroinserido;j++){


            if(vetorfinal[j]==NULL) {
                vetorfinal[j]=vetor[i];
                break;
            }
            if((vetor[i]->dif) > vetorfinal[j]->dif){
                for(int k=numeroinserido-2;k>=j;k--){
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];

                }
                vetorfinal[j]=vetor[i];
                break;}

        }
    }
}


void calculamediacidades(UNICODE *vetor[2019], int numerodedados,cidades *vetorcidades[1000]){

    float soma=0;
    int i=0;
    int numerodeinfo=0;
    cidades *auxv=NULL;

   while(i<numerodedados){
        numerodeinfo=0;
        soma=0;
        while(vetor[i]->next!=NULL){//alterar!!!!!!
            auxv=(cidades*)realloc(vetorcidades[i],(i+1)*sizeof(cidades));
            vetorcidades[i]=auxv;
            soma+=vetor[i]->next->payload->temperatura;
            numerodeinfo++;
            vetor[i]=vetor[i]->next;
        }
        vetorcidades[i]->media=soma/numerodeinfo;
        strcpy(vetorcidades[i]->cidade,vetor[i]->payload->cidade);
        i++;
   }
}



void movingAveragePais(UNICODE *copia,float *max,float *min,char pais[100],float minficheiro,int intervalo, int ano){

    int i=1743;
    float media_ano=0.0f;
    float media_mes[13]={0.0f};
    printf("%d\n",ano);
    UNICODE *listapaises=create_list();
    int check=0;


// sempre que der erro de nan é para fazer um if para a conta
    while(i<=ano){
            check=0;
            Ledadospais(copia,pais,listapaises,i,&check);
            if(check==1){
            //printf("O valor da temp é %f\n",listapaises->next->payload->temperatura);
            calculamediaparacadames_Pais(listapaises,media_mes);//fazer um check aqui para o valor não dar sempre igual
            criaagrupamentos(media_mes,intervalo,&media_ano);
            printf("O ano é %d  tem a media %f\n",i,media_ano);
            if(*max<media_ano){
                *max=media_ano;
                 printf("max=%f\n",*max);
            }
            if(*min>media_ano){
                *min=media_ano;
                printf("min=%f\n",*min);
            }
    clearList(&listapaises);// testar este clearlist
    media_ano=0.0f;
    }
    //printf("O ano é %d\n",i);

    i++;// caso ele encontre um sem dados
    }

}


void calculamediaparacadames_Pais(UNICODE *vetor,float media_mes[13]){

    float soma=0.0f;
    int i=1;
    int numerodeinfo=0;
    UNICODE *aux=vetor;
 // tenho de fazer aquilo do strlen


        while(aux->next!=NULL && i<13){//alterar!!!!!!
            numerodeinfo=0;
            soma=0.0f;
            while(aux->next!=NULL && aux->next->payload->dt.mes!=i){
                i++;
                if( i==13){
                    return;
                 }

            }
            //printf("%d\n",aux->next->payload->dt.mes);
            //printf("%d\n",i);
            while(aux->next!=NULL && aux->next->payload->dt.mes==i){
                soma+=aux->next->payload->temperatura;
                numerodeinfo++;
                //printf("Imprime %f\n",aux->next->payload->temperatura);
                aux=aux->next;
                while(aux->next!=NULL && aux->next->payload->dt.mes!=i){//descrepancia entre meses
                    i++;
                    if( i==13){
                        return;
                 }
            }
            }
            if(aux!=NULL && soma!=0.0f){
                if(aux->next!=NULL){
                soma+=aux->next->payload->temperatura;
                numerodeinfo++;
                }

                if(soma!=0.0f){
                media_mes[i-1]=soma/numerodeinfo;}
                //printf("Imprime %d e %f\n",numerodeinfo,soma);
                //printf("Os valores da temp no ano %d são %f\n",i,aux->payload->temperatura);
                //printf("o valor da media do mes é %f\n",media_mes[i-1]);
            }
            i++;
            aux=aux->next;
            if(aux==NULL){
                break;
            }
        }
    }



void criaagrupamentos(float media_mes[13],int intervalo, float *media_do_ano){
    int k,j=1;
    int i=0;
    float somatemp=0.0f;
    float somaagrupamentos=0.0f;
    int numerodeinfo,numagrupamentos=0,p=0;
    float media_agrupamentos[13]={0.0f};
   while(j<13){
   somatemp=0.0f;
   numerodeinfo=0;
    for(k=j;k<j+intervalo && k!=13 ;k++){
            somatemp+=media_mes[k-1];
            if(media_mes[k-1]!=0){
            numerodeinfo++;}
    }
    if(somatemp!=0.0f){
    media_agrupamentos[j-1]=somatemp/numerodeinfo;//media do agrupamento
    }
    j++;
}

    while(i<12){
        somaagrupamentos+=media_agrupamentos[i];
        //printf("O valor de interesse é %f\n",media_agrupamentos[i]);
        //printf("O valor de interesse soma é %f\n",somaagrupamentos);

        if(media_agrupamentos[i]!=0.0f){
        numagrupamentos++;}
        i++;
    }
    //printf("O valor de interesse  num é %d\n",numagrupamentos);

    *media_do_ano=somaagrupamentos/numagrupamentos;
        while(media_mes[p]!=0.0f){
            media_mes[p]=0.0f;
            p++;
    }
}








void Ledadospais(UNICODE *v,char pais[100],UNICODE *listapais, int ano, int *check){
   UNICODE *aux=v;
    dados_temp *vect[2000];
    int i=0;
    while(aux!=NULL && aux->payload->dt.ano!=ano){
        aux=aux->next;
    }

    while(aux!=NULL && aux->payload->dt.ano==ano){
        if(strstr(aux->payload->pais,pais)!=NULL){
            vect[i]= (aux->payload);
            insert_tail(listapais,vect[i]);
            //printf("----%d----\n",aux->payload->dt.ano);
            //printf("----->%f----\n",aux->payload->temperatura);

            i++;
            *check=1;
        }
    aux=aux->next;
    }
}


void movingAverage_cidade(UNICODE *copia,float *max,float *min,char cidade[100],float minficheiro,int intervalo, int ano){

    int i=1743;//ALTERAR!!!!!
    float media_ano=0.0f;
    float media_mes[13]={0.0f};
    printf("%d\n",ano);
    UNICODE *listacidades=create_list();
    int check=0;

// sempre que der erro de nan é para fazer um if para a conta
    while(i<=ano){
            check=0;
            //printf("%d\n",i);
            Ledadoscidades(copia,cidade,listacidades,i,&check);
            if(check==1){
            //printf("O valor da temp é %f\n",listapaises->next->payload->temperatura);
            calculamediaparacadames_cidades(listacidades,media_mes);//fazer um check aqui para o valor não dar sempre igual
            criaagrupamentos_cidades(media_mes,intervalo,&media_ano);
            printf("O ano é %d  tem a media %f\n",i,media_ano);
            if(*max<media_ano){
                *max=media_ano;
                 //printf("max=%f\n",*max);
            }
            if(*min>media_ano){
                *min=media_ano;
                //printf("min=%f\n",*min);
            }
    clearList(&listacidades);// testar este clearlist
    while(listacidades->next!=NULL){
        printf("OLA\n");
    }
    media_ano=0.0f;
    }
    //printf("O ano é %d\n",i);

    i++;// caso ele encontre um sem dados
    }

}


void calculamediaparacadames_cidades(UNICODE *vetor,float media_mes[13]){

    float soma=0.0f;
    int i=1;
    int numerodeinfo=0;
    UNICODE *aux=vetor;
 // tenho de fazer aquilo do strlen


        while(aux->next!=NULL && i<13){//alterar!!!!!!
            numerodeinfo=0;
            soma=0.0f;
            while(aux->next!=NULL && aux->next->payload->dt.mes!=i){
                i++;
                if( i==13){
                    return;
                 }

            }
            //printf("%d\n",aux->next->payload->dt.mes);
            //printf("%d\n",i);
            while(aux->next!=NULL && aux->next->payload->dt.mes==i){
                soma+=aux->next->payload->temperatura;
                numerodeinfo++;
                //printf("Imprime %f\n",aux->next->payload->temperatura);
                aux=aux->next;}

            if(aux!=NULL && soma!=0.0f){
                if(aux->next!=NULL && aux->next->payload->dt.mes==i){
                soma+=aux->next->payload->temperatura;
                numerodeinfo++;
                }

                if(soma!=0.0f){
                media_mes[i-1]=soma/numerodeinfo;}
                //printf("Imprime %d e %f\n",numerodeinfo,soma);
                //printf("Os valores da temp no ano %d são %f\n",i,aux->payload->temperatura);
                //printf("o valor da media do mes %d é %f\n",i,media_mes[i-1]);
            }
            while(aux->next!=NULL && aux->next->payload->dt.mes!=i){//descrepancia entre meses
                    i++;
                    if( i==13){
                        return;
                 }
            }

            if(aux==NULL){
                break;
            }
        }
    }



void criaagrupamentos_cidades(float media_mes[13],int intervalo, float *media_do_ano){
    int k,j=1;
    int i=0;
    float somatemp=0.0f;
    float somaagrupamentos=0.0f;
    int numerodeinfo=0,numagrupamentos=0,p=0;
    float media_agrupamentos[13]={0.0f};
   while(j<13){
   somatemp=0.0f;
   numerodeinfo=0;
    for(k=j;k<j+intervalo && k!=13 ;k++){
            somatemp+=media_mes[k-1];
            //printf("O valor de interesse é %f\n",media_mes[k-1]);

            if(media_mes[k-1]!=0.0f){
                numerodeinfo++;}
    }
    if(somatemp!=0.0f){
        media_agrupamentos[j-1]=somatemp/numerodeinfo;//media do agrupamento

    //printf("O interesse é %f\n",media_agrupamentos[j-1]);
    }
    j++;
}

    while(i<12){
        somaagrupamentos+=media_agrupamentos[i];
        if(media_agrupamentos[i]!=0.0f){
            numagrupamentos++;}
        //printf("O valor de interesse é %f\n",media_agrupamentos[i]);
        //printf("O valor de interesse soma é %f\n",somaagrupamentos);
        i++;
    }
    //printf("O valor de interesse  num de agrup é %d\n",numagrupamentos);

    *media_do_ano=somaagrupamentos/numagrupamentos;
        while(media_mes[p]!=0.0f){
            media_mes[p]=0.0f;
            p++;
    }
}








void Ledadoscidades(UNICODE *v,char cidade[100],UNICODE *listacidade, int ano, int *check){
   UNICODE *aux=v;
    int i=0;
    while(aux!=NULL && aux->payload->dt.ano!=ano){
        aux=aux->next;
    }

    while(aux!=NULL && aux->payload->dt.ano==ano){
        if(strstr(aux->payload->cidade,cidade)!=NULL){
            insert_tail(listacidade,aux->payload);
            printf("----%d----\n",aux->payload->dt.ano);
            //printf("----->%f----\n",aux->payload->temperatura);

            i++;
            *check=1;
        }
    aux=aux->next;
    }
}

void movingAverageG(UNICODE *copia,float *max,float *min,float minficheiro,int intervalo, int ano){

    int i=1743;//ALTERAR!!!!!
    float media_ano=0.0f;
    float media_mes[13]={0.0f};
    UNICODE *listaGlobal=create_list();
    int check=0;

// sempre que der erro de nan é para fazer um if para a conta
    while(i<=ano){
            check=0;
            //printf("%d\n",i);
            LedadosG(copia,listaGlobal,i,&check);
            if(check==1){
            //printf("O valor da temp é %f\n",listapaises->next->payload->temperatura);
            calculamediaparacadames_cidades(listaGlobal,media_mes);//fazer um check aqui para o valor não dar sempre igual
            criaagrupamentos_cidades(media_mes,intervalo,&media_ano);
            printf("O ano é %d  tem a media %f\n",i,media_ano);
            if(*max<media_ano){
                *max=media_ano;
                 //printf("max=%f\n",*max);
            }
            if(*min>media_ano){
                *min=media_ano;
                //printf("min=%f\n",*min);
            }
    clearList(&listaGlobal);// testar este clearlist

    media_ano=0.0f;
    }
    //printf("O ano é %d\n",i);

    i++;// caso ele encontre um sem dados
    }

}



void LedadosG(UNICODE *v,UNICODE *listacidade, int ano, int *check){
   UNICODE *aux=v;
    int i=0;
    while(aux!=NULL && aux->payload->dt.ano!=ano){
        aux=aux->next;
    }

    while(aux!=NULL && aux->payload->dt.ano==ano){
            insert_tail(listacidade,aux->payload);
            //printf("----%d----\n",aux->payload->dt.ano);
            //printf("----->%f----\n",aux->payload->temperatura);

            i++;
            *check=1;
    aux=aux->next;
    }
}
