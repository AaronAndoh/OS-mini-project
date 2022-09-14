#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char *argv[]) {
  FILE *fp;
  char *buffer = NULL;
  size_t buffer_size = 300;

  if (argc <= 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(EXIT_FAILURE);
  }

  char *term = argv[1];
  char *file = argv[2];

  if (file)
    fp = fopen(file, "r");
  else
    fp = stdin;
  

  if (fp == NULL) {
    printf("wgrep: cannot open file\n");
    exit(1);
  }

  while (getline(&buffer, &buffer_size, fp) != -1)
    if (strstr(buffer, term) )
      printf("%s", buffer);


     /* file error on given stream hence exit */
   if(ferror(fp)) {
      printf("wzip: cannot read content of file");
      fclose(fp);
      
      exit(1);
    }

     /* Unable to close file hence exit */
    if (fclose(fp)!=0){
        printf("wzip: cannot close file");
        exit(1);
    };
  free(buffer);
  exit(EXIT_SUCCESS);
}