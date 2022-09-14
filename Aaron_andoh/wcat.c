#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   /* File pointer to hold reference to our file */
    FILE *fp;

    char Filename[300];
    for (int t = 1; argv[t]; t++)
    {
        fp = fopen(argv[t],"r");
         /* Unable to open file hence exit */
        if (fp == NULL){
            printf("wcat: cannot open file\n");
            exit(1);
        }

    /* Repeat this until read line is not NULL */
        while (fgets(Filename, sizeof Filename, fp)!= NULL)
        printf("%s", Filename);
   
     /* file error on given stream hence exit */
   if(ferror(fp)) {
      printf("wcat: cannot read content of file");
      fclose(fp);
      exit(1);
    }

     /* Unable to close file hence exit */
    if (fclose(fp)!=0){
        printf("wcat: cannot close file");
        exit(1);
    };
    }
    
    exit(EXIT_SUCCESS);


}
