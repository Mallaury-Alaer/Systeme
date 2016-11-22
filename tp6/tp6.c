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
  if(entete->bitmap.profondeur == 24) 
    return 1;
  perror("Erreur : profondeur != 24");
  return 0;
}

unsigned char* allouer_pixels(entete_bmp *entete)
{
  return malloc((entete->bitmap.largeur * entete->bitmap.hauteur * 3));
}

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels)
{
  return read(de, pixels, entete->bitmap.largeur * entete->bitmap.hauteur * 3);
}

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels)
{
  return write(vers, pixels, entete->bitmap.largeur * entete->bitmap.hauteur * 3);
}


int copier_bmp(int de, int vers)
{
  entete_bmp entete;
  unsigned char *pixels;
  /* lecture du fichier source */
  lire_entete(de, &entete);
  pixels = allouer_pixels(&entete);
  lire_pixels(de, &entete, pixels);
  /* écriture du fichier destination */
  ecrire_entete(vers, &entete);
  ecrire_pixels(vers, &entete, pixels);
  /* on libère les pixels */
  free(pixels);
  return 1; /* on a réussi */
}

void rouge(entete_bmp *entete, unsigned char *pixels)
{
  int largeur = entete->bitmap.largeur * 3;
  int hauteur = entete->bitmap.hauteur;
  int padding = 4 - largeur % 4;
  int y;
  int x;
  for (y = 0; y < hauteur; y++) {
    for (x = 0; x < largeur; x += 3) {
      pixels[y * (largeur + padding) + x] = 0;
      pixels[y * (largeur + padding) + x + 1] = 0;
    }
  }
}

void negatif(entete_bmp *entete, unsigned char *pixels)
{
    int largeur = entete->bitmap.largeur * 3;
  int hauteur = entete->bitmap.hauteur;
  int padding = 4 - largeur % 4;
  int y;
  int x;
  for (y = 0; y < hauteur; y++) 
  {
    for (x = 0; x < largeur; x++) 
    {
      pixels[y * (largeur + padding) + x] = 255 - pixels[y * (largeur + padding) + x];
    }
  }
}

void noir_et_blanc(entete_bmp *entete,unsigned char *pixels)
{
    int largeur = entete->bitmap.largeur * 3;
  int hauteur = entete->bitmap.hauteur;
  int padding = 4 - largeur % 4;
  int y;
  int x;
  for (y = 0; y < hauteur; y++) 
  {
    for (x = 0; x < largeur; x += 3) 
    {
      int total = pixels[y * (largeur + padding) + x] + pixels[y * (largeur + padding) + x + 1] + pixels[y * (largeur + padding) + x + 2];
      pixels[y * (largeur + padding) + x] = total / 3;
      pixels[y * (largeur + padding) + x + 1] = total / 3;
      pixels[y * (largeur + padding) + x + 2] = total / 3;
    }
  }
}

void moitie(entete_bmp *entete, unsigned char *pixels, int sup)
{
   int hauteur = ( entete -> bitmap).hauteur ;
  int largeur = ( entete -> bitmap).largeur ;
  int demi = (hauteur*largeur*3)/2;
  int cpt = 1;

  for(; cpt <= hauteur*largeur*3 ; cpt=cpt+1)
  {
    if( sup == 1 && cpt < demi )
      *( pixels + cpt ) = 0 ;
     else if( sup == 0 && cpt > demi )
      *( pixels + cpt ) = 0 ;
  }
}