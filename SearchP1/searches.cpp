#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int V = 10;

int numLet(char letr)
{
    switch (letr)
    {
    case 'S':
        return 0;
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;
    case 'D':
        return 4;
    case 'E':
        return 5;
    case 'F':
        return 6;
    case '1':
        return 7;
    case '2':
        return 8;
    case 'H':
        return 9;
    }
    return -1;
}

char letNum(int num)
{
    switch (num)
    {
    case 0:
        return 'S';
    case 1:
        return 'A';
    case 2:
        return 'B';
    case 3:
        return 'C';
    case 4:
        return 'D';
    case 5:
        return 'E';
    case 6:
        return 'F';
    case 7:
        return '1';
    case 8:
        return '2';
    case 9:
        return 'H';
    }
    return ' ';
}

struct edge
{
    edge(pair<char, int> srcc, pair<char, int> destt, int weightt)
    {
        src = srcc;
        dest = destt;
        weight = weightt;
    }
    pair<char, int> src;
    pair<char, int> dest;
    int weight = 0;
};

void out(int S, queue<int> Open, queue<int> Closed)
{
    string closelist = "", openlist = "";
    while (!Closed.empty())
    {
        closelist += letNum(Closed.front());
        closelist += ' ';
        Closed.pop();
    }
    while (!Open.empty())
    {
        if (Open.front() == 7 || Open.front() == 8)
            openlist += 'G';
        openlist += letNum(Open.front());
        openlist += ' ';
        Open.pop();
    }

    cout << "GOAL Reached first: "
         << "G" << letNum(S) << endl;
    cout << "Expanded states: " << closelist << endl;
    cout << "OPEN List: " << openlist << endl;
    cout << "CLOSE List: " << closelist << endl;
}

void hSort(queue<int> &q, vector<pair<char, int>> vertecies)
{
    vector<int> v;
    while (!q.empty())
    {
        v.push_back(q.front());
        q.pop();
    }
    for (int i = 0; i < v.size() - 1; i++)
        for (int j = 0; j < v.size() - i - 1; j++)
            if (vertecies[v[j]].second > vertecies[v[j + 1]].second)
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
    for (int i : v)
        q.push(i);
}

int findWeight(vector<vector<edge>> edges, int src, int dest)
{
    for (edge i : edges[src])
        if (numLet(i.dest.first) == dest)
            return i.weight;
    return 99999;
}

void fhSort(vector<int> G, queue<int> &q, vector<pair<char, int>> vertecies, vector<vector<edge>> edges)
{
    vector<int> v;
    while (!q.empty())
    {
        v.push_back(q.front());
        q.pop();
    }
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if ((vertecies[v[j]].second + G[v[j]]) > (vertecies[v[j + 1]].second + G[v[j + 1]]))
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < v.size(); i++)
    {
        q.push(v[i]);
    }
}

void threeQ(queue<int> &q)
{
    queue<int> temp;
    for (int i = 0; i < 3 && !q.empty(); i++)
    {
        temp.push(q.front());
        q.pop();
    }
    swap(q, temp);
}

bool BestFS(vector<vector<edge>> edges, vector<pair<char, int>> vertecies)
{
    queue<int> Open, Closed;
    int S = 0;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    visited[S] = true;

    Open.push(S);

    while (!Open.empty())
    {
        S = Open.front();
        Open.pop();

        if (S == 7 || S == 8)
        {
            out(S, Open, Closed);
            return true;
        }

        Closed.push(S);

        for (int i = 0; i < edges[S].size(); i++)
        {
            if (!visited[numLet(edges[S][i].dest.first)])
            {
                visited[numLet(edges[S][i].dest.first)] = true;
                Open.push(numLet(edges[S][i].dest.first));
            }
        }
        hSort(Open, vertecies);
    }
    return false;
}

bool BreadthFS(vector<vector<edge>> edges, vector<pair<char, int>> vertecies)
{
    queue<int> Open, Closed;
    int S = 0;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    visited[S] = true;

    Open.push(S);

    while (!Open.empty())
    {
        S = Open.front();
        Open.pop();

        if (S == 7 || S == 8)
        {
            out(S, Open, Closed);
            return true;
        }

        Closed.push(S);

        for (int i = 0; i < edges[S].size(); i++)
        {
            if (!visited[numLet(edges[S][i].dest.first)])
            {
                visited[numLet(edges[S][i].dest.first)] = true;
                Open.push(numLet(edges[S][i].dest.first));
            }
        }
    }
    return false;
}

bool DFS(vector<vector<edge>> edges, vector<pair<char, int>> vertecies)
{
    queue<int> Open, Closed;
    int S = 0;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    visited[S] = true;
    Open.push(S);

    while (!Open.empty())
    {
        S = Open.front();
        Open.pop();

        if (S == 7 || S == 8)
        {
            out(S, Open, Closed);
            return true;
        }

        Closed.push(S);
        queue<int> depth;

        for (int i = 0; i < edges[S].size(); i++)
        {
            if (!visited[numLet(edges[S][i].dest.first)])
            {
                visited[numLet(edges[S][i].dest.first)] = true;
                depth.push(numLet(edges[S][i].dest.first));
            }
        }
        while (!Open.empty())
        {
            depth.push(Open.front());
            Open.pop();
        }
        while (!depth.empty())
        {
            Open.push(depth.front());
            depth.pop();
        }
    }
    return false;
}

bool AStar(vector<vector<edge>> edges, vector<pair<char, int>> vertecies)
{
    queue<int> Open, Closed;
    vector<int> G(V);
    int S = 0;
    Open.push(S);
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    visited[S] = true;
    G[S] = 0;
    while (!Open.empty())
    {
        S = Open.front();
        Open.pop();

        if (S == 7 || S == 8)
        {
            out(S, Open, Closed);
            return true;
        }

        Closed.push(S);

        for (int i = 0; i < edges[S].size(); i++)
        {
            if (!visited[numLet(edges[S][i].dest.first)])
            {
                visited[numLet(edges[S][i].dest.first)] = true;
                Open.push(numLet(edges[S][i].dest.first));
                if(G[numLet(edges[S][i].dest.first)] == 0 || G[S] + edges[S][i].weight<G[numLet(edges[S][i].dest.first)])
                    G[numLet(edges[S][i].dest.first)] = G[S] + edges[S][i].weight;
                
            }
        }
        fhSort(G, Open, vertecies, edges);
    }
    return false;
}

bool SMAStar(vector<vector<edge>> edges, vector<pair<char, int>> vertecies)
{
    queue<int> Open, Closed;
    int S = 0;
    Open.push(S);
    vector<int> G(V);
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    visited[S] = true;
    G[S] = 0;
    while (!Open.empty())
    {
        S = Open.front();
        Open.pop();

        if (S == 7 || S == 8)
        {
            out(S, Open, Closed);
            return true;
        }

        Closed.push(S);
        queue<int> depth;
        for (int i = 0; i < edges[S].size(); i++)
        {
            if (!visited[numLet(edges[S][i].dest.first)])
            {
                visited[numLet(edges[S][i].dest.first)] = true;
                Open.push(numLet(edges[S][i].dest.first));
                if(G[numLet(edges[S][i].dest.first)] == 0 || G[S] + edges[S][i].weight<G[numLet(edges[S][i].dest.first)])
                    G[numLet(edges[S][i].dest.first)] = G[S] + edges[S][i].weight;
                
            }
        }
        fhSort(G, Open, vertecies, edges);
        threeQ(Open);
    }
    return false;
}

int main()
{
    vector<vector<edge>> edges(V);
    vector<pair<char, int>> vertecies;

    pair<char, int> S('S', 10), A('A', 5), B('B', 8), C('C', 3), D('D', 2), E('E', 4), F('F', 9), G1('1', 0), G2('2', 0), H('H', 2);

    vertecies.push_back(S);
    vertecies.push_back(A);
    vertecies.push_back(B);
    vertecies.push_back(C);
    vertecies.push_back(D);
    vertecies.push_back(E);
    vertecies.push_back(F);
    vertecies.push_back(G1);
    vertecies.push_back(G2);
    vertecies.push_back(H);

    edges[0].push_back(edge(S, A, 3));
    edges[0].push_back(edge(S, F, 5));
    edges[0].push_back(edge(S, B, 7));
    edges[1].push_back(edge(A, C, 1));
    edges[1].push_back(edge(A, E, 4));
    edges[1].push_back(edge(A, D, 6));
    edges[2].push_back(edge(B, E, 1));
    edges[2].push_back(edge(B, G2, 9));
    edges[3].push_back(edge(C, S, 2));
    edges[3].push_back(edge(C, D, 4));
    edges[4].push_back(edge(D, G1, 6));
    edges[5].push_back(edge(E, H, 1));
    edges[5].push_back(edge(E, G2, 5));
    edges[6].push_back(edge(F, D, 4));
    edges[7].push_back(edge(G1, C, 2));
    edges[8].push_back(edge(G2, B, 8));
    edges[9].push_back(edge(H, G2, 1));

    cout << "Breadth First Search" << endl;
    BreadthFS(edges, vertecies);
    cout << endl;
    cout << "Depth First Search" << endl;
    DFS(edges, vertecies);
    cout << endl;
    cout << "Best First Search" << endl;
    BestFS(edges, vertecies);
    cout << endl;
    cout << "A Star Search" << endl;
    AStar(edges, vertecies);
    cout << endl;
    cout << "SMA Star Search" << endl;
    SMAStar(edges, vertecies);
    cout << endl;

    return 0;
}