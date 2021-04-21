#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "Lista_ligada.h"
#include "func.h"


#define ARRIVAL 1
#define DEPARTURE 0 
#define HISSIZE 50

/*compile: 
 *
 * gcc -Wall ErlangC-c.c -o ErlangC-c -lm
 * ./ErlangC-c <lambda><dm><N><sim_time><probability><pretended_size>
 * ex. ./ErlangC-c 200 0.008 1 2000 0.01 1
 * 
*/

int main(int argc, char* argv[]){
    

    srand(time(NULL));

    //Getting the inputs
    double lambda = atof(argv[1]);
    double dm = atof(argv[2]);
    int N = atoi(argv[3]);
    double sim_time = atof(argv[4]);
    double expected_p = atof(argv[5]);
    int L = atoi(argv[6]);

    //Histogram parameters
     int histogram[HISSIZE] = {0};
    // int his_size = JUMP*lambda;

    //List of events initialization 
    lista *event_list = NULL; 
    lista *queu = NULL;

    double c,s;

   // int bin=0;
   //new control variables

    int blocked=0;;
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
 
    printf("*** Simulation starting ***!\n");

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
    printf("*** Simulation ending ***!\n");
    printf("Total delayed: %d\n", delayed);
    printf("Number of calls: %d \n", total_calls);
    printf("Total delays: %lf\n", total_delays);
    printf("Delay avarage: %lf\n", ((double)total_delays) /((double)total_calls));
    printf("Delay probability: %lf\n", ((double)delayed)/((double)total_calls)*100);
    printf("Probability of the delay be greater than %lf is: %lf\n", expected_p, ((double)counter)/((double)total_calls)*100);
    printf("Queu size:%d\n", L);
    printf("Probability of losing a package: %lf\n", ((double)blocked)/((double)total_calls)*100);
    printf("Total of calls blocked: %d\n", blocked);
    //printf("Number of blocked calls: %d\n", blocked);
    //printf("Probability of a call to be blocked: %lf\n", ((double) blocked / (double) total_calls )*100);
   // printf("Simulation by %d samples!\n", samples);
   // printf("Theoretical value of lambda: %lf\n", (float)lambda);
   // printf("Estimator of lambda = %lf\n", (float)(samples/current_time));
   // printf("Number of calls simulated: %d\n", counter);
   // printf("Last Call received: %f\n", current_time);
   // printf("Avarage interval between calls: %lf\n", (float) current_time / counter);
    
    
   if(histogramCreation("histogramc.csv", histogram, HISSIZE)<0){
        perror("Problems on Histogram saving");
        return -1;
    }

    return 0;

}