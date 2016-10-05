#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tp4.h"

char * saisie()
{
  char *c = malloc(0);
  char sai = 'z';
  int i=0;

  while(sai!=EOF && !isspace(sai))
    {
      sai=getchar();
      *(c+i)=sai;
      i++;
      c=realloc(c,i);
    }

  *(c+i)='\0';
  return c;
}
