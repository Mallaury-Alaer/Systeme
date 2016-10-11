#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <ctype.h>
#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>


#define BUFFER_SIZE 80

int traiter (int f/*, int *car, int *mot, int *lig*/)
{
  char buffer [BUFFER_SIZE];
  int i=0;
  
  while(read(f, buffer, BUFFER_SIZE) != -1 && i<80)
    {
      printf("%c", buffer[i]);
      i++;
    }

  printf("\n");
  return 0;
  
}
