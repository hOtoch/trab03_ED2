#include "utils.h"
#include "page.h"

int verifyStopWord(char *word, char **stopWordsList, int countStopWords)
{
    int i;
    for (i = 0; i < countStopWords; i++)
    {
        if (strcmp(word, stopWordsList[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void searchAndPrint(TST* indexTST){
    if(indexTST){
        if(getValues(indexTST) != NULL){
            String** values = (String**)getValues(indexTST);
            
            printf("Pages: ");
            for(int i = 0; i < getCountValues(indexTST); i++){
                printf("%s ", getString(values[i]));
            }
            printf("\n");
        }

        searchAndPrint(getLeft(indexTST));
        searchAndPrint(getMid(indexTST));
        searchAndPrint(getRight(indexTST));
    }
}

TST* searchAndIndex(TST * indexTST, TST *pages, char *pathPage, String **stopWordsList, int swCount)
{

    if (pages)
    {
        if (getValues(pages) != NULL)
        {
            Page **pagesResult = (Page **)getValues(pages);
            Page *pageResult = pagesResult[0];
            // printf("Page: %s\n", getString(getNome(pageResult)));
            indexTST = indexador(indexTST, pageResult, pathPage, stopWordsList, swCount);

        }
        indexTST = searchAndIndex(indexTST, getLeft(pages), pathPage, stopWordsList, swCount);
        indexTST = searchAndIndex(indexTST, getMid(pages), pathPage, stopWordsList, swCount);
        indexTST = searchAndIndex(indexTST, getRight(pages), pathPage, stopWordsList, swCount);

    }
    return indexTST;
}

TST* indexador(TST *indexTST, Page *page, char *pathPage, String **stopWordsList, int swCount)
{
    char result[100];
    char *line = (char *)malloc(sizeof(char) * 100);
    size_t len = 0;
    char *termo;


    strcpy(result, pathPage);
    strcat(result, getString(getNome(page))); /* Definindo o caminho dos arquivos */
    removeNewLine(createString(result));


    FILE *filePage = fopen(result, "r");

    if (verificaArquivo(filePage))
    {

        // printf("---------------- Indexando %s ------------------\n", getString(getNome(page)));
        while (!feof(filePage))
        {
            getline(&line, &len, filePage);

            

            termo = strtok(line, " ");
            while (termo != NULL)
            {
                /* Remove o \n e transforma todas as letras em lowcase */
                String *termoString = createString(termo);
                toLowerCase(termoString);
                removeNewLine(termoString);

                // printf("Termo: %s", getString(termoString));

                // Verificar se eh stopword (busca binaria)
                int index = binarySearch(stopWordsList, 0, swCount - 1, getString(termoString));

                if (index == -1)
                {
                    // printf("--- Termo <%s> nao eh stopword ---\n", getString(termoString));
                    // root = RBT_insert(root, termoString, pages[i]);

                    indexTST = TST_insert(indexTST, termoString, (Page *)page); 
                }
                else
                {
                    // printf("--- Termo <%s> eh stopword ---\n", getString(termoString));
                }

                termo = strtok(NULL, " ");
                // printf("--------------------------------------------------------------------\n");
            }
        }
        fclose(filePage);
        return indexTST;
    }
    else
    {
        perror("Error: ");
        exit(1);
    }

}

double calculatePageRank(Page* page, int pagesCount){
   
    double alfa = 0.85;
    double rank;
    double e = 1 / pagesCount;
    if(getCountOutLinks(page) != 0){
        rank = ((1 - alfa) / (double)pagesCount);
    }else{
        rank = ((1 - alfa) / (double)pagesCount) + (alfa * getPageRank(page));
    }

    TST* links = getLinks(page);
    
    int iteracao = 0;

    
    while(1){
        Page** links = getValues(getLinks(page));
        double result = 0;
        double** resultadosPassados = (double**)malloc(sizeof(double) * pagesCount);
        double** resultadosAtuais = (double**)malloc(sizeof(double) * pagesCount);
        for(int i = 0; i < pagesCount; i++){
            r
            for(int j  = 0; j < getCountInLinks(page); j++){
                double auxResult = 0;
                resultadosAtuais[i][j] = getPageRank(links[i]) / getCountOutLinks(links[i]);
                result += getPageRank(links[i]) / getCountOutLinks(links[i]);
            }
        }
       

        double pagerank = rank + (alfa * result);
        
        e = (1 / pagesCount);
        double result2 = 0;
        for(int i = 0; i < getCountInLinks(page); i++){
            result2 += pagerank
        }


        resultadosPassados = resultadosAtuais;

        if(e < 1E-6){
            break;
        }
    }
        
}

TST* searchAndCalculatePR(TST* pages){
    if(pages){
        if(getValues(pages) != NULL){
            Page** pagesResult = (Page**)getValues(pages);
            Page* pageResult = pagesResult[0];
            pages = calculatePageRank(page);
        }

        pages = searchAndCalculatePR(getLeft(pages));
        pages = searchAndCalculatePR(getMid(pages));
        searchAndCalculatePR(getRight(pages));
    }

    return pages;
}

int binarySearch(String **arr, int left, int right, char *key)
{

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        // printf("left = %d, right = %d, mid = %d\n", left, right,mid);
        // printf("comparando %s com %s\n", key, getString(arr[mid]));
        int cmp = compare(createString(key), arr[mid]);

        if (cmp == 0)
        {
            return mid;
        }

        else if (cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}
