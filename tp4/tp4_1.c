#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

char * miroir (const char *s)
{/*
  int t = strlen(s)+1;
  s = s+t;
  char *s1 = malloc(t+1);

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

  *(s1+t+1)='\0';
  return (s1-t-1);
 */

  char *res;
  int i = strlen(s);
  int j;
  res = malloc(sizeof(char)*(i+1));
  if(res==NULL)
    {
      return NULL;
    }
  for (j = 0; j<i; j++)
    {
      res[j] = s[i-(j+1)];
    }
  res[i]='\0';
  return res;
}
