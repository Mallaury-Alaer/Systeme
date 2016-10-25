#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "tp6.h"
#include <fcntl.h>

//Reading of Bytes

int lire_deux_octets(int fd, uint16 *val){
  if(fd==-1) return -1;
  return read(fd,val,2);
}

int lire_quatre_octets(int fd, uint32 *val){
  if(fd==-1) return -1;
  return read(fd,val,4);
}

int lire_entete(int de, entete_bmp *entete){
  // entete fichier
  if(lire_deux_octets(de,&(entete->fichier.signature)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->fichier.taille_fichier)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->fichier.reserve)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->fichier.offset_donnees)) ==-1) return -1;
  // entete bitmap
  if(lire_quatre_octets(de,&(entete->bitmap.taille_entete)) ==-1) return -1;	
  if(lire_quatre_octets(de,&(entete->bitmap.largeur)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.hauteur)) ==-1) return -1;
  if(lire_deux_octets(de,&(entete->bitmap.nombre_plans)) ==-1) return -1;
  if(lire_deux_octets(de,&(entete->bitmap.profondeur)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.compression)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.taille_donnees_image)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.resolution_horizontale)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.resolution_verticale)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.taille_palette)) ==-1) return -1;
  if(lire_quatre_octets(de,&(entete->bitmap.nombre_de_couleurs_importantes)) ==-1) return -1;
  return 0;
}

//Writing of Bytes
int ecrire_deux_octets(int vers, uint16 *val){
  if(vers==-1) return -1;
  return write(vers,val,2);
}

int ecrire_quatre_octets(int vers, uint32 *val){
  if(vers==-1) return -1;
  return write(vers,val,4);
}

int ecrire_entete(int vers, entete_bmp *entete){
  // entete fichier
  if(ecrire_deux_octets(vers,&(entete->fichier.signature)) ==-1) 			return -1;
  if(ecrire_quatre_octets(vers,&(entete->fichier.taille_fichier)) ==-1) 	return -1;
  if(ecrire_quatre_octets(vers,&(entete->fichier.reserve)) ==-1) 			return -1;
  if(ecrire_quatre_octets(vers,&(entete->fichier.offset_donnees)) ==-1) 	return -1;
  // entete bitmap
  if(ecrire_quatre_octets(vers,&(entete->bitmap.taille_entete)) ==-1) 		return -1;	
  if(ecrire_quatre_octets(vers,&(entete->bitmap.largeur)) ==-1) 				return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.hauteur)) ==-1) 				return -1;
  if(ecrire_deux_octets(vers,&(entete->bitmap.nombre_plans)) ==-1) 			return -1;
  if(ecrire_deux_octets(vers,&(entete->bitmap.profondeur)) ==-1) 				return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.compression)) ==-1) 			return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.taille_donnees_image)) ==-1) 	return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.resolution_horizontale)) ==-1)return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.resolution_verticale)) ==-1)	return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.taille_palette)) ==-1) 		return -1;
  if(ecrire_quatre_octets(vers,&(entete->bitmap.nombre_de_couleurs_importantes)) ==-1) return -1;
  return 0;
}

//Exercice3

int verifier_entete(entete_bmp *entete){
  if(entete->bitmap.profondeur != 24) return 0;
  return 1;
}

unsigned char* allouer_pixels(entete_bmp *entete){
  int taille = entete->bitmap.taille_donnees_image;			
  unsigned char * c = malloc(taille);
  return c;
}

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels){
  if(de==-1 || entete->bitmap.profondeur != 24) return -1;	
  int taille = entete->bitmap.taille_donnees_image;				
  lseek(de,entete->fichier.offset_donnees,SEEK_SET);	
  *pixels = read(de,pixels,taille);	
  return 0;	

}
int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels){
  if(vers==-1) return -1;
  int taille = entete->bitmap.taille_donnees_image;		
  lseek(vers,entete->fichier.offset_donnees,SEEK_SET);		
  write(vers,pixels,taille);
  return 0;
}

//Exercice 8
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

void moitie(entete_bmp *entete, unsigned char *pixels, int sup){
   
  int dataSize = (entete->bitmap.taille_donnees_image);
  //diviser hauteur

  int i = 0;
  int j = 0;
  int newSize = 0;
  if (dataSize % 2 == 0)
    newSize = (dataSize / 2);
  else{
    newSize = (dataSize / 2);
    newSize = (dataSize - newSize);
  }
  for(i = ((sup == 0) ? (0) : (newSize)); i < ((sup == 0) ? (newSize) : (dataSize)); i++)
    {
      pixels[j] = pixels[i];
      j++;
    }
  entete->bitmap.taille_donnees_image = newSize;
  int hauteur =  entete->bitmap.hauteur;
  hauteur = (hauteur / 2);
  if (hauteur % 2 != 0)

    hauteur = (entete->bitmap.hauteur - hauteur);
  entete->bitmap.hauteur = hauteur;
  entete->fichier.taille_fichier = newSize + entete->bitmap.taille_entete +  (entete->fichier.offset_donnees -  entete->bitmap.taille_entete);

}
  

/*	
	int taille_ligne = (entete->bitmap.largeur)*3;
	while(taille_ligne%4 !=0) taille_ligne++;	
  
	if(sup==1) {
	int i;
	int j;
	int h = (entete->bitmap.hauteur/2);
	int l = (entete->bitmap.largeur);
	for (i = 0; i < h  ;i++){
	for(j=0;j< l;j++){
	int ind = i*taille_ligne + j;
	pixels[ind] = pixels[h*l*3 +ind];
	}
	}
	}
	entete->bitmap.hauteur = entete->bitmap.hauteur/2;
	entete->bitmap.taille_donnees_image = entete->bitmap.hauteur*(entete->bitmap.largeur*3+3);
	entete->fichier.taille_fichier = entete->bitmap.taille_donnees_image + entete->fichier.offset_donnees;

	}
*/




//Exercice 7
int copier_bmp(int de, int vers){
  entete_bmp entete;
  unsigned char *pixels;
  /* lecture du fichier source */
  lire_entete(de, &entete);
  pixels = allouer_pixels(&entete);
  lire_pixels(de, &entete, pixels);
  /* écriture du fichier destination */
  // rouge(&entete, pixels);
  // negatif(&entete,pixels);
  // noir_et_blanc(&entete,pixels);
  moitie(&entete, pixels,0);

  ecrire_entete(vers, &entete);
  lseek(vers, entete.fichier.offset_donnees, SEEK_SET);  
  ecrire_pixels(vers, &entete, pixels);
  /* on libère les pixels */
  free(pixels);
  return 1; /* on a réussi */
}

int ocompare_strings(char * s1, char * s2)
{
  int i = 0;
  int s1_len = strlen(s1);
  int s2_len = strlen(s2);
  int min = ((s1_len < s2_len) ? s1_len : s2_len);
  //Check de egalité des Strings
  while ((s1[i] == s2[i]) && (i <= min)) {
    //Si egal a fin
    if ((s1[i] == '\0') || (s2[i] == '\0'))
      return 1;
    i++;
  }
  //Si string diff
  return 0;
}

int main(int argc, char *argv[]){
  int t;
  t=open(argv[argc-2],O_RDONLY,0666);
  entete_bmp eb;
  if(lire_entete(t,&eb) ==-1){
    return -1;
  }
  unsigned char *pixels = allouer_pixels(&eb);
  if(lire_pixels(t,&eb,pixels) == -1){
    return -1;
  }

  if(argc==3){
    int t2=open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT,0666);
    ecrire_entete(t2,&eb);
    ecrire_pixels(t2,&eb,pixels);
    close(t2);
    return 0;	
  }

  int i;
  for(i=1;i<argc-2;i++){
    if(argv[i][0] != '-'){
      return -1;		
    }
    int j;
    int taille = strlen(argv[i]);
    for(j=1; j<taille;j++){
      if(argv[i][j] != 'r' && argv[i][j] != 'n'&& argv[i][j] != 'b'&& argv[i][j] != 's' && argv[i][j] != 'i' ){
	printf("mauvaise utilisation");
	return -1;	
      }
      if(argv[i][j] == 'r'){
	rouge(&eb,pixels);
	int t2=open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT,0666);
	ecrire_entete(t2,&eb);
	ecrire_pixels(t2,&eb,pixels);
	close(t2);
      }
      if(argv[i][j] == 'n'){
	negatif(&eb,pixels);
	int t2=open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT,0666);
	ecrire_entete(t2,&eb);
	ecrire_pixels(t2,&eb,pixels);
	close(t2);

      }
      if(argv[i][j] == 'b'){
	noir_et_blanc(&eb,pixels);
	int t2=open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT,0666);
	ecrire_entete(t2,&eb);
	ecrire_pixels(t2,&eb,pixels);
	close(t2);

      }
      if(argv[i][j] == 's'){
	moitie(&eb,pixels,1);
	int t2=open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT,0666);
	ecrire_entete(t2,&eb);
	ecrire_pixels(t2,&eb,pixels);
	close(t2);

      }
      if(argv[i][j] == 'i'){
	moitie(&eb,pixels,2);
	int t2=open(argv[argc-1],O_WRONLY | O_TRUNC | O_CREAT,0666);
	ecrire_entete(t2,&eb);
	ecrire_pixels(t2,&eb,pixels);
	close(t2);

      }
    }
  }
	
	
	
  close(t);
  free(pixels);



  return 0;

}
