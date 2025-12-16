#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nba.h"
#include "franquia.h"
#include "partida.h"

// #define MAX_FR 10 // Número máximo de franquias
// #define MAX_PT 10 // Número máximo de partidas
// #define CAD_FRANQUIA 'F' // Caractere para cadastro de franquia
// #define CAD_PARTIDA 'P' // Caractere para cadastro de partida
// #define ENCERRAR 'E' // Caractere para encerrar a NBA

// typedef struct nba * tNBA;
struct nba
{
    tFranquia *franquias;
    int qtd_franquias;
};

tFranquia BuscaFranquiaPorNome(tNBA nba, char *nomeTime)
{
    for (int i = 0; i < nba->qtd_franquias; i++)
    {
        char *nomeFranquiaAtual = GetNomeFranquia(nba->franquias[i]);

        if (!strcmp(nomeFranquiaAtual, nomeTime))
            return nba->franquias[i];
    }

    return NULL;
}

/**
 * @brief Cria uma nova instância da NBA.
 *
 * @return tNBA Retorna um ponteiro para a nova instância da NBA.
 */
tNBA CriaNBA()
{
    tNBA nba = (tNBA)malloc(sizeof(struct nba));

    nba->franquias = NULL;
    nba->qtd_franquias = 0;

    return nba;
}

/**
 * @brief Roda a NBA, permitindo a interação com o usuário.
 *
 * @param nba Ponteiro para a instância da NBA a ser executada.
 * @return tNBA Retorna um ponteiro para a instância da NBA após a execução.
 */
tNBA RodaNBA(tNBA nba)
{
    char cmd;

    while (scanf(" %c", &cmd) == 1 && cmd != ENCERRAR)
    {
        if (cmd == CAD_FRANQUIA)
        {
            tFranquia f = LeFranquia();

            nba->franquias = (tFranquia)realloc(nba->franquias, (nba->qtd_franquias + 1) * sizeof(struct nba));

            nba->franquias[nba->qtd_franquias] = f;
            nba->qtd_franquias++;
        }
        else if (cmd == CAD_PARTIDA)
        {
            tPartida p = LePartida();

            char *nomeTimeCasa = GetTime1Partida(p);
            char *nomeTimeFora = GetTime2Partida(p);

            tFranquia fCasa = BuscaFranquiaPorNome(nba, nomeTimeCasa);
            tFranquia fFora = BuscaFranquiaPorNome(nba, nomeTimeFora);

            if (fCasa && fFora)
            {
                int vencedor = GetVencedorPartida(p);

                if (vencedor == TIME_CASA)
                {
                    AdicionaVitoriaCasaFranquia(fCasa);
                    AdicionaDerrotaForaFranquia(fFora);
                }
                else if (vencedor == TIME_FORA)
                {
                    AdicionaDerrotaCasaFranquia(fCasa);
                    AdicionaVitoriaForaFranquia(fFora);
                }
            }

            LiberaPartida(p);
        }
    }

    return nba;
}

/**
 * @brief Imprime o relatório final da NBA.
 *
 * @param nba Ponteiro para a instância da NBA a ser impressa.
 */
void ImprimeRelatorioNBA(tNBA nba)
{
    int vitoriasLeste = 0, derrotasLeste = 0;
    int vitoriasOeste = 0, derrotasOeste = 0;

    for (int i = 0; i < nba->qtd_franquias; i++)
    {
        tFranquia f = nba->franquias[i];

        ImprimeFranquia(f);

        char *conf = GetConferenciaFranquia(f);

        if (!strcmp(conf, "LESTE"))
        {
            vitoriasLeste += GetVitoriaCasaFranquia(f) + GetVitoriaForaFranquia(f);
            derrotasLeste += GetDerrotaCasaFranquia(f) + GetDerrotaForaFranquia(f);
        }
        else
        {
            vitoriasOeste += GetVitoriaCasaFranquia(f) + GetVitoriaForaFranquia(f);
            derrotasOeste += GetDerrotaCasaFranquia(f) + GetDerrotaForaFranquia(f);
        }
    }

    float aprLeste = 0.0;
    int totalJogosLeste = vitoriasLeste + derrotasLeste;

    if (totalJogosLeste > 0)
    {
        aprLeste = (float)vitoriasLeste / totalJogosLeste * 100.0;
    }

    printf("LESTE %d %d %.2f\n", vitoriasLeste, derrotasLeste, aprLeste);

    float aprOeste = 0.0;
    int totalJogosOeste = vitoriasOeste + derrotasOeste;

    if (totalJogosOeste > 0)
    {
        aprOeste = (float)vitoriasOeste / totalJogosOeste * 100.0;
    }

    printf("OESTE %d %d %.2f\n", vitoriasOeste, derrotasOeste, aprOeste);
}

/**
 * @brief Libera a memória alocada para a instância da NBA.
 *
 * @param nba Ponteiro para a instância da NBA a ser liberada.
 */
void LiberaNBA(tNBA nba)
{
    for (int i = 0; i < nba->qtd_franquias; i++)
    {
        LiberaFranquia(nba->franquias[i]);
    }
    free(nba->franquias);
    free(nba);
}