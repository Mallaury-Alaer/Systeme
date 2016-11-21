#include <stdio.h>
#include "tp6.h"
#include "tp6_1.h"
#include "tp6_2.h"
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int verifier_entete(entete_bmp *entete)
{
  if(entete->bitmap.profondeur==24)
    return 1;
  else
    return 0; 
}

unsigned char* allouer_pixels(entete_bmp *entete)
{
  unsigned char *res= malloc(entete->bitmap.taille_donnees_image);
  return res;
}

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels)
{
  return read(de, pixels,entete->bitmap.taille_donnees_image);
}

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels)
{
  return write(vers,pixels,entete->bitmap.taille_donnees_image);
}

void print(entete_bmp *entete)
{
  printf("Signature %d\n",entete->fichier.signature);
  printf("Taille fichier %d\n",entete->fichier.taille_fichier);
  printf("Reserve %d\n",entete->fichier.reserve);
  printf("Offset donnees %d\n",entete->fichier.offset_donnees);

  printf("taille_entete %d\n",entete->bitmap.taille_entete);
  printf("largeur %d\n",entete->bitmap.largeur);
  printf("hauteur %d\n",entete->bitmap.hauteur);
  printf("nombre_plans %d\n",entete->bitmap.nombre_plans);
  printf("profondeur %d\n",entete->bitmap.profondeur);
  printf("compression %d\n",entete->bitmap.compression);
  printf("taille_donnees_image %d\n",entete->bitmap.taille_donnees_image);
  printf("resolution_horizontale %d\n",entete->bitmap.resolution_horizontale);
  printf("resolution_verticale %d\n",entete->bitmap.resolution_verticale);
  printf("taille_palette %d\n",entete->bitmap.taille_palette);
  printf("nombre_de_couleurs_importantes %d\n\n",entete->bitmap.nombre_de_couleurs_importantes);
    
}

void rouge(entete_bmp *entete, unsigned char *pixels)
{
  int i;
  int largeur = (entete->bitmap.largeur)*3;
  int decalage=largeur;
  
  for(i=2; i<(int)entete->bitmap.taille_donnees_image;i+=3)
    {
      if(i==(decalage+2))
	{
	  i+=2;
	  decalage+= largeur+2;
	}
      pixels[i-1]=0;
      pixels[i-2]=0;
    }
}
void noir_et_blanc(entete_bmp *entete, unsigned char *pixels)
{
  int i;
  
  for(i=2; i<(int)entete->bitmap.taille_donnees_image;i+=3)
    {
      pixels[i]=(pixels[i]+pixels[i-1]+pixels[i-2])/3;
      pixels[i-1]=pixels[i];
      pixels[i-2]=pixels[i];
    }
}
    
      
void moitie(entete_bmp *entete, unsigned char *pixels, int sup)
{
unsigned  int i;
  entete->bitmap.hauteur=entete->bitmap.hauteur/2;
  entete->bitmap.taille_donnees_image=entete->bitmap.taille_donnees_image/2;
  entete->fichier.taille_fichier=entete->fichier.taille_fichier-entete->bitmap.taille_donnees_image;
  if(sup==1)
    {
      for( i=0;i<(entete->bitmap.taille_donnees_image);i++)  
	{
	  pixels[i]=pixels[i+entete->bitmap.taille_donnees_image];
	}
	    }
    }
      
  void negatif(entete_bmp *entete, unsigned char *pixels)
  {
    unsigned int i;
    for(i=0; i<entete->bitmap.taille_donnees_image;i++)
      pixels[i]=~pixels[i];
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
    moitie(&entete, pixels, 0);
    ecrire_entete(vers, &entete);
    ecrire_pixels(vers, &entete, pixels);
    /* on libère les pixels */
    free(pixels);
    return 1; /* on a réussi */
  }

