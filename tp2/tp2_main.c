#include <stdio.h>
#include "tp2_1.h"
#include "tp2_2.h"

int main(void)
{
  printf("Premiere partie \n");
  int tab[5]={1,2,3,4,5};
  afficher(tab, 5);
  int s = somme(tab, 5);
  printf("Somme= %d \n", s);
  int tab2[5];
  copie_dans(tab2, tab, 5);
  afficher(tab2, 5);
  int dest[3] = {6,7,8};
  ajoute_apres(dest, 3, tab, 5);
  afficher(dest, 8);

  printf("Deuxieme partie \n");
  struct rat n1;
  n1.den=2;
  n1.num=3;

  struct rat n2;
  n2.den=5;
  n2.num=6;

  struct rat liste[10];
  int i=0;
  while(i<9)
    {
      liste[i].den=i+5;
      liste[i].num=i+6;
      i++;
    }
  liste[9].den=0;
  liste[9].num=0;

  struct rat res1 = rat_produit(n1, n2);
  printf("Produit = %d / %d \n", res1.den, res1.num);
  struct rat res2 = rat_somme(n1, n2);
  printf("Somme = %d / %d \n", res2.den, res2.num);
  struct rat res3 = rat_plus_petit(liste);
  printf("Plus petit = %d / %d \n", res3.den, res3.num);

  return 0;
}
