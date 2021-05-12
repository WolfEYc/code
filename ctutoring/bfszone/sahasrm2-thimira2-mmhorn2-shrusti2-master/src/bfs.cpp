#include <bits/stdc++.h>
#include "Matrix.h"
using namespace std;

vector<vector<bool>> convertMatrix(fin::Matrix m){
    unsigned size = m.getRows();

    vector<vector<bool>> boolMatrix (size, vector<bool> (size,0) );

    for(unsigned i = 0; i < size; i++)
        for(unsigned j = 0; j < size; j++)
            if(m[i][j] == 1)
                boolMatrix[i][j] = 1;
    
    return boolMatrix;
}

vector<unsigned> bfs(fin::Matrix m){

    vector<vector<bool>> adj_m = convertMatrix(m);

    unsigned size = adj_m.size(), start = 0;
    vector<bool> visited(size,0);
    queue<unsigned> open;
    vector<unsigned> closed;

    open.push(start);
    visited[start] = 1;

    while(!open.empty()){
        
        start = open.front();
        open.pop();
        closed.push_back(start);

        for(unsigned i = 0; i < size; i++){
            if(adj_m[start][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                open.push(i);
            }
        }
    }

    return closed;
}


void printvector(vector<unsigned> v){
    for(unsigned i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

/* for testing only
int main(){

    vector<vector<bool>> test = {
      {0,1,0,1},
      {1,0,1,0},
      {1,0,0,0},
      {0,1,1,0}
    };

    fin::Matrix m (4,4);

    for(unsigned i = 0; i < 4; i++)
        for(unsigned j = 0; j < 4; j++)
            m[i][j] = double(test[i][j]);
    

    vector<unsigned> output = bfs(m);

    printvector(output);


    return 0;

}
*/