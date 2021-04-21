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

/*compile: 
 *
 * gcc -Wall func.c LIsta_ligada.c ErlangB-a.c -o ErlangB-a -lm
 * ./ErlangB-a.c <lambda><dm><N><sim_time>
 * ex. ./ErlangB-a 200 0.008 1 2000
 * 
*/

int main(int argc, char* argv[]){
    
    
    //seed initialization 
    srand((unsigned)time(0));
    
    //Getting the inputs
    double lambda = atof(argv[1]);
    double dm = atof(argv[2]);
    int N = atoi(argv[3]);
    double sim_time = atof(argv[4]);


    //Histogram parameters
    // int *histogram;
    // int his_size = JUMP*lambda;

    //List of events initialization 
    lista *event_list = NULL; 

   
   // int bin=0;


    //new control variables

    int blocked=0;
    int total_calls=0;
    double current_time = 0;
    int busy=0;
    int type=0;
    double c,s;

    //File related variables
    //char filename[24];
   
  //  if(!strcpy(filename, argv[3])){
  //      perror("strcpy");
  //      return -1;
  //  }
 
    printf("*** Simulation starting ***\n");

   // histogram = (int*)calloc(his_size, sizeof(int));
        
        c = exponencial(lambda);
        event_list = adicionar(event_list, ARRIVAL, c);

         
        while(current_time < sim_time){
            /* //Histogram update
            bin = (int)(c/(1/(float)(his_size)));
            if(bin > his_size -1 ){
                histogram[his_size -1]++;
            }
            else
                histogram[bin]++;
            */
           current_time = event_list->tempo;
           type = event_list->tipo;
           
           event_list = remover(event_list);

            if(type == ARRIVAL){
                c = exponencial(lambda);
                event_list = adicionar(event_list, ARRIVAL,current_time+c);
                if(busy<N){
                    total_calls++;
                    busy++;
                    s = dm_calc(dm);
                    event_list = adicionar(event_list, DEPARTURE, current_time + s);
                    type = event_list->tipo;                
                }else if (busy >= N){
                    total_calls++;
                    blocked++;
                }
            }else if(type == DEPARTURE){
                   busy--;
               }

        }
    
    
    //Print Parameters
    printf("*** Simulation ending ***\n");
    printf("Lambda: %lf\n", lambda);
    printf("Number of channels: %d\n", N);
    printf("Simulation time: %lf\n", sim_time);
    printf("Number of calls: %d \n", total_calls);
    printf("Number of blocked calls: %d\n", blocked);
    printf("Probability of a call to be blocked: %lf\n", ((double) blocked / (double) total_calls )*100);
   // printf("Simulation by %d samples!\n", samples);
   // printf("Theoretical value of lambda: %lf\n", (float)lambda);
   // printf("Estimator of lambda = %lf\n", (float)(samples/current_time));
   // printf("Number of calls simulated: %d\n", counter);
   // printf("Last Call received: %f\n", current_time);
   // printf("Avarage interval between calls: %lf\n", (float) current_time / counter);
    
    
   // if(histogramCreation(filename, histogram, his_size, samples)<0){
   //     perror("Problems on Histogram saving");
   //     return -1;
   // }

    return 0;

}