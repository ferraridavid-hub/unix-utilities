#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { BUFFER_SZ = 256 };

int main(int argc, char **argv) {
  char buffer[BUFFER_SZ];

  if (argc == 1) {
    while ((fgets(buffer, BUFFER_SZ, stdin)) != NULL) {
      fputs(buffer, stdout);
    }
  }

  while (--argc) {
    char *filename = *(++argv);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }
    while ((fgets(buffer, BUFFER_SZ, fp)) != NULL) {
      printf("%s", buffer);
    }
  }

  return 0;
}
