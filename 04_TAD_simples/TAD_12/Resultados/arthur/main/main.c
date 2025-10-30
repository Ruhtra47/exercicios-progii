#include <stdio.h>
#include <string.h>

#include "paciente.h"

#define MAX_PACIENTES 100

int getIndicePaciente(int numPacientes, Paciente *pacientes, char *cartao) {
  for (int i = 0; i < numPacientes; i++) {
    char cartaoSusP[MAX_CARTAO_SUS];
    getCartaoSusPaciente(pacientes[i], cartaoSusP);
    if (strcmp(cartaoSusP, cartao) == 0) {
      return i;
    }
  }

  return -1;
}

int main() {
  char choice;
  Paciente pacientes[MAX_PACIENTES];
  int numPacientes = 0, mediaIdades = 0, totalLesoes = 0, totalCirurgias = 0;

  const Data dataBase = criaData(12, 9, 2023);

  while (scanf("%c\n", &choice) && choice != 'F') {
    switch (choice) {
      case 'P':
        if (numPacientes >= MAX_PACIENTES) {
          printf("Maximmo de pacientes no banco de dados alcancado.\n");
          return 1;
        }

        pacientes[numPacientes] = lerPaciente();

        mediaIdades += calculaIdadePaciente(pacientes[numPacientes], dataBase);
        numPacientes++;
        break;
      case 'L':
        Lesao lesao = lerLesao();
        char cartaoSus[MAX_CARTAO_SUS];
        getCartaoSusLesao(lesao, cartaoSus);
        int indexPaciente = getIndicePaciente(numPacientes, pacientes, cartaoSus);
        if (indexPaciente != -1) {
          pacientes[indexPaciente] = vinculaLesaoPaciente(pacientes[indexPaciente], lesao);
        }
        break;
    }
  }

  if (numPacientes)
    mediaIdades /= numPacientes;

  for (int i = 0; i < numPacientes; i++) {
    totalLesoes += getNumLesoesPaciente(pacientes[i]);
    totalCirurgias += qtdLesoesCirurgicasPaciente(pacientes[i]);
  }

  printf("TOTAL PACIENTES: %d\n", numPacientes);
  printf("MEDIA IDADE (ANOS): ");
  if (mediaIdades) printf("%d\n", mediaIdades);
  else printf("-\n");
  printf("TOTAL LESOES: %d\n", totalLesoes);
  printf("TOTAL CIRURGIAS: %d\n", totalCirurgias);
  printf("LISTA DE PACIENTES:\n");

  for (int i = 0; i < numPacientes; i++) {
    imprimePaciente(pacientes[i]);
  }

  return 0;
}
