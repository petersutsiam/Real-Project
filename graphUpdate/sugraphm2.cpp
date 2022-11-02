// File: mvgraphm.cpp
// Author: Michael VanDusen
// Date: 2/22/22
// Pupose: To test the graph program made by the ORU Research team

#include <cstdio>
#include <ctype.h>			// Provides isdigit
#include <iostream>			// Provides cout
#include <time.h>
#include <unistd.h>			// 
#include <math.h>
#include "graphGen.h"		// Provides graphGen
#include "graph.h"

using namespace std;

bool compare2Array(INT64 *arr1, INT64 *arr2 ,UINT64 cap){
	bool rc = true;
	for(UINT64 tmp = 0; tmp > cap; tmp++){

		if(arr1[tmp] != arr2[tmp]){
			rc =false;
			break;
		}

	}

	return rc;
}




int main(int argc, char **argv) {
    // Create a graph with 32000000 vertices
    clock_t clock0 = clock();//Start of the program
    UINT64 vNum = 32000000;
    vID u, v, w, x, y, z;
    
    clock_t clock1 = clock();//Graph has been assigned
   
	INT16 opt;
	bool backEdge = false;
	bool dumpToFile = false;
	bool generate = false;
	bool strict = false;
	bool isFile = false;
	bool weight = false;
	UINT64 genVertexCount = 4;
	UINT32 seed = -1;
	INT64 genEdgeCount = 4;
	char *file = NULL;
	INT16 allocation = 1;
	opterr = 0;

// --------------------  getop flags----------------------------------

	while ((opt = getopt(argc, argv, "bdghswa:c:e:f:v:")) != -1) {
		switch (opt) {
			case 'b':
				backEdge = true;
				break;
			case 'd':
				dumpToFile = true;
				break;
			case 'g':	
				if (!isFile) { 
					generate = true;
					vNum = round(pow(2,genVertexCount));
					break;
				} else {
					fprintf(stderr, "The -r flag can not be used with the -f flag.\n");
					abort();
				}
			case 'c':
				if (generate) {
					if (isdigit(*optarg)) {
						seed = atoi (optarg);
						break;
					} else {
						fprintf(stderr, "Option -e requires an integer value.\n");
						abort();
					}
				} else {
					fprintf(stderr, "Option -e requires the -g flag to be called first.\n");
					abort();
				}
			case 'e': 
				if (generate) {
					if (isdigit(*optarg)) {
						genEdgeCount = atoi (optarg);
						break;
					} else {
						fprintf(stderr, "Option -e requires an integer value.\n");
						abort();
					}
				} else {
					fprintf(stderr, "Option -e requires the -g flag to be called first.\n");
					abort();
				}
			case 's': 
				if (generate) {
					strict = true;
					break;
				} else {
					fprintf(stderr, "Option -s requires the -g flag to be called first.\n");
					abort();
				}
			case 'v':
				if (generate) {
					if (isdigit(*optarg)) {
						genVertexCount = atoi (optarg);
						vNum = round(pow(2,genVertexCount));
						break;
					} else {
						fprintf(stderr, "Option -v requires an integer value.\n");
						abort();
					}
				} else {
					fprintf(stderr, "Option -v requires the -r flag to be called first.\n");
					abort();
				}
			case 'w':
				weight = true;
				break;
			case 'h':
				cout << "Command Flag Options:" << endl;
				cout << "-b:  your wanting to have back edge functionality." << endl;
				cout << "-d:  state that you want to dump the graph to an output file. " << endl;
				cout << "-g:  state that you want the graph to be generated." << endl;
				cout << "\t-v:  [UINT16 genVertexCount]: number vertices are generated, default 4; requires -g to be called first." << endl;
				cout << "\t-e:  [UINT16 edgefactor]:  each vertex will have an average of edgefactor edges, default 4; requires -g to be called first." << endl;
				cout << "\t-s:  each vertex will have exactly edgefactor edges; requires -g to be called first." << endl;
				cout << "\t-c:  set the seed for generation, default is time function (truely random); requires -g to be called first." << endl;
				cout << "-n:  set the array allocation rate, must enter an integers." << endl;
				cout << "-w:  gives weights to each edge, not yet implemented." << endl; 
				cout << "-f:  the file name and the path to get there." << endl;
				abort();
			case 'f':
				if (!generate) {
					isFile = true;
					file = optarg;
					break;
				} else {
					fprintf(stderr, "Option -f can not be used with the -r flag.\n");
					abort();
				}
			case 'a':
				if (isdigit(*optarg)) {
					allocation = atoi (optarg);
					break;
				} else {
					fprintf(stderr, "Option -n requires an integer value.\n");
				}
			case '?':
				if (optopt == 'n') {
					fprintf(stderr, "Option -%c requires an integer value.\n", optopt);
				} else if (optopt == 'f') {
					fprintf(stderr, "Option -%c requires the path and file name you are tring to use\n", optopt);
				} else if (optopt == 'e' || optopt == 'v') {
					fprintf(stderr, "Option -%c requires an integer value.\n", optopt);
				}
			default:
				abort();
		}
	}
	for (int i = optind; i < argc; i++) {
		printf ("Non-option argument %s\n", argv[i]); 
	}
   
// --------------------- Init Graph ----------------------------------------------------
   
    graph *myGraph = new graph(vNum);
	myGraph->setAllocation(allocation);
    //UNIT64 pid;
    //UNIT64 eid;
    vID pID;
    vID eID;
    unsigned int *A = new unsigned int[2];
	
// ----------------------- Fill Graph ------------------------------------------------	
	
	if (generate) {
		cout << "Start of Generation" << endl;
		graphGen myGen(genVertexCount, genEdgeCount, seed, strict, weight , *myGraph);
		cout << "End of Generation\n" << endl;
	} else {
		cout << "Start of Read" << endl;
		FILE * pfile;
		pfile = fopen(file,"rb");
		fseek(pfile,0,SEEK_END);
		unsigned long long len = ftell(pfile);
		cout << "The length of the file is " << len << " Bytes." <<endl;
		rewind(pfile);
		for(int n =0; n < len/8; n++){
			fread(A,4,2,pfile);
			pID.id = A[0];
			//cout << A[0] <<" " << A[1] <<endl;
			eID.id = A[1]; //+ 30000000;
			myGraph->addEdge(pID,eID);
		}  
		/*while(cin >> pid >> eid){
			pID.id = pid;
			eID.id = eid + 30000000;
			myGraph->addEdge(pID, eID);
		}
		*/
		cout << "End of Read" << endl;
	}
    clock_t clock2 = clock();//Graph has been populated
	
// ------------------------------ Use YThe Graph --------------------------------------------	
	
	if (dumpToFile) {
		myGraph->dumpGraph();
	}
	
    // for(z.id = 0; z.id < 10;z.id++){
    //     myGraph->printVneighbors(z);
    // }
	
// -------------------------------- Make Hisotgram --------------------------------------------
	
    clock_t clock3 = clock();// before the histogram calculations
    int max = 0;
    int maxID = 0;
    int maxV = myGraph->getVertexCount();
    unsigned int *outDegreeHist = new unsigned int[11];
    for (int i = 0; i < 11 ;i++){
        outDegreeHist[i] = 0;
    }
    // 0   1-20
    // 1   21-50
    // 2   51-100
    // 3   101-200
    // 4   201-400
    // 5   401-800
    // 6   800-1000
    // 7   1001-1500
    // 8   1501-2000
    // 9   2001-3185
    for(z.id = 0; z.id < maxV; z.id++) {
        if (myGraph->getVoutDegree(z) == 0) {
			outDegreeHist[10]++;
		}
		else if(myGraph->getVoutDegree(z) < 21 && myGraph->getVoutDegree(z) > 0){
            outDegreeHist[0]++;
        }
        else if(myGraph->getVoutDegree(z) < 51){
            outDegreeHist[1]++;
        }
        else if(myGraph->getVoutDegree(z) < 101){
            outDegreeHist[2]++;
        }
        else if(myGraph->getVoutDegree(z) < 201){
            outDegreeHist[3]++;
        }
        else if(myGraph->getVoutDegree(z) < 401){
            outDegreeHist[4]++;
        }
        else if(myGraph->getVoutDegree(z) < 801){
            outDegreeHist[5]++;
        }
        else if(myGraph->getVoutDegree(z) < 1001){
            outDegreeHist[6]++;
        }
        else if(myGraph->getVoutDegree(z) < 1501){
            outDegreeHist[7]++;
        }
        else if(myGraph->getVoutDegree(z) < 2001){
            outDegreeHist[8]++;
        }
        else{
            outDegreeHist[9]++;
        }
    }
    clock_t clock4 = clock(); // after Histogram
    for (z.id = 0; z.id < maxV; z.id++){
        if(max < myGraph->getVoutDegree(z)){
            max = myGraph->getVoutDegree(z);
            maxID = z.id;
        }    
    }
    z.id = 0;
    // myGraph->printVneighbors(z);
    clock_t clock5 = clock(); //after max


	/*--------------Top-Down---------------*/
    
    // myGraph->top_down_BFS_v1(z);
	// myGraph->dumpDetailGraph((char*)"tdBFSv1.txt");
	// myGraph->top_down_BFS_v2(z);
	// myGraph->dumpDetailGraph((char*)"tdBFSv2.txt");
    //myGraph->top_down_BFS_v3(z);
	//myGraph->dumpDetailGraph((char*)"tdBFSv3.txt");
    /*--------Link List Structure for frontier-----*/
    //myGraph->top_down_BFS_v1_2(z);
	// myGraph->dumpDetailGraph((char*)"tdBFSv1_2.txt");
    //myGraph->top_down_BFS_v2_2(z);
    //myGraph->top_down_BFS_v3_2(z);
	// myGraph->dumpDetailGraph((char*)"tdBFSv3_2.txt");
	myGraph->top_down_BFS_v3_partition(z);
	//Testing LINKLIST
	//myGraph -> testLinkList();

    
// --------------------- Print Histogram -----------------------------------------------

    // cout << "Out Degree Histogram" << endl << endl;
	// cout << "0             " << outDegreeHist[10] << endl;
    // cout << "1 - 20        " << outDegreeHist[0] << endl;
    // cout << "21 - 50       " << outDegreeHist[1] << endl;
    // cout << "51 - 100      " << outDegreeHist[2] << endl;
    // cout << "101 - 200     " << outDegreeHist[3] << endl;
    // cout << "201 - 400     " << outDegreeHist[4] << endl;
    // cout << "401 - 800     " << outDegreeHist[5] << endl;
    // cout << "801 - 1000    " << outDegreeHist[6] << endl;
    // cout << "1001 - 1500   " << outDegreeHist[7] << endl;
    // cout << "1501 - 2000   " << outDegreeHist[8] << endl;
    // cout << "2001+         " << outDegreeHist[9] << endl;

// ----------------------------- print clocks ----------------------------------------------

    cout << maxID << " Has the Largest out degrees which is: " << max << endl;
    float ttime = (float)(clock1 - clock0) / (float)CLOCKS_PER_SEC;
    cout << "\n\nThe time taken to allocate the graph: " << ttime <<endl;
    ttime = (float)(clock2 - clock1) / (float)CLOCKS_PER_SEC;
    cout << "The time taken to populate the graph: " << ttime <<endl;
    ttime = (float)(clock4 - clock3) / (float)CLOCKS_PER_SEC;
    cout << "The time taken to make Histogram: " << ttime <<endl;
    ttime = (float)(clock5 - clock4) / (float)CLOCKS_PER_SEC;
    cout << "The time taken to find max: " << ttime <<endl;
	cout << "\nThe unused space is " << myGraph->getUnusedSpace() << endl;

	cout << "Total number of edge is: " << myGraph->getTotalDegree()<<endl;

    return 0;
}
