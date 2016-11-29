#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "tp6.h"
#include <fcntl.h>


int main(int argc,char *argv[])
{
  
  if(argc<4)
    {
      printf("Erreur nb arguments\n");
      return 1;
    }
    
 
  int input = open(argv[argc-2], O_RDONLY);
  int output = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (input != -1 && output != -1) {
    entete_bmp entete;
    unsigned char *pixels;

    lire_entete(input, &entete);
    pixels = allouer_pixels(&entete);

    lire_pixels(input, &entete, pixels);

    if (argc > 1) {

      int i;
      for (i = 1; i < (argc-2); i++) { 

  if (argv[i][0] == '-') { 
    unsigned int j;
    for (j = 1; j < strlen(argv[i]); j++) {
      
      switch (argv[i][j]) { 
      case 'r':
        rouge(&entete, pixels);
        break;
      case 'n':
        negatif(&entete, pixels);
        break;
      case 'b':
        noir_et_blanc(&entete, pixels);
        break;
      case 's':
        moitie(&entete, pixels, 1);
        break;
      case 'i':
        moitie(&entete, pixels, 0);
        break;
      }
    }
  }
  else {
    return 1;
  }

      }
    }

    ecrire_entete(output, &entete);
    ecrire_pixels(output, &entete, pixels);

    free(pixels);

    close(input);
    close(output);
    return 0;
  }
  return 1;
}