#include <stdio.h>
#include <stdlib.h>

#include "loja.h"

int findIdLojas(int numLojas, tLoja *lojas, int id) {
  for (int i = 0; i < numLojas; i++) {
    if (VerificaIdLoja(lojas[i], id)) {
      return i;
    }
  }

  printf("ID nao existe.");
  exit(1);
}

int main() {
  int numLojas = 0, lojasRegistradas = 0, choice = 0;

  scanf("%d\n", &numLojas);

  tLoja lojas[numLojas];

  while (scanf("%d\n", &choice) && choice != 0) {
    if (choice == 1) {
      int id;
      float aluguel;

      scanf("%d %f\n", &id, &aluguel);

      lojas[lojasRegistradas] = AbreLoja(id, aluguel);
      lojasRegistradas++;
    } else if (choice == 2) {
      char nome[50];
      float salario, prct_comissao;
      int id;

      scanf("%s %f %f\n", nome, &salario, &prct_comissao);
      scanf("%d\n", &id);

      tVendedor vendedor = RegistraVendedor(nome, salario, prct_comissao);
      lojas[findIdLojas(lojasRegistradas, lojas, id)] = ContrataVendedor(lojas[findIdLojas(lojasRegistradas, lojas, id)], vendedor);
    } else if (choice == 3) {
      int id;
      char nome[50];
      float venda;

      scanf("%d %s %f\n", &id, nome, &venda);

      lojas[findIdLojas(lojasRegistradas, lojas, id)] = RegistraVenda(lojas[findIdLojas(lojasRegistradas, lojas, id)], nome, venda);
    } else if (choice == 4) {
      for (int i = 0; i < lojasRegistradas; i++) {
        lojas[i] = CalculaLucro(lojas[i]);
        ImprimeRelatorioLoja(lojas[i]);
        puts("");
      }
    }
  }

  return 0;
}
