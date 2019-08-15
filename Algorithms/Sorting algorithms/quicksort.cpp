//
//  quicksort.cpp
//
//  The following code is based on procedure from the book Introduction to algorithms (third edition).
//

#include <iostream>

int partition(int* arr, int lowIndex, int highIndex) {
    int pivot = arr[highIndex];
    int i = lowIndex - 1;
    for (size_t j = lowIndex; j < highIndex; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[highIndex]);
    return i+1;
}

void quicksort(int*arr, int lowIndex, int highIndex) {
    if (lowIndex < highIndex) {
        int newIndex = partition(arr, lowIndex, highIndex);
        quicksort(arr, lowIndex, newIndex - 1);
        quicksort(arr, newIndex + 1, highIndex);
    }
}

int main() {
    
    int arr[] = {2, 8, 7, 1, 3, 5, 6, 4};
    int maxIndex = 7;
    quicksort(arr, 0, maxIndex);

}
