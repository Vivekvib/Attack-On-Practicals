#include <iostream>
using namespace std;
int comparisons =0;
int partition(int arr[], int low, int high){
    int index = rand() % (high-low+1)+low;
    swap(arr[index], arr[high]);
    int pivot = arr[high];
    int i = low-1;
    for(int j = low;j<high; j++){
        comparisons++;
        if(arr[j] < pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}
void quicksort(int arr[], int low, int high){
    if(low<high){
        int pi= partition(arr, low, high);
        quicksort(arr,low,pi-1);
        quicksort(arr,pi+1,high);
    }
}
void printArray(int arr[], int high){
    for(int i=0; i<high;i++){
        cout << arr[i] <<" ";
    }
    cout<<endl;
}
int main(){
    int n;
    cout<<"Enter the number of elements: ";
    cin >> n;
    int *arr = new int[n];
    for(int i=0; i<n; i++){
        cout<<"Enter element "<<i+1 <<": ";
        cin>> arr[i];
    }
    quicksort(arr,0,n-1);
    printArray(arr,n);
    cout<<"Number of comparisons: " <<comparisons<<endl;
    return 0;
}
