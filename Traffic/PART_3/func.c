#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "func.h"
#include "Lista_ligada.h"


#define SPECIFIC 0
#define GENERAL 1
#define ARRIVAL 0
#define DEPARTURE 1 
#define HISSIZE 50


double uniform(){
    double u = (double)(rand()%RAND_MAX +1 ) / (double)RAND_MAX;
    return u;
}


double exponencial(double lambda){
    double c = -(1/lambda)*log(uniform());
    return c;
}

int histogramCreation(char *filename, int* histogram, int his_size){

    FILE *F;


    fprintf(stderr, "Init the confi of file %s\n", filename);

    F = fopen(filename, "w+");
    if(F == NULL){
        perror("fopen");
        return -1;
   }

   
   for(int i=0; i<his_size; i++){
       fprintf(F, "%d, %lf, %d\n", i, (2*i+1)/(float)(his_size*2), histogram[i]);
   }
  
    fclose(F);
    return 0;
}

double dm_calc(double s){
    double dm;
    double u = uniform();

    dm = ((double)-s) * log(u);

    return dm;
}


int determine_call_type(){
    if((rand() % 100) <70)
        return SPECIFIC;
    else 
        return GENERAL;
}