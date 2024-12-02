#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


using namespace std;

// Utility function to check if a value is within a specified range
bool is_within_range(int value, int lower, int upper) {
    return value >= lower && value <= upper;
}

int main() {
    ifstream inputFile("day-2/input.txt");
    vector<vector<int>> data;
    string line;

    // Readl data from file
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


    int safeCount = 0;

    for (size_t reportIndex = 0; reportIndex < data.size(); ++reportIndex) {
        const auto& report = data[reportIndex];
        int modifier = report[0] - report[1];

        bool isSafe = true;
        for (size_t i = 0; i < report.size() - 1; ++i) {
            if ((report[i] - report[i + 1]) == 0) {
                isSafe = false;
                break;
            }
            if (modifier > 0) {
                if (!is_within_range(report[i] - report[i + 1], 1, 3)) {
                    isSafe = false;
                    break;
                }
            } else if (modifier < 0) {
                if (!is_within_range(report[i] - report[i + 1], -3, -1)) {
                    isSafe = false;
                    break;
                }
            }
        }

        safeCount += isSafe;

        if (isSafe) {
            cout << "Report index " << reportIndex << ": Safe\n";
        }
    }

    cout << "Safe count: " << safeCount << endl;

    return 0;
}
