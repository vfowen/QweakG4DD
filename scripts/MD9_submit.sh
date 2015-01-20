#!/bin/bash

#Programmer: Valerie Gray
#Purpose: This script creates the job and macro files
#for the MD9 bar study in Geant4
#
#This will create root files for simulations in 
#octants 1, 8, 7 for MD9 positions at nominal and
# +- 5 mm from nominal
#
#Date: 11-22-2012
#Modified:
#Assisted By: Wouter Deconinck
#


basename=MD9_Run1

#min and max positions of MD9 in each dimension (cm)
X_position_min=-73.36;
X_position_max=-72.36;

Y_position_min=368.34;
Y_position_max=369.34;

Z_position_min=736.36;
Z_position_max=737.36;

#how much we are moving the MD9 bars (5mm or .5cm)
position_step=0.5;

#first job number (can change if just want to add
#on to the get more simultaions)
firstjob=1
#last job number one would like done
lastjob=1
#number of events simulated in each Geant4 file
nevents=125000
#batch system
batch=xml
qwgeant4=~/QwGeant4

#go throught each octant that a simulation is looking at
#since in this case only one octant is active in the simulation
for octant in 1 8 7; do
  echo "octant = ${octant}"

  #go through each dimention - changing the position of the
  #of MD9 in that dimension only
	for axis in X Y Z; do
	  echo "axis = ${axis}"

    #get the max and min poisiton for whatever dimesion we are 
    #simulationg now
    min=$(eval echo "\$${axis}_position_min")
    max=$(eval echo "\$${axis}_position_max")
    #get the strating postion in away to force bash to use floating values
	  position=`echo "scale=2; ${min}" | bc -l`
 		while [ "`echo "${position} <= ${max}" | bc -l`" -eq 1 ] ; do
    	echo "position = ${position}"

      #come up with the basename that will be used  to name the rootfiles
		  name=${basename}_Oct${octant}_${axis}_${position}cm_LargeHut

		  let jobid=${firstjob}
	    while [[ ${jobid} -le ${lastjob} ]] ; do
			  echo "Job ${jobid}"

        #create a randome seed so that the simultaions are not all the same
			  unixtime=`date +%s`
	  		nanosecond=`date +%N`
			  let seedA=10#${unixtime}+${current}+${jobid}
	  		let seedB=10#${nanosecond}+${current}+${jobid}

			  mkdir -p random/${name}_${jobid}
				mkdir -p jobs/${batch}
				mkdir -p macros/jobs

        #replace the variables in the file macros/${basename}.in
        #which creates the mac file that Geant4 uses
			  sed -e "s|%nevents%|${nevents}|g" \
    	    	-e "s|%qwgeant4%|${qwgeant4}|g" \
    	    	-e "s|%octant%|${octant}|g" \
      	  	-e "s|%axis%|${axis}|g" \
        		-e "s|%position%|${position}|g" \
			  		-e "s|%seedA%|${seedA}|g" \
				  	-e "s|%seedB%|${seedB}|g" \
		  			-e "s|%jobid%|${jobid}|g" \
		  			-e "s|%name%|${name}|g" \
	 	  		macros/${basename}.in \
			  > macros/jobs/${name}_${jobid}.mac

        #replace the variables in the file ${basename}.in
        #which creates the job file that is submitted to the farm
	  		sed -e "s|%nevents%|${nevents}|g" \
    	    	-e "s|%qwgeant4%|${qwgeant4}|g" \
		        -e "s|%octant%|${octant}|g" \
    		    -e "s|%axis%|${axis}|g" \
        		-e "s|%position%|${position}|g" \
				  	-e "s|%seedA%|${seedA}|g" \
					  -e "s|%seedB%|${seedB}|g" \
		  			-e "s|%jobid%|${jobid}|g" \
				  	-e "s|%name%|${name}|g" \
				  jobs/job.${batch}.in \
			  > jobs/${batch}/${name}_${jobid}.${batch}

        #define where the rootfile will be stored, check to see if a rootfile  
        #exists, if not then submit the job if it is there do not submit it 
        #if so then move to the next job
    		rootfile=/mss/home/${USER}/rootfiles/${name}/${name}_${jobid}.root
        if [ -e ${rootfile} ] ; then
          echo "File ${rootfile} already exists on mss."
        else
          echo "File ${rootfile} doesn't exist. Will submit job."
          if [ "${batch}" == "xml" ] ; then
            jsub -xml jobs/${batch}/${name}_${jobid}.${batch}
          fi
          if [ "${batch}" == "sh" ] ; then
            echo "Submitting job jobs/${batch}/${name}_${jobid}.${batch}..."
            qsub jobs/${batch}/${name}_${jobid}.${batch}
          fi
        fi

        #increase the jobid number
	  		let jobid=${jobid}+1

			done
      #update the position
			position=`echo "scale=2; ${position}+${position_step}" | bc -l`
	  done
	done
done

# :)
