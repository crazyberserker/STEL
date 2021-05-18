#ifndef FUNC_H
#define FUNC_H

#include "Lista_ligada.h"


//Function for the uniform number gereration, with numbers between ]0,1[
// returns the number generated
double uniform();

//Lambda is the arrival calls rate - number of calls per period of time
//This function gives you the duration of calls
double exponencial();

//Creats a file with the values for an histogram
// the file returned, has a column for the index, a column for the time interval,
//  and a column with the total times that consecutive calls had that interval
int histogramCreation(char *filename, int* histogram, int his_size);

//
//
//
lista * client_arrival(lista *event_list, float lambda, float s, float current_time, int n);

//
//
//
lista * client_departure(lista *event_list, int n);

//
//
//
double dm_calc(double s);

//
//
//
int determine_call_type();


//
//
//
double running_average(int n, double current_time, double previous_average);


//
//
//
double general_call(int area);


//
//
//
double specific_call();

#endif