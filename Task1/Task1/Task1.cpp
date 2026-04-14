#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateArray(vector<int>& arr, int size) {
    arr.resize(size);
    for (int& x : arr)
        x = rand() % 10000;
}

void printArray(const vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void countingSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);

    for (int x : arr)
        count[x]++;

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]--) {
            arr[index++] = i;
        }
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main() {
    srand(time(0));

    vector<int> sizes = { 8, 80, 1200, 4000, 25000, 100000 };

    for (int size : sizes) {
        vector<int> arr;
        generateArray(arr, size);

        vector<int> bubble = arr;
        vector<int> counting = arr;
        vector<int> quick = arr;

        cout << "\nArray size = " << size << endl;

        auto start = chrono::high_resolution_clock::now();
        bubbleSort(bubble);
        auto end = chrono::high_resolution_clock::now();
        cout << "Bubble Sort: "
            << chrono::duration_cast<chrono::milliseconds>(end - start).count()
            << " ms\n";

        start = chrono::high_resolution_clock::now();
        countingSort(counting);
        end = chrono::high_resolution_clock::now();
        cout << "Counting Sort: "
            << chrono::duration_cast<chrono::milliseconds>(end - start).count()
            << " ms\n";

        start = chrono::high_resolution_clock::now();
        quickSort(quick, 0, quick.size() - 1);
        end = chrono::high_resolution_clock::now();
        cout << "Quick Sort: "
            << chrono::duration_cast<chrono::milliseconds>(end - start).count()
            << " ms\n";
    }

    return 0;
}