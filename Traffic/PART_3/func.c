#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "func.h"
#include "Lista_ligada.h"

//Simulation Constants
#define LAMBDA 0.022 //Calls per second
#define SPECIFIC 0
#define GENERAL 1
#define ARRIVAL 0
#define DEPARTURE 1 
#define HISSIZE 50


//General Constants in seconds
#define MIN_DURATION 60
#define EXPONENTIAL_AVERAGE 120
#define MAX_DURATION 300


//Specific Constants in seconds
#define GUASSIAN_AVERAGE 60
#define STANDARD_DEVIATION 20
#define MIN_DURATION_SPECIFIC 30
#define MAX_DURATION_SPECIFIC 120
#define TRANSFERED_STANDARD_DEVINATION 150



double uniform(){
    double u = (double)(rand()%RAND_MAX +1 ) / (double)RAND_MAX;
    return u;
}


double exponencial(){
    double c = -(1/LAMBDA)*log(uniform());
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


double running_average(int n, double current_time, double previous_average){
    double res;

        res = (double)(previous_average*(n-1) + current_time)/n;

    return res;
}



double general_call(int area){

    double res; 
    double u = uniform();
    double u2 = uniform();

    if(area == GENERAL){
    
        res = (double) MIN_DURATION - EXPONENTIAL_AVERAGE*log(u);
        if(res > MAX_DURATION)
            res = (double) MAX_DURATION;
    }
    else{

        double teta = 2*M_PI*u;
        res = (sqrt(-2*log(u2))*cos(teta));

        res = ((res*STANDARD_DEVIATION) + GUASSIAN_AVERAGE);

        if(res > MAX_DURATION_SPECIFIC)
            res = MAX_DURATION_SPECIFIC;
    }


    return res;
}



double specific_call(){
    double u = uniform();


    double res = (double) GUASSIAN_AVERAGE - TRANSFERED_STANDARD_DEVINATION*log(u);


    return res;

}


