#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int find_modifier(const vector<int>& report) {
    int modifier {};
    for (size_t i = 0; i < report.size()-1; i++) {
        if (report[i] - report[i+1] > 0) {
            modifier--;
        } else if (report[i] - report[i+1] < 0) {
            modifier++;
        }
    }

    return modifier;
}

// Utility function to check if a value is within a specified range
bool is_within_range(int value, int lower, int upper) {
    return value >= lower && value <= upper;
}




int main() {
    ifstream inputFile("day-2/test.txt");
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

    int safeCount = 0;
    for (size_t reportIndex = 0; reportIndex < data.size(); ++reportIndex) {
        auto& report = data[reportIndex];

        int modifier = find_modifier(report);
        int magicDiff = 3;
        cout << "Modifier: " << modifier << endl;
        cout << "Report size: " << report.size() << endl;

        bool isSafe = true;

        if (abs(modifier) + magicDiff < report.size()) {
            isSafe = false;
        } else {
            bool increasing = modifier > 0;

            bool problemDampner = false;
            for (int i = 0; i < report.size() - 1; i++) {
                if (i == report.size() - 1 && !problemDampner){
                    break;
                }

                if (increasing == (report[i] - report[i + 1] > 0) || !is_within_range(abs(report[i] - report[i + 1]), 1, 3) ) {
                   if (!problemDampner) {
                        problemDampner = true;

                        if (report[i] > report[i + 2]) {
                           report.erase(report.begin() + i);

                        }
                        else {
                            report.erase(report.begin() + i + 1);
                            i--;
                        }
                    } else {
                        isSafe = false;
                    }
                } else if (!increasing == (report[i] - report[i + 1] < 0) || !is_within_range(abs(report[i] - report[i + 1]), 1, 3)) {
                    if (!problemDampner) {
                        problemDampner = true;

                        if (report[i] < report[i + 2]) {
                           report.erase(report.begin() + i);

                        }
                        else {
                            report.erase(report.begin() + i + 1);
                            i--;
                        }
                    } else {
                        isSafe = false;
                    }
                }

                // if (!is_within_range(report[i] - report[i + 1], 1, 3)) {
                //     if (!problemDampner) {
                //         problemDampner = true;
                //         report.erase(report.begin() + i + 1);
                //         i--;
                //     } else {
                //         isSafe = false;
                //     }
                // }
            }
        }


        safeCount += isSafe;

        if (isSafe) {
            cout << "Report index " << reportIndex << ": Safe\n";
        } else {
            cout << "Report index " << reportIndex << ": Unsafe\n";
        }
    }

    cout << "Safe count: " << safeCount << endl;

    return 0;
}
