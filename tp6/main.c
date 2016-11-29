#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "tp6.h"
#include <fcntl.h>


int main(int argc,char *argv[])
{
  /*
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
  */
  int j;
  int fd;
  int vers;
  entete_bmp entete;
  unsigned char *pixels;

  if(argc < 3){
    printf("Wrong number of parameters\n");
    printf("Usage: %s <bmp file> <bmp file>\n", argv[0]);
    return -1;
  }

  fd = open(argv[argc-2], O_RDONLY);

  if (fd == -1){
    perror(argv[1]);
    return -1;
  }

  lire_entete(fd,&entete);
  if(verifier_entete(&entete) == 0 ){
    perror(argv[1]);
    return -1;
  }

  pixels = allouer_pixels(&entete);
  lire_pixels(fd, &entete, pixels);

  if ((vers = open(argv[argc-1], O_WRONLY | O_CREAT | O_RDONLY, 0666 )) == -1){
    perror(argv[1]);
    return -1;
  }

  
  
  

  if (fd == -1){
    perror(argv[2]);
    return -1;
  }
  
  for ( j = 1; j < argc-2; j++) {
    
    if (argv[j][0] == '-' && argv[j][1] == 'r'){
      rouge(&entete, pixels);
    } else if (argv[j][0] == '-' && argv[j][1] == 'n'){
      negatif(&entete, pixels);
    } else if (argv[j][0] == '-' && argv[j][1] == 'b'){
      noir_et_blanc(&entete, pixels);
    } else if (argv[j][0] == '-' && argv[j][1] == 's'){
      moitie(&entete, pixels, 1);
    } else if (argv[j][0] == '-' && argv[j][1] == 'i'){
      moitie(&entete, pixels, 8);
    }
  }

 

  //affichage(&entete);
  ecrire_entete(vers,&entete);
  ecrire_pixels(vers,&entete,pixels);

  free(pixels);

  return 0;
}