Entry Numbers and Name and Contribution:
	2020CS50440 - Sahil Shahare          	- 33.33%
	2020CS50423 - Dharmeswar Basumatary  	- 33.33%
	2020EE30313 - Vibhor Sengar		- 33.33%
	


Directory Structure:
	
HW_CS5200423
    |-> part1
	|
	|
	|
    |-> part2
    	  |->generateDataset_d_dim_hpc_compiled
    	  |-> q2.py
    	  |-> elbow_plot.sh
    |-> CS5200423.pdf
    |-> README.txt
    


Files Explanation:

part2:
	generateDataset_d_dim_hpc_compiled:
		used to generate datasets as given in the problem statement of Assignment 2
		
	q2.py
		The python file containing the code to run K-means algorithm on dataset passed as 
		command-line argument and plot the elbow-plot. Uses sklearn.cluster library for
		k-means algorithm.
	
	elbow_plot.sh
		The script file used to run the python code. The command to run is given below.
		
		
		
Execution Instructions:
	
	part2:
		change the directory to part2 folder using command'
		
			cd part2

		execute the following command to run the code for part2
		
			sh elbow_plot.sh <dataset> <dimension> q3_<dimension>_<RollNo>.png
    
   

 
