#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  int fc;
  int totalcar = 0;
  int totalmot = 0;
  int totallig = 0;
  int optc = 0;
  int optm = 0;
  int optl = 0;
  int i=1;
  int j;
  int car = 0;
  int ligne = 0;
  int mots = 0;
  int plrfich=0;

  while(i<argc && argv[i][0] == '-')
    {
      j=1;
      if(argv[i][1] == '\0')
	{
	  printf("Erreur d'argument");
	  exit(1);
	}
      while(argv[i][j] != '\0')
	{
	  if( argv[i][j] != 'c' && argv[i][j] != 'w' && argv[i][j] != 'l')
	    {
	      printf("Erreur d'argument: %s \n", argv[i]);
	      exit(1);
	    }
	  if(argv[i][j] == 'c')
	    {
	      optc =1;
	    }
	  if(argv[i][j] == 'w')
	    {
	      optm = 1;
	    }
	  if(argv[i][j] == 'l')
	    {
	      optl = 1;
	    }
	  j++;
	}
      i++;
    }

  if(optc==0 && optm==0 && optl==0)
    {
      optc=1;
      optm=1;
      optl=1;
    }

  if(i == argc)
    {
      traiter(0, &car, &mots, &ligne);
      if(optc == 1)
	{
	  printf("Nb caracteres : %d \n", car);
	}
      if(optm == 1)
	{
	  printf("Nb mots : %d \n", mots);
	}
      if(optl == 1)
	{
	  printf("Nb lignes : %d \n", ligne);
	}
    }

  while(i<argc)
    {
      if((fc = open(argv[i], O_RDONLY)) == -1)
	{
	  perror(argv[i]);
	}
      else
	{
	  printf("%s : ", argv[i]);
	  traiter(fc, &car, &mots, &ligne);
	  totalcar += car;
	  totalmot += mots;
	  totallig +=ligne;
	  
	  if(optc == 1)
	    {
	      printf(" Caracteres : %d ", car);
	    }
	  if(optm == 1)
	    {
	      printf(" Mots : %d ", mots);
	    }
	  if(optl == 1)
	    {
	      printf(" Lignes : %d ",ligne); 
	    }
	  printf("\n");
	   if(car != totalcar || mots!=totalmot || ligne!=totallig){
	    plrfich=1;
	    }
	  car=0;
	  mots=0;
	  ligne=0;
	  close(fc);
	}
      i++;
    }

  if(plrfich == 1)
    {
      printf("Total des fichiers : Caracteres : %d | Mots : %d | Lignes : %d \n",totalcar,totalmot,totallig);
    }
  
  return 0;
}
