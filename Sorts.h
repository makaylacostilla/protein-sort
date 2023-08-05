//
// Created by R M on 8/5/23.
//

#ifndef LOCALVERSION_SORTS_H
#define LOCALVERSION_SORTS_H
#include <vector>
#include <iostream>

void swap(std::string* s1, std::string* s2){
    std::string temp = *s1;
    *s1 = *s2;
    *s2 = temp;

}

//generic merge sort
void mergeAscending(std::vector<std::string>& arr, int left, int mid, int right){
    int arr1 = mid - left + 1;
    int arr2 = right - mid;
    auto *leftArr = new std::string[arr1];
    auto *rightArr = new std::string[arr2];

    for (auto i = 0; i < arr1; i++){
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < arr2; j++){
        rightArr[j] = arr[mid + 1 + j];
    }

    auto i = 0;
    auto j = 0;
    int k = left;

    while (i < arr1 && j < arr2){
        if (leftArr[i] <= rightArr[j]){
            arr[k] = leftArr[i];
            i++;
        }
        else{
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < arr1){
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < arr2){
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSortAscending(std::vector<std::string>& arr, int l, int r){
    if (l >= r){
        return;
    }

    int m = l + (r - l)/2;
    mergeSortAscending(arr, l, m);
    mergeSortAscending(arr, m + 1, r);
    mergeAscending(arr, l, m, r);
}

void mergeDescending(std::vector<std::string>& arr, int left, int mid, int right){
    int arr1 = mid - left + 1;
    int arr2 = right - mid;
    auto *leftArr = new std::string[arr1];
    auto *rightArr = new std::string[arr2];

    for (auto i = 0; i < arr1; i++){
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < arr2; j++){
        rightArr[j] = arr[mid + 1 + j];
    }

    auto i = 0;
    auto j = 0;
    int k = left;

    while (i < arr1 && j < arr2){
        if (leftArr[i] >= rightArr[j]){
            arr[k] = leftArr[i];
            i++;
        }
        else{
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < arr1){
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < arr2){
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSortDescending(std::vector<std::string>& arr, int l, int r){
    if (l >= r){
        return;
    }

    int m = l + (r - l)/2;
    mergeSortDescending(arr, l, m);
    mergeSortDescending(arr, m + 1, r);
    mergeDescending(arr, l, m, r);
}

//generic quick sort
int partitionAscending(std::vector<std::string>& arr, int low, int high){
    swap(&arr[rand() % (high-low+1) + low], &arr[high]);
    std::string pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i+1);
}

void quickSortAscending(std::vector<std::string>& arr, int low, int high){
    if (low < high) {
        int pivot = partitionAscending(arr, low, high);
        quickSortAscending(arr, low, pivot - 1);
        quickSortAscending(arr, pivot + 1, high);
    }
}

int partitionReversed(std::vector<std::string>& arr, int low, int high){
    swap(&arr[rand() % (high-low+1) + low], &arr[high]);
    std::string pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++){
        if (arr[j] > pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i+1);
}

void quickSortReversed(std::vector<std::string>& arr, int low, int high){
    if (low < high) {
        int pivot = partitionReversed(arr, low, high);
        quickSortReversed(arr, low, pivot - 1);
        quickSortReversed(arr, pivot + 1, high);
    }
}

#endif //LOCALVERSION_SORTS_H
