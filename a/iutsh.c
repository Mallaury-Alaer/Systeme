/* 
	IUTSH.C V3
	Par foinej & ramaharm
	Jan 2005
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ligne_commande.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

/*
int sigaction (int signum, const struct sigaction * act, struct sigaction *oldact);
int strcmp (const char *s1, const char *s2);
size_t strlen (const char *s);
char * strdup (const char *s);
char * get_current_dir_name (void);
int gethostname(char *nom, size_t lg);
extern char **environ;
*/

int stop, nbpile;
int ** pile;
int * pids;
int nbpids;

void affiche_prompt(){
	char * user;
	char machine[255];

	char * cwd;
	int taille_cwd;

	user = getenv("USER");
	gethostname (machine, 255);

	taille_cwd = 256;
	cwd = malloc(taille_cwd);
	while ( getcwd(cwd, taille_cwd) == NULL){
		taille_cwd += 256;
		cwd = realloc(&cwd, taille_cwd);
	}

	printf("[%s@%s %s] # ", user, machine, cwd);
	fflush(NULL);

	free(cwd);
}

void stoppe_commande(int * pid, int nb){
	int i;
	printf("fonction stop commande!\n");
	for (i=0; i<nb; i+=1) {
		kill(pid[i], SIGSTOP);
	}
}

int lance_commande(int in, int out, char * com, char ** argv){
	/*!*/
	int pid, res;

	pid = fork();

	if (pid==-1) return -1;

	if (pid==0){
		if (in!=0){
			close(0);
			dup(in);
		}
		if (out!=1){
			close(1);
			dup(out);
		}
		res = execvp(com, argv);
		printf("ligne de commande incorrecte.\n");
		exit(1);
	}

	return pid;		
}

void execute_ligne_commande(){
	char *** ligne;
	int flag, nb;
	int pid;
	int ind, outd;
	int t[2];
	int i;

	ligne = ligne_commande(&flag, &nb);

	if (ligne == NULL){
		printf("ligne de commande incorrecte (2).\n");
		return;
	}
	if (!strcmp(ligne[0][0], "exit")){
		libere(ligne);
		free(pile);
		exit(0);
	}

	if (!strcmp(ligne[0][0], "cd")){
		if (ligne[0][2]!=NULL){
			printf("cd ne prend qu'un parametre.\n");
		}else{
			if (chdir(ligne[0][1])==-1) perror("Impossible de changer de repertoire!");
		}
		libere(ligne);
		return;
	}

	ind = 0;

	pids = (int *) malloc(sizeof(int)*nb);	
	for (i=0; i<nb; i+=1){

		if (i==nb-1){
			outd = 1;
		}else{
			pipe(t);
			outd = t[1];
		}

		pid = lance_commande(ind, outd, ligne[i][0], ligne[i]);

		if (pid==-1){
				printf("Erreur de lancement.\n");
		}

		pids[i] = pid;
		nbpids = i+1;

		if (!flag){
			waitpid(pid, NULL, 0);
		}
		
		if (i!=nb-1){
			close(outd);
			if (i!=0) {
				close(ind);
			}
		}else{
			if ( (nb>1) && (i==nb-1) ){
				close(ind);
			}
		}	
		if (nb!=1) ind = t[0];
	}
	free(pids);
	nbpids = 0;
	libere(ligne);
}

void shell(){
	printf("shell!\n");
	while (1){
		affiche_prompt();
		execute_ligne_commande();
	}
}

void traitement(int sig){
	if (sig == SIGCHLD){
		printf("One of my sons is dead !\n");
		waitpid(0, NULL, WNOHANG);
	}
	if (sig == SIGTSTP){
		stoppe_commande(pids, nbpids);
		waitpid(0, NULL, WNOHANG);
		printf("signal stop!\n");
		shell();
	}
}

void redirection(){
	struct sigaction action;
	action.sa_handler = traitement;
	action.sa_flags = SA_RESTART;
	if (sigfillset(&action.sa_mask) == -1) return;
	sigaction(SIGCHLD, &action, NULL);
	sigaction(SIGTSTP, &action, NULL);
}

int main(){
	/* initialisation */
	stop = 0;
	nbpile = 0;
	nbpids = 0;

	redirection();
	shell();

	return 0;
}


