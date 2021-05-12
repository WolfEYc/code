#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;



void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

int main(){

    srand(time(NULL));
    int n;
    cin>>n;
    int myarr[n],mergearr[n];


    for(int i = 0;i<n;i++){
        myarr[i] = rand();
        mergearr[i] = myarr[i];
    }

    /*
    for(int i = 0;i<n;i++)
        cout << mergearr[i] << endl;

    cout << endl;*/

    auto startmerge = high_resolution_clock::now();
    
    mergeSort(mergearr,0,n-1);

    auto endmerge = high_resolution_clock::now();

    /*for(int i = 0;i<n;i++)
        cout << mergearr[i] << endl;

    cout << endl;


    for(int i = 0;i<n;i++)
        cout << myarr[i] << endl;

    cout << endl;*/
    

    auto startmine = high_resolution_clock::now();

    //sort(myarr,n);

    auto endmine = high_resolution_clock::now();


    /*for(int i = 0;i<n;i++)
        cout << myarr[i] << endl;

    cout << endl;*/
    
    auto mergeduration = duration_cast<microseconds>(endmerge - startmerge);
    auto myduration = duration_cast<microseconds>(endmine - startmine);

    cout << "Time taken by Merge Sort: "
        << mergeduration.count() << " microseconds" << endl << endl;

    cout << "Time taken by My Sort: "
        << myduration.count() << " microseconds" << endl << endl;
}