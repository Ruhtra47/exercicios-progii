#include <stdio.h>
#include <stdlib.h>

#include "circulo.h"
#include "ponto.h"

int main()
{
    float xc, yc, r, xp, yp;

    scanf("%f %f %f %f %f", &xc, &yc, &r, &xp, &yp);

    tCirculo c = Circulo_Cria(xc, yc, r);
    tPonto p = Pto_Cria(xp, yp);

    printf("%d\n", Circulo_Interior(c, p));

    Pto_Apaga(p);
    Circulo_Apaga(c);

    return 0;
}