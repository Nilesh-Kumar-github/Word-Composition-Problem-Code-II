#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to process the file and find compound words
void processFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    vector<string> words;
    string word;

    // Read words from the file
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    // Start measuring time
    auto start = high_resolution_clock::now();

    // Sort words by length
    sort(words.begin(), words.end(), [](const string &a, const string &b) {
        return a.length() < b.length();
    });

    // Store words in a map for easy lookup
    unordered_map<string, int> wordMap;
    for (const string &s : words) {
        wordMap[s]++;
    }

    int count = 0;
    string longest, secondLongest;

    // Check words from longest to shortest
    for (int i = words.size() - 1; i >= 0; --i) {
        string currentWord = words[i];
        string sb;
        int mismatchCount = 0;

        // Check if current word can be formed by other words
        for (int j = currentWord.length() - 1; j >= 0; --j) {
            sb = currentWord[j] + sb;

            if (wordMap.find(sb) != wordMap.end()) {
                if (sb == currentWord) continue;
                sb.clear();
                mismatchCount = 0;
            } else {
                mismatchCount++;
            }
        }

        // If it's a compound word
        if (mismatchCount == 0) {
            count++;
            if (count == 1) {
                longest = currentWord;
            } else if (count == 2) {
                secondLongest = currentWord;
            }

            if (count == 2) break;
        }
    }

    // Stop measuring time
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    // Output the results
    cout << "Processing file: " << filename << endl;
    cout << "Longest Compound Word: " << longest << endl;
    cout << "Second Longest Compound Word: " << secondLongest << endl;
    cout << "Time taken to process file: " << duration << " milliseconds." << endl;
    cout << endl;
}

int main() {
    // Process both Input_01.txt and Input_02.txt files
    processFile("Input_01.txt");
    processFile("Input_02.txt");

    return 0;
}
