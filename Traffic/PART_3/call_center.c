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


int main(int argc, char* argv[]){

    srand(time(NULL));

    //Getting the inputs
    int samples = atof(argv[1]);
    int n_general_operators = atof(argv[2]);
    int n_specific_operators = atoi(argv[3]);
    int L = atof(argv[4]);
    
    //Histogram parameters
     int histogram1[HISSIZE] = {0};
     int histogram2[HISSIZE] = {0};
    // int his_size = JUMP*lambda;
    
  
    //List of events initialization 
    lista *specific_queue = NULL; 
    lista *general_queue = NULL;
  //  lista *general_events = NULL;
    lista *specific_events = NULL;
    lista *event_list = NULL;
    
  
    //Statistics variables initialization
    //abs error
    double absolut_error = 0;
    // double relative_error = 0;
    int error_counter = 0;
    double  a_sum=0;
    double global_average = 0;
    double average_absolute = 0;
    
    //All delay variables
    int delayed = 0;
    double delay=0, specific_delay=0;
    double total_delays=0, total_specific_delay=0;


    //Auxiliary variables initialization
    int type = 0, area = 0;
    double s=0, c=0;
    //samples counter
    int i = 0;
    int queue_size=0;
    int busy_general=0, busy_specific=0;
    double current_time=0;
    int counter =0;
   

    //Output variables initialization
    double average = 0;
    int specific_counter = 0;
    int blocked=0;
    int total_calls=0;
    int specific_delayed=0;

   
    //Array auxiliary 
    double *arrayDelays = NULL;
    arrayDelays = (double*)calloc(1, sizeof(double));
    int arrayCouter=0;
    double array_average = 0;

    // int bin=0;
    //new control variables


    //   int type=0;
    
    //File related variables
    //char filename[24];
    
    //  if(!strcpy(filename, argv[3])){
    //      perror("strcpy");
    //      return -1;
    //  }
      
   // histogram = (int*)calloc(his_size, sizeof(int));
        event_list = adicionar(event_list, ARRIVAL, SPECIFIC,0,0);
           
        while(i < samples){
            /* //Histogram update
            bin = (int)(c/(1/(float)(his_size)));
            if(bin > his_size -1 ){
                histogram[his_size -1]++;
            }
            else
                histogram[bin]++;
            */
             //printf("ENtrei0\n");
            //current_time = event_list->tempo;
            type = event_list->tipo;
          
           

            if(type == ARRIVAL){
               // printf("ENtrei1\n");
                i++;
                area = determine_call_type();
                c = exponencial();
                event_list = adicionar(event_list,ARRIVAL,area,c+event_list->tempo, 0);
                total_calls++;

                if(busy_general<n_general_operators){
                 //   s = dm_calc(dm);
                    busy_general++;
                    s = general_call(event_list->area);
                    event_list = adicionar(event_list, DEPARTURE, event_list->area,event_list->tempo+s,0);
                    type=event_list->tipo;
                
                }else if (queue_size < L){
                   /* if(queu_size < L){
                        total_calls++;
                        delayed++;
                        queu_size++;
                        queu = adicionar(queu, ARRIVAL, current_time);

                    } else if (queu_size == L){
                        blocked++;
                        total_calls++;*/
                        printf("Waiting time: %lf\n", average);
                        general_queue = adicionar(general_queue, ARRIVAL, event_list->area, event_list->tempo,0);
                        queue_size++;
                        delayed++;
                        
                    } else 
                        blocked++;
                    // event_list = remover(event_list);
                   // c=exponencial(lambda);
                   // event_list = adicionar(event_list, ARRIVAL, current_time+c);
                     // printf("ENtrei3\n");
                } else{
                    busy_general--;

                    if(general_queue != NULL && L>0){
                        busy_general++;
                        delay = event_list->tempo - general_queue->tempo;
                        //printf("ENtrei5\n");
                        general_queue->delay += delay;
                        total_delays+=delay;

                        
                        //Delay Histogram
                        for(int i=0; i<HISSIZE-1;i++){
                           if(delay >= i*0.005 && delay<(i+1)*0.005){
                               histogram1[i]++;
                               break;
                           }
                        }
                        if(delay>=(HISSIZE-1)*0.005){
                           histogram1[HISSIZE-1]++;
                        }

                        
                        //Absolut error
                        absolut_error = fabs(delay-average);
                        error_counter++;
                        a_sum += absolut_error;

                        //Prediction Histogram
                        for(int i=0; i<HISSIZE-1;i++){
                           if(absolut_error >= i*0.005 && absolut_error<(i+1)*0.005){
                               histogram2[i]++;
                               break;
                           }
                        }
                        if(absolut_error>=(HISSIZE-1)*0.005){
                           histogram2[HISSIZE-1]++;
                        }
                            average = running_average(error_counter, delay, average);
                            s = general_call(general_queue->area);
                            event_list = adicionar(event_list, DEPARTURE, general_queue->area, event_list->tempo+s, general_queue->delay);
                            general_queue = remover(general_queue);
                            queue_size--;
                    }

                    if(event_list->area == SPECIFIC){
                        specific_counter++;
                        specific_events = adicionar(specific_events, ARRIVAL, SPECIFIC, event_list->tempo, event_list->delay);
                      
                        while(specific_events->tempo < event_list->tempo && n_specific_operators > 0 && specific_events!=NULL){
                     
                             if(specific_events->tipo == DEPARTURE){
                                busy_specific--;

                                if(specific_queue != NULL){
                                    busy_specific++;

                                    specific_delay = specific_events->tempo - specific_queue->tempo;
                                    specific_queue->delay += specific_delay;
                                    total_specific_delay += specific_delay;

                                    s=specific_call();
                                    arrayCouter++;
                                    arrayDelays = (double*)realloc(arrayDelays, (arrayCouter)*sizeof(double));
                                    arrayDelays[arrayCouter-1] = specific_queue->delay;
                                    
                                  // arrayDelays = (double *)realloc(arrayDelays, arrayCouter *sizeof(double));

                                    
                                    specific_events = adicionar(specific_events, DEPARTURE, SPECIFIC, specific_events->tempo+s, specific_queue->delay);
                                    specific_queue = remover(specific_queue);
                                    
                                }
                            } else{
                                if(busy_specific < n_specific_operators){
                                    busy_specific++;
                                    s = specific_call();
                                    //arrayDelays[arrayCouter] = specific_queue->delay;
                                    //arrayCouter++;
                                    arrayCouter++;
                                    arrayDelays = (double*)realloc(arrayDelays, (arrayCouter)*sizeof(double));
                                    arrayDelays[arrayCouter-1] = specific_events->delay;
                                    //arrayDelays = (double*)realloc(arrayDelays, (arrayCouter)*sizeof(double));
                                    //arrayDelays = (double *)realloc(arrayDelays, arrayCouter *sizeof(double));
                                    specific_events = adicionar(specific_events, DEPARTURE, SPECIFIC, specific_events->tempo + s, specific_events->delay);

                                }   else{
                                    specific_queue = adicionar(specific_queue, ARRIVAL, SPECIFIC, specific_events->tempo, specific_events->delay);
                                    specific_delayed++;
                                }                             
                            }
                            specific_events = remover(specific_events);
                        }
                     
                   
                    }
                }
                
                event_list = remover(event_list);
                 // printf("ENtrei4\n");
                  
        }

    //Output calculations    
     global_average = (double) total_delays / (double) delayed; 

    for(counter = 0; counter < arrayCouter; counter++){
        array_average += arrayDelays[counter];
    }
     
    array_average = array_average / arrayCouter;
    
    average_absolute = a_sum / average;

    //Print Parameters
    
    printf("-----------------------------------------------------\n\n");

   
    printf("*** Inputs: ****\n\n");
    printf("Number of samples: %d\n\n", samples);
    printf("Number of General operators: %d\n\n", n_general_operators);
    printf("Number of Specific operators: %d\n\n", n_specific_operators);
    printf("Queue Length: %d\n\n", L);


    printf("-----------------------------------------------------\n\n");
 
    printf("*** Debugging: ****\n\n");

    printf("Total delayed: %d\n\n", delayed);
    printf("Number of calls: %d \n\n", total_calls);
    printf("Total delays: %lf\n\n", total_delays);
    printf("Average delay time: %lf\n\n", global_average);
    
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

    printf("*** General Purpose: ****\n\n");
 
    printf("Probability of a call being delayed at the general-purpose: %lf\n\n", (double) delayed / (double) total_calls);
    printf("Probability of a call being lost at the general_purpose: %lf\n\n", (double) blocked /(double) total_calls);
    
    printf("Absolute error: %lf\n\n", average_absolute);
   
    printf("Relative error: %lf\n\n", (double) absolut_error /(double) average);


    printf("*** Specific Purpose: ****\n\n");

    printf("Average of specific calls delayed: %lf\n\n", (double)specific_delayed / (double)specific_counter);

    printf("Average of the specific delay time: %lf seconds\n\n", (double)total_specific_delay /specific_delayed);
    
    printf("Average time in Queue: %lf\n\n", array_average);


    //printf("Average time between the arrival of the call from the general purpose and the call beeing answered by the area specific: %lf \n\n", );
    
   
   
   /*
    printf("*** Delays: ****\n\n");
   
    printf("Average delay of the calls (for the calls that suffer delay at the input of the general-purpose answering system): %lf\n\n");
    printf("Average total delay of the calls, since they arrive at the genereal-purpose answering until they are answered by the are-specific answering system: %lf\n\n");
  

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
 
    printf("-----------------------------------------------------\n\n");*/

   if(histogramCreation("Delay.txt", histogram1, HISSIZE)<0){
        perror("Problems on Histogram1 saving");
        return -1;
    }

    if(histogramCreation("Prediction.txt", histogram2, HISSIZE)<0){
        perror("Problems on Histogram2 saving");
        return -1;
    }

    free(arrayDelays);
    return 0;

}