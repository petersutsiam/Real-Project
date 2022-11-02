// File: graphGen.cpp
// Author: Dr. Stephen Wheat, Samuel Udall, Michael Vandusen, Andrew Westlund
// Date: 9/16/22
// Pupose: Will generate a random graph based on the passed in vaules.

#include <iostream>			// Provides cout
#include <math.h>			// Provides math functions
#include "graphGen.h"		// Provides header file containing definitions
#include "graph.h"			// Provides graph object.

using namespace std;

graphGen::graphGen(UINT64 vertexCount, UINT64 edgeFactor, UINT32 seed, bool strict, bool weight, graph &Graph) {
	vCount = vertexCount;
	edges = edgeFactor;
	Weighted = weight;
	edgeList = new UINT64 [3];
	this->Graph = &Graph;				// pointer to the graph object
	
	if (seed == -1) {
		srand((unsigned) time(NULL)); 	// sets the rand seed to the time, so true random.
	} else {
		srand((unsigned) seed);			// sets passed in rand seed.
	}
	if (strict) {
		strictOutGraph(vCount,edges);
	} else {
		randGraph(vCount,edges);
	}
	
}

graphGen::~graphGen() {
	
}

void graphGen::randGraph(UINT64 vNum, UINT64 edgefactor){
    // the number of vertices
	vCount = round(pow(2, vNum));
	// Set number of edges
    long long edgeNum = edgefactor * vCount;
    // set Probabilities
    double A, B, C;
    A = 25;
    B = 15;
    C = 35;

    // Create index arrays
    
    int ab = A + B;
    int c_norm = round((C/(100 - (A + B))) * 100);
    int a_norm =round((A/(A + B)) * 100);

    bool ii_bit;
    bool jj_bit;
	bool max;
	
    for (long long j = 0; j < edgeNum; j++){
        edgeList[0] = 0;		// starting vertex.
        edgeList[1] = 0;		// edge goes to this vertex.
        edgeList[2] = 0;		// for weighted graphs (not yet implemented)
        for (int i = 0; i < vNum; i++){
			max = false;	// for preventing self loops 
			// random math generation made by Michael Vandusen
            ii_bit = rand() % 100 > ab;
            jj_bit = rand() % 100 >(c_norm * ii_bit + a_norm * !ii_bit);
            edgeList[0] = edgeList[0] + pow(2, i) * ii_bit;
            edgeList[1] = edgeList[1] + pow(2, i) * jj_bit;
			edgeList[2] = rand() % 100 + 1;

			
			if (Weighted) {
				cout << "not implemented yet, sorry." << endl;
				abort();
			} 
			
			pID.id = edgeList[0];		// makes the ids to add to graph.
			eID.id = edgeList[1];
			Graph->addEdge(pID,eID);
        } 
	}
}

void graphGen::strictOutGraph(UINT64 vNum, UINT64 edgefactor){
    // Create index arrays
	bool maxed = false;
	int v = round(pow(2, vNum));
	for (int i = 0; i < edgefactor; i++) {
		for (int j = 0; j < v; j++) {
			edgeList[0] = j;
			edgeList[1] = rand() % v;
			pID.id = edgeList[0];		// makes the ids to add to graph.
			eID.id = edgeList[1];
		
			if (Weighted) {
				edgeList[2] = rand() % 100 + 1;
				
				cout << "not implemented yet, sorry." << endl;
				abort();
			} else {		
				while(!Graph->addEdge(pID,eID)) {
					if (eID.id < v && !maxed) {
						eID.id = eID.id + 1;
					} else {
						eID.id = eID.id - 1;
						maxed = true;
					}
				}	
			}
		}
	}
}