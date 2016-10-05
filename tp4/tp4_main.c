#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[])
{
  /* 
     main provisoire
     const char *c = "coucou";

     printf("Miroir : %s \n", miroir(c));
     printf("Saisie : %s \n", saisie());
  */

  int i=0;
  int m=0;
  int s=0;
  int a=0;

  for(i=1; i<argc; i++)
    {
      if(strchr(argv[i],'-') != NULL && strchr(argv[i],'m') != NULL)
	{
	  m=1;
	}
      if(strchr(argv[i],'-') != NULL && strchr(argv[i],'s') != NULL)
	{
	  s=1;
	}
      if(strchr(argv[i],'-') == NULL && a==0)
	{
	  a=i;
	}
      
    }
  
  if(m==1 && s==0)//Si seulement m est present
    {
      if(a != 0)
	{
	  printf("Miroir: %s \n", miroir(argv[a]));
	}
      else
	{
	  printf("Mauvaise utilisation. \n");
	}
    }
  else if(m==0 && s==1)//Si seulement s est present
    {
      printf("Saisir une chaine: \n");
      printf("Saisie: %s \n",saisie());
    }
  else if(m==1 && s==1)//Si les deux sont presents
    {
      printf("Saisir une chaine: \n");
      char *chaine = saisie();
      printf("%s \n",miroir(chaine)); 
    }
  else
    {
      printf("Mauvaise utilisation. \n");
    }
      
  

    return 0;
}
