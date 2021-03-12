#ifndef FUNC_H
#define FUNC_H

//Function for the uniform number gereration, with numbers between ]0,1[
// returns the number generated
float uniform();

//Lambda is the arrival calls rate - number of calls per period of time
//This function gives you the duration of calls
float exponencial(float lambda);

//Creats a file with the values for an histogram
// the file returned, has a column for the index, a column for the time interval,
//  and a column with the total times that consecutive calls had that interval
int histogramCreation(char *filename, int* histogram, int his_size, int samples);


#endif