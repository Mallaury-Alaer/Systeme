#include <stdio.h>
#include "tp6.h"
#include <unistd.h>

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int lire_deux_octets(int fd, uint16 *val)
{
  return read(fd,val,2);
}

int lire_quatre_octets(int fd, uint32 *val)
{
  return read(fd,val,4);
}

int lire_entete_fichier(int de, entete_bmp *entete)
{
  if(lire_deux_octets(de,&entete->fichier.signature)<0)
    return -1;
  else if(lire_quatre_octets(de,&entete->fichier.taille_fichier) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->fichier.reserve) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->fichier.offset_donnees) <0)
    return -1;
  return 0;
}

int lire_entete_bmp(int de, entete_bmp *entete)
{
  if(lire_quatre_octets(de,&entete->bitmap.taille_entete) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.largeur) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.hauteur) <0)
    return -1;
  if(lire_deux_octets(de,&entete->bitmap.nombre_plans)<0)
    return -1;
  if(lire_deux_octets(de,&entete->bitmap.profondeur)<0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.compression) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.taille_donnees_image) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.resolution_horizontale) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.resolution_verticale) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.taille_palette) <0)
    return -1;
  else if(lire_quatre_octets(de,&entete->bitmap.nombre_de_couleurs_importantes) <0)
    return -1;
  
  return 0;
}


int lire_entete(int de, entete_bmp *entete)
{
  if(lire_entete_fichier(de,entete)<0)
    return -1;
  else if(lire_entete_bmp(de,entete)<0)
    return -1;
  return 0;
}
