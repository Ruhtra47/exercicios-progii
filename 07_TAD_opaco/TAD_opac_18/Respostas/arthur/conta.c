#include <stdlib.h>
#include <stdio.h>

#include "conta.h"

// typedef struct Conta tConta;

struct Conta
{
    int id;
    float saldo;
};

/**
 * @brief Cria uma variável (alocada dinamicamente) do tipo tConta. Ponteiros devem ser inicializados com NULL e variáveis numéricas com valor zero (exceto aquelas passadas como parâmetro para a função).
 *
 * @param id - o Id da conta que será criada
 *
 * @return A variável do tipo tConta inicializada.
 */
tConta *CriaConta(int id)
{
    tConta *c = (tConta *)malloc(sizeof(struct Conta));

    c->id = id;
    c->saldo = 0.0;

    return c;
}

/**
 * @brief Libera toda a memória alocada para armazenar dados de uma conta.
 *
 * @param A variável do tipo tConta que será apagada.
 */
void DestroiConta(tConta *conta)
{
    if (conta != NULL)
    {
        free(conta);
    }
}

/**
 * @brief Função que altera o saldo de uma conta específica.
 *
 * @param conta - A conta que terá seu saldo alterado
 * @param valor - O valor a ser alterado no saldo atual da conta
 *
 */
void AlteraSaldoConta(tConta *conta, float valor)
{
    conta->saldo += valor;
}

/**
 * @brief Função que confere se uma conta possui um id específico
 *
 * @param conta - A conta que terá seu id conferido
 * @param id - O id a ser comparado com a conta
 *
 * @return Uma variável inteira com 1 caso o id da conta seja igual ao parâmetro id, e 0 caso contrárioconferido
 *
 */
int ConfereIdConta(tConta *conta, int id)
{
    return (conta->id == id);
}

/**
 * @brief Função que retorna o Id de uma conta
 *
 * @param conta - A conta que terá seu id retornado.
 *
 * @return O id da conta passada como parâmetro.
 *
 */
int RetornaIdConta(tConta *conta)
{
    return conta->id;
}

/**
 * @brief Função que retorna o Saldo de uma conta.
 *
 * @param conta - A conta que terá seu saldo retornado
 *
 * @return O saldo da conta passada como parâmetro.
 *
 */
float RetornaSaldoConta(tConta *conta)
{
    return conta->saldo;
}
