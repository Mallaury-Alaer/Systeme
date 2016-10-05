#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

char * miroir (const char *s)
{
  int t = strlen(s)-1;
  s = s+t;
  char *s1 = malloc(t);

  if(s1 == NULL)
    {
      return NULL;
    }

  while((*s)!= '\0')
    {
      *s1 = *s;
      s1++;
      s--;
    }

  *(s1+t)='\0';
  return (s1-t)-1;
}
