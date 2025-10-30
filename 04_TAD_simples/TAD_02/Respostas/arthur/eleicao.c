#include <stdio.h>

#include "candidato.h"
#include "eleitor.h"

// typedef struct {
//     tCandidato presidentes[MAX_CANDIDATOS_POR_CARGO];
//     int totalPresidentes;
//
//     tCandidato governadores[MAX_CANDIDATOS_POR_CARGO];
//     int totalGovernadores;
//
//     int votosBrancosPresidente;
//     int votosNulosPresidente;
//
//     int votosBrancosGovernador;
//     int votosNulosGovernador;
//
//     tEleitor eleitores[MAX_ELEITORES];
//     int totalEleitores;
//     
// } tEleicao;

/**
 * @brief Inicializa uma eleição com valores padrão (zerando os votos invalidos).
 * Ainda nessa função, é lido a quantidade de candidatos e os candidatos são lidos e armazenados.
 * @return Eleição inicializada.
 */
tEleicao InicializaEleicao() {
  tEleicao eleicao;

  scanf("%d", &eleicao.totalPresidentes);

  for (int i = 0; i < eleicao.totalPresidentes; i++) {
    eleicao.presidentes[i] = LeCandidato();
  }

  scanf("%d", &eleicao.totalGovernadores);

  for (int i = 0; i < eleicao.totalGovernadores; i++) {
    eleicao.governadores[i] = LeCandidato();
  }

  eleicao.votosBrancosPresidente = 0;
  eleicao.votosNulosPresidente = 0;

  eleicao.votosBrancosGovernador = 0;
  eleicao.votosNulosGovernador = 0;

  return eleicao;
}

/**
 * @brief Realiza uma eleição.
 * Nessa função, é lido a quantidade de eleitores e os eleitores são lidos e armazenados.
 * @param eleicao Eleição a ser realizada.
 * @return Eleição com os resultados da votação.
 */
tEleicao RealizaEleicao(tEleicao eleicao);

/**
 * @brief Imprime o resultado da eleição na tela a partir da aparucao dos votos.
 * @param eleicao Eleição a ser impressa.
 */
void ImprimeResultadoEleicao(tEleicao eleicao);
