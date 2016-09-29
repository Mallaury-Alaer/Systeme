#include <stdio.h>
#include "tp3.h"
#include "tp3_6.h"

char *mon_strchr(char *s, int c)
{
  int i=0;
  
  while( *(s+i) != '\0')
    {
      if(*(s+i) == c)
	{
	  return s+i;
	}
      i++;
    }
  return NULL;
}
