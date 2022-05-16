/*
Name: Sanket Karna
Class: CSS 343
Professor: Dong Si
Created Date: 05/01/22
Last Modification: 05/15/22
---------------------------------------------------------------------------------------------------
Purpose: The purpose of the graphm.cpp is to implement the method and fucntion definitions that 
were in written in graphm.h. These method and fucntions help make a Graph of the nodes provided by the 
input file. These nodes are connected in a graph, and the main purpose of this graphm is to implement 
the Dijkstra's greedy shortest path algorithm between one node to another. Once the shortest path is 
found for each node, the algorithm end and displays it.
---------------------------------------------------------------------------------------------------
Inclusion of <iomanip> helps with setting the width of the output.
All inputs are assumed to be valid with a .txt file
*/
#include "graphm.h"

/*
----------------------------------Default constructor----------------------------------------------
This constructor for the empty matric table to initialize all the values
---------------------------------------------------------------------------------------------------
*/
GraphM::GraphM()
{
    this->size = 0;

    for(int i =1; i < MAXNODES; i++)
    {
        for(int j = 1; j < MAXNODES; j++)
        {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }
}

/*
----------------------------------buildGraph------------------------------------------------------
Builds a graph by the input from the text file, fills the adjancy matrix and wright for each node
---------------------------------------------------------------------------------------------------
*/

void GraphM::buildGraph(ifstream &in)
{
    int start, end, weight; // 3 varibales from the input file
    string input;
    in >> this->size;
    getline(in, input); // gets the input line by line

    for(int i = 1; i <= size; i++) // loop to set the data in the table
    {
        data[i].setData(in);
    }

    while(in >> start >> end >> weight) // fills weight between two nodes 
    {
        if(start == 0)
        {
            break;
        }
        this->C[start][end] = weight;
    }
}

/*
----------------------------------insertEdge------------------------------------------------------
Creates and inserts a edge between two given nodes, and then also sets the weight of that node
---------------------------------------------------------------------------------------------------
*/

bool GraphM::insertEdge(int start, int end, int weight)
{
    if(start > this->size || start < 1) // cant insert if begin node is > size or < 1
    {
        return false;
    }
    else if(end > this->size || end < 1) // cant insert if end node is > size or < 1
    {
        return false;
    }
    else if(start == end && weight != 0) // cant insert if start = end and weight isnt 0
    {
        return false;
    }
    else if (weight < 0) // cant insert if the weight is negative
    {
        return false;
    }
    else 
    {
        this->C[start][end] = weight; // once all edge cases are passed
        return true;
    }
}

/*
----------------------------------removeEdge------------------------------------------------------
Removes edge between two given nodes
---------------------------------------------------------------------------------------------------
*/

bool GraphM::removeEdge(const int start, const int end)
{
    if(start < 1 || start > this->size) // cant remove is start < 1 and start > size
    {
        return false;
    }
    else if ( end < 1 || end > this->size) // cant remove is ebd < 1 and end > size
    {
        return false;
    }
    else if (this->C[start][end] == INT_MAX) // cant remove is the give edge is infinite
    {
        return false;
    }
    else 
    {
        this->C[start][end] == INT_MAX; // once all edge cases are passes
        return true; 
    }
}

/*
---------------------------------------findShortestPath()-------------------------------------------------
This algorithm find the shortest path between two nodes by using Dijkstra's greedy algorithm
---------------------------------------------------------------------------------------------------
*/

void GraphM::findShortestPath()
{
    int nextVisit = 0; // helper variables
    int loop = 1;

    for(int i = 1; i <= size; i++)
    {
        for(int j = 1; j <= size; j++)
        {
            T[i][j].visited = false; // fill all the visited with false
        }
    }

    for(int first = 1; first <= size; first++)
    {
        T[first][first].dist = 0; // first node has a dist of 0

        while(loop != size)
        {
            nextVisit = findNext(T[first]); // finds the next node from the first node that is the shortest
            T[first][nextVisit].visited = true; // visited

            for (int i =1; i <= size; i++)
            {
                if(!T[first][i].visited && C[nextVisit][i] != INT_MAX) // if the next node isnt visited
                {
                    if(T[first][i].dist > T[first][nextVisit].dist + C[nextVisit][i]) 
                    {
                        T[first][i].dist = T[first][nextVisit].dist + C[nextVisit][i];
                        T[first][i].path = nextVisit;
                    }
                }
            }
            loop++; // loop moves forward
        }
    loop = 1;
    }
}

/*
----------------------------------findNext------------------------------------------------------
Find the next node in the graph from the current node, that is the shortest
---------------------------------------------------------------------------------------------------
*/

int GraphM::findNext(TableType other[])
{
    int next = 1;
    int inf = INT_MAX; // helper varible

    for(int i = 1; i <= size; i++) // for loop searches the next node
    {
        if(other[i].dist < inf && !(other[i].visited))
        {
            next = i;
            inf = other[i].dist;
        }
    }
    return next;
}

/*
----------------------------------findPath------------------------------------------------------
Finds a path between two given ndoes
---------------------------------------------------------------------------------------------------
*/

void GraphM::findPath(int start, int end) const
{
    if(T[start][end].dist == INT_MAX) 
    {
        return;
    }
    else if(start == end)
    {
        cout << end << " ";
        return;
    }
    else 
    {
        int path = end;
        findPath(start, end = T[start][end].path);
        cout << path << " ";
    }
}

/*
----------------------------------findPath------------------------------------------------------
Finds a path between two given ndoes
---------------------------------------------------------------------------------------------------
*/

void GraphM::findData(int start, int end) const
{
    if(T[start][end].dist == INT_MAX)
    {
        return;
    }
    else if(start == end)
    {
        cout << data[end] << endl;
        return;
    }
    else 
    {
        int temp = end;
        findData(start, end = T[start][end].path);
        cout << data[temp] << endl << endl;
    }
}

/*
----------------------------------displayAll------------------------------------------------------
Displays all the information of the shortest path between the nodes
---------------------------------------------------------------------------------------------------
*/

void GraphM::displayAll() const
{
    cout << "Description" << setw(20) << "From Node" << setw(12) << "To Node";
    cout << setw(14) << "Dijkstra's" << setw(8) << "Path" << endl;

    for(int i =1; i <=  size; i++)
    {
        cout << this->data[i] << endl;

        for(int j = 1; j<= size; j++)
        {
            if(T[i][j].dist > 0 && T[i][j].dist < INT_MAX)
            {
                cout << setw(27) << i << setw(12) << j;
                cout << setw(12) << T[i][j].dist << setw(10);
                findPath(i,j);
                cout << endl;
            }
            else if (i != j)
            {
                cout << setw(27) << i << setw(12) << j;
                cout << setw(12) << "----" << endl;
            }
        }
    }
}

/*
----------------------------------display------------------------------------------------------
Displays the shortest distance with information about the path between each nodes
---------------------------------------------------------------------------------------------------
*/

void GraphM::display(int start, int end) const{
    if((start > size || start < 1) || (end > size || end < 1))
    {
        cout << setw(7) << start << setw(9) << end << setw(11) << "----" << endl;
    }
    else if(T[start][end].dist != INT_MAX)
    {
        cout << setw(7) << start << setw(9) << end << setw(11) << T[start][end].dist << setw(15);
        
        findPath(start, end);
        cout << endl;
        findData(start, end);
    }
    else 
    {
        cout << setw(7) << start << setw(9) << end << setw(11) << "----" << endl;
    }
    cout << endl;
}