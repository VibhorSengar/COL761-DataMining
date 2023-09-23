#!/bin/sh
#PBS -N elbow_plot
### Set the project name, your department code by default
#PBS -P col761
### Request email when job begins and ends
#PBS -m bea
### Specify email address to use for notification.
#PBS -M $cs5200440@iitd.ac.in
####
#PBS -l select=1:ncpus=1
### Specify "wallclock time" required for this job, hhh:mm:ss
#PBS -l walltime=00:01:59
#PBS -l software=replace_with_Your_software_name
# After job starts, must goto working directory. 
# $PBS_O_WORKDIR is the directory from where the job is fired. 
#PBS -l software=PYTHON

echo "==============================="
echo $PBS_JOBID
cat $PBS_NODEFILE
echo "==============================="
cd /home/cse/dual/cs5200440/scratch/part2
#job 
module purge
module load apps/anaconda/3
sh elbow_plot.sh CS5200440_generated_dataset_5D.dat 5 plot.png
module purge
#Note
# The job line is an example : users need to change it to suit their applications
# The PBS select statement picks n nodes each having m free processors
# OpenMPI needs more options such as $PBS_NODEFILE
