#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

auto input_reader = []() {
    ifstream inputFile("day-3/input.txt");
    string line;
    string input;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            input += line;
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
    return input;
};

int mul_func(const string& match) {
    regex pattern(R"(\d{1,3})");
    smatch matches;
    vector<int> numbers;
    string::const_iterator searchStart(match.cbegin());
    while (regex_search(searchStart, match.cend(), matches, pattern)) {
        numbers.push_back(stoi(matches[0]));
        searchStart = matches.suffix().first;
    }

    if (numbers.size() == 2) {
        return numbers[0] * numbers[1];
    } else {
        cerr << "Error: Expected exactly 2 numbers in the match." << endl;
        return 0;
    }
}

int main() {
    string input = input_reader();
    regex pattern(R"(mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\))");
    smatch matches;
    vector<string> match_results;
    int total {0};
    bool do_mul {true};

    string::const_iterator searchStart(input.cbegin());
    while (regex_search(searchStart, input.cend(), matches, pattern)) {
        match_results.push_back(matches[0]);
        searchStart = matches.suffix().first;
    }

    // Output the matches and their products to verify
    for (const auto& match : match_results) {
        if (match == "do()") {
            do_mul = true;
            continue;
        } else if (match == "don't()") {
            do_mul = false;
            continue;
        } else {
            if (do_mul) {
                total += mul_func(match);
            }
        }

    }

    cout << "Total: " << total << endl;

    return 0;
}
