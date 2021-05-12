#include "graph.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

Graph::Graph(const string& filename)
{
    ifstream ifs(filename);
    if (!ifs) throw logic_error("Failed to open file.");

    string first_line;
    getline(ifs, first_line);
    if (first_line.empty() || (first_line != "Weighted"&& first_line != "Unweighted") )
        inval_graph();
    else if (first_line == "Weighted")
        is_weighted = true;
    else if (first_line == "Unweighted")
        is_weighted = false;
    
    string sec_line;
    getline(ifs, sec_line);
    if (sec_line.empty() || (sec_line != "Directed" && sec_line != "Undirected"))
        inval_graph();
    else if (sec_line == "Directed")
        is_directed= true;
    else if (sec_line == "Undirected")
        is_directed= false;
    
    string third_line;
    getline(ifs, third_line);
    if (third_line.empty() || (third_line != "AdjMatrix"
        && third_line != "AdjList" && third_line != "ListEdges"))
        inval_graph();
    else if (third_line == "AdjMatrix" )
        graph_type = 1;
    else if (third_line == "AdjList" )
        graph_type = 2;
    else if (third_line == "ListEdges" )
        graph_type = 3;
    
    string fourth_line;
    getline(ifs, fourth_line);
    if (stoi(fourth_line) <= 0)
        inval_graph();
    else    
        num_of_vert = stoi(fourth_line);

    //want to initialize the rest of the file contents into the rest_arg vector
    /*
        looks like:
        {
            {"5 0 6 7"}      or {"T F T F F"}
            {"60 8 2 7"}     or {"  F T F F"}
            {"3 4 6 6"}      or {"    T F F"}
        }

    */
    num_edges = 0;
    string rest_lines;
    int i = 0;
    while(getline(ifs, rest_lines))
    {
        //to be able to parse the line 
        //these are still strings but just parsed and put as individuals 
        //use auto 
        string buf;

        stringstream temp_ss(rest_lines);
        vector<int> temp;
        int j = 0;
        if (graph_type == 1 && !is_weighted){
            temp = vector<int> (num_of_vert,0);
        }

        while(temp_ss >> buf)
        {
            if ((graph_type == 1) && !is_weighted) //adjm
            {
                if(!is_directed){
                    if (buf == "F")
                        temp[i+j] = 0;
                    else if (buf == "T") {
                        temp[i+j] = 1; 
                        num_edges++;
                    }else{
                        inval_graph();
                    }
                }else{
                    if (buf == "F")
                        temp[j] = 0;
                    else if(buf == "T"){
                        temp[j] = 1; 
                        num_edges++;
                    }else{
                        inval_graph();
                    }
                }
            }
            else 
                temp.push_back(stoi(buf));

            if(graph_type == 1 && is_weighted && buf != "0")
                num_edges++;

            if(graph_type == 2 && is_weighted && j%2==0 && (stoi(buf) < 0 || stoi(buf) >= int(num_of_vert)))
                inval_graph();            
            else if( (graph_type==3 && !is_weighted && j >= 2) || (graph_type==3 && !is_weighted && j >= 3))
                inval_graph();

            if(graph_type==3 && j<2 && (stoi(buf) < 0 || stoi(buf) >= int(num_of_vert)))
                inval_graph();

            if(graph_type == 2 && !is_weighted && stoi(buf) == i)
                inval_graph();

            if(graph_type == 2 && is_weighted && stoi(buf) == i && j%2==0)
                inval_graph();

            j++;
        }
        if(graph_type == 2 && is_weighted)
            num_edges+=(j/2);
        if(graph_type == 2 && !is_weighted)
            num_edges+=j;
        if(graph_type == 3)
            num_edges++;
        
        

        main_vec.push_back(temp);
        i++;
    }
    

}

//unweighted
Graph::Graph(unsigned numVertices,
        const vector<pair<unsigned, unsigned> >& edges,
        bool isDirected) 
{
    num_of_vert = numVertices;
    main_vec = vector<vector<int>> (num_of_vert);
    num_edges = 0;
    for (const auto &edge: edges)
    {
        //save 
        //use auto
        //make a list from edges. Each source (a->b) and dest edge
        //create adjacency list
        num_edges++;
        main_vec[edge.first].push_back(edge.second);
    
    }
    is_directed = isDirected;
    is_weighted = false;
    graph_type = 2;
}

//weighted
Graph::Graph(unsigned numVertices,
        const vector<tuple<unsigned, unsigned, int> > &edges,
        bool isDirected)
{
    num_of_vert = numVertices;
    main_vec = vector<vector<int>> (num_of_vert, vector<int> (num_of_vert));
    for (const auto &edge: edges)
    {
        main_vec[get<0>(edge)][get<1>(edge)] = get<2>(edge);
    }
    is_directed = isDirected;
    is_weighted = true;
    graph_type = 2;
}

/*Graph(const Graph&) = delete;
Graph& operator=(const Graph&) = delete;*/

/******************************************************
 * Accessor methods.
*****************************************************/
bool Graph::isWeighted() const
{
    return is_weighted;
}
bool Graph::isDirected() const
{
    return is_directed;
}
unsigned Graph::getNumVertices() const
{
    return num_of_vert;
}
unsigned Graph::getNumEdges() const
{
    return num_edges;
}
vector<vector<int>> Graph::getMainVec() {
    return main_vec;
}

std::vector<std::vector<int>> Graph::getAdjacencyMatrix() const
{

    vector<vector<int> > Adj_Mgraph (num_of_vert, vector<int>(num_of_vert,0));

    if(graph_type == 1)
        return main_vec;

    if(graph_type == 3 && !is_weighted){
        for(unsigned int i = 0; i < num_edges; i++){            
            Adj_Mgraph[main_vec[i][0]][main_vec[i][1]] = 1;
            if(!is_directed)
                Adj_Mgraph[main_vec[i][1]][main_vec[i][0]] = 1;
        }
    }
    if(graph_type == 3 && is_weighted){       
        for(unsigned int i = 0; i < num_edges; i++){
            Adj_Mgraph[main_vec[i][0]][main_vec[i][1]] = main_vec[i][2];
            if(!is_directed)
                Adj_Mgraph[main_vec[i][1]][main_vec[i][0]] = main_vec[i][2];
        }
    }
    if(graph_type == 2 && !is_weighted){
        for(unsigned int i = 0; i < num_of_vert; i++){
            for(long unsigned int j = 0; j < main_vec[i].size(); j++){
                Adj_Mgraph[i][main_vec[i][j]] = 1;
                if(!is_directed){
                    Adj_Mgraph[main_vec[i][j]][i] = 1;
                }
            }
        }
    }
    if(graph_type == 2 && is_weighted){
        for(unsigned int i = 0; i < num_of_vert; i++){
            for(long unsigned int j = 0; j < main_vec[i].size(); j+=2){
                Adj_Mgraph[i][main_vec[i][j]] = main_vec[i][j+1];
                if(!is_directed){
                    Adj_Mgraph[main_vec[i][j]][i] = main_vec[i][j+1];
                }
            }
        }
    }
    /**
     * Returns 2D vector of ints representing an adjacency matrix.
     * If graph is unweighted, then each int is either 1 or 0;
     * otherwise, each int is the weight.
     * 0 indicates a nonexistent edge.
     */
    return Adj_Mgraph;

}

std::vector<std::vector<std::pair<unsigned, int>>> Graph::getAdjacencyList() const
{
    /**
     * Returns adjacency list represented by a 2D vector in which the vector at
     * index i contains the neighbor entries of vertex i.
     * For each neighbor entry, the unsigned gives the neighbor's ID,
     * and the int gives the weight of the edge to that neighbor.
     * If the graph is unweighted, then each int is 1.
     */
    std::vector<std::vector<std::pair<unsigned, int>>> Adj_List(num_of_vert);

    if(graph_type == 2 && !is_weighted){
        for(unsigned int i = 0; i < num_of_vert; i++){            
            for(long unsigned int j = 0; j < main_vec[i].size(); j++){                
                Adj_List[i].push_back(make_pair(main_vec[i][j],1));
            }
        }
        return Adj_List;
    }

    if(graph_type == 2 && is_weighted){
        for(unsigned int i = 0; i < num_of_vert; i++){            
            for(long unsigned int j = 0; j < main_vec[i].size(); j+=2){
                Adj_List[i].push_back(make_pair(main_vec[i][j],main_vec[i][j+1]));
            }
        }
        return Adj_List;
    }

    if(graph_type == 1 && !is_weighted){
        for(unsigned int i = 0; i < num_of_vert; i++){            
            for(long unsigned int j = 0; j < main_vec[i].size(); j++){
                if(main_vec[i][j] == 1){
                    Adj_List[i].push_back(make_pair(j,1));
                }                
            }
        }
        return Adj_List;
    }

    if(graph_type == 1 && is_weighted){
        for(unsigned int i = 0; i < num_of_vert; i++){            
            for(long unsigned int j = 0; j < main_vec[i].size(); j++){
                if(main_vec[i][j] != 0){
                    Adj_List[i].push_back(make_pair(j,main_vec[i][j]));
                }                
            }
        }
        return Adj_List;
    }

    if(graph_type == 3){
        for(unsigned int i = 0; i < num_edges; i++){
            if(!is_weighted){
                Adj_List[main_vec[i][0]].push_back(make_pair(main_vec[i][1],1));
                if(!is_directed)
                    Adj_List[main_vec[i][1]].push_back(make_pair(main_vec[i][0],1));
            }else{
                Adj_List[main_vec[i][0]].push_back(make_pair(main_vec[i][1],main_vec[i][2]));
                if(!is_directed)
                    Adj_List[main_vec[i][1]].push_back(make_pair(main_vec[i][0],main_vec[i][2]));            
            }
        }
    }
    return Adj_List;

}
    /******************************************************
     * Graph traversals.
     *
     * Returns a BFS/DFS ordering of all vertices reachable from the start node.
     * Throws exception if @start is invalid, i.e. too high.
     *****************************************************/

std::vector<unsigned> Graph::getBFSOrdering(unsigned start) const
{
    if(start < 0 || start >= num_of_vert)
        throw exception();

    std::vector<std::vector<std::pair<unsigned, int>>> Adj_list = getAdjacencyList();

    queue<unsigned> Open;
    vector<unsigned> Closed;
    vector<bool> visited(num_of_vert,0);

    Open.push(start);
    visited[start] = 1;

    while(!Open.empty()){

        start = Open.front();
        Closed.push_back(start);
        Open.pop();

        for(long unsigned int i = 0; i < Adj_list[start].size(); i++){
            if(!visited[Adj_list[start][i].first]){
                Open.push(Adj_list[start][i].first);
                visited[Adj_list[start][i].first] = 1;
            }
        }
    }

    return Closed;
}
std::vector<unsigned> Graph::getDFSOrdering(unsigned start) const
{
    if(start < 0 || start >= num_of_vert)
        throw exception();

    std::vector<std::vector<std::pair<unsigned, int>>> Adj_list = getAdjacencyList();

    stack<unsigned> Open;
    vector<unsigned> Closed;
    vector<bool> visited(num_of_vert,0);

    Open.push(start);
    visited[start] = 1;

    while(!Open.empty()){

        start = Open.top();
        Closed.push_back(start);
        Open.pop();

        for(long unsigned int i = 0; i < Adj_list[start].size(); i++){
            if(!visited[Adj_list[start][i].first]){
                Open.push(Adj_list[start][i].first);
                visited[Adj_list[start][i].first] = 1;
            }
        }
    }

    return Closed;
}

std::vector<std::vector<bool>> Graph::getTransitiveClosure() const
{
    vector<vector<bool>> trans (num_of_vert, vector<bool> (num_of_vert,0));
    for(unsigned int i = 0; i < num_of_vert; i++){
        vector<unsigned> temp =  getBFSOrdering(i);
        for(long unsigned int j = 0; j < temp.size(); j++){
            trans[i][temp[j]] = 1;
        }
    }
    return trans;
}


void Graph::inval_graph()
{
    throw logic_error("Invalid graph");
}

