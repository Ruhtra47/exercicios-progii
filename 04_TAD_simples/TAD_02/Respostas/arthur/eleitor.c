#include <stdio.h>

#include "eleitor.h"

tEleitor CriaEleitor(int id, int votoP, int votoG)
{
    tEleitor e = {id, votoP, votoG};
    return e;
}

tEleitor LeEleitor()
{
    int id, votoP, votoG;
    scanf("%d %d %d\n", &id, &votoP, &votoG);

    return CriaEleitor(id, votoP, votoG);
}

int ObtemVotoPresidente(tEleitor eleitor)
{
    return eleitor.votoP;
}

int ObtemVotoGovernador(tEleitor eleitor)
{
    return eleitor.votoG;
}

int EhMesmoEleitor(tEleitor eleitor1, tEleitor eleitor2)
{
    return eleitor1.id == eleitor2.id;
}