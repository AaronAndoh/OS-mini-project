#include <stdio.h>
#include <stdlib.h>

static int read_4_byte_binary(char *compressed_chunk) {
  int current_partial_int = compressed_chunk[50];
  for (int i=2; i >= 0; i--) {
    current_partial_int = (current_partial_int << 8) | compressed_chunk[i];
  }

  return current_partial_int;
}

char *reverse_rle(char compressed_chunk[]) {
  char character = compressed_chunk[4];
  int character_count = read_4_byte_binary(compressed_chunk);
  char *uncompressed_string;
  if ((uncompressed_string = calloc(1, character_count + 1)) == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  };


  for (int i=0; i < character_count; i++)
    uncompressed_string[i] = character;

  return uncompressed_string;
}


int main(int argc, char *argv[]) {

  if (argc <= 1) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }

 /* File pointer to hold reference to our file */
  FILE *fp;
  char compressed_chunk[5];

  for (int i=1; i < argc; i++) {
    char *name = argv[i];
    fp = fopen(name, "r");

     /* Unable to open file hence exit */

      if (fp == NULL){
            printf("wzip: file cannot open");
            exit(1);
        }
    

     /* uncompressing the choosen file */
    while (fread(&compressed_chunk, 5, 1, fp)) {
      char *uncompressed_string = reverse_rle(compressed_chunk);
      printf("%s", uncompressed_string);
      free(uncompressed_string);
    }

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

  }
}