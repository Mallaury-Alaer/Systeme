#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "tp6.h"
#include <fcntl.h>


int lire_deux_octets(int fd, uint16 *val)
{
  if(fd == -1)
  {
    return -1;
  }
  return(read(fd, val, 2));
}

int lire_quatre_octets(int fd, uint32 *val)
{
  if(fd == -1)
  {
    return -1;
  }
  return(read(fd, val, 4));
}

int lire_entete(int de, entete_bmp *entete)
{
  // Lecture entete fichier
  if(lire_deux_octets(de, &(entete->fichier.signature)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->fichier.taille_fichier))==-1) return -1;
  if(lire_quatre_octets(de, &(entete->fichier.reserve)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->fichier.offset_donnees)) == -1) return -1; 

  //Lecture entete bitmap
  if(lire_quatre_octets(de, &(entete->bitmap.taille_entete)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.largeur)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.hauteur)) == -1)return -1;
  if(lire_deux_octets(de, &(entete->bitmap.nombre_plans)) == -1) return -1;  
  if(lire_deux_octets(de, &(entete->bitmap.profondeur)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.compression)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.taille_donnees_image)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.resolution_horizontale)) == -1)return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.resolution_verticale)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.taille_palette)) == -1) return -1;
  if(lire_quatre_octets(de, &(entete->bitmap.nombre_de_couleurs_importantes)) == -1) return -1;

  return 0;
}

int ecrire_deux_octets(int fd, uint16 *val)
{
 if(fd == -1) return -1;
 return(write(fd, val, 2));
}

int ecrire_quatre_octets(int fd, uint32 *val)
{
  if(fd == -1) return -1;
  return(write(fd, val, 4)); 
}

int ecrire_entete(int vers, entete_bmp *entete)
{
      // entete fichier
  if(ecrire_deux_octets(vers,&(entete->fichier.signature)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->fichier.taille_fichier)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->fichier.reserve)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->fichier.offset_donnees)) ==-1) return -1;
  // entete bitmap
  if(ecrire_quatre_octets(vers,&(entete->bitmap.taille_entete)) ==-1) return -1;  
  if(ecrire_quatre_octets(vers,&(entete->bitmap.largeur)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.hauteur)) ==-1) return -1;
  if(ecrire_deux_octets(vers,&(entete->bitmap.nombre_plans)) ==-1) return -1;
  if(ecrire_deux_octets(vers,&(entete->bitmap.profondeur)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.compression)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.taille_donnees_image)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.resolution_horizontale)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.resolution_verticale)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.taille_palette)) ==-1) return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.nombre_de_couleurs_importantes)) ==-1) return -1;
  return 0;
}


int verifier_entete(entete_bmp *entete)
{
  if(entete->bitmap.profondeur == 24) return 1;
  perror("Erreur : profondeur != 24");
  return 0;
}
/*
unsigned char* allouer_pixels(entete_bmp *entete)
{

}
*/


