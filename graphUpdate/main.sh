#!/bin/bash


#export OMP_NUM_THREADS=1

echo "This Run all the compiler and test"

#compile the graphmain graph and bfs
#g++ graphm.cpp graph.cpp bfs.cpp -fopenmp -o test
#g++ graph.cpp graphGen.cpp sugraphm2.cpp -o exe
clang++ -Xpreprocessor -fopenmp -I/usr/local/include -L/usr/local/lib -lomp graphGen.cpp sugraphm2.cpp graph.cpp linkList.cpp bfs.cpp -o test
#Run the program 
time ./test -g -c5 -v10 -e8 -s -d
 
sleep 3

echo "\nTesting BFS RESULT:"

# echo "BFSv1 and BFSv2"
# ./compare2txt tdBFSv1.txt tdBFSv2.txt

# echo "BFSv1 and BFSv1_2"
# ./compare2txt tdBFSv1.txt tdBFSv1_2.txt

# echo "BFSv1_2 and BFSv3_2"
# ./compare2txt tdBFSv1_2.txt tdBFSv3_2.txt


