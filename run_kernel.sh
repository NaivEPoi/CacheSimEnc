#!/bin/sh
# Compile, Run and extract trace from matmul kernel

export PIN_ROOT=/home/naivepoi/CSE530/Final_Project/pin-3.18-98332-gaebd7b1e6-gcc-linux

mkdir -p bin/
mkdir -p traces/

echo compiling...
g++ -Wall src/mat_columncopy.cpp -o bin/mat_columncopy.o
g++ -Wall src/mat_gather.cpp -o bin/mat_gather.o 
g++ -Wall src/mat_scatter.cpp -o bin/mat_scatter.o 
g++ -Wall src/mat_transpose.cpp -o bin/mat_transpose.o 


for entry in bin/*.o
do
  for input in input/*.in
  do
    f=$(echo "${entry##*/}");
    kernelname=$(echo $f| cut  -d'.' -f 1);
    in=$(echo "${input##*/}");
    inputname=$(echo $in| cut  -d'.' -f 1);
    filename="${kernelname}_${inputname}_traces.out"
    echo "Passing matrix in dense fmt"
      echo "Running $kernelname on input $kernelname"
      time $PIN_ROOT/pin -t $PIN_ROOT/source/tools/ManualExamples/obj-intel64/pinatrace.so -- $entry --input_file input
    head pinatrace.out  
    mv pinatrace.out traces/$filename  
  done
done

./run_simulator.sh /home/naivepoi/CSE530/Final_Project/CacheSimEnc/traces
