#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

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

long long measureBubble(vector<int> arr) {
	auto start = high_resolution_clock::now();
	bubbleSort(arr);
	auto end = high_resolution_clock::now();
	return duration_cast<milliseconds>(end - start).count();
}

long long measureCounting(vector<int> arr) {
	auto start = high_resolution_clock::now();
	countingSort(arr);
	auto end = high_resolution_clock::now();
	return duration_cast<milliseconds>(end - start).count();
}

long long measureQuick(vector<int> arr) {
	auto start = high_resolution_clock::now();
	quickSort(arr, 0, arr.size() - 1);
	auto end = high_resolution_clock::now();
	return duration_cast<milliseconds>(end - start).count();
}

int main() {
	srand(time(0));

	vector<int> sizes = { 8, 80, 1200, 4000, 25000, 100000 };

	for (int size : sizes) {
		cout << "\n=============================\n";
		cout << "Array size = " << size << endl;

		for (int run = 1; run <= 5; run++) {
			vector<int> arr;
			generateArray(arr, size);

			if (size == 8 && run == 1) {
				cout << "Generated array: ";
				printArray(arr);
			}

			vector<int> bubble = arr;
			vector<int> counting = arr;
			vector<int> quick = arr;

			long long bubbleTime = measureBubble(bubble);
			long long countingTime = measureCounting(counting);
			long long quickTime = measureQuick(quick);

			cout << "\nRun #" << run << endl;
			cout << "Bubble Sort: " << bubbleTime << " ms\n";
			cout << "Counting Sort: " << countingTime << " ms\n";
			cout << "Quick Sort: " << quickTime << " ms\n";

			auto asyncStart = high_resolution_clock::now();

			auto f1 = async(launch::async, measureBubble, arr);
			auto f2 = async(launch::async, measureCounting, arr);
			auto f3 = async(launch::async, measureQuick, arr);

			long long asyncBubble = f1.get();
			long long asyncCounting = f2.get();
			long long asyncQuick = f3.get();

			auto asyncEnd = high_resolution_clock::now();
			auto totalAsync = duration_cast<milliseconds>(asyncEnd - asyncStart).count();

			cout << "Async total time: " << totalAsync << " ms\n";
		}
	}

	vector<int> searchArray;
	generateArray(searchArray, 20);
	quickSort(searchArray, 0, searchArray.size() - 1);

	cout << "\n\nSorted array for binary search:\n";
	printArray(searchArray);

	int target;
	cout << "\nEnter element to search: ";
	cin >> target;

	int index = binarySearch(searchArray, target);

	if (index != -1)
		cout << "Element found at index: " << index << endl;
	else
		cout << "Element not found.\n";

	return 0;
}