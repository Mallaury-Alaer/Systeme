#include <stdio.h>
#include "tp1_2.h"
#include "tp1_3.h"

void fonction_b(int param)
{
  if (param == 0)
    printf("Le parametre est nul\n");
  else
    printf("Le retour de la fonction_a est %d\n", fonction_a(param));
}
