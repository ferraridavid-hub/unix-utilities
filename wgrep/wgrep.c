#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool found_term(char *line, char *term) {
  size_t termlen = strlen(term);

  if (termlen == 0) {
    return true;
  }

  if (termlen > strlen(line)) {
    return false;
  }

  for (int i = 0; line[i] != '\0'; i++) {
    if (term[0] == line[i]) {
      if (strncmp(line + i, term, termlen) == 0) {
        return true;
      }
    }
  }
  return false;
}

void match_lines(char *term, FILE *stream) {
  char *line = NULL;
  size_t n = 0;
  while (getline(&line, &n, stream) != -1) {
    if (found_term(line, term)) {
      printf("%s", line);
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  } else if (argc == 2) {
    char *term = *++argv;
    match_lines(term, stdin);

  } else {
    char *term = *++argv;
    while (--argc > 1) {
      char *filename = *++argv;
      FILE *fp = fopen(filename, "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
      match_lines(term, fp);
    }
  }
  return EXIT_SUCCESS;
}
