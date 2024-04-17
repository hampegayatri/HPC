#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

// Function to merge two sorted subarrays
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential merge sort
void mergeSortSequential(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortSequential(arr, left, mid);
    mergeSortSequential(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Parallel merge sort with OpenMP
void mergeSortParallel(vector<int>& arr, int left, int right, int threshold) {
    if (left >= right)
        return;

    if (right - left <= threshold) {
        mergeSortSequential(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

#pragma omp parallel sections
    {
#pragma omp section
        mergeSortParallel(arr, left, mid, threshold);
#pragma omp section
        mergeSortParallel(arr, mid + 1, right, threshold);
    }

    merge(arr, left, mid, right);
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int threshold = 100; // Threshold for switching to sequential

    // Perform parallel merge sort
    mergeSortParallel(arr, 0, n - 1, threshold);

    // Output sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
