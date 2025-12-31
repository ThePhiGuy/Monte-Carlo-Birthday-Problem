/* birthday.c is a parallelized Monte Carlo simulation for the Birthday Problem
*  
*  The birthday problem is a problem for a set of n people, what is the probability that
*  at least two share the same birthday.
*
*  Use: ./Birthday matches trials runs maxGroupSize minGroupSize birthdayResolution
*
*  Created by Ryan Deaton, Calvin University, in January 2025, for Fun! :)
*
* Note: This uses lcrng.h to generate random numbers for
*       better parallel random distributions compared to rand().
**/

#include "birthday.h"


int main(int argc, char **argv) {
    const int MASTER = 0;
    double startTime;
    int outputMode;
    int GROUP_MIN = 2;
    int GROUP_MAX = 366;
    int GROUP_RUNS = 100;
    int TRIALS = 100000;
    int MATCHED_SIZE = 3;
    int BIRTHDAY_RESOLUTION = 365; // This is a representation of how close of a birthday, ex. same day, same year, same hour.
                                         // This should be the total number of possible birthday number representations.
                                         // 365 for one day per year, ignoring age and ignoring leap year.

    // @TODO Add functionality with un population reports for randomization of group with some biases towards enviornmental factors.
    // @TODO Also add functionality with additional birthday resolutions (needed for above..)

    int numProcesses = 1;
    int id = 0;

    processCommandLine(argc, argv, &outputMode, &MATCHED_SIZE, &TRIALS, &GROUP_RUNS, &GROUP_MAX, &GROUP_MIN, &BIRTHDAY_RESOLUTION);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    if (id == MASTER) {
        startTime = MPI_Wtime();
    }
    lcrng randomNumberGenerator = lcrng_initialize(numProcesses, id);
    
    int *trialValues = (int *)calloc(GROUP_RUNS, sizeof(int));
    double *trialResults = (double *)calloc(GROUP_RUNS, sizeof(double));

    double *totalTrialResults = (double *)calloc(GROUP_RUNS, sizeof(double));

    double trialStep = (double)(GROUP_MAX - GROUP_MIN) / (double)(GROUP_RUNS);

    for (int i = 0; i < GROUP_RUNS; i++) {
        trialValues[i] = GROUP_MIN + (int)(i * trialStep);
    }

    
    for (int i = id; i < GROUP_RUNS; i+=numProcesses) {
        for (int g = 0; g < TRIALS; g++) {
            trialResults[i] += (double)runTrial(MATCHED_SIZE, trialValues[i], BIRTHDAY_RESOLUTION, &randomNumberGenerator);
        }
    }

    MPI_Reduce(trialResults, totalTrialResults, GROUP_RUNS, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (id == MASTER) {
        for (int i = 0; i < GROUP_RUNS; i++) {
            totalTrialResults[i] /= TRIALS;
        }

        if (outputMode == 0) {
            outputCSV(trialValues, totalTrialResults, GROUP_RUNS);
        } else {
            outputCommandLine(trialValues, totalTrialResults, GROUP_RUNS);
        }


        printf("\nRuntime: %g seconds\nProcesses: %d\n", MPI_Wtime() - startTime, numProcesses);
    }
    

    free(trialValues);
    free(trialResults);

    MPI_Finalize();
}


int runTrial(int matchSize, int groupSize, int birthdayResolution, lcrng* rng) {
    short* matchTable = (short *)calloc(birthdayResolution, sizeof(short));
    int rand;
    for (int i = 0; i < groupSize; i++) {
        rand = getRandomNumber(rng, 0, birthdayResolution - 1);
        matchTable[rand]++;
        if (matchTable[rand] == matchSize) {
                return 1;
        }
    }
    return 0;
    
}

int getRandomNumber(lcrng* rng, int min, int max) {
    double rand = (double)lcrng_random(rng) / (double)RAND_MAX;
    return min + (int)(rand * (max - min + 1));
}

void processCommandLine(int argc, char **argv, int *outputMode, int *matches, int *trials, int *runs, int *maxGroupSize, int *minGroupSize, int* birthdayResolution)
{
    if (argc > 1)
    {
        sscanf(argv[1], "%d", outputMode);
    }
    if (argc > 2)
    {
        sscanf(argv[2], "%d", matches);
    }
    if (argc > 3)
    {
        sscanf(argv[3], "%d", trials);
    }
    if (argc > 4)
    {
        sscanf(argv[4], "%d", runs);
    }
    if (argc > 5)
    {
        sscanf(argv[5], "%d", maxGroupSize);
    }
    if (argc > 6)
    {
        sscanf(argv[6], "%d", minGroupSize);
    }
    if (argc > 7)
    {
        sscanf(argv[7], "%d", birthdayResolution);
    }
}


void outputCSV(int* vals, double* res, int runs) {
    FILE *fp = fopen("output.csv", "w");
    if (fp == NULL) {
        perror("Failed to open output.csv");
        return;
    }

    fprintf(fp, "groupSize,probability\n");

    for (int i = 0; i < runs; i++) {
        fprintf(fp, "%d,%.10f\n", vals[i], res[i]);
    }

    fclose(fp);
    return;
}

void outputCommandLine(int* vals, double* res, int runs) {
    for(int i = 0; i < runs; i++) {
        printf("\nGroup Members: %i \t Probability of a Pair: %g", vals[i], res[i]);
    }
    return;
}