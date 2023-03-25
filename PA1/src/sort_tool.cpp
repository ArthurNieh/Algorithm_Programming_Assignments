// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i=1;i<data.size();i++){
        int key = data[i];

        int index_forward = i-1;
        while(index_forward >= 0 && data[index_forward] > key){
            data[index_forward+1] = data[index_forward];
            index_forward --;
        }
        data[index_forward+1] = key;
    }
    return;
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low<high){
        int q = Partition(data, low, high);
        QuickSortSubVector(data, low, q-1);
        QuickSortSubVector(data, q+1, high);
    }
    return;
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[high];

    if((data[low] < x && data[(high+low)/2] < data[low]) || (data[low] > x && data[(high+low)/2] > data[low])){
        x = data[low];
        data[low] = data[high];
        data[high] = x;
    }
    else if((data[low] < data[(high+low)/2] && data[(high+low)/2] < x) || (data[low] > data[(high+low)/2] && data[(high+low)/2] > x)){
        x = data[(high+low)/2];
        data[(high+low)/2] = data[high];
        data[high] = x;
    }

    int index = low - 1;
    for(int i=low;i<high;i++){
        if(data[i]<=x){
            index ++;
            swap(data[index], data[i]);
        }
    }
    swap(data[index+1],data[high]);
    return index+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high){
        MergeSortSubVector(data, low, (low+high)/2);
        MergeSortSubVector(data, (low+high)/2 + 1, high);
        Merge(data, low, (low+high)/2, (low+high)/2+1, high);
    }
    return;
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int length_1 = middle2 - low;
    int length_2 = high - middle1;
    vector<int> left_subarray;
    vector<int> right_subarray;
    for(int i=low;i<middle2;i++){
        left_subarray.push_back(data[i]);
    }
    for(int i=middle2;i<=high;i++){
        right_subarray.push_back(data[i]);
    }

    int index_left = 0;
    int index_right = 0;
    for(int i=low;i<=high;i++){
        if((left_subarray[index_left] <= right_subarray[index_right] && index_left<length_1) || index_right>=length_2){
            data[i] = left_subarray[index_left];
            index_left ++;
        }
        else{
            data[i] = right_subarray[index_right];
            index_right ++;
        }
    }
    return;
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here

    if((root+1)*2-1 >= heapSize) return;
    else if((root+1)*2 == heapSize){
        if(data[root]<data[(root+1)*2-1]){
            swap(data[root],data[(root+1)*2-1]);
        }
        return;
    }
    else{
        int max_key = data[root];
        if(data[(root+1)*2-1] > max_key) max_key = data[(root+1)*2-1];
        if(data[(root+1)*2] > max_key) max_key = data[(root+1)*2];
        
        if(max_key == data[(root+1)*2-1]){
            swap(data[root],data[(root+1)*2-1]);
            MaxHeapify(data, (root+1)*2-1);
        }
        else if(max_key == data[(root+1)*2]){
            swap(data[root],data[(root+1)*2]);
            MaxHeapify(data, (root+1)*2);
        }
        return;
    }   
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=heapSize-1;i>=0;i--){
        MaxHeapify(data, i);
    }
}
