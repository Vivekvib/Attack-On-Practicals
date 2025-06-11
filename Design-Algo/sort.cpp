#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

int mergeComparision, quickComparision, heapComparision;

class SortingAlgo
{
private:
    vector<int> arr;

public:
    SortingAlgo(int size)
    {
        arr.resize(size);
    }

    void inputArray()
    {
        for (int i = 0; i < arr.size(); i++)
        {
            arr[i] = rand() % 1000 + 1;
        }
    }

    int insertionSort()
    {
        int comparision = 0;
        for (int i = 1; i < arr.size(); i++)
        {
            int temp = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > temp)
            {
                arr[j + 1] = arr[j];
                j--;
                comparision++;
            }
            if (j >= 0)
                comparision++;
            arr[j + 1] = temp;
        }
        return comparision;
    }

    void merge(int st, int mid, int end)
    {
        vector<int> temp(end - st + 1);
        int i = st, j = mid + 1, idx = 0;

        while (i <= mid && j <= end)
        {
            mergeComparision++;
            if (arr[i] <= arr[j])
            {
                temp[idx++] = arr[i++];
            }
            else
            {
                temp[idx++] = arr[j++];
            }
        }
        while (i <= mid)
        {
            temp[idx++] = arr[i++];
        }
        while (j <= end)
        {
            temp[idx++] = arr[j++];
        }

        for (int t = 0; t < temp.size(); ++t)
        {
            arr[st + t] = temp[t];
        }
    }

    void mergeSortDivide(int st, int end)
    {
        // base case untill single element left
        if (st >= end)
            return;

        int mid = st + (end - st) / 2;
        mergeSortDivide(st, mid);
        mergeSortDivide(mid + 1, end);
        // now merge two sorted arrays
        merge(st, mid, end);
    }

    void quickSort(int st, int end)
    {
        if (st < end)
        {
            int pivot = arr[end], idx = st - 1;
            for (int j = st; j < end; j++)
            {
                quickComparision++;
                if (arr[j] <= pivot)
                    swap(arr[idx++], arr[j]);
            }
            swap(arr[idx++], arr[end]);

            quickSort(st, idx - 1);  // left half
            quickSort(idx + 1, end); // right half
        }
    }

    void heapify(int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
        {
            heapComparision++;
            largest = left;
        }
        if (right < n && arr[right] > arr[largest])
        {
            heapComparision++;
            largest = right;
        }

        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(n, largest);
        }
    }

    void heapSort()
    {
        // build max heap
        for (int i = arr.size() / 2 - 1; i >= 0; i--)
        {
            heapify(arr.size(), i);
        }
        // performing heap sort in each step by swapping the largest value with the last leaf of the tree
        for (int i = arr.size() - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            heapify(i, 0);
        }
    }
};

int main()
{
    srand(time(0));
    ofstream file("sorting_data.csv");
    file << "Size,Insertion,Merge,Quick,Heap,nlogn\n";

    for (int size = 30; size <= 1000; size += 10)
    {
        int insertionAvg = 0, mergeAvg = 0, quickAvg = 0, heapAvg = 0;

        for (int i = 0; i < 10; i++)
        {
            SortingAlgo algo(size);
            algo.inputArray();

            insertionAvg += algo.insertionSort();

            mergeComparision = quickComparision = heapComparision = 0;
            algo.mergeSortDivide(0, size - 1);
            mergeAvg += mergeComparision;

            algo.quickSort(0, size - 1);
            quickAvg += quickComparision;

            algo.heapSort();
            heapAvg += heapComparision;
        }

        insertionAvg /= 10;
        mergeAvg /= 10;
        quickAvg /= 10;
        heapAvg /= 10;
        double nlogn = size * log2(size);

        file << size << "," << insertionAvg << "," << mergeAvg << "," << quickAvg << "," << heapAvg << "," << nlogn << "\n";
    }

    file.close();
    cout << "Data saved to sorting_data.csv. Use Python to plot the graph." << endl;
    return 0;
}
