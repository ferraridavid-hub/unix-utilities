#include<stdio.h>
#include<stdlib.h>


int main(int argc, char ** argv) { 
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");	
		exit(EXIT_FAILURE);
	}

	int runlen = 0;
	char last;

	while(--argc) {
		char *filename = *++argv;
		FILE *fp;
		if ((fp = fopen(filename, "r")) == NULL) {
			perror("fopen");
			exit(EXIT_FAILURE);
		}

		char c;

		while((c = fgetc(fp)) != EOF) {
			if (runlen == 0) {
				last = c;
				runlen++;
			} else if (c != last) {
				fwrite(&runlen, sizeof(int), 1, stdout);	
				fwrite(&last, sizeof(char), 1, stdout);	
				runlen = 1;
				last = c;
			} else {
				runlen++;
			}
		}

		fclose(fp);
	}

	fwrite(&runlen, sizeof(int), 1, stdout);
	fwrite(&last, sizeof(char), 1, stdout);

	return EXIT_SUCCESS;
}
