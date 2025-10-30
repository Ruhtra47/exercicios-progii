#include  <stdio.h>
#include <string.h>

#include "vendedor.h"

// typedef struct Vendedor {
//     char nome[50]; /**< Nome do vendedor */
//     float valor_vendido; /**< Valor total vendido pelo vendedor */
//     float salario; /**< Salário base do vendedor */
//     float prct_comissao; /**< Porcentagem de comissão do vendedor */
// } tVendedor;

/**
 * @brief Registra um novo vendedor.
 * 
 * @param nome Nome do vendedor.
 * @param salario Salário base do vendedor.
 * @param prct_comissao Porcentagem de comissão do vendedor.
 * @return tVendedor Retorna a estrutura do tipo tVendedor com os dados do vendedor registrado.
 */
tVendedor RegistraVendedor(char nome[50], float salario, float prct_comissao) {
  tVendedor v;
  strcpy(v.nome, nome);
  v.salario = salario;
  v.prct_comissao = prct_comissao;
  v.valor_vendido = 0;

  return v;
}

/**
 * @brief Verifica se o nome de um vendedor é igual a outro.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor a ser verificado.
 * @param nome Nome do vendedor a ser comparado.
 * @return int Retorna 1 se o nome do vendedor é igual ao nome passado como parâmetro, ou 0 caso contrário.
 */
int VerificaNomeVendedor(tVendedor vendedor, char nome[50]) {
  return (strcmp(vendedor.nome, nome) == 0);
}

/**
 * @brief Contabiliza uma venda para um vendedor.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor.
 * @param valor Valor da venda a ser contabilizada.
 * @return tVendedor Retorna a estrutura do tipo tVendedor atualizada com o valor da venda contabilizada.
 */
tVendedor ContabilizaVenda(tVendedor vendedor, float valor) {
  vendedor.valor_vendido += valor;

  return vendedor;
}

/**
 * @brief Obtém o salário de um vendedor.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor.
 * @return float Retorna o salário do vendedor.
 */
float GetSalario(tVendedor vendedor) {
  return vendedor.salario;
}

/**
 * @brief Obtém a comissão de um vendedor.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor.
 * @return float Retorna a comissão do vendedor.
 */
float GetComissao(tVendedor vendedor) {
  return (vendedor.prct_comissao * vendedor.valor_vendido);
}

/**
 * @brief Obtém o total vendido por um vendedor.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor.
 * @return float Retorna o total vendido pelo vendedor.
 */
float GetTotalVendido(tVendedor vendedor) {
  return vendedor.valor_vendido;
}

/**
 * @brief Obtém o total recebido por um vendedor.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor.
 * @return float Retorna o total recebido pelo vendedor (salário + comissão).
 */
float GetTotalRecebido(tVendedor vendedor) {
  return (vendedor.salario + (vendedor.valor_vendido * vendedor.prct_comissao));
}

/**
 * @brief Imprime o relatório de um vendedor.
 * 
 * @param vendedor Estrutura do tipo tVendedor contendo os dados do vendedor.
 */
void ImprimeRelatorioVendedor(tVendedor vendedor) {
  printf("\t%s > Total vendido: R$%.2f\n", vendedor.nome, vendedor.valor_vendido);
  printf("\t\tTotal recebido: R$%.2f\n", GetTotalRecebido(vendedor));
}
