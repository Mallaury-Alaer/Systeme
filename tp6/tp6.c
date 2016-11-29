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
  long taille = entete->bitmap.taille_donnees_image;
  unsigned char* res = malloc(sizeof(char)*taille);
  return res;
}

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels)
{
  int res;
  lseek(de, entete->fichier.offset_donnees, SEEK_SET);
  res = read(de, pixels, entete->bitmap.taille_donnees_image);
  return res;
}

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels)
{
  int res;
  lseek(vers, entete->fichier.offset_donnees, SEEK_SET);
  res = write(vers, pixels, entete->bitmap.taille_donnees_image);
  return res; 
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
/*
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
*/

int taille_ligne(const entete_bmp *entete){
  int taille = (entete->bitmap.largeur) * 3;
  int bourrage = 0;
  if (taille % 4 != 0){
    bourrage = 4 - (taille % 4);
  }
  return taille + bourrage;
}

int taille_image(const entete_bmp *entete){
  return entete->bitmap.hauteur * taille_ligne(entete);
}

void rouge(entete_bmp *entete, unsigned char *pixels){
  
  int y;
  int x;
  int hauteur = entete->bitmap.hauteur;
  int largeur = entete->bitmap.largeur;
  int taille_ligne = largeur*3;
  while(taille_ligne%4 !=0) taille_ligne++; 

  for(y=0; y<hauteur;y++){
    for(x=0;x<largeur;x++){
      int ind = y*taille_ligne + x*3;
      pixels[ind]=0;
      pixels[ind+1]=0;
    }
  }
}

void negatif(entete_bmp *entete, unsigned char *pixels){
 unsigned int i = 0;

  for (i = 0; i < (entete->bitmap.taille_donnees_image) ;i++)
    pixels[i] = ~pixels[i];
}


void noir_et_blanc(entete_bmp *entete, unsigned char *pixels){
  unsigned int i=0;
  for (i = 0; i < (entete->bitmap.taille_donnees_image)-3 ;i+=3){
    int m = (pixels[i]+pixels[i+1]+pixels[i+2])/3;
    pixels[i] = m;
    pixels[i+1] = m;
    pixels[i+2] = m;
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