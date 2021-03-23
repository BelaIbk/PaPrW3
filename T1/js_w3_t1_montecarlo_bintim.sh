#!/bin/bash

# Executes job in the queue "lva.q" unless you have special requirements.
#$ -q lva.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N PaPr_W3_T1

# Redirect output stream to this file.
#$ -o output.csv

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0

# Set up any environment variables
#export ENVIRONMENT_VARIABLE=foobar


for THR in 1 2 4 8
do
    echo "\tThreads $THR"
    echo "Critical:"
    /usr/bin/time -v ./montecarlo_critical $THR
    echo "Atomic:"
    /usr/bin/time -v ./montecarlo_atomic $THR
    echo "Reduction:"
    /usr/bin/time -v ./montecarlo_reduction $THR
done