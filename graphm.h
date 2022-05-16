/*
Name: Sanket Karna
Class: CSS 343
Professor: Dong Si
Created Date: 05/01/22
Last Modification: 05/15/22
---------------------------------------------------------------------------------------------------
Purpose: The purpose of the graphm.h is to declare the fucntion defnitions, variables,
structs that is going to be implemened in graphm.cpp. These method and fucntions help make a
Graph of the nodes provided by the input file. These nodes are connected in a graph, and the main
purpose of this graphm is to implement the Dijkstra's greedy shortest path algorithm between one
node to another. Once the shortest path is found for each node, the algorithm end and displays it.
---------------------------------------------------------------------------------------------------
Inclusion of <iomanip> helps with setting the width of the output.
All inputs are assumed to be valid with a .txt file
*/
#pragma once

#include "nodedata.h"
#include <iostream>
#include <iomanip>
#include "limits.h"

using namespace std;

class GraphM 
{
    public:

        GraphM(); // default constructor
        void buildGraph(ifstream &in); // builds the graph
        bool insertEdge(int start, int end, int weight); // insert edge in the graph
        bool removeEdge(int start, int end); // remove edge from the graph
        void findShortestPath(); // Dijkstra's algorithm
        void displayAll() const; // displays the algorithm is working
        void display(const int start, const int end) const; // displays path between nodes

    private:
        struct TableType 
        {
            bool visited; // memeber variable to mark nodes visited
            int dist; // memeber variable to keep track of distance between two nodes
            int path; // member varibale to keep track of the previous min dist
        };

        const static int MAXNODES = 101; // max nodes is 100, 101 to account for index 0

        NodeData data[MAXNODES]; // data for the nodes
        int C[MAXNODES][MAXNODES]; // adjancy matric
        int size; // number of nodes in data
        TableType T[MAXNODES][MAXNODES]; // stores visited, distance and path

        int findNext(TableType other[]); // finds the next node in the table
        void findPath(int start, int end) const; // find poth between two nodes
        void findData(int start, int end) const; // finds data between two nodes

};

