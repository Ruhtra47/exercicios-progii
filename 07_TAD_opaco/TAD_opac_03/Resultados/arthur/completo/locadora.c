#include "locadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INCREMENTO_FILMES_LOC 3

struct Locadora
{
    tFilme **filmes;
    int qtdFilmes;
    int lucro;

    int qtdFilmesAloc;
};

/**
 * @brief Cria uma nova instância de tLocadora e inicializa filme como NULL,
 * numFilmes como 0 e lucro como 0.
 *
 * @return tLocadora* Ponteiro para a nova instância de tLocadora criada ou
 * encerra o programa caso não haja memória suficiente.
 */
tLocadora *CriarLocadora()
{
    tLocadora *loc = (tLocadora *)malloc(sizeof(tLocadora));
    loc->qtdFilmesAloc = TAM_INCREMENTO_FILMES_LOC;
    loc->filmes = (tFilme **)malloc(loc->qtdFilmesAloc * sizeof(tFilme *));
    loc->qtdFilmes = 0;
    loc->lucro = 0;

    return loc;
}

/**
 * @brief Destrói uma instância de tLocadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser destruída.
 */
void DestruirLocadora(tLocadora *locadora)
{
    for (int i = 0; i < locadora->qtdFilmes; i++)
    {
        DestruirFilme(locadora->filmes[i]);
    }
    free(locadora->filmes);
    free(locadora);
}

/**
 * @brief Verifica se um filme está cadastrado na locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser verificada.
 * @param codigo Código do filme a ser verificado.
 * @return int 1 se o filme está cadastrado, 0 caso contrário.
 */
int VerificarFilmeCadastrado(tLocadora *locadora, int codigo)
{
    for (int i = 0; i < locadora->qtdFilmes; i++)
    {
        if (EhMesmoCodigoFilme(locadora->filmes[i], codigo))
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Cadastra um novo filme na locadora caso ele não esteja cadastrado.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 * @param filme Ponteiro para o filme a ser cadastrado.
 */
void CadastrarFilmeLocadora(tLocadora *locadora, tFilme *filme)
{
    if (locadora->qtdFilmes >= locadora->qtdFilmesAloc)
    {
        locadora->qtdFilmesAloc += TAM_INCREMENTO_FILMES_LOC;
        locadora->filmes = (tFilme **)realloc(
            locadora->filmes, locadora->qtdFilmesAloc * sizeof(tFilme *));
    }
    printf("Filme cadastrado %d - ", ObterCodigoFilme(filme));
    ImprimirNomeFilme(filme);
    printf("\n");
    locadora->filmes[locadora->qtdFilmes] = filme;
    locadora->qtdFilmes++;
}

/**
 * @brief Lê os dados de cadastro de um filme e o cadastra na locadora.
 *
 * @param Locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void LerCadastroLocadora(tLocadora *Locadora)
{
    int cod;
    while (scanf("%d,", &cod) == 1)
    {
        tFilme *filme = CriarFilme();
        LeFilme(filme, cod);
        if (VerificarFilmeCadastrado(Locadora, cod))
        {
            printf("Filme ja cadastrado no estoque\n");
            DestruirFilme(filme);
            continue;
        }
        CadastrarFilmeLocadora(Locadora, filme);
    }
}

/**
 * @brief Aluga um ou mais filmes da locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 * @param codigos Vetor contendo os códigos dos filmes a serem alugados.
 * @param quantidadeCodigos Número de códigos de filmes a serem alugados.
 */
void AlugarFilmesLocadora(tLocadora *locadora, int *codigos,
                          int quantidadeCodigos)
{
    int totalAlugado = 0, custoTotal = 0;
    for (int i = 0; i < quantidadeCodigos; i++)
    {
        if (!VerificarFilmeCadastrado(locadora, codigos[i]))
        {
            printf("Filme %d nao cadastrado.\n", codigos[i]);
            continue;
        }

        for (int j = 0; j < locadora->qtdFilmes; j++)
        {
            if (EhMesmoCodigoFilme(locadora->filmes[j], codigos[i]))
            {
                if (ObterQtdEstoqueFilme(locadora->filmes[j]) > 0)
                {
                    AlugarFilme(locadora->filmes[j]);
                    totalAlugado++;
                    custoTotal += ObterValorFilme(locadora->filmes[j]);
                }
                else
                {
                    printf("Filme %d - ", codigos[i]);
                    ImprimirNomeFilme(locadora->filmes[j]);
                    printf(" nao disponivel no estoque. Volte mais tarde.\n");
                }
            }
        }
    }
    if (totalAlugado > 0)
    {
        printf("Total de filmes alugados: %d com custo de R$%d\n", totalAlugado,
               custoTotal);
    }
}

/**
 * @brief Lê o aluguel de um conjunto de filmes a partir da entrada padrão e os
 * aluga na locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void LerAluguelLocadora(tLocadora *locadora)
{
    int *cods = NULL;
    int qtdcods = 0;

    int aux;
    while (scanf("%d\n", &aux) == 1)
    {
        cods = (int *)realloc(cods, (qtdcods + 1) * sizeof(int));
        cods[qtdcods] = aux;
        qtdcods++;
    }

    AlugarFilmesLocadora(locadora, cods, qtdcods);
    free(cods);
}

/**
 * @brief Devolve um ou mais filmes alugados da locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 * @param codigos Vetor contendo os códigos dos filmes a serem devolvidos.
 * @param quantidadeCodigos Número de códigos de filmes a serem devolvidos.
 */
void DevolverFilmesLocadora(tLocadora *locadora, int *codigos,
                            int quantidadeCodigos)
{
    for (int i = 0; i < quantidadeCodigos; i++)
    {
        if (!VerificarFilmeCadastrado(locadora, codigos[i]))
        {
            printf("Filme %d nao cadastrado.\n", codigos[i]);
            continue;
        }

        for (int j = 0; j < locadora->qtdFilmes; j++)
        {
            if (EhMesmoCodigoFilme(locadora->filmes[j], codigos[i]))
            {
                if (ObterQtdAlugadaFilme(locadora->filmes[j]) > 0)
                {
                    DevolverFilme(locadora->filmes[j]);
                    locadora->lucro += ObterValorFilme(locadora->filmes[j]);
                    printf("Filme %d - ", codigos[i]);
                    ImprimirNomeFilme(locadora->filmes[j]);
                    printf(" Devolvido!\n");
                }
                else
                {
                    printf("Nao e possivel devolver o filme %d - ", codigos[i]);
                    ImprimirNomeFilme(locadora->filmes[j]);
                    printf(".\n");
                }
            }
        }
    }
}

/**
 * @brief Lê os dados de devolução de um ou mais filmes e os devolve na
 * locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void LerDevolucaoLocadora(tLocadora *locadora)
{
    int *cods = NULL;
    int qtdcods = 0;

    int aux;
    while (scanf("%d\n", &aux) == 1)
    {
        cods = (int *)realloc(cods, (qtdcods + 1) * sizeof(int));
        cods[qtdcods] = aux;
        qtdcods++;
    }

    DevolverFilmesLocadora(locadora, cods, qtdcods);
    free(cods);
}

/**
 * @brief Ordena os filmes cadastrados na locadora por ordem alfabética.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void OrdenarFilmesLocadora(tLocadora *locadora)
{
    int pronto = 0;
    while (!pronto)
    {
        for (int i = 1; i < locadora->qtdFilmes; i++)
        {
            if (CompararNomesFilmes(locadora->filmes[i - 1], locadora->filmes[i]) >
                0)
            {
                tFilme *aux = locadora->filmes[i - 1];
                locadora->filmes[i - 1] = locadora->filmes[i];
                locadora->filmes[i] = aux;
            }
        }
        pronto = 1;
        for (int i = 1; i < locadora->qtdFilmes; i++)
        {
            if (CompararNomesFilmes(locadora->filmes[i - 1], locadora->filmes[i]) >
                0)
            {
                pronto = 0;
                break;
            }
        }
    }
}

/**
 * @brief Consulta o estoque de filmes da locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser consultada.
 */
void ConsultarEstoqueLocadora(tLocadora *locadora)
{
    printf("~ESTOQUE~\n");
    for (int i = 0; i < locadora->qtdFilmes; i++)
    {
        printf("%d - ", ObterCodigoFilme(locadora->filmes[i]));
        ImprimirNomeFilme(locadora->filmes[i]);
        printf(" Fitas em estoque: %d\n",
               ObterQtdEstoqueFilme(locadora->filmes[i]));
    }
}

/**
 * @brief Consulta o lucro da locadora.
 *
 * @param locadora Ponteiro para a instância de tLocadora a ser consultada.
 */
void ConsultarLucroLocadora(tLocadora *locadora)
{
    if (locadora->lucro > 0)
    {
        printf("\nLucro total R$%d\n", locadora->lucro);
    }
}