#include "netflow.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>

using namespace std;

/**
 * For your convenience (so that you do not have to type out all of these),
 * I provide the exception messages below.
 * FYI some may argue that const std::string objects are preferable over
 * macros here.
 */
#define ERR_NONEXISTENT_VERTEX "At least one edge is to a nonexistent vertex."
#define ERR_UNSORTED_NEIGHBORS "Found at least one unsorted neighbor list."
#define ERR_DISCONNECTED "Flow network is disconnected graph."
#define ERR_SRC "Flow network does not contain exactly one source."
#define ERR_SINK "Flow network does not contain exactly one sink."

typedef std::vector<std::vector<NeighborEntry>> AdjList;
/*
    this adjacent list represents the flow network capacity 
    based on the user 

*/

void printList(AdjList l){
    for(unsigned i = 0; i < l.size(); i++){
        for(unsigned j = 0; j < l[i].size(); j++){
            cout << "(" << l[i][j].neighbor << ", " << l[i][j].weight << ") ";
        }
        cout << endl;
    }
    cout << endl;

}

void printPath(vector<unsigned> path){
    for(unsigned i : path){
        cout << i << " ";
    }
    cout << endl;
}


//BFS reused from P3
bool bfs(const AdjList &residual, unsigned src, unsigned snk, vector<unsigned> &path) 
{
    //throws an error when a node has been marked false in discovered
    queue<unsigned> q;
    vector<unsigned> closed;
    path.clear();
    vector<bool> discovered(residual.size());
    bool connected = 0;

    vector<pair<unsigned,unsigned>> connections;

    for (unsigned vert = 0; vert < residual.size(); vert++)
    {
        discovered[vert] = 0;
    }

    q.push(src);
    discovered[src] = 0;

    while (!q.empty())
    {
        unsigned curr_node = q.front(); 
        closed.push_back(curr_node);
        q.pop();

        if(curr_node == snk)
            connected = 1;

        for (NeighborEntry entry : residual[curr_node])
        {
            if (!discovered[entry.neighbor] && entry.weight != 0)
            {
                q.push(entry.neighbor);
                discovered[entry.neighbor] = 1;
                connections.push_back({curr_node, entry.neighbor});
            }
        }

    }

    if(!connected)
        return false;

    unsigned curr = snk;

    while(curr != src){

        path.insert(path.begin(),curr);
        
        for(auto i : connections){
            if(i.second == curr){
                curr = i.first;
                break;
            }
        }
    }
    path.insert(path.begin(),curr);

    return true;

}

AdjList solveNetworkFlow(const AdjList& flowNetwork)
{
    /*
        must return an AdjList object representing max flow 
        must have same vertices and edges as the Adjlist 
        Input Validation:
            1. Each vertex (unsigned integer) list as neighbor 
               must be in the range 0 to n-1 where n is the number of the vertices 
            2. Each vertex’s neighbor list must be sorted by neighbor. 
               For example, if the neighbors of vertex 2 were listed as 3, 1, 6, 
               then that would be an unsorted neighbor list. It would need to be 1, 3, then 6.
            3. The graph must be connected.
            4. The graph must contain exactly one source node, i.e. exactly one node with an in-degree of 0. Note that this node/vertex
                need not be node 0.
            5. The graph must contain exactly one sink node, i.e. exactly one node with an out-degree of 0.

    */


   //initializing the source and sink nodes based on the flow network given 
    unsigned num_vert = flowNetwork.size(), //6
             source = 0,
             sink = num_vert-1; //5
    
    //where flow can be added or subtracted 
    //max list at zero since we are starting with zero flow. 
    //parent 
    AdjList residual(num_vert);
    AdjList max_list(num_vert);
    vector<unsigned> path;

    //input validation
    //copied the contents of flowNetwork to residual. 
    for (unsigned row = 0; row < flowNetwork.size(); row++)
    {
        
        for (unsigned col = 0;  col < flowNetwork[row].size(); col++)
        {
            if (flowNetwork[row][col].neighbor >= flowNetwork.size())
                throw (ERR_NONEXISTENT_VERTEX);  
            else if (col < flowNetwork[row].size()-1 && flowNetwork[row][col].neighbor > flowNetwork[row][col+1].neighbor)
                throw (ERR_UNSORTED_NEIGHBORS);

            max_list[row].push_back({flowNetwork[row][col].neighbor, 0});        
        }
        residual[row] = flowNetwork[row];        
    }

    //cout << "no seg" << endl;
    //printList(flowNetwork);



    bool augment_path = bfs(residual, source, sink, path);

    //printPath(path);
    //cout << "Tried to print path!!\n";


    while (augment_path)
    {
        unsigned bottleneck = 9999; //get min
        for(unsigned i = 0; i < path.size() - 1; i++){
            unsigned weight = 9999;
            for(auto j : residual[path[i]]){
                if(j.neighbor == path[i+1]){
                    weight = j.weight;
                    break;
                }
            }
            if(weight < bottleneck)
                bottleneck = weight;
        }

        for(unsigned i = 0; i < path.size() - 1; i++){
            for(unsigned j = 0; j < max_list[path[i]].size(); j++){
                if(max_list[path[i]][j].neighbor == path[i+1]){
                    max_list[path[i]][j].weight+=bottleneck;
                    residual[path[i]][j].weight-=bottleneck;
                    break;
                }
            }            
        }

        /*
        cout << "\nResidual:\n";
        printList(residual);
        cout << "\nFlow:\n";
        printList(max_list);
        */

        augment_path = bfs(residual, source, sink, path);

    }

    


    return max_list;

}

std::vector<std::string> assignTutoring(
    const std::vector<std::vector<std::string>>& preferences,
    const std::vector<std::string>& offered)
{
    vector<string> taken(preferences.size());
    vector<unsigned> option(preferences.size(),0);

    for(unsigned t = 0; t < offered.size(); t++){
        
        taken[t] = preferences[t][option[t]];

        bool cuckoo = 0;
        do{
            cuckoo = 0;
            for(unsigned i = 0; i <= t; i++){
                for(unsigned j = 0; j < t; j++){
                    if(i == j)
                        continue;
                    
                    if(taken[j]==taken[i]){ //conflict
                        if(preferences[j].size()-1==option[j]){//cant push a prev tutor to next sub
                            option[i]++;
                            taken[i] = preferences[i][option[i]];
                            cuckoo = 1;
                        }else{ //can push a prev tutor to another class
                            option[j]++;
                            taken[j] = preferences[j][option[j]];
                            cuckoo = 1;
                        }
                    }
                }
            }
        }while(cuckoo);

    }

    return taken;
}