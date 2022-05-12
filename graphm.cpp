#include "graphm.h"

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

void GraphM::buildGraph(ifstream &in)
{
    int start, end, weight; 
    string input;
    in >> this->size;
    getline(in, input);

    for(int i = 1; i <= size; i++)
    {
        data[i].setData(in);
    }

    while(in >> start >> end >> weight)
    {
        if(start == 0)
        {
            break;
        }
        this->C[start][end] = weight;
    }
}

bool GraphM::insertEdge(int start, int end, int weight)
{
    if(start > this->size || start < 1)
    {
        return false;
    }
    else if(end > this->size || end < 1)
    {
        return false;
    }
    else if(start == end && weight != 0)
    {
        return false;
    }
    else if (weight < 0)
    {
        return false;
    }
    else 
    {
        this->C[start][end] = weight;
        return true;
    }
}

bool GraphM::removeEdge(const int start, const int end)
{
    if(start < 1 || start > this->size)
    {
        return false;
    }
    else if ( end < 1 || end > this->size)
    {
        return false;
    }
    else if (this->C[start][end] == INT_MAX)
    {
        return false;
    }
    else 
    {
        this->C[start][end] == INT_MAX;
        return true; 
    }
}

void GraphM::findShortestPath()
{
    int nextVisit = 0;
    int loop = 1;

    for(int i = 1; i <= size; i++)
    {
        for(int j = 1; j <= size; j++)
        {
            T[i][j].visited = false;
        }
    }

    for(int first = 1; first <= size; first++)
    {
        T[first][first].dist = 0;

        while(loop != size)
        {
            nextVisit = findNext(T[first]);
            T[first][nextVisit].visited = true;

            for (int i =1; i <= size; i++)
            {
                if(!T[first][i].visited && C[nextVisit][i] != INT_MAX)
                {
                    if(T[first][i].dist > T[first][nextVisit].dist + C[nextVisit][i])
                    {
                        T[first][i].dist = T[first][nextVisit].dist + C[nextVisit][i];
                        T[first][i].path = nextVisit;
                    }
                }
            }
            loop++;
        }
    loop = 1;
    }
}

int GraphM::findNext(TableType other[])
{
    int next = 1;
    int inf = INT_MAX;

    for(int i = 1; i <= size; i++)
    {
        if(other[i].dist < inf && !(other[i].visited))
        {
            next = i;
            inf = other[i].dist;
        }
    }
    return next;
}

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

void GraphM::findData(int start, int end) const
{
    if(T[start][end].dist == INT_MAX)
    {
        return;
    }
    else if(start == end)
    {
        cout << data[end];
        return;
    }
    else 
    {
        int temp = end;
        findData(start, end = T[start][end].path);
        cout << data[temp] << endl << endl;
    }
}

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