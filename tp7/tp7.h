void execute_ligne_commande();
void affiche_prompt();
int lance_commande(int in, int out, char * com, char ** argv);
void stoppe_commande(int * pid, int nb);
void shell();
void traitement(int sig);
void redirection();