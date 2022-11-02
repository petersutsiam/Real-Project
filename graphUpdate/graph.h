// File: graph.h
// Author: Dr. Stephen Wheat, Austin Lehman, Samuel Udall, Michael Vandusen, Andrew Westlund
// Date: 1/31/22
// Pupose: This program will recieve a graph and will create a list of all the vertices
// and will list all the vertices adjacent to each vertex.
// The both the list and the lists of adjacent vertices will be dynamically allocated
// and will be sorted least to greatest. 

#ifndef __GRAPH_H
#define __GRAPH_H

// Create typedefs for variables
typedef unsigned long long UINT64;
typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;

typedef long long INT64;
typedef int INT32;
typedef short INT16;
typedef char INT8;

class vID {
    public:
	UINT64 id;
};

class vertex {
    private:
	vID *nList;	// An array of vertex ID objects (neighbor list for a given index).	
	UINT16 inDegree;	// The count of incoming egdes.
	UINT16 outDegree;	// The count of outgoing egdes.
	UINT16 capacity;	// The capacity of the vertex array.
	UINT16 myPos;		// Identifies where this vertex should be in the nList if it were there.
	INT16 myLevel;		// The generation level from source
	UINT16 dummy;
	UINT16 dummy2;
	UINT16 dummy3;
	vID *dummyList;			//cap
	



	// Preconditions: vID v is not already on the adjacency list
	// Postconditions: Will insert the vID to the adjacency list in ascending order
	bool addNeighbor0(vID v);
	
    public:
	// Constructor of an object to hold an array of vertices and related variables
	vertex();
	~vertex();

	// Preconditions: None.
	// Postconditions: Initializes the nList, setting all values to zero or null.
	void initVertex();
		
	// Preconditions: None.
	// Postconditions: Clears the nList and resets the stored values.
	void clearVertex();
	
	// Preconditions: none
	// Postconditions: increments myPos 
	void incPos();
	
	// Preconditions: none
	// Postconditions: decrements myPos
	void decPos();

	// Preconditions: None. 
	// Postconditions: Will return the position of the indicated vertex if it is in this vertex's 
	// adjacency list; will return -1 if it is not in the vertex's adjacency list.
	INT16 isNeighbor(vID v);
	
	// Preconditions: None
	// Postconditions: Will check if the vertex is already on the vertex's adjacency list;
	// if the vertex is not already on it, it then checks if there is free space on the list, if there is no free space,
	// it will increase the capacity by two, then it calls addNeighbor0 to add the vID.
	bool addNeighbor1(vID v, INT16 a);
	
	// Preconditions: None
	// Postconditions: Will return true if the vertex is on the vertex's adjacency list and then 
	// removes it; if it is not on the list, will return false.
	bool delNeighbor(vID n);
	
	// Preconditions: None.
	// Postconditions: Will increase the value of the indegree of the vertex getting pointed to by one.
	void incInDegree();
	
	// Preconditions: None.
	// Postconditions: Will decrease the value of the indegree of the vertex getting pointed to by one.
	void decInDegree();
	
	// Preconditions: None.
	// Postconditions: Will print the list of adjacent vertices.
	void printNeighbors();
	
	// Preconditions: None
	// Postconditions: Returns the vertex's in degree
	UINT16 getInDegree();

	// Preconditions: None
	// Postconditions: Returns the vertex's out degree
	// return -1.
	UINT16 getOutDegree();

    // Preconditions: None
    // Postconditions: Returns the capacity of  the nList
    UINT16 getCapacity() const;
	
	vID * getNList() const;

	INT16 getmyLevel() const;

	void setmyLevel(INT16 lvl);

	


};

class graph {
    private:
	vertex *vList;		// An array of vertex objects.
	UINT64 vertexCount;	// Stores how many vertices there are in the graph
	UINT64 totalDegree;	// Stores how many edges there are in the graph
	INT16 allocation;   // The value of how much the vertex capacity increments by
	bool loops;
	
    public:
	// Constructor
	graph(UINT64 numberOfVertices);
	
	// Destructor
	~graph();

	// Preconditions: None.
	// Postconditions: clears the graph and resets all values of all nLists.
	void clear();
	
	// Preconditions: None.
	// Postconditions: Clears the nList and resets the stored values of vID v.
    void clearNlist(vID v);
	
	// Preconditions: None.
	// Postconditions: Will set allocation to a if a is between 1 and 16; if under 1, will be set to 1
	// and if over 16 will be set to 16
	void setAllocation(INT16 a);

	// Preconditions: vertex(u) and vertex(v) must be existing vertices
	// Postconditions: If the edge does not already exist, a new edge is added that 
	// points from vertex(u) to v(v), the edge array for vertex(u) grows, the corresponding 
	// values, i.e. inDegree, are incremented accordingly, and true is returned.
	// Otherwise, return false.
	bool addEdge(vID u, vID v);
	
	// Preconditions: v(u) and v(v) must be existing vertices
	// Postconditions: If the edge already exists, the edge that points from vertex(u) to 
	// vertex(v) is removed, the edge array for vertex(u) shrinks, the corresponding values, 
	// i.e. inDegree, are decremented accordingly, and true is returned.
	// Otherwise, return false.
	bool delEdge(vID u, vID v);
	
	// Preconditions: None. 
	// Postconditions: Will return the position of the indicated vertex if it is in this vertex's 
	// adjacency list; will return -1 if it is not in the vertex's adjacency list.
	bool isEdge(vID u, vID v);
	
	void dumpGraph();
	
	// Preconditions: vNum must be the id of a vertex on the graph.
	// Postconditions: The vertex's neighbors are printed.
	void printVneighbors(vID v);
	
	// Preconditions: None.
	// Postconditions: Returns the vertex indegree
	UINT16 getVinDegree(vID v) const;

	// Preconditions: None.
	// Postconditions: Returns the vertex outdegree
	UINT16 getVoutDegree(vID v) const;

	// Preconditions: None
	// Postconditions: Returns |V|
	UINT64 getVertexCount() const;

	// Preconditions: None
	// Postconditions: Returns |E|
	UINT64 getTotalDegree() const;
	
	UINT64 getUnusedSpace();
	
	vID * getNList(UINT64 v);

	INT16 getmyLevel(UINT64 v) const;

	void setmyLevel(UINT64 v,INT16 lvl);

	void resetLvl();
	
	// Preconditions: None.
	// Postconditions: Will print the list of all vertices and their adjacent vertices.
	void printGraph();

	void dumpDetailGraph(char *fName);

	#include "bfs.h"
};

#endif
