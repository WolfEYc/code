#include <bits/stdc++.h>
#include <cuda_runtime.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

__global__
void add(int* arr, int n){
    int index = threadIdx.x;
    int stride = blockDim.x;
    for(int i = index; i < n; i+=stride){
        arr[i] = arr[i]*arr[i];
    }
}

void cpuadd(int* arr, int n){
    for(int i = 0; i < n; i++){
        arr[i] = arr[i]*arr[i];
    }
}

int main(void){

    int n;
    cin >> n;

    int* arr;
    int* arrcopy = new int [n];

    cudaMallocManaged(& arr, n*sizeof(int));

    for(int i = 0; i < n; i++){
        arr[i] = i;
        arrcopy[i] = i;
    }

    auto gpustart = high_resolution_clock::now();

    add <<<1, 256>>> (arr,n);

    cudaDeviceSynchronize();

    auto gpuend = high_resolution_clock::now();

    auto gputime = duration_cast<microseconds>(gpuend - gpustart);

    cout << "Gpu time: " << gputime.count() << endl;

    auto normalstart = high_resolution_clock::now();

    cpuadd(arrcopy,n);

    auto normalend = high_resolution_clock::now();

    auto normaltime = duration_cast<microseconds>(normalend - normalstart);

    cout<< "Normal time: " << normaltime.count() << endl;

    for(int i = 0; i < n; i++){
        if(arr[i] != arrcopy[i]){
            cout << "Arrays not equal" << endl;
            break;
        }
    }

    cudaFree(arr);

    delete[] arrcopy;

    return 0;
}