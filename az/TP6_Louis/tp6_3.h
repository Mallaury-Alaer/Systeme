int verifier_entete(entete_bmp *entete);

unsigned char* allouer_pixels(entete_bmp *entete);

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels);

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels);

void print(entete_bmp *entete);

void rouge(entete_bmp *entete, unsigned char *pixels);

void noir_et_blanc(entete_bmp *entete, unsigned char *pixels);

void moitie(entete_bmp *entete, unsigned char *pixel, int sup);

void negatif(entete_bmp *entete, unsigned char *pixels);

int copier_bmp(int de, int vers);

