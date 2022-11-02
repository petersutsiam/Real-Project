// File: graph.h
// Author: Sut Siam
// Date: 8/30/22
// Pupose:

#ifndef __BFS_H
#define __BFS_H
#include "graph.h"


	void testLinkList();

	vID *addElement2Array(vID *arr,UINT64 arrNum, vID val);

	void printArr(vID *arr,UINT64 arrNum);

	void printArr(UINT64 *arr,UINT64 arrNum);

	void hybird_BFS(vID source);

	void top_down_BFS_v1( vID source);

	void top_down_BFS_v1_2( vID source);

	void top_down_BFS_v2( vID source);

	void top_down_BFS_v3( vID source);

	void top_down_BFS_v2_2( vID source);

	void top_down_BFS_v3_2( vID source);
	
	void bottom_up_BFS_v1(vID source);

	void top_down_BFS_v3_partition(vID source);

	

#endif