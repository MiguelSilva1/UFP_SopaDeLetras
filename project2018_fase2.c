#include "project2018_fase2.h"

void main_project2018_fase2(int argc, const char * argv[])
{
    //----------------------------------------Estrutura Dicionário----------------------------------------
    /**< R5.a. */
/*
    int linhasDicionario = 0;
    printf("Insira o numero de palavras do dicionario:\n");
    scanf("%d", &linhasDicionario);
    printf("\n");
    DICIONARIO dicionario = {NULL, 0};
    int i = 0;
    char palavraAux[50];
    char* pPalavraAux;
    for(i = 0; i < linhasDicionario; i++)
    {
        printf("Insira a palavra:\n");
        scanf("%s", palavraAux);
        pPalavraAux = create_copy_dyn_string(palavraAux);
        inserePalavraNoDicionario(&dicionario, pPalavraAux);
    }
    printf("\nDicionario:\n");
    imprimeDicionario(dicionario);
    printf("\n");
*/


    //----------------------------------------Estrutura Dicionário de Ficheiro----------------------------------------
    /**< R5.b. */
    char nomeFicheiro[] = "dicionario.txt";
    int linhasDicionarioFicheiro = 4;
    DICIONARIO dicionario = {NULL, 0};
    lerDicionarioDeFicheiro(nomeFicheiro, linhasDicionarioFicheiro, &dicionario);
    imprimeDicionario(dicionario);
    printf("\n");



    //----------------------------------------MergeSort----------------------------------------
    /**< R6. */
    struct Node* noLista = NULL;
    struct Node** lista = &noLista;
    PALAVRADICIONARIO* palavraAux = dicionario.pfirst;
    int i;
    for(i = 0; i < dicionario.nPalavras; i++)
    {
        addElement(lista, palavraAux->palavra, i);
        palavraAux = palavraAux->pnext;
    }
    printf("\nLista ordenada com MergeSort:\n");
    MergeSort(lista, 1);
    printList(noLista);
    printf("\n");



    //----------------------------------------Estrutura Sopa de Letras de Ficheiro----------------------------------------
    /**< R8.a. */
    SOPADELETRAS sopaDeLetras = {NULL, 8, 10};
    char nomeFicheiroSopaDeLetras[] = "sopaDeLetras.txt";
    lerSopaDeLetrasDeFicheiro(nomeFicheiroSopaDeLetras, &sopaDeLetras);



    //----------------------------------------Tabuleiro bidimensional----------------------------------------
    /**< R7. */
	ligaAsLetras(&sopaDeLetras);



	//----------------------------------------Caractere dados movimentos----------------------------------------
    /**< R10. */
    movimentos(sopaDeLetras);
    printf("\n");



    //----------------------------------------Pesquisa----------------------------------------
    /**< R9. (Incompleto - não pesquisa corretamente as palavras) */
    char palavra[50];
    PALAVRADICIONARIO *palavraAtual = dicionario.pfirst;
    int posLetra = 0;
    LETRASOPA *letraAtual;
    //Percorre as palavras da estrutura dicionário
    for(i = 0; i < dicionario.nPalavras; i++)
    {
        strcpy(palavra, palavraAtual->palavra);
        posLetra = 0;
        letraAtual = sopaDeLetras.pfirst;
        //Procura pela primeira letra (palavra[0])
        while(letraAtual != NULL)
        {
            //printf("TESTE: [%d, %d]%c\n", letraAtual->linha, letraAtual->coluna, letraAtual->letra);
            if(letraAtual->letra == palavra[posLetra])
            {
                //printf("TESTE: [%d, %d]%c -> '%c' encontrada\n", letraAtual->linha, letraAtual->coluna, letraAtual->letra, palavra[posLetra]);
                encontraPalavra(letraAtual, palavra, posLetra + 1);
            }
            letraAtual = letraAtual->pnext;
        }
        palavraAtual = palavraAtual->pnext;
    }



    //----------------------------------------Ficheiro Texto----------------------------------------
    /**< R12. (Incompleto - Não lê corretamente do ficheiro de texto) */
    char fn[] = "FicheiroResultados.txt";

    //Guarda no ficheiro:
    RESULTADO re2 = {"faro", 4, 5, 6, 7, {3, 2, 1, -1}, NULL};
    RESULTADO re1 = {"porto", 1, 2, 3, 4, {5, 6, 7, 8, -1}, &re2};
    RESULTADOSPESQUISA re = {2, &re1};
    save_results_txt(re, fn);
/*
    //Lê do ficheiro:
    RESULTADOSPESQUISA re = {0, NULL};
    read_results_txt(&re, fn);
    print_results(re);
*/


    //----------------------------------------Ficheiro Binário----------------------------------------
    /**< R13. (Incompleto - não lê do ficheiro binário)*/
    char fnb[] = "FicheiroResultadosBin.bin";
    //Guarda no ficheiro:
    RESULTADO re2b = {"faro", 4, 5, 6, 7, {3, 2, 1, -1}, NULL};
    RESULTADO re1b = {"porto", 1, 2, 3, 4, {5, 6, 7, 8, -1}, &re2b};
    RESULTADOSPESQUISA reb = {2, &re1b};
    save_results_bin(reb, fnb);
}





//----------------------------------------MergeSort----------------------------------------
/* Function to insert a node at the beginging of the linked list */
void addElement(struct Node** list, char * new_data, int key)
{
    /* allocate node */
    struct Node* new_node =
            (struct Node*) malloc(sizeof(struct Node));

    new_node->data = (char *) malloc(sizeof(strlen(new_data)));
    /* put in the data  */
    strcpy(new_node->data,new_data);
    new_node->id = key;
    /* link the old list off the new node */
    new_node->next = (*list);
    /* move the head to point to the new node */
    (*list) = new_node;
}

/* Function to print nodes in a given linked list */
void printList(struct Node *node)
{
    while(node!=NULL)
    {
        printf("id -> %d %s\n",node->id, node->data);
        node = node->next;
    }
}

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Node** list, int flag)
{
    struct Node* aux = *list;
    struct Node* a;
    struct Node* b;
    /* Base case -- length 0 or 1 */
    if ((aux == NULL) || (aux->next == NULL))
    {
        return;
    }
    /* Split aux into 'a' and 'b' sublists */
    FrontBackSplit(aux, &a, &b);
    /* Recursively sort the sublists */
    MergeSort(&a, flag);
    MergeSort(&b, flag);
    /* answer = merge the two sorted lists together */
    *list = Merge(a, b, flag);
}

struct Node* Merge(struct Node *a, struct Node *b, int flag)
{
    struct Node* result = NULL;
    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);
    /* Pick either a or b, and recur */
    if(flag){
        if (strcmp(a->data,b->data) < 0) {
            result = a;
            result->next = Merge(a->next, b, flag);

        } else {
            result = b;
            result->next = Merge(a, b->next, flag);
        }
    } else {
        if (a->id < b->id) {
            result = a;
            result->next = Merge(a->next, b, flag);

        } else {
            result = b;
            result->next = Merge(a, b->next, flag);
        }
    }
    return(result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef)
{
    struct Node* fast;
    struct Node* slow;
    if (source==NULL || source->next==NULL)
    {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;
        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}





//----------------------------------------Ficheiro Binário----------------------------------------
/** \brief R13. Imprime as estruturas com os resultados da pesquisa para um ficheiro binário.
 *
 * \param RESULTADOSPESQUISA res
 * \param char fn[]
 * \return void
 *
 */
void save_results_bin(RESULTADOSPESQUISA res, char fnb[])
{
    FILE* fp;
    fp = fopen(fnb, "wb");

    if(fp != NULL)
    {
        fwrite(&res, sizeof(RESULTADOSPESQUISA), 1, fp);
        RESULTADO* temp = res.pfirst;
        int i;
        for(i = 0; i < res.nresultados; i++)
        {
            fwrite(temp, sizeof(RESULTADO), 1, fp);
            temp = temp->pnext;
        }
        fclose(fp);
    }
}





//----------------------------------------Ficheiro Texto----------------------------------------
/** \brief R12. Função para testar a leitura dos resultados do ficheiro de texto.
 *
 * \param RESULTADOSPESQUISA res
 * \return void
 *
 */
void print_results(RESULTADOSPESQUISA res)
{
    RESULTADO *temp = res.pfirst;
    int i;
    for(i = 0; i < res.nresultados; i++)
    {
        printf("%s - %d/%d -> %d/%d -> ", temp->ppalavra, temp->linhaInicio, temp->colunaInicio, temp->linhaFim, temp->colunaFim);
        int j = 0;
        while(temp->direcoes[j] != -1)
        {
            printf("%d ", temp->direcoes[j]);
        }
        printf("\n");
    }
}

/** \brief R12. (Incompleto - Não lê corretamente do ficheiro de texto) - Lê os resultados de um ficheiro de texto.
 *
 * \param RESULTADOSPESQUISA* pres
 * \param char fn[]
 * \return void
 *
 */
void read_results_txt(RESULTADOSPESQUISA* pres, char fn[])
{
    FILE* fp;
    fp = fopen(fn, "r");

    if(fp != NULL)
    {
        //Lê o número de resultados (nresultados) para a estrutura RESULTADOSPESQUISA
        fscanf(fp, "%*s %*s %*s %d\n", &(pres->nresultados));
        //Se tiver resultados para ler
        if(pres->nresultados)
        {
            RESULTADO* previous;
            int i;
            for(i = 0; i < pres->nresultados; i++)
            {
                RESULTADO* current = malloc(sizeof(RESULTADO));
                char palavra[50];
                fscanf(fp, "%s %*s %d %*[/] %d %*s %d %*[/] %d %*s", palavra, &current->linhaInicio, &current->colunaInicio,
                       &current->linhaFim, &current->colunaFim);
                current->ppalavra = malloc(sizeof(char)*(strlen(palavra) + 1));
                strcpy(current->ppalavra, palavra);
                int j;
                for(j = 0; j < (strlen(palavra) - 1); j++)
                {
                    char direcao[3];
                    fscanf(fp, "%s", direcao);
                    if(strcmp(direcao, "N") == 0)
                    {
                        current->direcoes[j] = 1;
                    }
                    else if(strcmp(direcao, "NE") == 0)
                    {
                        current->direcoes[j] = 2;
                    }
                    else if(strcmp(direcao, "E") == 0)
                    {
                        current->direcoes[j] = 3;
                    }
                    else if(strcmp(direcao, "SE") == 0)
                    {
                        current->direcoes[j] = 4;
                    }
                    else if(strcmp(direcao, "S") == 0)
                    {
                        current->direcoes[j] = 5;
                    }
                    else if(strcmp(direcao, "SO") == 0)
                    {
                        current->direcoes[j] = 6;
                    }
                    else if(strcmp(direcao, "O") == 0)
                    {
                        current->direcoes[j] = 7;
                    }
                    else if(strcmp(direcao, "NO") == 0)
                    {
                        current->direcoes[j] = 8;
                    }
                }
                fscanf(fp, "\n");
                current->direcoes[j] = -1;

                previous = current;
                //Se estiver no último resultado
                if(i == pres->nresultados - 1)
                {
                    current = NULL;
                }
                else
                {
                    current = malloc(sizeof(RESULTADO));
                }
                previous->pnext = current;
            }
        }
        fclose(fp);
    }
}

/** \brief R12. Imprime as estruturas com os resultados da pesquisa para um ficheiro de texto.
 *
 * \param RESULTADOSPESQUISA res
 * \param char fn[]
 * \return void
 *
 */
void save_results_txt(RESULTADOSPESQUISA res, char fn[])
{
    FILE* fp;
    fp = fopen(fn, "w");

    if(fp != NULL)
    {
        fprintf(fp, "Numero de resultados: %d\n", res.nresultados);
        RESULTADO* temp = res.pfirst;
        int i, j = 0;
        for(i = 0; i < res.nresultados; i++)
        {
            fprintf(fp, "%s - %d/%d -> %d/%d -> ", temp->ppalavra, temp->linhaInicio, temp->colunaInicio,
                    temp->linhaFim, temp->colunaFim);
            while(temp->direcoes[j] != -1)
            {
                if(temp->direcoes[j] == 1)
                {
                    fprintf(fp, "N ");
                }
                if(temp->direcoes[j] == 2)
                {
                    fprintf(fp, "NE ");
                }
                if(temp->direcoes[j] == 3)
                {
                    fprintf(fp, "E ");
                }
                if(temp->direcoes[j] == 4)
                {
                    fprintf(fp, "SE ");
                }
                if(temp->direcoes[j] == 5)
                {
                    fprintf(fp, "S ");
                }
                if(temp->direcoes[j] == 6)
                {
                    fprintf(fp, "SO ");
                }
                if(temp->direcoes[j] == 7)
                {
                    fprintf(fp, "O ");
                }
                if(temp->direcoes[j] == 8)
                {
                    fprintf(fp, "NO ");
                }
                j++;
            }
            fprintf(fp, "\n");
            j = 0;
            temp = temp->pnext;
        }
        fclose(fp);
    }
}





//----------------------------------------Pesquisa----------------------------------------
/** \brief R9. (Incompleto - não pesquisa corretamente as palavras)
 *
 * \param LETRASOPA *letraAtual
 * \param char palavra[]
 * \param int posLetra
 * \return void
 *
 */
void encontraPalavra(LETRASOPA *letraAtual, char palavra[], int posLetra)
{
    if(palavra[posLetra] == '\0')
    {
        //printf("TESTE: [%d, %d]%c -> '%s' encontrada\n", letraAtual->linha, letraAtual->coluna, letraAtual->letra, palavra);
        return;
    }
    if(verificaConsistencia(letraAtual->pN, palavra[posLetra])) //N
    {
        letraAtual = letraAtual->pN;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pNE, palavra[posLetra])) //NE
    {
        letraAtual = letraAtual->pNE;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pE, palavra[posLetra])) //E
    {
        letraAtual = letraAtual->pE;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pSE, palavra[posLetra])) //SE
    {
        letraAtual = letraAtual->pSE;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pS, palavra[posLetra])) //S
    {
        letraAtual = letraAtual->pS;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pSO, palavra[posLetra])) //SO
    {
        letraAtual = letraAtual->pSO;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pO, palavra[posLetra])) //O
    {
        letraAtual = letraAtual->pO;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    if(verificaConsistencia(letraAtual->pNO, palavra[posLetra])) //NO
    {
        letraAtual = letraAtual->pNO;
        encontraPalavra(letraAtual, palavra, posLetra + 1);
    }
    return;
}

/** \brief R9. Função para verificar se na posição recebida tem a próxima letra da palavra a pesquisar.
            Retorna 1 se for a letra certa, retorna 0 se não for a letra certa.
 *
 * \param LETRASOPA *letraAVerificar
 * \param char letra
 * \return 1
 * \return 0
 *
 */
int verificaConsistencia(LETRASOPA *letraAVerificar, char letra)
{
    //Verifica se está dentro do tabuleiro
    if(letraAVerificar != NULL)
    {
        //Verifica se a estrutura tem a letra
        if(letraAVerificar->letra == letra)
        {
            //printf("TESTE: [%d][%d]tem a letra %c\n", letraAVerificar->linha, letraAVerificar->coluna, letra);
            return 1;
        }
    }
    return 0;
}





//----------------------------------------Caractere dados movimentos----------------------------------------
/** \brief R10. - Imprime caracteres dada uma posição inicial e um conjunto de movimentos.
 *
 * \param SOPADELETRAS sopa
 * \return void
 *
 */
void movimentos(SOPADELETRAS sopa)
{
    int linhaInicial, colunaInicial;
    printf("Introduza a linha da posicao inicial(0-%d): ", sopa.linhas-1);
    scanf("%d", &linhaInicial);
    printf("Introduza a coluna da posicao inicial(0-%d): ", sopa.colunas-1);
    scanf("%d", &colunaInicial);
    LETRASOPA *current = sopa.pfirst;
    while(current != NULL)
    {
        if(current->linha == linhaInicial && current->coluna == colunaInicial)
        {
            break;
        }
        current = current->pnext;
    }
    printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
    fflush(stdin);
    int direcao;
    printf("\n");
    while(1)
    {
        printf("Introduza a direcao do movimento\nN=1/NE=2/E=3/SE=4/S=5/SO=6/O=7/NO=8 ou 0 para terminar: ");
        scanf("%d", &direcao);
        fflush(stdin);
        printf("\n");
        if(direcao == 0)
        {
            break;
        }
        else if(direcao == 1)
        {
            if(current->pN == NULL)
            {
                printf("Movimento impossivel. Posicao fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pN;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 2)
        {
            if(current->pNE == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pNE;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 3)
        {
            if(current->pE == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pE;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 4)
        {
            if(current->pSE == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pSE;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 5)
        {
            if(current->pS == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pS;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 6)
        {
            if(current->pSO == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pSO;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 7)
        {
            if(current->pO == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pO;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else if(direcao == 8)
        {
            if(current->pNO == NULL)
            {
                printf("Movimento impossivel. Fica fora do tabuleiro.\n");
                printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
                continue;
            }
            current = current->pNO;
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
        else
        {
            printf("Movimento nao reconhecido.\n");
            printf("Letra atual: [%d][%d] = %c\n", current->linha, current->coluna, current->letra);
        }
    }
}





//----------------------------------------Estrutura Sopa de Letras de Ficheiro----------------------------------------
/** \brief R7. - Cria o tabuleiro, fazendo as ligações de cada letra com as letras à sua volta
 *
 * \param SOPADELETRAS* pSopa
 * \return void
 *
 */
void ligaAsLetras(SOPADELETRAS* pSopa)
{
	LETRASOPA *current = pSopa->pfirst;
	LETRASOPA *aux = pSopa->pfirst;

    while(current != NULL)
    {
        //N
        while(aux != NULL)
        {
            if(aux->linha == (current->linha - 1) && aux->coluna == current->coluna)
            {
                current->pN = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //NE
        while(aux != NULL)
        {
            if(aux->linha == (current->linha - 1) && aux->coluna == (current->coluna + 1))
            {
                current->pNE = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //E
        while(aux != NULL)
        {
            if(aux->linha == current->linha && aux->coluna == (current->coluna + 1))
            {
                current->pE = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //SE
        while(aux != NULL)
        {
            if(aux->linha == (current->linha + 1) && aux->coluna == (current->coluna + 1))
            {
                current->pSE = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //S
        while(aux != NULL)
        {
            if(aux->linha == (current->linha + 1) && aux->coluna == current->coluna)
            {
                current->pS = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //SO
        while(aux != NULL)
        {
            if(aux->linha == (current->linha + 1) && aux->coluna == (current->coluna - 1))
            {
                current->pSO = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //O
        while(aux != NULL)
        {
            if(aux->linha == current->linha && aux->coluna == (current->coluna - 1))
            {
                current->pO = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        //NO
        while(aux != NULL)
        {
            if(aux->linha == (current->linha - 1) && aux->coluna == (current->coluna - 1))
            {
                current->pNO = aux;
                break;
            }
            aux = aux->pnext;
        }
        aux = pSopa->pfirst;

        current = current->pnext;
    }
}

/** \brief R8.a. - Lê caractere a caractere, as letras da Sopa De Letras de um ficheiro txt
 *
 * \param char nomeFicheiro[]
 * \param SOPADELETRAS* pSopa
 * \return void
 *
 */
void lerSopaDeLetrasDeFicheiro(char nomeFicheiro[], SOPADELETRAS* pSopa)
{
    char linha[100];
    FILE *arquivo;
    int i = 0, j;
    arquivo = fopen(nomeFicheiro, "r");
    if(arquivo == NULL)
    {
        printf("O arquivo %s nao existe.\n", nomeFicheiro);
        return;
    }
    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        for(j = 0; j < pSopa->colunas; j++)
        {
            insereLetraNaSopaDeLetras(pSopa, linha[j], i, j);
        }
        i++;
    }
    fclose(arquivo);
}

/** \brief R8.a. - Cria uma lista de estruturas com as letras da Sopa de Letras
 *
 * \param SOPADELETRAS* pSopa
 * \param char letra
 * \param int coluna
 * \param int linha
 * \return void
 *
 */
void insereLetraNaSopaDeLetras(SOPADELETRAS* pSopa, char letra, int linha, int coluna)
{
    LETRASOPA *temp = malloc(sizeof(LETRASOPA));
    temp->letra = letra;
    temp->linha = linha;
    temp->coluna = coluna;
    temp->pN = NULL;
    temp->pNE = NULL;
    temp->pE = NULL;
    temp->pSE = NULL;
    temp->pS = NULL;
    temp->pSO = NULL;
    temp->pO = NULL;
    temp->pNO = NULL;
    temp->pnext = NULL;
    //Se for a primeira letra, liga-a à estrutura "SOPADELETRAS"
    if(linha == 0 && coluna == 0)
    {
        pSopa->pfirst = temp;
    }
    //Se não for a primeira letra, liga-a à última letra da lista
    else
    {
        LETRASOPA *current = pSopa->pfirst;
        //percorre a lista de palavras e poe current a apontar para a última palavra da lista
        while(current->pnext != NULL)
        {
            current = current->pnext;
        }
        current->pnext = temp;
    }
}





//----------------------------------------Estrutura Dicionário de Ficheiro----------------------------------------
/** \brief R5.b. - Lê as palavras do dicionário a partir de um ficheiro.
 *
 * \param char nomeFicheiro[]
 * \param int linhas
 * \param DICIONARIO *pDicio
 * \return void
 *
 */
void lerDicionarioDeFicheiro(char nomeFicheiro[], int linhas, DICIONARIO *pDicio)
{
    char palavraAux[50];
    FILE *ficheiro;
    int i;
    char* pPalavraAux;
    ficheiro = fopen(nomeFicheiro, "r");
    if(ficheiro == NULL)
    {
        printf("O ficheiro %s nao existe.\n", nomeFicheiro);
        return;
    }
    while(fgets(palavraAux, sizeof(palavraAux), ficheiro) != NULL)
    {
        for(i = 0; i < strlen(palavraAux); i++)
        {
            if(palavraAux[i] == '\n')
            {
                palavraAux[i] = '\0';
            }
        }
        pPalavraAux = create_copy_dyn_string(palavraAux);
        inserePalavraNoDicionario(pDicio, pPalavraAux);
    }
    fclose(ficheiro);
}



//----------------------------------------Estrutura Dicionário----------------------------------------
/** \brief R5.a. - Cria uma string dinâmica aponas com o tamanho da palavra inserida.
 *
 * \param char* str
 * \return char* pc
 *
 */
char* create_copy_dyn_string(char* str)
{
    char* pc = malloc((strlen(str) + 1) * sizeof(char)); //+1 para o '\0'
    strcpy(pc, str);
    return pc;
}

/** \brief R5.a. - Insere a palavra na estrutura "PALAVRADICIONARIO" e na estrutura "DICIONARIO".
 *
 * \param DICIONARIO *pDicio
 * \param char* pPalavra
 * \return void
 *
 */
void inserePalavraNoDicionario(DICIONARIO *pDicio, char* pPal)
{
    PALAVRADICIONARIO *temp = malloc(sizeof(PALAVRADICIONARIO));
    temp->palavra = pPal;
    temp->pnext = NULL;
    //Se for a primeira palavra, liga-a à estrutura "DICIONARIO"
    if(pDicio->nPalavras == 0)
    {
        pDicio->pfirst = temp;
        pDicio->nPalavras++;
    }
    //Se não for a primeira palavra, liga-a à última palavra da lista
    else
    {
        PALAVRADICIONARIO *current = pDicio->pfirst;
        //percorre a lista de palavras e poe current a apontar para a última palavra da lista
        while(current->pnext != NULL)
        {
            current = current->pnext;
        }
        current->pnext = temp;
        pDicio->nPalavras++;
    }
}

/** \brief R5.a. - Imprime o Dicionário.
 *
 * \param DICIONARIO dicio
 * \return void
 *
 */
void imprimeDicionario(DICIONARIO dicio)
{
    PALAVRADICIONARIO *temp = dicio.pfirst;
    int i;
    for(i = 0; i < dicio.nPalavras; i++)
    {
        printf("PALAVRA[%d]: %s\n", i, temp->palavra);
        temp = temp->pnext;
    }
}
