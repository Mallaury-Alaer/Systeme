int lire_deux_octets(int fd, uint16 *val);

int lire_quatre_octets(int fd, uint32 *val);

int lire_entete_fichier(int de, entete_bmp *entete);

int lire_entete_bmp(int de, entete_bmp *entete);

int lire_entete(int de, entete_bmp *entete);
