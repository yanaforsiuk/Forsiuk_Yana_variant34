#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> readSentences(const string& filename) {
	ifstream fin(filename);
	vector<string> sentences;
	string line;

	while (getline(fin, line)) {
		if (!line.empty()) {
			sentences.push_back(line);
		}
	}

	fin.close();
	return sentences;
}

void sortByLength(vector<string>& sentences) {
	sort(sentences.begin(), sentences.end(),
		[](const string& a, const string& b) {
			return a.length() < b.length();
		});
}

void writeReverseToFile(const string& filename, const vector<string>& sentences) {
	ofstream fout(filename);

	for (auto it = sentences.rbegin(); it != sentences.rend(); ++it) {
		fout << *it << endl;
	}

	fout.close();
}

int main() {
	string inputFile = "input.txt";
	string outputFile = "output.txt";

	vector<string> sentences = readSentences(inputFile);

	sortByLength(sentences);

	writeReverseToFile(outputFile, sentences);

	cout << "Processing completed. Check output.txt" << endl;

	return 0;
}