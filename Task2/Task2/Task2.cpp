#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double sumElements(const vector<double>& t, int start, int end) {
    double sum = 0;
    for (int i = start; i <= end; i++) {
        sum += t[i];
    }
    return sum;
}

double calculateExpression(double a, double b, const vector<double>& t) {
    double sum1_7 = sumElements(t, 0, 6);
    double sum1_9 = sumElements(t, 0, 8);
    double sum1_4 = sumElements(t, 0, 3);

    double numerator = cbrt(sum1_7 + pow(a, 2) + exp(cbrt(a + pow(b, 2))));
    double denominator = cbrt(b + pow(sum1_9, 2)) + sum1_4;

    return 1 - numerator / denominator;
}

int main() {
    double a = 6.54;
    double b = 4.85;

    vector<double> T = { 3, 4, 15, 2, 3, 4, 5, 4, 1 };

    double result = calculateExpression(a, b, T);

    cout << "Result = " << result << endl;

    return 0;
}