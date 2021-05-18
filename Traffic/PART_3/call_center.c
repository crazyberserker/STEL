#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "Lista_ligada.h"
#include "func.h"

/*compile: 
 *
 * gcc -Wall func.c LIsta_ligada.c call_center.c -o call_center -lm
  * ./call_center <N_samples><N_General_Operators><N_Specific_operators><L_queue_length>
 * ex. ./call_center 200 0.008 1 2000 0.01 1
 * 
*/

//Simulation Constants
#define LAMBDA 0.022
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

//Other Constants in seconds
#define TRANSFRED_MIN_DURATION 60
#define TRANSFERED_STANDARD_DEVINATION 150



int main(int argc, char* argv[]){

    srand(time(NULL));

    //Getting the inputs
    int samples = atof(argv[1]);
    int n_general_operators = atof(argv[2]);
    int n_specific_operators = atoi(argv[3]);
    int L = atof(argv[4]);
    
    //Histogram parameters
     int histogram[HISSIZE] = {0};
    // int his_size = JUMP*lambda;

    
    
    
    
    
    
    //List of events initialization 
    lista *event_list = NULL; 
    lista *queu = NULL;

    double c,s;

   // int bin=0;
   //new control variables

    int blocked=0;
    int queu_size=0, delayed = 0;
    int total_calls=0;
    double current_time=0;
    int busy=0;
 //   int type=0;
    double delay=0;
    double total_delays=0;
    int counter =0;
    //File related variables
    //char filename[24];
    
  //  if(!strcpy(filename, argv[3])){
  //      perror("strcpy");
  //      return -1;
  //  }
 
  

    int type = 0;
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
             //printf("ENtrei0\n");
            current_time = event_list->tempo;
            type = event_list->tipo;
            event_list = remover(event_list);

            if(type == ARRIVAL){
               // printf("ENtrei1\n");
                c = exponencial(lambda);
                event_list =adicionar(event_list,ARRIVAL,c+current_time);
                if(busy<N){
                    total_calls++;
                    s = dm_calc(dm);
                    busy++;
                    event_list = adicionar(event_list, DEPARTURE, current_time+s);
                    type=event_list->tipo;
                
                }else {
                    if(queu_size < L){
                        total_calls++;
                        delayed++;
                        queu_size++;
                        queu = adicionar(queu, ARRIVAL, current_time);

                    } else if (queu_size == L){
                        blocked++;
                        total_calls++;
                    }
                    // event_list = remover(event_list);
                   // c=exponencial(lambda);
                   // event_list = adicionar(event_list, ARRIVAL, current_time+c);
                     // printf("ENtrei3\n");
                }
            }
            else if(type == DEPARTURE){
                    
                    
                        busy--;
                   // printf("ENtrei4\n");
                  if(queu != NULL){
                   //     printf("ENtrei5\n");
                       delay = current_time - queu->tempo;
                       queu = remover(queu);
                       queu_size--;
                       if(delay>expected_p)
                            counter++;
                       s = dm_calc(dm);
                       event_list = adicionar(event_list,DEPARTURE,current_time+s);
                       busy++;   
                       type= event_list->tipo;                  
                       total_delays += delay;
                       
                       
                       for(int i=0; i<HISSIZE-1;i++){
                           if(c >= i*0.005 && c<(i+1)*0.005){
                               histogram[i]++;
                               break;
                           }
                       }
                       if(c>=(HISSIZE-1)*0.005){
                           histogram[HISSIZE-1]++;
                       }
                       
                    }
               }

        }       

        
    
    //Print Parameters
    
    printf("-----------------------------------------------------\n\n");

   
    printf("*** Inputs: ****\n\n");
    printf("Number of samples: %d\n\n", n_samples);
    printf("Number of General operators: %d\n\n", n_general_pperators);
    printf("Number of Specific operators: %d\n\n", n_specific_pperators);
    printf("Queue Length: %d\n\n", queue_length);


    printf("-----------------------------------------------------\n\n");
 
    printf("*** Debugging: ****\n\n");

    //printf("Total delayed: %d\n", delayed);
    //printf("Number of calls: %d \n", total_calls);
    //printf("Total delays: %lf\n", total_delays);
    //printf("Delay avarage: %lf\n", ((double)total_delays) /((double)total_calls));
    //printf("Delay probability: %lf\n", ((double)delayed)/((double)total_calls)*100);
    //printf("Probability of the delay be greater than %lf is: %lf\n", expected_p, ((double)counter)/((double)total_calls)*100);
    //printf("Queu size:%d\n", L);
    //printf("Probability of losing a package: %lf\n", ((double)blocked)/((double)total_calls)*100);
    //printf("Total of calls blocked: %d\n", blocked);
    //printf("Number of blocked calls: %d\n", blocked);
    //printf("Probability of a call to be blocked: %lf\n", ((double) blocked / (double) total_calls )*100);
   // printf("Simulation by %d samples!\n", samples);
   // printf("Theoretical value of lambda: %lf\n", (float)lambda);
   // printf("Estimator of lambda = %lf\n", (float)(samples/current_time));
   // printf("Number of calls simulated: %d\n", counter);
   // printf("Last Call received: %f\n", current_time);
   // printf("Avarage interval between calls: %lf\n", (float) current_time / counter);
    

    printf("-----------------------------------------------------\n\n");
 
    printf("*** Outputs: ****\n\n");

    printf("*** Probabilities: ****\n\n");
 
    printf("Probability of a call being delayed at the input of the feneral-purpose answering system: %lf\n\n");
    printf("Probability of a call being lost at the input of the general_purpose answering: %lf\n\n");
   
    printf("*** Delays: ****\n\n");
   
    printf("Average delay of the calls (for the calls that suffer delay at the input of the general-purpose answering system): %lf\n\n");
    printf("Average total delay of the calls, since they arrive at the genereal-purpose answering until they are answered by the are-specific answering system: %lf\n\n");


    printf("-----------------------------------------------------\n\n");
    
    printf("*** Wainting time: ****\n\n");

    printf("Mean of the absolute error of the expected waiting time in the incoming operator_general queue: %lf\n\n");
    printf("Mean of the relative error of the expected waiting time in the incoming operator_general queue: %lf\n\n");
    printf("Standard deviation from the expected waiting time in the operator_general queue: %lf\n\n");


    printf("-----------------------------------------------------\n\n");

    printf("*** Sensitivity: ****\n\n");

    printf("Sensitivity for lambda equal to 80 calls/hour\n\n");
    

    printf("-----------------------------------------------------\n\n");

    printf("*** Graphic Output design: ****\n\n");

    printf("Histogram 1: Distribution of delay times in the general-purpose\n\n");
    printf("Histogram 2: General-purpose queue forecasting error\n\n");
    printg("Sensitivity graphic: Time sensitivity analysis \n\n");

    printf("-----------------------------------------------------\n\n");

    printf("*** Simulation Ending: ****\n\n");
 
    printf("-----------------------------------------------------\n\n");

   if(histogramCreation("histogramc.txt", histogram, HISSIZE)<0){
        perror("Problems on Histogram saving");
        return -1;
    }

    return 0;

}