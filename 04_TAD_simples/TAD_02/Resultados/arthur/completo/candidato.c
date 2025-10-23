#include <stdio.h>

#include "candidato.h"

tCandidato CriaCandidato(char *nome, char *partido, char cargo, int id)
{
    tCandidato c = {nome, partido, cargo, id, 0};
    return c;
}

tCandidato LeCandidato()
{
    char *nome, *partido, cargo;
    int id;

    scanf("%*c,%*c,%c,%d", nome, partido, &cargo, &id);

    tCandidato c = CriaCandidato(nome, partido, cargo, id);

    return c;
}

int VerificaIdCandidato(tCandidato candidato, int id)
{
}

int EhMesmoCandidato(tCandidato candidato1, tCandidato candidato2)
{
    return candidato1 == candidato2;
}

char ObtemCargo(tCandidato candidato)
{
    return candidato.cargo;
}

tCandidato IncrementaVotoCandidato(tCandidato candidato)
{
    candidato.votos++;
    return candidato;
}

int ObtemVotos(tCandidato candidato)
{
    return candidato.votos;
}

float CalculaPercentualVotos(tCandidato candidato, int totalVotos)
{
    return candidato.votos / totalVotos * 100;
}

void ImprimeCandidato(tCandidato candidato, float percentualVotos)
{
}