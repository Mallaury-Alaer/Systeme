#include <stdio.h>
#include "tp4.h"

int main(void)
{
  const char *c = "coucou";

  printf("Miroir : %s \n", miroir(c));
  printf("Saisie : %s \n", saisie());

  return 0;
}
