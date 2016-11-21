#include <stdio.h>
#include "tp6.h"
#include "tp6_1.h"
#include "tp6_2.h"
#include "tp6_3.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
  printf("%d\n",argc);
  
  int de = open(argv[argc-2], O_RDONLY), vers=open(argv[argc-1], O_RDWR | O_CREAT, 0666);
  
  if(de==-1)
    perror(argv[1]);
  else if(vers==-1)
    perror(argv[2]);
  else
    {
      entete_bmp entete; 
      unsigned char *pixels; 
      /*lecture du fichier source */
      lire_entete(de, &entete); 
      pixels = allouer_pixels(&entete); 
      lire_pixels(de, &entete, pixels);

      if(argc>3)
	{
	  int i;
	  for(i=1;i<argc-2;i++)
	    {
	      if(strcmp(argv[i],"-r")==0)
		rouge(&entete, pixels);
	      else if(strcmp(argv[i],"-n")==0)
		negatif(&entete, pixels);
	      else if(strcmp(argv[i],"-b")==0)
		noir_et_blanc(&entete, pixels);
	      else if(strcmp(argv[i],"-s")==0)
		moitie(&entete, pixels, 1);
	      else if(strcmp(argv[i],"-i")==0)
		moitie(&entete, pixels, 0);
	    }
	}
     
      /* écriture du fichier destination*/
      ecrire_entete(vers, &entete); 
      ecrire_pixels(vers, &entete, pixels); 
      /* on libère les pixels */
      free(pixels); 
    }
  close(de);
  close(vers);
  return 0;
}

