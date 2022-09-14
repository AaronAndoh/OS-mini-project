#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

 /* File pointer to hold reference to our file */ 
 if (argc <= 1) {
   printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }	

 /* File pointer to hold reference to our file */
  FILE *fp;
  char character[2] = "";
  char past_character[2] = "";
  int char_occurrences = 0;

   /* opening of the file */

  for (int i=1; i < argc; i++) {
    char *name = argv[i];
    fp = fopen(name, "r");

     /* Unable to open file hence exit */

      if (fp == NULL){
            printf("wzip: file cannot open");
            exit(1);
        }

    /* Reads character */

    while (fread(&character, 1, 1, fp)) {
      if (strcmp(character, past_character) == 0) {
        char_occurrences++;
      } else {
        if (past_character[0] != '\0') {
          fwrite(&char_occurrences, 4, 1, stdout);
          fwrite(past_character, 1, 1, stdout);
        }
        char_occurrences = 1;
        strcpy(past_character, character);
      }
    }
    fclose(fp);
  }

  fwrite(&char_occurrences, 4, 1, stdout);
  fwrite(past_character, 1, 1, stdout);
}

