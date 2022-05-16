/*
Name: Sanket Karna
Class: CSS 343
Professor: Dong Si
Created Date: 05/01/22
Last Modification: 05/15/22
---------------------------------------------------------------------------------------------------
Purpose: The purpose of the graphm.l is to define methods, fucntions, structs and memeber variables 
for it to be implemented in graphl.cpp. Graphl is similar to Graphm in a sense that with the input
file a Graph is created with nodes and information about the nodes. However, this in GraphL we 
implement the Depth First Search algorithm and display that to the console
---------------------------------------------------------------------------------------------------
Inclusion of <iomanip> helps with setting the width of the output.
All inputs are assumed to be valid with a .txt file
*/

#pragma once 

#include <iostream>
#include "limits.h"
#include "iomanip"
#include "nodedata.h"

class GraphL
{
    public:

        GraphL(); // default constructor
        ~GraphL(); // destructor

        void buildGraph(ifstream &in); // builds the graph
        void depthFirstSearch(); // depth first search algorithm
        void displayGraph() const; // displays the graph

    private:
        
        static const int MAX = 101; // max nodes is 100, 101 to account for index 0

        struct EdgeNode; // reference for compiler

        struct GraphNode  
        {
            EdgeNode* edgeHead; // head of the edge list
            NodeData* data; // data of the list of edges
            bool visited; 
        };

        struct EdgeNode
        {
            int adjGraphNode;
            EdgeNode* nextEdge;
        };

        GraphNode arr[MAX]; // array with the nodes
        int size; // size of the nodes in the graph
        void destroy(); // helper for destructor
        void dfsHelper(int index); // helper for depth first search
};