# 📊 Monte Carlo Simulation of the Birthday Problem

This repository contains a Monte Carlo simulation that explores the Birthday Paradox — the unintuitive result from probability theory that in a group of just 23 people, the chance of at least two people sharing a birthday exceeds 50%. 
https://en.wikipedia.org/wiki/Birthday_problem

The simulation repeatedly randomizes birthdays for a set of groups of n people and estimates the probability of a shared birthday through experimental sampling.

I got the idea for this project from a Project in Joel Adams' CS374 course at Calvin University, where we did monte carlo simulations of forest fire to learn MPI.

# 🧠 Features

This Project Features
  - MPI for Parallelization
  - Monte Carlo Simulation Technique
  - CSV Output for Import into Excel/Sheets
  - Command Line Options for Simulation Parameters

# 🧪 Usage
Use the Makefile included in this project to build the required executable.

Run the simulation with 

> mpirun -np (processes) ./Birthday (outputType) (matches) (trials) (runs) (maxGroupSize) (minGroupSize) (birthdayResolution)

The optional parameters are
  - outputType : currently supported is 0 (or no optional parameters) for default command line output, and 1 being CSV output. 
  - matches : the size of the matches you are looking for, the birthday problem generally utilizes 2, indicating two people with the same birthday.
  - trials : the number of monte carlo simulated trials, similar to a resolution for the accuracy of the answers.
  - runs : the amount of division between the minimum and maximum group size, should not exceed max-min group size.
  - maxGroupSize : the largest group size tested.
  - minGroupSize : the smallest group size tested.
  - birthdayResolution : the parameter for the number of birthday options, 365 represents once a day, but you can simulate with birth day and year, or even year day and hour.


# 📫 Contact

If you use this code for a project or classroom work, let me know — I’d love to hear about it!

