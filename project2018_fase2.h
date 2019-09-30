#ifndef PROJECT2018_FASE2_H_INCLUDED
#define PROJECT2018_FASE2_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main_project2018_fase2(int argc, const char * argv[]);
//----------------------------------------Estrutura Dicionário----------------------------------------
typedef struct palavraDicionario
{
    char* palavra;
    struct palavraDicionario* pnext;
}PALAVRADICIONARIO;
typedef struct dicionario
{
    PALAVRADICIONARIO *pfirst;
    int nPalavras;
}DICIONARIO;

char* create_copy_dyn_string(char* str);
void inserePalavraNoDicionario(DICIONARIO *pDicio, char* pPal);
void imprimeDicionario(DICIONARIO dicio);



//----------------------------------------Estrutura Dicionário de Ficheiro----------------------------------------
void lerDicionarioDeFicheiro(char nomeFicheiro[], int linhas, DICIONARIO *pDicio);



//----------------------------------------Estrutura Sopa de Letras----------------------------------------
typedef struct letraSopa
{
    char letra;
    int linha;
    int coluna;
    struct letraSopa* pN;
    struct letraSopa* pNE;
    struct letraSopa* pE;
    struct letraSopa* pSE;
    struct letraSopa* pS;
    struct letraSopa* pSO;
    struct letraSopa* pO;
    struct letraSopa* pNO;
    struct letraSopa* pnext;
}LETRASOPA;
typedef struct sopaDeLetras
{
    LETRASOPA* pfirst;
    int linhas;
    int colunas;
}SOPADELETRAS;



//----------------------------------------Estrutura Sopa de Letras de Ficheiro----------------------------------------
void lerSopaDeLetrasDeFicheiro(char nomeFicheiro[], SOPADELETRAS* pSopa);
void insereLetraNaSopaDeLetras(SOPADELETRAS* pSopa, char letra, int linha, int coluna);



//----------------------------------------Tabuleiro bidimensional----------------------------------------
void ligaAsLetras(SOPADELETRAS* pSopa);



//----------------------------------------Caractere dados movimentos----------------------------------------
void movimentos(SOPADELETRAS sopa);



//----------------------------------------Pesquisa----------------------------------------
typedef struct resultado
{
    char* ppalavra;
    int linhaInicio;
    int colunaInicio;
    int linhaFim;
    int colunaFim;
    int direcoes[10];
    struct resultado* pnext;
}RESULTADO;
typedef struct resultadosPesquisa
{
    int nresultados;
    RESULTADO* pfirst;
}RESULTADOSPESQUISA;

void encontraPalavra(LETRASOPA *letraAtual, char palavra[], int posLetra);
int verificaConsistencia(LETRASOPA *letraAVerificar, char letra);



//----------------------------------------Ficheiro Texto----------------------------------------
void save_results_txt(RESULTADOSPESQUISA res, char fn[]);
void read_results_txt(RESULTADOSPESQUISA* pres, char fn[]);
void print_results(RESULTADOSPESQUISA res);



//----------------------------------------Ficheiro Binário----------------------------------------
void save_results_bin(RESULTADOSPESQUISA res, char fnb[]);



//----------------------------------------MergeSort----------------------------------------
struct Node
{
    char * data;
    int id;
    struct Node* next;
};
struct Node* Merge(struct Node *a, struct Node *b, int flag);
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef);
void printList(struct Node *node);
void MergeSort(struct Node** list, int flag);
void addElement(struct Node** list, char * new_data, int key);

#endif // PROJECT2018_FASE2_H_INCLUDED
