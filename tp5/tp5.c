#include <stdio.h>
#include "tp5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <ctype.h>
#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>

int main(void)
{
  int fd = open("tp5.c", O_RDONLY);
  traiter(fd);

  return 0;
}
