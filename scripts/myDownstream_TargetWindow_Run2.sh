#!/bin/bash
#Original Programmer: Val Gray
#Programmer: Kurtis Bartlett
#Purpose: This script creates the job and macro files for the isolated 
# target window simulations
#
#Date: 11-22-2012
#Modified: 5-15-2013
#Assisted By: Wouter Deconinck
#

name=myDownstream_TargetWindow_Run2

#first job number (can change if just want to add
#on to the get more simultaions)
firstjob=1
#last number of jobs one would like done
lastjob=50
#number of events simulated in each Geant4 file
nevents=125000
#batch system
batch=xml
qwgeant4=~/QwGeant4

let jobid=${firstjob}
 while [[ ${jobid} -le ${lastjob} ]] ; do
	echo "Job ${jobid}"

  #create a randome seed so that the simultaions are not all the same
	unixtime=`date +%s`
	nanosecond=`date +%N`
	let seedA=10#${unixtime}+${current}+${jobid}
	let seedB=10#${nanosecond}+${current}+${jobid}

	mkdir -p ../random/${name}_${jobid}
	mkdir -p ../jobs/${batch}
	mkdir -p ../macros/jobs

  #replace the variables in the file macros/${basename}.in
  #which creates the mac file that Geant4 uses
	sed -e "s|%nevents%|${nevents}|g" \
			-e "s|%qwgeant4%|${qwgeant4}|g" \
			-e "s|%seedA%|${seedA}|g" \
			-e "s|%seedB%|${seedB}|g" \
			-e "s|%jobid%|${jobid}|g" \
			-e "s|%name%|${name}|g" \
		../macros/${name}.in \
	> ../macros/jobs/${name}_${jobid}.mac

  #replace the variables in the file ${basename}.in
  #which creates the job file that is submitted to the farm
	sed -e "s|%nevents%|${nevents}|g" \
			-e "s|%qwgeant4%|${qwgeant4}|g" \
			-e "s|%seedA%|${seedA}|g" \
			-e "s|%seedB%|${seedB}|g" \
			-e "s|%jobid%|${jobid}|g" \
			-e "s|%name%|${name}|g" \
		../jobs/job.${batch}.in \
	> ../jobs/${batch}/${name}_${jobid}.${batch}

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

# :)
