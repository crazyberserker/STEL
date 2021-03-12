#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "func.h"

float uniform(){
    float u = (rand()%RAND_MAX +1 ) / (float)RAND_MAX;
    return u;
}


float exponencial(float lambda){
    float c = -(1/lambda)*log(uniform());
    return c;
}

int histogramCreation(char *filename, int* histogram, int his_size, int samples){

    FILE *F;


    fprintf(stderr, "Init the confi of file %s\n", filename);

    F = fopen(filename, "w+");
    if(F == NULL){
        perror("fopen");
        return -1;
   }

   fprintf(F, "Index, Interval times, Arrival Calls (of %d)\n", samples);
   for(int i=0; i<his_size; i++){
       fprintf(F, "%d, %lf, %d\n", i, (2*i+1)/(float)(his_size*2), histogram[i]);
   }
  
    fclose(F);
    return 0;
}




