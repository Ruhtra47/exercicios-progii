#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "franquia.h"

/**
 * @brief Estrutura que representa uma franquia.
 *
 * A estrutura franquia contém informações sobre o nome da franquia, sua conferência e seu desempenho em casa e fora.
 *
 */
// typedef struct franquia *tFranquia;

// #define MAX_NOME 32

struct franquia
{
    char nome[MAX_NOME];
    char conf[6];

    int numVitorias;
    int numDerrotas;

    int vitoriasCasa;
    int vitoriasFora;

    int derrotasCasa;
    int derrotasFora;
};

/**
 * @brief Lê uma franquia da entrada padrao e retorna um ponteiro para ela.
 *
 * @return tFranquia Retorna um ponteiro para a franquia lida.
 */
tFranquia LeFranquia()
{
    tFranquia franquia = (tFranquia)malloc(sizeof(struct franquia));

    scanf("%s %s\n", &franquia->nome, &franquia->conf);

    franquia->numVitorias = 0;
    franquia->numDerrotas = 0;
    franquia->vitoriasCasa = 0;
    franquia->vitoriasFora = 0;
    franquia->derrotasCasa = 0;
    franquia->derrotasFora = 0;

    return franquia;
}

/**
 * @brief Libera a memória alocada para uma franquia.
 *
 * @param f Ponteiro para a franquia a ser liberada.
 */
void LiberaFranquia(tFranquia f)
{
    free(f);
}

/**
 * @brief Imprime as informações de uma franquia.
 *
 * @param f Ponteiro para a franquia a ser impressa.
 */
void ImprimeFranquia(tFranquia f)
{
    printf("%s ", f->nome);

    if (!strcmp(f->conf, "LESTE"))
        printf("[CL] ");
    else if (!strcmp(f->conf, "OESTE"))
        printf("[CO] ");

    float aprov = 0.0;

    if ((f->numDerrotas + f->numVitorias) > 0)
        aprov = (float)(f->numVitorias) / (f->numDerrotas + f->numVitorias);

    aprov *= 100.0;

    printf("%d %d %.2f %d %d\n", f->numVitorias, f->numDerrotas, aprov, f->vitoriasCasa, f->vitoriasFora);
}

/**
 * @brief Retorna o nome da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return char* Retorna o nome da franquia.
 */
char *GetNomeFranquia(tFranquia f)
{
    return f->nome;
}

/**
 * @brief Retorna a conferência da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return char* Retorna a conferência da franquia.
 */
char *GetConferenciaFranquia(tFranquia f)
{
    return f->conf;
}

/**
 * @brief Adiciona uma vitória em casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaVitoriaCasaFranquia(tFranquia f)
{
    f->numVitorias++;
    f->vitoriasCasa++;
}

/**
 * @brief Adiciona uma vitória fora de casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaVitoriaForaFranquia(tFranquia f)
{
    f->numVitorias++;
    f->vitoriasFora++;
}

/**
 * @brief Adiciona uma derrota em casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaDerrotaCasaFranquia(tFranquia f)
{
    f->derrotasCasa++;
    f->numDerrotas++;
}

/**
 * @brief Adiciona uma derrota fora de casa para a franquia.
 *
 * @param f Ponteiro para a franquia.
 */
void AdicionaDerrotaForaFranquia(tFranquia f)
{
    f->derrotasFora++;
    f->numDerrotas++;
}

/**
 * @brief Retorna o número de vitórias em casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de vitórias em casa da franquia.
 */
int GetVitoriaCasaFranquia(tFranquia f)
{
    return f->vitoriasCasa;
}

/**
 * @brief Retorna o número de vitórias fora de casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de vitórias fora de casa da franquia.
 */
int GetVitoriaForaFranquia(tFranquia f)
{
    return f->vitoriasFora;
}

/**
 * @brief Retorna o número de derrotas em casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de derrotas em casa da franquia.
 */
int GetDerrotaCasaFranquia(tFranquia f)
{
    return f->derrotasCasa;
}

/**
 * @brief Retorna o número de derrotas fora de casa da franquia.
 *
 * @param f Ponteiro para a franquia.
 * @return int Retorna o número de derrotas fora de casa da franquia.
 */
int GetDerrotaForaFranquia(tFranquia f)
{
    return f->derrotasFora;
}