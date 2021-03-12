#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "Lista_ligada.h"
#include "func.h"


#define RAND_MAX 2147483647
#define ARRIVAL 1
#define DEPARTURE 0 
#define JUMP 5



/*compile: 
 *
 * gcc -Wall  func.c LIsta_ligada.c Poisson_b.c -o Poisson_b -lm
 * ./Poisson_b <lambda><n_samples><filename1>
*/

int main(int argc, char* argv[]){
    
    //time variables; 
    float current_time=0, before_time = 0;
    //seed initialization 
    srand((unsigned)time(0));
    
    //Getting the inputs
    float lambda = atof(argv[1]);
    int samples = atoi(argv[2]);
    
    //Histogram parameters
    int *histogram;
    int his_size = JUMP*lambda;

    //List of events initialization 
    lista *event_list = NULL; 
    event_list = adicionar(event_list,ARRIVAL,0);
    float u=1;
    int counter =0; 
    int bin=0;


    //Probabilities
    float delta = 1.0 / (1000*lambda);
    float p = lambda*delta;


    //File related variables
    char filename[24];
   
    if(!strcpy(filename, argv[3])){
        perror("strcpy");
        return -1;
    }
 
    printf("*** Simulation starting ***!\n");

    histogram = (int*)calloc(his_size, sizeof(int));


        for(int i=0; i<samples; i++){
            u = uniform();
            if(u<p){
                
                current_time = i*delta;
                remover(event_list);
                event_list = adicionar(event_list, ARRIVAL, current_time);
                counter++;
                
                 //Histogram update
                bin = (int)((current_time - before_time)/(1/(float)(his_size)));
                if(bin > his_size -1 ){
                histogram[his_size -1]++;
                }
                else
                histogram[bin]++;
                before_time = current_time;
            }
            
        }

    
   
    
    //Print Parameters
    printf("Simulation by %d samples!\n", samples);
    printf("Theoretical value of lambda: %lf\n", (float)lambda);
    printf("Estimator of lambda = %lf\n", (float) (counter)/ (float)(current_time));
    printf("Number of calls simulated: %d\n", counter);
    printf("Last Call received: %f\n", current_time);
    printf("Avarage interval between calls: %lf\n", (float) current_time / counter);
  
  
    if(histogramCreation(filename, histogram, his_size, samples)<0){
        perror("Problems on Histogram saving");
        return -1;
    }

    return 0;

}