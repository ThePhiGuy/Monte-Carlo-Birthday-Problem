/* birthday.h is the header for birthday.c, a parallelized Monte Carlo simulation for the Birthday Problem
*  
*  Created by Ryan Deaton, Calvin University, in December 2025, for Fun! :)
*
* Note: This uses lcrng.h to generate random numbers for
*       better parallel random distributions compared to rand().
**/

#include <mpi.h>
#include "lcrng.h"
#include <stdio.h>

int runTrial(int matchSize, int groupSize, int birthdayResolution, lcrng* rng);
int getRandomNumber(lcrng* rng, int min, int max);
void processCommandLine(int argc, char **argv, int* outputMode, int *matches, int *trials, int *runs, int *maxGroupSize, int *minGroupSize, int *birthdayResolution);
void outputCommandLine(int* vals, double* res, int runs);
void outputCSV(int* vals, double* res, int runs);