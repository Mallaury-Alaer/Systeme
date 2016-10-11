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

  char optstring[]="ms";
  int inc=0;
  int m=0;
  int sopt=0;
  int c;
  char *s;
  char *sai;
  char *mir;

  while( (c=getopt(argc, argv, optstring)) != EOF)
    {
      if(((char) c == 'm' && !m) || ((char) c == 's' && !sopt))
	{
	  if((char) c == 'm')
	    {
	      m=1;
	    }
	  else
	    {
	      sopt=1;
	    }
	}
      else
	{
	  inc = 1;
	}
    }
  
  if(!inc)
    {
      if(m && sopt)
	{
	  printf("Saisir une chaine: ");
	  sai = saisie();
	  mir = miroir(sai);
	  printf("Miroir : %s \n",mir);
	  free(sai);
	  free(mir);
	}
      else
	{
	  if(m)
	    {
	      s = argv[optind];
	      if(s == '\0')
		{
		  printf("Mauvaise utilisation. \n");
		}
	      else
		{
		  mir = miroir(s);
		  printf("Miroir : %s \n",mir);
		  free(mir);
		}
	    }
	  if(sopt)
	    {
	      printf("Saisir une chaine: ");
	      sai = saisie();
	      printf("Saisie : %s \n", sai);
	      free(sai);
	    }
	}
    }
  else
    {
      printf("Mauvaise utilisation.");
    }

  
  return 0;
}
