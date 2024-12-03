#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Utility function to check if a value is within a specified range
bool is_within_range(int value, int lower, int upper) {
    return value >= lower && value <= upper;
}

bool safe_check (vector<int>& report, bool increasing) {
    bool isSafe = true;
    for (size_t i = 0; i < report.size() - 1; ++i) {
        if ((report[i] - report[i + 1]) == 0) {
            isSafe = false;
            break;
        }
        if (increasing) {
            if (!is_within_range(report[i] - report[i + 1], 1, 3)) {
                isSafe = false;
                break;
            }
        } else {
            if (!is_within_range(report[i] - report[i + 1], -3, -1)) {
                isSafe = false;
                break;
            }
        }
    }
    return isSafe;
}

bool brute_check_report(vector<int>& report) {

    for (size_t i = 0; i < report.size() - 1; i++) {

        bool isSafe = false;
        bool increasing = true;

        isSafe = isSafe || safe_check(report, increasing);
        isSafe = isSafe || safe_check(report, !increasing);

        if (isSafe) {
            return true;
        } else {
            for (size_t i = 0; i < report.size(); i++) {
                auto reportCopy = report;
                reportCopy.erase(reportCopy.begin() + i);

                isSafe = isSafe || safe_check(reportCopy, increasing);
                isSafe = isSafe || safe_check(reportCopy, !increasing);

                if (isSafe) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    ifstream inputFile("day-2/input.txt");
    vector<vector<int>> data;
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            vector<int> report;
            stringstream ss(line);
            int number;
            while (ss >> number) {
                report.push_back(number);
            }
            data.push_back(report);
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }

    // Part 1
    int safeCount = 0;
    for (size_t reportIndex = 0; reportIndex < data.size(); ++reportIndex) {
        auto& report = data[reportIndex];
        bool isSafe = false;
        bool increasing = true;

        isSafe = isSafe || safe_check(report, increasing);
        isSafe = isSafe || safe_check(report, !increasing);

        safeCount += isSafe;
    }

    cout << "Safe count: " << safeCount << endl;


    // Part 2
    int safeCount2 = 0;
    for (size_t reportIndex = 0; reportIndex < data.size(); ++reportIndex) {
        auto& report = data[reportIndex];
        bool isSafe = true;
        isSafe = brute_check_report(report);

        safeCount2 += isSafe;
    }

    cout << "Safe count 2: " << safeCount2 << endl;

    return 0;
}
