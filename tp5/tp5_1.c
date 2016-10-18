#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int traiter (int f, int *car, int *mot, int *lig)
{
  int n;
  char buffer[80];
  int i = 0;
  int mots=0;
  *car=0;
  *mot=0;
  *lig=0;

  while((n=read(f, buffer, 80*sizeof(char)))>0)
    {
      while(i<n)
	{
	  if(!mots && !isspace(buffer[i]))
	    {
	      (*mot)++;
	    }
	  if(isspace(buffer[i]))
	    {
	      mots = 0;
	    }
	  else
	    {
	      mots = 1;
	    }

	  if(buffer[i] == '\n')
	    {
	      (*lig)++;
	    }
	  
	  (*car)++;
	  i++;
	}
      i=0;
    }
  
  return 0;  
}
