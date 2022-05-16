/*
Name: Sanket Karna
Class: CSS 343
Professor: Dong Si
Created Date: 05/01/22
Last Modification: 05/15/22
---------------------------------------------------------------------------------------------------
Purpose: The purpose of the graphm.cpp is to imeplement the method definitions that were written in
graphl.h. Graphl is similar to Graphm in a sense that with the input file a Graph is created with 
nodes and information about the nodes. However, this in GraphL we implement the Depth First Search 
algorithm and display that to the console
---------------------------------------------------------------------------------------------------
Inclusion of <iomanip> helps with setting the width of the output.
All inputs are assumed to be valid with a .txt file
*/
#include "graphl.h"

/*
----------------------------------Default constructor----------------------------------------------
This constructor for the empty array to initialize everything
---------------------------------------------------------------------------------------------------
*/

GraphL::GraphL()
{
    this->size = 0;

    for(int i = 0; i < MAX; i++)
    {
        arr[i].edgeHead = nullptr;
        arr[i].data = nullptr;
        arr[i].visited = false;
    }
}

/*
----------------------------------Destructor------------------------------------------------------
The destructor calls the helper destroy() function
---------------------------------------------------------------------------------------------------
*/

GraphL::~GraphL()
{
    destroy();
}

/*
----------------------------------Destroy------------------------------------------------------
Helper function for Destructor
---------------------------------------------------------------------------------------------------
*/

void GraphL::destroy()
{
    for (int i =1; i <= size; i++) // loop for the entire size
    {
        arr[i].visited =false;
        if(arr[i].data != nullptr)
        {
            delete arr[i].data;
            arr[i].data = nullptr;
        }
        if (arr[i].edgeHead != nullptr) // goes and deletes each node and sets it to nullptr
        {
            EdgeNode* temp = arr[i].edgeHead;

            while(temp != nullptr)
            {
                arr[i].edgeHead = arr[i].edgeHead->nextEdge;
                delete temp;
                temp = nullptr;
                temp = arr[i].edgeHead;
            }
        }
    }
}

/*
----------------------------------buildGraph------------------------------------------------------
Build graph using ifstream, the input is going to be coming from a .txt file
---------------------------------------------------------------------------------------------------
*/

void GraphL::buildGraph(ifstream &in)
{
    int start, end; // start and end file
    string input;

    in >> this->size;
    getline(in, input);

    for(int i =1; i <= size; i++) // get the input line by line 
    {
        getline(in, input);
        NodeData *temp = new NodeData(input);
        arr[i].data = temp;
        temp = nullptr;
    }

    while(in >> start >> end) // filling the matrix
    {
        if(start == 0)
        {
            break;
        }
        if(arr[start].edgeHead = nullptr) // first node
        {
            EdgeNode *data = new EdgeNode;
            data->adjGraphNode = end;
            data->nextEdge = nullptr;
            arr[start].edgeHead = data;
        }
        else 
        {
            EdgeNode *data = new EdgeNode; // rest of the nodes in the array
            data->adjGraphNode = end;
            data->nextEdge = arr[start].edgeHead;
            arr[start].edgeHead = data;
        }
    }
}

/*
----------------------------------depthFirstSearch------------------------------------------------------
This algorithm does depth first search on the graph that was created by calling the helper method 
---------------------------------------------------------------------------------------------------
*/

void GraphL::depthFirstSearch()
{
    cout << endl << "Depth-first ordering:";

    for(int i = 1; i <= size; i++)
    {
        if(!arr[i].visited)
        {
            dfsHelper(i); // call for the heler method
            cout << endl;
        }
    }
    cout << endl;
}

/*
----------------------------------dfsHelper------------------------------------------------------
This method is a helper function of depthFirstSearch, which is a recursive method to search the graph
---------------------------------------------------------------------------------------------------
*/

void GraphL::dfsHelper(int index)
{
    cout << setw(3) << index; // cout first node
    arr[index].visited = true; // set it to visited
    EdgeNode *temp = arr[index].edgeHead; 

    while(temp != nullptr) // while the nextEdge isnt nullptr
    {
        if(!(arr[temp->adjGraphNode].visited))
        {
            dfsHelper(temp->adjGraphNode); // recursive call
        }
        temp = temp->nextEdge;
    }
}

/*
----------------------------------displayGraph------------------------------------------------------
This method displays the graph including edge of nodes in the graph
---------------------------------------------------------------------------------------------------
*/

void GraphL::displayGraph() const
{
    cout << "Graph:" << endl;

    for(int i = 1; i <= size; i++) // loop through the number of nodes 
    {
        cout << "Node" << i << "         " << *arr[i].data << endl << endl; // cout information of the array

        EdgeNode* temp = arr[i].edgeHead;

        while(temp != nullptr) // while edgeHead isnt null
        {
            cout << setw(7) << "edge " << i << setw(3) << temp->adjGraphNode << endl; // display adjGraphNode
            temp = temp->nextEdge;
        }
    }
}
