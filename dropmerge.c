/******************************************************/
/*                   Jogo feito por                   */
/*  Nome: Filipe Nobre Nunes    Matricula: 242023523  */
/******************************************************/

/****************/
/*Legenda:*/
/*Menu linha tal*/
/************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matriz[10][5];                          /*Gera matriz de 10 linhas por 5 colunas*/

void limpa_tela()                           /*Checa o respectivo comando para limpar tela*/
{
    #ifdef _WIN32                           /*Caso seja windows32*/
        system("cls");
    #else
        system("clear");                    /*Caso seja outra versao do sistema (linux)*/
    #endif
}

void PrintaMenu()
{
    printf("*** JOGO DROP MERGE de APC ***\n\n");
    printf("1 - Jogar\n");
    printf("2 - Configuracoes\n");
    printf("3 - Instrucoes\n");
    printf("4 - Ranking\n");
    printf("5 - Sair\n\n");
    printf("Digite a opcao desejada: ");
}

void PrintaMConfig()
{
    printf("*** CONFIGURACOES ***\n\n");
    printf("1 - Zerar Ranking\n");
    printf("2 - Modo de Dificuldade\n");
    printf("3 - Voltar ao Menu Principal\n\n");
    printf("Digite a opcao desejada: ");
}

void Mostra(int nro,int nro_seguinte)       /*Printa tela com numeros da matriz, numero atual e seguinte a cair*/
{
    int i,j;
    printf("           +----+  +----+\n");
    printf("           |%4d|  |%4d|\n",nro,nro_seguinte);
    printf("           +----+  +----+\n");
    for (i=9; i>=0; i--){
        printf("  +----+----+----+----+----+\n");
        printf("  |");
        for(j=0;j<5;j++){
            if (matriz[i][j] != 0) 
                printf("%4d|",matriz[i][j]);
            else
                printf("    |");
        }
        printf("\n");
    }
    printf("  +----+----+----+----+----+\n");
    printf("  +----+----+----+----+----+\n");
    printf("  |  1 |  2 |  3 |  4 |  5 |\n");
    printf("  +----+----+----+----+----+\n\n");
}

int main()
{
    int pos,num1,num2,posArq;
    char texto[5],nome[101];                          /*Numeros de ate 4 casas*/
    FILE *arquivo;

    int opcao=0;

    printf("Bem vindo(a) ao Jogo DROP MERGE de APC!!!\n\n");
    printf("Informe seu nickname (Informacao totalmente descartavel): ");
    fgets(nome,101,stdin);

/***********************************************Loop do Menu***************************************************/

    while (opcao!=6)
    {
        limpa_tela();
        PrintaMenu();
        do
        {
            scanf("%d",&opcao);
            fflush(stdin);
        }
        while (opcao<1 || opcao>5);

        switch (opcao)
        {
            case 1: opcao=6; break;
            case 2: while (opcao!=3)
                    {
                        limpa_tela();
                        PrintaMConfig();
                        do
                        {
                            scanf("%d",&opcao);
                            fflush(stdin);
                        }
                        while (opcao<1 || opcao>5);

                        switch (opcao)
                        {
                            case 1: printf("NAO FAZ ISSO DE NOVO\n"); getchar(); break;
                            case 2: printf("PARA DE CLICARAAAAAAAAAAAAAA\n"); getchar(); break;
                            case 3: break;
                            default: printf("ERRO NO MENU\n"); getchar(); break;
                        }
                    }
                    break;
            case 3: printf("AINDA NAO TA PRONTO\n"); getchar(); break;
            case 4: printf("EU FALEI QUE NAO TA PRONTO\n"); getchar(); break;
            case 5: return 0;
            default: printf("ERRO NO MENU\n"); getchar(); break;
        }
    }

/***********************************************Loop do Jogo***************************************************/

    for (int i = 0; i < 10; i++)            /*Inicia matriz com zeros*/
    {
        for (int j = 0; j < 5; j++)
        {
            matriz[i][j]=0;
        }
    }

    arquivo = fopen("numeros.txt","r");     /*Abre arquivo com numeros para leitura*/

    while (1)                               /*LOOP PRINCIPAL*/
    {
        fscanf(arquivo,"%[^,],",&texto);    /*scaneia um numero ate a virgula e "come" a virgula*/
        num1=atoi(texto);                   /*converte o numero de string para inteiro*/
        fscanf(arquivo,"%[^,],",&texto);    /*scaneia um numero ate a virgula e "come" a virgula*/
        num2=atoi(texto);                   /*converte o numero de string para inteiro*/
        posArq=strlen(texto)+1;             /*Posicao de leitura do arquivo = tamanho do numero + virgula*/
        fseek(arquivo,-posArq,SEEK_CUR);    /*Retorna o leitor do arquivo em (posArq) posicoes*/

        limpa_tela();
        Mostra(num1,num2);                  /*chama funcao mostra com o numero atual e o proximo*/
        do
        {
            scanf("%d",&pos);               /*Scaneia posicao a ser jogado o numero*/
            fflush(stdin);
        }
        while (pos<1 || pos>5);             /*Enquanto o numero digitado for invalido, scaneia*/
        
        for (int i = 9; i >= 0; i--)        /*Comecando a contar a partir do 9, loop de 10 decrescente*/
        {
            if (matriz[0][pos-1]==0)        /*Se o ultimo numero da matriz na posicao escolhida for 0*/
            {
                matriz[0][pos-1]=num1;      /*printa la*/
                break;                      /*encerra o for*/
            }
            else
            {           
                if (matriz[i][pos-1]!=0)    /*ate ser lido um numero diferente de 0 na coluna escolhida...*/
                {
                    if (i==9)               /*se houver um numero na 9 linha*/
                    {
                        printf("VOCE PERDEU AHAHAHAHAHAHHAHAHAHAHAHAH\n"); /*perdeu*/
                        return 0;           /*encerra*/
                    }
                    else                    /*se nao*/
                    {
                        matriz[i+1][pos-1]=num1;    /*Coloca o numero na posicao acima do ultimo numero da coluna*/
                        break;                      /*encerra o for*/
                    }
                }
            }
        }
        limpa_tela();
    }
}