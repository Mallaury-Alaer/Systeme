#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* On déclare des types dont on est sûr de la taille.
   Si on doit implémenter le TP sur une architecture différente, il
   suffit de changer ces déclarations
*/

typedef unsigned short uint16;
typedef unsigned int uint32;

typedef struct
{
  uint16 signature;
  uint32 taille_fichier;
  uint32 reserve;
  uint32 offset_donnees;
} entete_fichier;

typedef struct
{
  uint32 taille_entete;
  uint32 largeur;
  uint32 hauteur;
  uint16 nombre_plans;
  uint16 profondeur;
  uint32 compression;
  uint32 taille_donnees_image;
  uint32 resolution_horizontale;
  uint32 resolution_verticale;
  uint32 taille_palette; /* en nombre de couleurs */
  uint32 nombre_de_couleurs_importantes; /* 0 */
} entete_bitmap;

typedef struct
{
  entete_fichier fichier;
  entete_bitmap bitmap;
} entete_bmp;

int lire_deux_octets(int fd, uint16 *val){
  return (read(fd,val,2))==2;  
}

int lire_quatre_octets(int fd, uint32 *val){
  return (read(fd,val,4))==4;  
}

int lire_entete(int de, entete_bmp *entete){
  int ok=1;
  ok=ok&&lire_deux_octets(de,&((*entete).fichier.signature));
  ok=ok&&lire_quatre_octets(de,&((*entete).fichier.taille_fichier));
  ok=ok&&lire_quatre_octets(de,&((*entete).fichier.reserve));
  ok=ok&&lire_quatre_octets(de,&((*entete).fichier.offset_donnees));

  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.taille_entete));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.largeur));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.hauteur));
  printf("%d %d\n",entete->bitmap.largeur,entete->bitmap.hauteur);
  
  ok=ok&&lire_deux_octets(de,&((*entete).bitmap.nombre_plans));
  ok=ok&&lire_deux_octets(de,&((*entete).bitmap.profondeur));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.compression));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.taille_donnees_image));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.resolution_horizontale));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.resolution_verticale));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.taille_palette));
  ok=ok&&lire_quatre_octets(de,&((*entete).bitmap.nombre_de_couleurs_importantes));
  
  return ok;
}

int ecrire_deux_octets(int fd, uint16* val){
  return (write(fd,val,2)); 
}

int ecrire_quatre_octets(int fd, uint32* val){
  return (write(fd,val,4)); 
}

int ecrire_entete(int de, entete_bmp *entete) {
  int ok=1;
  ok=ok&&ecrire_deux_octets(de,&((*entete).fichier.signature));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).fichier.taille_fichier));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).fichier.reserve));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).fichier.offset_donnees));

  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.taille_entete));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.largeur));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.hauteur));
  ok=ok&&ecrire_deux_octets(de,&((*entete).bitmap.nombre_plans));
  ok=ok&&ecrire_deux_octets(de,&((*entete).bitmap.profondeur));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.compression));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.taille_donnees_image));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.resolution_horizontale));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.resolution_verticale));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.taille_palette));
  ok=ok&&ecrire_quatre_octets(de,&((*entete).bitmap.nombre_de_couleurs_importantes));
  return ok;
}

int verifier_entete(entete_bmp *entete){
  if (entete->bitmap.profondeur == 24)
    return 1;
  perror("ERROR: Profondeur fausse");
  return 0;
}

unsigned char* allouer_pixels(entete_bmp *entete) {
  return malloc((entete->bitmap.largeur * entete->bitmap.hauteur * 3));
}

int lire_pixels(int file, entete_bmp *entete, unsigned char *pixels) {
  return read(file, pixels, entete->bitmap.largeur * entete->bitmap.hauteur * 3);
}

int ecrire_pixels(int file, entete_bmp *entete, unsigned char *pixels) {
  return write(file, pixels, entete->bitmap.largeur * entete->bitmap.hauteur * 3);
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

void rouge(entete_bmp *entete, unsigned char *pixels) {
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

void negatif(entete_bmp *entete, unsigned char *pixels) {
  int largeur = entete->bitmap.largeur * 3;
  int hauteur = entete->bitmap.hauteur;
  int padding = 4 - largeur % 4;
  int y;
  int x;
  for (y = 0; y < hauteur; y++) {
    for (x = 0; x < largeur; x++) {
      pixels[y * (largeur + padding) + x] = 255 - pixels[y * (largeur + padding) + x];
    }
  }
}

void noir_blanc(entete_bmp *entete, unsigned char *pixels) {
  int largeur = entete->bitmap.largeur * 3;
  int hauteur = entete->bitmap.hauteur;
  int padding = 4 - largeur % 4;
  int y;
  int x;
  for (y = 0; y < hauteur; y++) {
    for (x = 0; x < largeur; x += 3) {
      int total = pixels[y * (largeur + padding) + x] + pixels[y * (largeur + padding) + x + 1] + pixels[y * (largeur + padding) + x + 2];
      pixels[y * (largeur + padding) + x] = total / 3;
      pixels[y * (largeur + padding) + x + 1] = total / 3;
      pixels[y * (largeur + padding) + x + 2] = total / 3;
    }
  }
}

/*void moitie(entete_bmp *entete, unsigned char *pixels, int top) {
  int largeur = entete->bitmap.largeur ;
  int hauteur = entete->bitmap.hauteur;
  int padding = 4 - largeur % 4;
  int y;
  int x;
  for (y = !top * (largeur * 3/ 2); y < hauteur - top * (hauteur / 2); y++) {
    for (x = 0; x < largeur * 3 ; x++) {
      pixels[y * (largeur * 3 + padding) + x] = 0;
    }
  }
  }*/

void moitie(entete_bmp *entete,unsigned char *pixels,int top){
  int hauteur = ( entete -> bitmap).hauteur ;
  int largeur = ( entete -> bitmap).largeur ;
  int demi = (hauteur*largeur*3)/2;
  int cpt = 1;

  for(; cpt <= hauteur*largeur*3 ; cpt=cpt+1){
    if( top == 1 && cpt < demi )
      *( pixels + cpt ) = 0 ;
     else if( top == 0 && cpt > demi )
      *( pixels + cpt ) = 0 ;
  }
}

int main(int argc,char *argv[])
{
 
  int input = open("image2.bmp", O_RDONLY);
  int output = open("retour.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (input != -1 && output != -1) {
    entete_bmp entete;
    unsigned char *pixels;

    lire_entete(input, &entete);
    pixels = allouer_pixels(&entete);

    lire_pixels(input, &entete, pixels);

    if (argc > 1) {

      int i;
      for (i = 1; i < argc; i++) { 

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
	      noir_blanc(&entete, pixels);
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
