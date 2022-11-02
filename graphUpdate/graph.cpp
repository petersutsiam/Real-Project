// File: graph.cpp
// Author: Dr. Stephen Wheat, Austin Lehman, Samuel Udall, Michael Vandusen, Andrew Westlund
// Date: 1/31/22
// Pupose: This program will recieve a graph and will create a list of all the vertices
// and will list all the vertices adjacent to each vertex.
// The both the list and the lists of adjacent vertices will be dynamically allocated
// and will be sorted least to greatest.

#include <cstdio>
#include <iostream>			// Provides cout
#include "graph.h"			// Provides header file containing definitions

using namespace std;

// Constructor for vertex object
vertex::vertex() {
    initVertex();
}

vertex::~vertex() {
    delete [] nList;
}

void vertex::initVertex() {
    inDegree = 0;				// The vertex starts off with no incoming edges
    outDegree = 0;				// The vertex starts off with no outgoing edges
    capacity = 0;				// The list of adjacent vertices starts off empty
    myPos = 0;	
	myLevel = -1;
	dummy2 = 0;
	dummy = 0;
	dummy3 = 0;				
	
	dummyList = NULL;
    // The list of adjacent vertices starts off empty
    nList = NULL;
}

// This differs from initVertex, as we must deal with getting rid of a possible neighbor list
void vertex::clearVertex() {
    if (nList) {
		delete [] nList;
    }
	
    initVertex();
}

INT16 vertex::isNeighbor(vID n) {
    bool check = false;	// Equals false if n is not a neighbor
    INT16 mid;		
    INT16 lowerBound = 0;
    // Set the upper bound to start as the last possible position of the vertex list
    INT16 upperBound = outDegree - 1;
    
    // While the indicated id has not been found and the entire list has not been searched
    while (lowerBound <= upperBound) {
		mid = lowerBound + ((upperBound - lowerBound) / 2);
	
		if ((nList[mid]).id > n.id) {
			upperBound = mid - 1;
		} else if ((nList[mid]).id < n.id) {
			lowerBound = mid + 1;
		} else {
			check = true;
			break;
		}
    }
    
    // If the vertex with the indicated ID is not pointed to by the current vertex, return -1
    if (check == false) {
		mid = -1;
    }

    return mid;
}

bool vertex::addNeighbor0(vID n) {
	UINT16 j = outDegree;
	for (; j > 0 ; j--) {
		// moves array entries greater than vID n to the right to insert n in order
		if (nList[j-1].id > n.id) {   
			nList[j] = nList[j-1];
		} else {
			break;
		}
	}
	
	nList[j] = n;
	outDegree++;	
	return true;
}

bool vertex::addNeighbor1(vID n, INT16 allocation) {
	bool rc = false;
	if (isNeighbor(n) == -1) {
		if (outDegree == capacity) {
			try {
				vID *newList = new vID[capacity + allocation];
				for (int i = 0; i < capacity; i++) {
					newList[i] = nList[i];
				}
				delete [] nList;
				nList = newList;
				capacity += allocation;
			} catch (bad_alloc& badAlloc) {
				cerr << "Not enough memory: " << badAlloc.what() << endl;
			}
		}
		rc = addNeighbor0(n);
	}
	return rc;
}

bool vertex::delNeighbor(vID v) {
    bool rc = false;
    INT16 t = isNeighbor(v);

    if (t != -1) {
		// Create new array with decremented capacity.
		vID *temp = new vID[capacity - 1];	
		
		for (int i = 0; i < t; i++) {
			temp[i] = nList[i];
		}

		for (int i = t; i < capacity-1; i++) {
			temp[i] = nList[i + 1];
		}

		

		delete [] nList;
		nList = temp;
	
		capacity--;
		outDegree--;

		rc = true;
	}

    return rc;
}

void vertex::incInDegree() {
    inDegree++;
}

void vertex::decInDegree() {
    inDegree--; 
}

void vertex::printNeighbors() {
    for (UINT16 j = 0; j < outDegree; j++) {
		cout << (nList[j].id) << " ";
    }
	//cout << " MyPos " << myPos;
    cout << endl;
}

void vertex::incPos() {
	myPos++;
}

void vertex::decPos() {
	myPos--;
}

UINT16 vertex::getInDegree() {
    return inDegree;
}

UINT16 vertex::getOutDegree() {
    return outDegree;
}

UINT16 vertex::getCapacity() const {
	return capacity;
}

vID * vertex::getNList() const {
	return nList;
}

INT16 vertex::getmyLevel() const{
	return myLevel;
}

void vertex::setmyLevel(INT16 lvl){
	myLevel = lvl;
}

// -------------------------------------- Graph -----------------------------------------

// Constructor for graph
graph::graph(UINT64 numberOfVertices) {
    vertexCount = numberOfVertices;
    vList = new vertex[vertexCount];
    totalDegree = 0;
	allocation = 1;
	loops = false;
}

// Destructor for graph
graph::~graph() {
    clear();
    delete [] vList;
}

void graph::clear() {
    for (UINT64 i = 0; i < vertexCount; i++) {
		vList[i].clearVertex();
    }
    totalDegree = 0;
}

// Clear the neighbor list of a particular vertex
void graph::clearNlist(vID v) {
	vID * clearList = getNList(v.id);
	// Decrement all of the vertices affected
	for (int i = 0; i < vList[v.id].getOutDegree(); i++) {
		vList[(clearList[i]).id].decInDegree();
	}
	// Decrease total degree by the appropriate amount
	totalDegree = totalDegree - vList[v.id].getOutDegree();
	vList[v.id].clearVertex();
}

void graph::setAllocation(INT16 a) {
	if (a < 1) {
		allocation = 1;
	} else if (a > 16) {
		allocation = 16;
	} else {
		allocation = a;
	}
}

bool graph::addEdge(vID u, vID v) {
    bool rc = false;

	if (loops) {
		rc = vList[u.id].addNeighbor1(v, allocation);
	} else {
		if (u.id != v.id) {
			rc = vList[u.id].addNeighbor1(v, allocation);
		}
	}

    if (rc) {
		// If the edge is successfully added, increase vertex v's inDegree by 1
		vList[v.id].incInDegree();
		totalDegree++;
		if (u.id > v.id) {
			vList[u.id].incPos();
		}
    }

    return rc;
}

bool graph::delEdge(vID u, vID v) {
    bool rc;
    
    rc = vList[u.id].delNeighbor(v);

    if (rc) {
		// If the edge is successfully deleted, decrease vertex v's inDegree by 1
		vList[v.id].decInDegree();
		totalDegree--;
		if (u.id > v.id) {
			vList[u.id].decPos();
		}
		
    }

    return rc;
}

bool graph::isEdge(vID u, vID v) {
    bool rc = false;
 
    // If vertex u points to vertex v, return true
    if (vList[u.id].isNeighbor(v) != -1) {
		rc = true;
    }

    return rc;
}

void graph::dumpGraph() {
	vID *V;
	UINT64 *A;
	int n = 0;
	FILE * pfile;
    pfile = fopen("dumpOutput.txt","w");
	for (UINT64 i = 0; i < vertexCount; i++) {
		V = vList[i].getNList();
		n = vList[i].getOutDegree();
		for (UINT32 j = 0; j < n; j++) {
			fprintf(pfile, "%llu %llu \n",i,V[j].id);
		}
	}
    fclose(pfile);
	
}

void graph::printVneighbors(vID v) {
    // Print out the neighbors for vertex v
    cout << "Vertex " << v.id << "'s neighbors are: ";
    vList[v.id].printNeighbors();
}

UINT16 graph::getVinDegree(vID v) const {
    return(vList[v.id].getInDegree());
}

UINT16 graph::getVoutDegree(vID v) const {
    return(vList[v.id].getOutDegree());
}

UINT64 graph::getVertexCount() const {
    // Return the number of vertices there are in the entire adjacency list
    return vertexCount;
}

UINT64 graph::getTotalDegree() const {
    // Return |E| - this only works for a directed graph
    return totalDegree;
}

UINT64 graph::getUnusedSpace() {
	UINT64 space = 0;
	for (int i = 0; i < vertexCount; i++) {
		space += (vList[i].getCapacity() - vList[i].getOutDegree());
	}
	
	return space;
}

vID * graph::getNList(UINT64 v) {
	return vList[v].getNList();
}

INT16 graph::getmyLevel(UINT64 v) const{
	return vList[v].getmyLevel();
}

void graph::setmyLevel(UINT64 v,INT16 lvl){
	vList[v].setmyLevel(lvl);
}

void graph::resetLvl() {
	for (UINT64 x = 0; x < vertexCount; x++){
		vList[x].setmyLevel(-1);
	}
}

void graph::printGraph() {
    // Print out the ID of each vertex that the indicated vertex points to
    for (UINT64 i = 0; i < vertexCount; i++) {
	cout << "Vertex " << i << "\tlvl: " << vList[i].getmyLevel() << endl;
	cout << "Neighbor: ";
	// vList[i].printNeighbors();
	cout << endl;
    }
}

void graph::dumpDetailGraph(char *fName) {
	vID *V;
	UINT64 *A;
	int n = 0;
	FILE * pfile;
    pfile = fopen(fName,"w");
	
	for (UINT64 i = 0; i < vertexCount; i++) {
			if(vList[i].getmyLevel()==-1){
				fprintf(pfile, "Vertex :%llu \tlvl: %hd\n",i,vList[i].getmyLevel());
	
			}
			
	}
    fclose(pfile);
	
}