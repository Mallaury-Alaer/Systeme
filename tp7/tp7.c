#include "tp7.h"
#include "ligne_commande.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


int stop, nbpile;
int ** pile;
int * pids;
int nbpids;

void execute_ligne_commande()
{
	char *** ligne;
	int flag, nb = 0;
	int pid;
	int ind, outd;
	int t[2];
	int i;

	ligne = ligne_commande(&flag, &nb);

	if (ligne == NULL || nb==0){
		printf("Commande line not correct\n");
		return;
	}
	if (!strcmp(ligne[0][0], "exit")){
		libere(ligne);
		free(pile);
		exit(0);
	}

	if (!strcmp(ligne[0][0], "cd")){
		if (ligne[0][2]!=NULL){
			printf("cd : not enough arguments. \n");
		}else{
			if (chdir(ligne[0][1])==-1) perror("cd impossible");
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
				printf("Launch error.\n");
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

	printf("[%s@%s]-[%s]$ ", user, machine, cwd);
	fflush(NULL);

	free(cwd);
}


int lance_commande(int in, int out, char * com, char ** argv)
{
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
		printf("%d", res);
		printf(" **Command not found, try again bro**\n");
		exit(1);
	}

	return pid;		
}

void stoppe_commande(int * pid, int nb)
{
	int i;
	//<printf("fonction stop commande!\n");
	for (i=0; i<nb; i+=1) {
		kill(pid[i], SIGSTOP);
	}
}


void shell()
{
	printf("*** iutsh ***\n");
	while (1){
		affiche_prompt();
		execute_ligne_commande();
	}
}

void traitement(int sig)
{
	if (sig == SIGCHLD){
		waitpid(0, NULL, WNOHANG);
	}
	if (sig == SIGTSTP){
		stoppe_commande(pids, nbpids);
		waitpid(0, NULL, WNOHANG);
		printf("No signal\n");
		shell();
	}
}

void redirection()
{
	struct sigaction action;
	action.sa_handler = traitement;
	action.sa_flags = SA_RESTART;
	if (sigfillset(&action.sa_mask) == -1) return;
	sigaction(SIGCHLD, &action, NULL);
	sigaction(SIGTSTP, &action, NULL);
}

int main()
{
	/* initialisation */
	stop = 0;
	nbpile = 0;
	nbpids = 0;

	redirection();
	shell();

	return 0;
}
