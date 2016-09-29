#include <stdio.h>
#include "tp3.h"
#include "tp3_5.h"

char *mon_strcat(char *s1, const char *s2)
{
  int ts1 = mon_strlen(s1);
  int i = 0;

  while( *(s2+i) != '\0' )
    {
      *(s1+ts1+i) = *(s2+i);
      i++;
    }

  *(s1+ts1+i)='\0';

  return s1;
}
