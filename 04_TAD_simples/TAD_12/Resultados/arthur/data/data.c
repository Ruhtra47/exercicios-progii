#include <stdio.h>

#include "data.h"

// typedef struct {
//     int dia;
//     int mes;
//     int ano;
// } Data;

/*
Função que cria uma data a partir do dia, mês e ano fornecidos e retorna a data criada.
@param dia: Dia da data.
@param mes: Mês da data.
@param ano: Ano da data.
@return Data criada.
*/
Data criaData(int dia, int mes, int ano) {
  Data d;
  d.dia = dia;
  d.mes = mes;
  d.ano = ano;

  return d;
}

/*
Função que lê uma data do formato DD/MM/AAAA a partir da entrada padrão e retorna a data lida.
@return Data lida.
*/
Data lerData() {
  int dia, mes, ano;
  scanf("%d/%d/%d\n", &dia, &mes, &ano);

  return criaData(dia, mes, ano);
}

/*
Função que calcula a diferença em anos entre duas datas. A diferença é calculada como o número de anos completos entre a data inicial e a data atual.
Ex: Se a data inicial for 15/08/2000 e a data atual for 14/08/2023, a diferença será 22 anos. 
@param inicial: Data inicial.
@param atual: Data atual.
@return Diferença em anos entre as duas datas.
*/
int diferencaAnoData(Data inicial, Data atual) {
  int difAnos = atual.ano - inicial.ano;

  if (difAnos < 0) {
    return 0;
  }

  if (atual.mes < inicial.mes) {
    difAnos--;
  } else if (atual.mes == inicial.mes) {
    if (atual.dia < inicial.dia) {
      difAnos--;
    }
  }

  return difAnos;
}

/*
Função que imprime uma data no formato DD/MM/AAAA.
@param d: Data a ser impressa.
*/
void imprimeData(Data d) {
  printf("%02d/%02d/%02d\n", d.dia, d.mes, d.ano);
}
