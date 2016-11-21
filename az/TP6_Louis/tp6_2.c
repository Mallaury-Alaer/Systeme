#include <stdio.h>
#include "tp6.h"
#include <unistd.h>

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int ecrire_deux_octets(int fd, uint16 val)
{
  return write(fd,&val,2);
}

int ecrire_quatre_octets(int fd, uint32 val)
{
  return write(fd,&val,4);
}

int ecrire_entete_fichier(int vers, entete_bmp *entete)
{
  if(ecrire_deux_octets(vers,entete->fichier.signature)<0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->fichier.taille_fichier) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->fichier.reserve) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->fichier.offset_donnees) <0)
    return -1;
  return 0;
}

int ecrire_entete_bitmap(int vers, entete_bmp *entete)
{
  if(ecrire_quatre_octets(vers,entete->bitmap.taille_entete) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.largeur) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.hauteur) <0)
    return -1;
  else if(ecrire_deux_octets(vers,entete->bitmap.nombre_plans)<0)
    return -1;
  else if(ecrire_deux_octets(vers,entete->bitmap.profondeur)<0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.compression) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.taille_donnees_image) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.resolution_horizontale) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.resolution_verticale) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.taille_palette) <0)
    return -1;
  else if(ecrire_quatre_octets(vers,entete->bitmap.nombre_de_couleurs_importantes) <0)
    return -1;

  return 0;
}

int ecrire_entete(int vers, entete_bmp *entete)
{
  if( ecrire_entete_fichier(vers,entete) <0)
    return -1;
  else if(ecrire_entete_bitmap(vers, entete) <0)
    return -1;
  return 0;
}
