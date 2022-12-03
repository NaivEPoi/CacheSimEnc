#!/bin/sh
# Run Simulator on input traces 

input_file=${1:-'traces/'}   #Pass absolute path
cd Simulator/src/

for entry in $input_file/*.out
do
  f=$(echo "${entry##*/}");
  tracename=$(echo $f| cut  -d'.' -f 1);
  echo $tracename	
  filename="../../logs/${tracename}_level_3.log"
  echo "Running $tracename on simulator"
  time python3 ./cache_simulator.py -dc ../config/config_simple_multilevel -t $entry | tee stats.txt
  mv cache_simulator.log $filename  
done
