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
 * gcc -Wall Poisson_a.c -o Poisson_a -lm
 * ./Poisson_a.c <lambda><n_samples><filename1>
*/

int main(int argc, char* argv[]){
    
    //time variables; 
    float current_time = 0;
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
    float c;
    int counter =0; 
    int bin=0;

    //File related variables
    char filename[24];
   
    if(!strcpy(filename, argv[3])){
        perror("strcpy");
        return -1;
    }
 
    printf("*** Simulation starting ***!\n");

    histogram = (int*)calloc(his_size, sizeof(int));
        
         for(int i=0; i<samples; i++){
            c = exponencial(lambda);

            //Histogram update
            bin = (int)(c/(1/(float)(his_size)));
            if(bin > his_size -1 ){
                histogram[his_size -1]++;
            }
            else
                histogram[bin]++;
            
            current_time= event_list->tempo + c;   
            remover(event_list);
            event_list = adicionar(event_list, ARRIVAL, current_time);
            counter++;
        }
    
    
    //Print Parameters
    printf("Simulation by %d samples!\n", samples);
    printf("Theoretical value of lambda: %lf\n", (float)lambda);
    printf("Estimator of lambda = %lf\n", (float)(samples/current_time));
    printf("Number of calls simulated: %d\n", counter);
    printf("Last Call received: %f\n", current_time);
    printf("Avarage interval between calls: %lf\n", (float) current_time / counter);
    
    
    if(histogramCreation(filename, histogram, his_size, samples)<0){
        perror("Problems on Histogram saving");
        return -1;
    }

    return 0;

}