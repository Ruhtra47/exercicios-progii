#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "conta.h"
#include "operacao.h"
#include "agencia.h"

#define LIMITE_SUSPEITO 20000.0

// typedef struct Agencia tAgencia;
struct Agencia
{
    tConta **contas;
    int numContas;
    tOperacao **operacoes;
    int numOperacoes;
};

void AdicionaConta(tAgencia *agencia, tConta *conta)
{
    agencia->numContas++;
    agencia->contas = (tConta **)realloc(agencia->contas, agencia->numContas * sizeof(tConta *));

    agencia->contas[agencia->numContas - 1] = conta;
}

void AdicionaOperacao(tAgencia *agencia, tOperacao *operacao)
{
    agencia->numOperacoes++;
    agencia->operacoes = (tOperacao **)realloc(agencia->operacoes, agencia->numOperacoes * sizeof(tOperacao *));

    agencia->operacoes[agencia->numOperacoes - 1] = operacao;
}

int ComparaContasPorSaldo(const void *a, const void *b)
{
    tConta *contaA = *(tConta **)a;
    tConta *contaB = *(tConta **)b;

    float saldoA = RetornaSaldoConta(contaA);
    float saldoB = RetornaSaldoConta(contaB);

    return saldoB - saldoA;
}

/**
 * @brief Cria uma variável (alocada dinamicamente) do tipo tAgencia. Ponteiros devem ser inicializados com NULL e variáveis numéricas com valor zero.
 *
 * @return A variável do tipo Agencia inicializada.
 */
tAgencia *CriaAgencia()
{
    tAgencia *agencia = (tAgencia *)malloc(sizeof(struct Agencia));

    agencia->contas = NULL;
    agencia->numContas = 0;
    agencia->operacoes = NULL;
    agencia->numOperacoes = 0;

    return agencia;
}

/**
 * @brief Libera toda a memória alocada para armazenar dados de uma agencia.
 *
 * @param A variável do tipo Agencia que será apagada.
 */
void DestroiAgencia(tAgencia *agencia)
{
    for (int i = 0; i < agencia->numOperacoes; i++)
        DestroiOperacao(agencia->operacoes[i]);
    free(agencia->operacoes);

    for (int i = 0; i < agencia->numContas; i++)
        DestroiConta(agencia->contas[i]);
    free(agencia->contas);

    free(agencia);
}

/**
 * @brief Le as informações de uma agencia - contas e operações, no formato especificado no roteiro
 *
 * @param agencia - A variável do tipo agencia que salvará os dados lidos
 */
void LeOperacoes(tAgencia *agencia)
{
    int numContas, numOperacoes, idConta;
    float valorOperacao;
    tConta *conta;

    scanf("%d", &numContas);

    for (int i = 0; i < numContas; i++)
    {
        scanf("%d", &idConta);

        if (idConta > 0)
        {
            tConta *novaConta = CriaConta(idConta);

            AdicionaConta(agencia, novaConta);
        }
    }

    scanf("%d", &numOperacoes);

    for (int i = 0; i < numOperacoes; i++)
    {
        scanf("%d %f", &idConta, &valorOperacao);

        conta = BuscaContaPorId(agencia, idConta);

        if (conta != NULL)
        {
            tOperacao *novaOperacao = CriaOperacao(conta, valorOperacao);
            AdicionaOperacao(agencia, novaOperacao);
        }
    }
}

/**
 * @brief Busca uma conta na agencia que possui um id específico
 *
 * @param agencia - A agencia na qual queremos buscar a conta com o id específico
 * @param id - o ID da conta que queremos buscar
 *conferido
 * @return A conta, caso exista, e NULL, caso contrário
 */
tConta *BuscaContaPorId(tAgencia *agencia, int id)
{
    for (int i = 0; i < agencia->numContas; i++)
    {
        if (ConfereIdConta(agencia->contas[i], id))
            return agencia->contas[i];
    }

    return NULL;
}

/**
 * @brief Função que imprime em tela as operações suspeitas de uma agência
 *
 * @param agencia A Agência na qual as operações suspeitas serão impressas em tela.
 */
void ImprimeOperacoesSuspeitas(tAgencia *agencia)
{
    printf("\nA lista de operações suspeitas:\n");

    for (int i = 0; i < agencia->numOperacoes; i++)
    {
        tOperacao *op = agencia->operacoes[i];
        float valor = ConsultaValorOperacao(op);
        if ((valor > LIMITE_SUSPEITO) || (valor < -LIMITE_SUSPEITO))
        {
            ImprimeOperacao(agencia->operacoes[i]);
        }
    }
}

/**
 * @brief Função que imprime em tela os dois correntistas com maior saldo
 *
 * @param agencia A Agência na qual os dois correntistas com maior saldo impressos em tela.
 */
void ImprimeDoisCorrentistasComMaiorSaldo(tAgencia *agencia)
{
    tConta **contasOrdenadas = (tConta **)malloc(agencia->numContas * sizeof(struct tConta *));

    memcpy(contasOrdenadas, agencia->contas, agencia->numContas * sizeof(tConta *));

    qsort(contasOrdenadas, agencia->numContas, sizeof(tConta *), ComparaContasPorSaldo);

    int limite = (agencia->numContas < 2) ? agencia->numContas : 2;

    printf("Os dois correntistas com maior saldo são:\n");

    for (int i = 0; i < limite; i++)
    {
        printf("Id: %d, Saldo: %.2f\n", RetornaIdConta(contasOrdenadas[i]), RetornaSaldoConta(contasOrdenadas[i]));
    }

    free(contasOrdenadas);
}

/**
 * @brief Função que imprime em tela o saldo total da agência
 *
 * @param agencia A Agência na qual o saldo total impresso em tela.
 */
void ImprimeSaldoTotal(tAgencia *agencia)
{
    float saldoTotal = 0.0;

    for (int i = 0; i < agencia->numContas; i++)
    {
        saldoTotal += RetornaSaldoConta(agencia->contas[i]);
    }

    printf("O saldo total da agencia eh: %.2f\n", saldoTotal);
}