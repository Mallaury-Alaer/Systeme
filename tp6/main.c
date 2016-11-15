#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "tp6.h"
#include <fcntl.h>

int main(void)
{
  entete_bmp entete;

  int fd = open("test.bmp", O_RDONLY);

  if(lire_entete(fd, &entete) == -1)
  {
    perror("Erreur lecture entete");
    return -1;
  }

  printf("Lecture entete : \n");
  // Lecture entete fichier
  printf("Signature : 0x%x \n", entete.fichier.signature);
  printf("Taille fichier : %d bytes \n", entete.fichier.taille_fichier);
  printf("Reserve : %d \n", entete.fichier.reserve);
  printf("DataOffset : %x \n", entete.fichier.offset_donnees);

  // Lecture entete bmp
  printf("Taille entete : %d \n", entete.bitmap.taille_entete);
  printf("Taille Image : %dx%d \n", entete.bitmap.largeur, entete.bitmap.hauteur);
  printf("Nombre plans : %d \n", entete.bitmap.nombre_plans);
  printf("Profondeur : %d \n", entete.bitmap.profondeur);
  printf("Compression : %d \n", entete.bitmap.compression);
  printf("Taille donnees image : %d bytes \n", entete.bitmap.taille_donnees_image);
  printf("Resolution : %dx%d ppm\n", entete.bitmap.resolution_horizontale, entete.bitmap.resolution_verticale);
  printf("Taille palette : %d \n", entete.bitmap.taille_palette);
  printf("Nombre de couleurs importantes : %d \n", entete.bitmap.nombre_de_couleurs_importantes);

 return 0; 
}