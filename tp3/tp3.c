#include <stdio.h>
#include "tp3.h"

/*
int mon_strlen(char s[])
{
  int i;
  for(i=0; s[i]!='\0'; i++)
    ;
  return i;
}
*/

int mon_strlen(const char *s)
{
  const char *p;
  for(p=s; *p!='\0'; p++)
    ;
  return p-s;
}
