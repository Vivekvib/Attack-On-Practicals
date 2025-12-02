#include <iostream>
using namespace std;
int comparisons = 0;
int partition(int arr[], int low, int high){
    int index = rand() % (high - low + 1) + low;
    swap(arr[index], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
int quickselect(int arr[], int low, int high, int k) {
    if(low == high){
        return arr[low];
    }  
    int pi = partition(arr, low, high);   
    int length = pi - low + 1;
    if(k == length){
        return arr[pi];
    }  
    else if(k < length){
        return quickselect(arr, low, pi - 1, k);
    }  
    else{
        return quickselect(arr, pi + 1, high, k - length);
    }   
}
int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }
    int k;
    cout << "Enter the value of k to find the k-th smallest element: ";
    cin >> k;
    if (k < 1 || k > n) {
        cout << "Invalid value of k\n";
        delete[] arr;
        return 1;
    }
    int kth_smallest = quickselect(arr, 0, n - 1, k);
    cout << k << "-th smallest element is: " << kth_smallest << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    delete[] arr;
    return 0;
}
