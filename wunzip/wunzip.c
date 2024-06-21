#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv) {
	if(argc < 2) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(EXIT_FAILURE);
	} 

	while(--argc) {
		char *filename = *++argv;
		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			perror("fopen");
			exit(EXIT_FAILURE);
		}

		int runlen;
		char c;
		while(fread(&runlen, 4, 1, fp)) {
			if ( ! fread(&c, 1, 1, fp)) {
				if ( ! feof(fp)) {
					perror("fread");
					exit(EXIT_FAILURE);
				}
			}
			while(runlen--) {
				putchar(c);
			}
		}

}
	return EXIT_SUCCESS;
}
