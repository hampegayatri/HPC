#include <iostream>
#include <vector>
#include <omp.h>
#include <limits>
#include <numeric>

using namespace std;

// Parallel reduction for finding minimum value
int parallelMin(const vector<int>& arr) {
    int min_val = numeric_limits<int>::max();

#pragma omp parallel for reduction(min: min_val)
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    return min_val;
}

// Parallel reduction for finding maximum value
int parallelMax(const vector<int>& arr) {
    int max_val = numeric_limits<int>::min();

#pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    return max_val;
}

// Parallel reduction for finding sum
int parallelSum(const vector<int>& arr) {
    int sum = 0;

#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }

    return sum;
}

// Parallel reduction for finding average
double parallelAverage(const vector<int>& arr) {
    int sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main() {
    // Example array
    vector<int> arr = {5, 2, 9, 1, 7, 3, 8, 6, 4};

    // Calculate min, max, sum, and average in parallel
    int min_val = parallelMin(arr);
    int max_val = parallelMax(arr);
    int sum = parallelSum(arr);
    double average = parallelAverage(arr);

    // Output results
    cout << "Minimum value: " << min_val << endl;
    cout << "Maximum value: " << max_val << endl;
    cout << "Sum of values: " << sum << endl;
    cout << "Average value: " << average << endl;

    return 0;
}
