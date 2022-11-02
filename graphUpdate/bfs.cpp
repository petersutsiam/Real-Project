// File: graph.cpp
// Author: Sut Siam
// Date: 8/30/22
// Pupose:

#include <iostream>			// Provides cout
#include "graph.h"			// Provides header file containing definitions
#include "bfs.h"
#include "linkList.h"
#include <omp.h>
using namespace std;

//********HELPER FUNCTION********
void graph::testLinkList(){
    linkedList *someF = new linkedList;
    linkedList *secF = new linkedList;
    vID tmp;
   
    for (int x = 0; x < 10; x++){
        tmp.id = x;
        someF -> add(tmp);
        tmp.id = 4 * 3 + x;
        secF -> add (tmp);
    }

    cout << "Before deletePOP" << endl;
    someF -> printIt();
    someF -> deletePop();
    someF -> deletePop();
    someF -> deletePop();
    someF -> deletePop();

    cout << "After deletePOP" << endl;
    someF -> printIt();

     cout << "secF" << endl;
    secF -> printIt();

    someF -> addLinkList(secF);
    cout << "After addtList" << endl;
    someF -> printIt();


    someF -> clear();

    someF -> printIt();
}

vID * graph::addElement2Array(vID *arr,UINT64 arrNum, vID val){
    vID * rc = new vID[arrNum+1];
    UINT64 x = 0;
    while (x < arrNum){
        rc[x] = arr[x];
        x++;
    }
    rc[arrNum] = val;
    
    return rc;
}

void graph::printArr(vID *arr, UINT64 arrNum){
    for( UINT64 xt = 0; xt < arrNum; xt++){
                    cout << "Index: "<< xt << " val: " << arr[xt].id << endl;
                }
}

void graph::printArr(UINT64 *arr, UINT64 arrNum){
    for( UINT64 xt = 0; xt < arrNum; xt++){
                    cout << "Index: "<< xt << " val: " << arr[xt] << endl;
                }
}

void graph::hybird_BFS(vID source){
    
        //number of unvisited verticiess
    UINT64 unVisited = 0;
    UINT64 levelCount = 0;
    UINT64 btmUP = 0;
    UINT64 tpDwn = 0;
    UINT64 stepCount = 0;
    UINT64 mU = 0;

    //parent[:] ← −1, 
    INT64 *parent = new INT64[vertexCount];
    INT16 level = 0;
    
    //Track the vertices if visited or not
    bool *traceVid = new bool[vertexCount];
    
    for (int x = 0; x < vertexCount; x++){
        parent[x]=-1;
        traceVid[x] = false;
        mU += vList[x].getOutDegree();
    }
    cout << "This is mU: " << mU << endl;
    
    //parent[s] ← s
    parent[source.id] = level;
    level = 1;

    //frontier ← null, 
    UINT64 frontierSize = 1;
    vID *frontier = new vID[frontierSize];

    //push s -> frontier
    frontier[0] = source;

    //next ← null
    vID *next;
    UINT64 nextSize = 0;

    

    //while frontier is not empty
    while (frontier != NULL){


        //nF - the number of vertices in Frontier
        //eF - the number of edges in Frontier
        //k - average degree
        //UINT64 nF = frontierSize;
        UINT64 mf = 0;
        // for(UNIT64 tph; tph < frontierSize;tph++){
        //     eF =+ getOutDegree(tph);
        // }
        
        //UNIT64 k = eF/nF;
        // // UNIT64 c1=n/(2*k);
       // UINT64 c2=2*nF;
        // UNIT64 c3=nF/(2*k);
        // UNIT64 pred = 0;
            for(UINT64 po = 0; po < frontierSize; po++){
                mf += vList[frontier[po].id].getOutDegree();
            }
        
            
        if(mf <= mU ){

            tpDwn++;
            /*TOP DOWN */
            //each u in frontier
            for(UINT64 u = 0; u < frontierSize;u++){

                //
                mU-=vList[frontier[u].id].getOutDegree();
                
                //mark the vertice visited
                traceVid[u]= true;

                vID *ulist;
                ulist = getNList(frontier[u].id);
                UINT16 ulistSize = vList[frontier[u].id].getCapacity();
            
                //each neighbor v of u
                for(UINT16 v =0; v<ulistSize;v++){
                    

                    //parent[v] = −1
                    if (parent[ulist[v].id] == -1){

                        //push v -> next[]

                        if(nextSize==0){
                            next = new vID[1];
                            next[0] = ulist[v];
                            nextSize++;
                        }else{
                            UINT16 tempSize = nextSize+1;
                        vID *temp = new vID[tempSize];
                        for(UINT16 ye = 0; ye >nextSize; ye++){
                            temp[ye] = next[ye];
                        }
                        nextSize++;
                        next = temp;
                        next[nextSize-1]=ulist[v];
                        
                        }
                        //parent[v] set to level
                        parent[ulist[v].id] = level;
                        if(level > levelCount){
                            levelCount = level;
                        }
                    }
                }
            
            }
        }else{

            btmUP++;
            /*BOTTOM UP */
            //each u in V
            for(UINT64 u = 0; u < vertexCount;u++){
                
                vID uTemp = vID();
                uTemp.id = u;

                vID *ulist;
                ulist = getNList(u);
                UINT64 ulistSize = vList[u].getOutDegree();

                //parent[u] = −1
                if (parent[u] == -1){
                    

                    //each neighbor v of u
                    for(UINT64 v =0; v<ulistSize;v++){


                        bool result =false;
                        
                        for(UINT32 fo=0; fo<frontierSize;fo++){

                            if(ulist[v].id==frontier[fo].id){
                                result = true; 
                                break;
                            }
                            
                        }
                        
                        //if v in frontier
                        if(result){

                            //push u -> next[]
                            if(nextSize==0){
                                next = new vID[1];
                                next[0] = uTemp;
                                nextSize++;
                            }else{
                                UINT16 tempSize = nextSize+1;
                            vID *temp = new vID[tempSize];
                            for(UINT16 ye = 0; ye >nextSize; ye++){
                                temp[ye] = next[ye];
                            }
                            nextSize++;
                            next = temp;
                            next[nextSize-1]=uTemp;
                            
                            }
                        
                            //parent[u] set to level
                            parent[u] = level; 
                            if(level > levelCount){
                            levelCount = level;
                            }
                            break;
                        }
                    }
                }
                
            }

        }
    
        //set frontier to next
        frontier = next;
        frontierSize = nextSize;
        level++;

        //empty next
        next = NULL;
        nextSize = 0; 

       
    } 
    
     //stepCount Increment
        stepCount = btmUP + tpDwn;;   

        for(UINT64 jo = 0; jo < vertexCount; jo++){
            if(traceVid[jo]){
                unVisited++;
            }

        }

        cout << "Hybird BFS" << endl;
        cout << "This is mU: " << mU << endl;
        cout << "Highest Level : " << levelCount << endl;
        cout << "Step Count : " << stepCount << endl;
         cout << "Topdown Count : " << tpDwn << endl;
          cout << "BottomUp Count : " << btmUP << endl;
        cout << "UnVisited Verticies : " << unVisited << endl;

}


//********Top-Down FUNCTION********
void graph::top_down_BFS_v1( vID source){

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    cout << "\n-----Top-down BFS------" << endl;
    //---contruct Global variable---
    
    //reset all vertex visited to -1
    resetLvl();

    //declare level
    INT64 level = 0;
    
    //soure visited = 0
    setmyLevel(source.id,level);

    //create vID array of frontier with size one and set it to source
    //frontier ← null, 
    UINT64 frontierSize = 1;
    vID *frontier = new vID[frontierSize];
    frontier[0] = source;

    //create a global vID array of next 
    vID *next;
    UINT64 nextSize = 0;
    UINT64 nextNum = 0;
    \

    //---Computation---

    //while frontier is not empty
    while (frontier != NULL){
        
        //increment level
        level++;

        // cout << "Frontier LVL " << level << endl;
        
        //each vertex u in frontier
        for(UINT64 u = 0; u < frontierSize;u++){

            //create temp vID array to accomade the neighbor of u
            vID *ulist;
            UINT64 uID = frontier[u].id;

            ulist = getNList(uID);
            UINT64 ulistSize = vList[uID].getOutDegree();

            //each neighbor v of ulist
            for(UINT64 v =0; v<ulistSize;v++){
                // cout << "\tvID: " << ulist[v].id << endl;

                //parent[v] = −1 not visited
                if (getmyLevel(ulist[v].id) == -1){

                    // cout << "\t\tNOT VISITED" << endl;
                    //push v -> next[]
                    
                    bool inList = false;

                        //next array empty
                        if(nextNum==0){
                            next = new vID[ulistSize];

                        //add new item to next
                        }else{
                            
                            if(ulistSize == nextNum){
                                UINT64 tmpSize = nextNum+1;
                                vID *tmp = new vID[tmpSize];
                                UINT64 x = 0;
                                while ( x <nextNum ){
                                    tmp[x] = next[x];
                                    if (tmp[x].id == ulist[v].id){
                                        inList = true;
                                    }
                                    x++;
                                }
                            }
                           
                        }
                        if(!inList){
                                next[nextNum] = ulist[v];
                                nextNum++;
                            }
        
                        //parent[v] set to level
                        setmyLevel(ulist[v].id,level);
                }
            }          
        }

        frontier = NULL;

        //set frontier to next
        frontier = next;
        frontierSize = nextNum;

        //RESET next
        next = NULL;  
        nextNum = 0; 
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;


    //--Data print out---    
    cout << "Level : " << level << endl;
    cout << "Time elapse: " << exec_time << endl;
    cout << endl;
    //--Deconstruct---
    delete[] next;
    delete[] frontier;

}

//frontier with list link structure
void graph::top_down_BFS_v1_2( vID source){
    
    cout << "\n-----Top-down BFS linkList on Frontier/ Next------" << endl;

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    
    //---contruct Global variable---

    //reset all vertex visited to -1
    resetLvl();

    //declare level
    INT64 level = 0;
    
    //soure visited = 0
    setmyLevel(source.id,level);

    //create vID of frontier with size one and set it to source
    //LinkList of frontier
    linkedList *frontier = new linkedList;
    frontier->clear();
    frontier->add(source);

    //next
    linkedList *next = new linkedList;
    next->clear();

    //---Computation--- 
    
    //while frontier is not empty
    while (frontier->countReturn() != 0){

        //Increment level
        level++;

        UINT64 frontierSize = frontier->countReturn();
        
        //each u in frontier
        for(UINT64 u = 0; u < frontierSize; u++){
            
            //create temp vID array to accomade the neighbor of u
            vID *ulist;
            UINT64 uID = frontier->readAt(u).id;
            
            // cout << "uID: " << uID << endl;

            ulist = getNList(uID);
            UINT64 ulistSize = vList[uID].getOutDegree();
            
            //each neighbor v of ulist
                for(UINT64 v =0; v<ulistSize;v++){
                //  cout << "\tvID: " << ulist[v].id << endl;

                    //parent[v] = −1 not visited
                    if (getmyLevel(ulist[v].id) == -1){
                        // cout << "\t\tNot visided" << endl;
                        //parent[v] set to level
                        setmyLevel(ulist[v].id,level);
                        //next->add(ulist[v]);
                        frontier->add(ulist[v]);
                        

                    }   
                   
                }  
                 frontier->deletePop();
        }   
        //frontier->setLinkList(next);
            
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    
    //--Data print out---    

    cout << "Level : " << level << endl;
    cout << "Time elapse: " << exec_time << endl;

    //deconstructer
    frontier->clear();
    next->clear();
    delete frontier;
    delete next;

}

//Single Thread
void graph::top_down_BFS_v2( vID source){

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    cout << "-----Top-down BFS Sing Thread------" << endl;
    //---contruct Global variable---

    //reset all vertex visited to -1
    resetLvl();

    //declare level
    INT64 level = 0;

    //soure visited = 0
    setmyLevel(source.id,level);

    //create vID array of frontier with size one and set it to source
    //frontier ← null, 
    UINT64 frontierSize = 1;
    vID *frontier = new vID[frontierSize];
    frontier[0] = source;

    //create a global vID array of next 
    vID *next;
    UINT64 nextSize = 0;
    UINT64 nextNum = 0;

    //---Computation---

    //while frontier is not empty
    while (frontier != NULL){
       
        //increment level
        level++;

        //Single thread 
        #pragma omp parallel num_threads(1)
        {
            
            //each vertex u in frontier
            for(UINT64 u = 0; u < frontierSize;u++){

                //create temp vID array to accomade the neighbor of u
                vID *ulist;
                ulist = getNList(frontier[u].id);
                UINT64 ulistSize = vList[frontier[u].id].getOutDegree();

                vID *temp;
                UINT64 tempSize;

                //each neighbor v of ulist
                for(UINT64 v =0; v<ulistSize;v++){

                    //parent[v] = −1 not visited
                    if (getmyLevel(ulist[v].id) == -1){

                        //push v -> next[]

                            //next array empty
                            if(nextNum==0){
                                next = new vID[ulistSize];
                                next[0] = ulist[v];
                                nextNum++;

                            //add new item to next
                            }else{
                                if(ulistSize == nextNum){
                                    next = addElement2Array(next,nextNum,ulist[v]);
                                }else{
                                    next[nextNum] = ulist[v];
                                }
                                nextNum++;
                            }
                            //parent[v] set to level
                            setmyLevel(ulist[v].id,level);
                    }
                }
             
            }
        }
        
        //set frontier to next
        frontier = next;
        frontierSize = nextNum;

        //RESET next
        next = NULL;  
        nextNum = 0; 
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    

    //--Data print out---    
    cout << "Level : " << level << endl;
    cout << "Time elapse: " << exec_time << endl;

    //--Deconstruct---
    delete [] next;
    delete [] frontier;

}

//single thread
//frontier with list link structure
void graph::top_down_BFS_v2_2( vID source){
    
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    
    cout << "-----Top-down BFS linkList on Frontier/ Next------" << endl;

    //---contruct Global variable---   

    //reset all vertex visited to -1
    resetLvl();

    //declare level
    INT64 level = 0;

    //soure visited = 0
    setmyLevel(source.id,level);

    //create vID of frontier with size one and set it to source
    //LinkList of frontier
    linkedList *frontier = new linkedList;
    frontier->clear();
    frontier->add(source);

    //---Computation--- 

    //while frontier is not empty
    while (frontier->countReturn() != 0){

        //Increment level
        level++;

        //Single thread 
        #pragma omp parallel num_threads(1)
        {

            UINT64 frontierSize = frontier->countReturn();

            //each u in frontier
            for(UINT64 u = 0; u < frontierSize; u++){
                
                //create temp vID array to accomade the neighbor of u
                vID *ulist;
                UINT64 uID = frontier->readAt(0).id;

                ulist = getNList(uID);
                UINT64 ulistSize = vList[uID].getOutDegree();
                
                //each neighbor v of ulist
                    for(UINT64 v =0; v<ulistSize;v++){

                        //parent[v] = −1 not visited
                        if (getmyLevel(ulist[v].id)  == -1){
                            
                            //add vID to frontier
                            frontier->add(ulist[v]);

                            //parent[v] set to level
                            setmyLevel(ulist[v].id,level);
                        }
                    }

                //since already visited frontier of u, pop off
                frontier->deletePop();
            }
        }
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    

    //--Data print out---    
    cout << "-----Top-down BFS linkList on Frontier/ Next------" << endl;
    cout << "Level : " << level << endl;
    cout << "Time elapse: " << exec_time << endl;
    
    //deconstructor
    delete frontier;

}

//Parallel
void graph::top_down_BFS_v3( vID source){
    //---contruct Global variable---

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    cout << "-----Top-down BFS-Top-Down multil-threading------" << endl;
    //extra variable of count
   
    INT64 level = 0;

    //reset all vertex visited to -1
    resetLvl();

    //soure visited = 0
    setmyLevel(source.id,level);

    //create vID array of frontier with size one and set it to source
    //frontier ← null, 
    UINT64 frontierSize = 1;
    vID *frontier = new vID[frontierSize];
    frontier[0] = source;

    //create a global vID array of next 
    UINT64 nextNum = 0;
    vID *next;
    

    //---contruct local variable---
    //create a global vID array of local_next 
    vID *local_next;
    UINT64 local_nextNum;
    

    //---Computation---

    //while frontier is not empty
    while (frontier != NULL){
        
        //increment level
        level++;

        #pragma omp parallel private(local_next, local_nextNum) shared(next, nextNum) 
        { 
          
            //declare local varable
            local_next= NULL;
            local_nextNum = 0; 
            
            //the array is distributde statically between threads
            #pragma omp for collapse(2) 
            //each vertex u in frontier
            for(UINT64 u = 0; u < frontierSize;u++){

                //create temp vID array to accomade the neighbor of u
                vID *ulist;
                ulist = getNList(frontier[u].id);
                UINT64 ulistSize = vList[frontier[u].id].getOutDegree();
                
                //each neighbor v of ulist
                for(UINT64 v =0; v<ulistSize;v++){
                    
                    //parent[v] = −1 not visited
                    if (getmyLevel(ulist[v].id) == -1){

                        //push v -> next[]

                            //next array empty
                            if(local_nextNum==0){
                                local_next = new vID[ulistSize];
                                local_next[0] = ulist[v];
                                local_nextNum++;
                               
                            //add new item to next
                            }else{
                            
                                //if nextSize if full
                                if(local_nextNum == ulistSize){
                                    local_next = addElement2Array(local_next,local_nextNum,ulist[v]);
                                }else{
                                    local_next[local_nextNum] = ulist[v];
                                }
                                local_nextNum++;
                            }                       
                            
                            //parent[v] set to level
                            setmyLevel(ulist[v].id,level);                 
                    }
                }   

                //update the global next
                #pragma omp critical
                {
                        //next is empty
                        if(nextNum == 0){
                            next = local_next;
                            nextNum = local_nextNum;

                        }else{
                            bool match = false;
                            for(UINT64 xp = 0; xp < local_nextNum; xp++){
                                for(UINT64 ap = 0; ap < nextNum; ap ++){
                                    if(next[ap].id == local_next[xp].id){
                                        match = true;
                                    }
                                }
                                if(!match){
                                    next=addElement2Array(next,nextNum,local_next[xp]);
                                    nextNum++;
                                }
                            }
                            
                        }
                }
            }
        }
        //END of Parallel
       
        //set frontier to next
        frontier = next;
        frontierSize = nextNum;

        //RESET next
        next = NULL; 
        nextNum = 0;
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    //--Data print out---    
    
    cout << "Level : " << level << endl;
    cout << "Time elapse: " << exec_time << endl;
    
    //--Deconstruct---
    delete [] next;
    delete [] frontier;

}

//frontier with list link structure
void graph::top_down_BFS_v3_2( vID source){

     cout << "-----Top-down BFS linkList Multi-Thread on Frontier/ Next------" << endl;
    
    double itime, ftime, exec_time;
    itime = omp_get_wtime();   
    
    //---contruct Global variable---    

    //reset all vertex visited to -1
    resetLvl();

    //declare level
    INT64 level = 0;
    
    //soure visited = 0
    setmyLevel(source.id,level);

    //create vID of frontier with size one and set it to source
    //LinkList of frontier
    linkedList *frontier = new linkedList;
    
    frontier->add(source);

    linkedList *nextGbl = new linkedList;
    

    //---Computation--- 

    //while frontier is not empty
    while (frontier->countReturn() != 0){

        //Increment level
        level++;
       
        //set frontierSize
        UINT64 frontierSize = frontier->countReturn();

       
        #pragma omp parallel shared(nextGbl) 
        {   
            int thread_id = omp_get_thread_num();
		    int nthreads = omp_get_num_threads();
           
            //each u in frontier
            for(UINT64 u = thread_id; u < frontierSize; u+=nthreads){
               
                //next
                linkedList *nextLocal = new linkedList;
                
                //create temp vID array to accomade the neighbor of u
                vID *ulist;
                UINT64 uID = frontier->readAt(u).id;
                
                // cout << "Frontier of: " << uID << endl;

                ulist = getNList(uID);
                UINT64 ulistSize = vList[uID].getOutDegree();
                
                //each neighbor v of ulist
                    for(UINT64 v =0; v<ulistSize;v++){

                        //parent[v] = −1 not visited
                        if (getmyLevel(ulist[v].id) == -1){
                            
                                //parent[v] set to level
                                setmyLevel(ulist[v].id,level);
                                nextLocal->add(ulist[v]); 
                            }  
                    }

                //update the global next
                #pragma omp critical 
                {    
                     cout << "THreads num: " << omp_get_num_threads()<< endl;
                    //copy next array into frontier
                    cout << "nextLocal Size: " << nextLocal->countReturn() << endl;
                    nextGbl -> addLinkList(nextLocal);
                    
                    delete nextLocal;
                           
                }
            }
        }   

            //set frontier to nextGbl
            frontier -> setLinkList(nextGbl);
            

    }


    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    //--Data print out---    
   
    cout << "Level : " << level << endl;
    cout << "Time elapse: " << exec_time << endl;
    
    //deconstructor
    delete frontier;
    delete nextGbl;
}

//********Bottom-up FUNCTION********
void graph::bottom_up_BFS_v1( vID source){

    // clock_t clock0 = clock();//Start of the program

    //parent[:] ← −1, 
    INT64 *parent = new INT64[vertexCount];
    INT64 level = 0;

    for (int x = 0; x < vertexCount; x++){
        parent[x]=-1;
    }

    //parent[s] ← s
     parent[source.id] = level;
     level = 1;

    //frontier ← null, 
    UINT64 frontierSize = 1;
    vID *frontier = new vID[frontierSize];

    //push s -> frontier
    frontier[0] = source;

    //next ← null
    vID *next;
    UINT64 nextSize = 0;

    UINT64 unVisited = vertexCount;
    UINT64 levelCount = 0;
    UINT64 stepCount = 0;


    //while frontier is not empty
    while (frontier != NULL){
       
        //each u in V
        for(UINT64 u = 0; u < vertexCount;u++){
            
            vID uTemp = vID();
            uTemp.id = u;

            vID *ulist;
            ulist = getNList(u);
            UINT64 ulistSize = vList[u].getOutDegree();

            //parent[u] = −1
            if (parent[u] == -1){
                

                //each neighbor v of u
                for(UINT64 v =0; v<ulistSize;v++){
                   
                    bool result =false;
                    
                    for(UINT64 fo=0; fo<frontierSize;fo++){

                        if(ulist[v].id==frontier[fo].id){
                            result = true; 
                            break;
                        }
                    }
                    
                    //if v in frontier
                    if(result){

                        //push u -> next[]
                        if(nextSize==0){
                            next = new vID[1];
                            next[0] = uTemp;
                            nextSize++;
                        }else{
                            UINT64 tempSize = nextSize+1;
                        vID *temp = new vID[tempSize];
                        for(UINT64 ye = 0; ye >nextSize; ye++){
                            temp[ye] = next[ye];
                        }
                        nextSize++;
                        next = temp;
                        next[nextSize-1]=uTemp;
                        }
                        
                        //parent[u] set to level
                        parent[u] = level; 
                        if(level > levelCount){
                        levelCount = level;
                        }
                        
                        break;
                    }
                }
            }
            
        }
        //decrement unvisited count
        unVisited -= frontierSize;
        //set frontier to next
        frontier = next;
        frontierSize = nextSize;
        level++;

        //empty next
        next = NULL;
        nextSize = 0;  
        stepCount++;  
    } 

    // clock_t clock1 = clock();//End of the program
    // float ttime = (float)(clock1 - clock0) / (float)CLOCKS_PER_SEC;
    // cout << "\n\nThe time taken to run BfS Bottom Up insde graph: " << ttime <<endl;


    // for (int x = 0; x < vertexCount; x++){
    //         cout<<"\nIndex "<<x<<" is at level = "<<parent[x];
    //     }

    cout << "Bottom-up BFS" << endl;
    cout << "Highest Level : " << levelCount << endl;
    cout << "Step Count : " << stepCount << endl;
    cout << "UnVisited Verticies : " << unVisited << endl;
}

void graph::top_down_BFS_v3_partition(vID source){
    //loop cutoff
    bool go = true;

    //set number of threads
    int num_thtreads = 4;

    //reset all vertex visited to -1
    resetLvl();

    //declare level
    INT64 level = 0;
    
    //soure visited = 0
    setmyLevel(source.id,level);

    //currL is a list of linkList
    linkedList currL [num_thtreads];
    
    //create temp vID array to accomade the neighbor of source
    vID *ulist;
    ulist = getNList(source.id);
    //set currL to the source neighborList
    UINT64 nLsize = getVoutDegree(source);

    for(UINT64 n = 0; n < nLsize; n++){
        currL[n % num_thtreads].add(ulist[n]); 
    }

    //futL is a list of linkList
    linkedList futL [num_thtreads];

    range rangeL [num_thtreads];
    
    //loop till go is false = till current list is not all NULL
    while(go){

        //generate next horizon
        for(int i = 0; i < num_thtreads; i++){
            #pragma omp parallel shared(nextGbl) {   
                for(int j = ){

                }
            }
        }

        //update bool go
        for(int i = 0; i < num_thtreads; i++){
            
            //reset go
            go = false;

            //check the array is not empty
            if(currL[i].countReturn() > 0){

                //set go to true and exit out of the update loop
                go = true;
                break;
            }
        }
    }
}