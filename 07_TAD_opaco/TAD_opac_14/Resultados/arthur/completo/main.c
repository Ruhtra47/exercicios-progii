#include <stdio.h>
#include <stdlib.h>

#include "nba.h"
#include "franquia.h"
#include "partida.h"

int main()
{
    tNBA nba = CriaNBA();

    nba = RodaNBA(nba);

    ImprimeRelatorioNBA(nba);

    LiberaNBA(nba);

    return 0;
}