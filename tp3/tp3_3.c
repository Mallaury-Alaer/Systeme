#include <stdio.h>
#include "tp3.h"
#include "tp3_3.h"

int mon_strcmp(const char * s1,const  char * s2)
{
  int taille_s1 = mon_strlen(s1);
  int taille_s2 = mon_strlen(s2);
  int i=0;
  int cpt=0;

  while( i<taille_s1 && i<taille_s2 && cpt==0)
    {
      if( *(s1+i) > *(s2+i))
	{
  	  cpt++;
	}
      else if( *(s1+i) < *(s2+i))
	{
	  cpt--;
	}
      i++;
    }
  return cpt;
}

int mon_strncmp(const char *s1, const char *s2, int n)
{
  int taille_s1 = mon_strlen(s1);
  int taille_s2 = mon_strlen(s2);
  int cpt=0;
  int i=0;

  while(i<n && i<taille_s1 && i<taille_s2 && cpt==0)
    {
      if(*(s1+i) > *(s2+i))
	{
	  cpt++;
	}
      else if(*(s1+i) < *(s2+i))
	{
	  cpt--;
	}
      i++;
    }
  return cpt;
}
