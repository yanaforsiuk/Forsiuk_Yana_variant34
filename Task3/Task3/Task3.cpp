#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

int** createMatrix(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void fillMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 89 - 44;
        }
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int findMostFrequent(int** matrix, int n) {
    map<int, int> frequency;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            frequency[matrix[i][j]]++;
        }
    }

    int mode = matrix[0][0];
    int maxCount = 0;

    for (auto pair : frequency) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mode = pair.first;
        }
    }

    return mode;
}

int countNegativeSector1(int** matrix, int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i && i + j <= n - 1) {
                if (matrix[i][j] < 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

int replaceSector6(int** matrix, int n, int value) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j > n - 1) {
                matrix[i][j] = value;
                count++;
            }
        }
    }

    return count;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter matrix size n: ";
    cin >> n;

    int** matrix = createMatrix(n);

    fillMatrix(matrix, n);

    cout << "\nOriginal matrix:\n";
    printMatrix(matrix, n);

    int negativeCount = countNegativeSector1(matrix, n);
    cout << "\nNegative elements in sector *1: " << negativeCount << endl;

    int mostFrequent = findMostFrequent(matrix, n);
    int replacedCount = replaceSector6(matrix, n, mostFrequent);

    cout << "Elements replaced in sector 6: " << replacedCount << endl;
    cout << "Most frequent value in matrix: " << mostFrequent << endl;

    cout << "\nModified matrix:\n";
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);

    return 0;
}