#pragma once

#include "nodedata.h"
#include <iostream>
#include <iomanip>
#include "limits.h"

using namespace std;

class GraphM 
{
    public:

        GraphM();
        void buildGraph(ifstream &in);
        bool insertEdge(int start, int end, int weight);
        bool removeEdge(int start, int end);
        void findShortestPath();
        void displayAll() const;
        void display(const int start, const int end) const;

    private:
        struct TableType 
        {
            bool visited;
            int dist;
            int path;
        };

        const static int MAXNODES = 101;

        NodeData data[MAXNODES];
        int C[MAXNODES][MAXNODES];
        int size;
        TableType T[MAXNODES][MAXNODES];

        int findNext(TableType other[]);
        void findPath(int start, int end) const;
        void findData(int start, int end) const;

};