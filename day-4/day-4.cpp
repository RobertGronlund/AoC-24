#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

auto input_reader = []() {
    ifstream inputFile("day-4/input.txt");
    string line;
    vector<string> lines;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
    return lines;
};

bool is_within_bounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int search_word(vector<string>& grid, const string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;
    int word_len = word.size();

    int directions[8][2] = {
        {0, 1}, {1, 0}, {1, 1}, {-1, 1}, // right, down, down-right, up-right
        {0, -1}, {-1, 0}, {-1, -1}, {1, -1} // left, up, up-left, down-left
    };

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (grid[x][y] == word[0]) {
                for (auto& dir : directions) {
                    bool match = true;
                    for (int k = 0; k < word_len; ++k) {
                        int new_x = x + k * dir[0];
                        int new_y = y + k * dir[1];
                        if (!is_within_bounds(new_x, new_y, rows, cols) || grid[new_x][new_y] != word[k]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) count++;
                }
            }
        }
    }
    return count;
}

int main() {
    vector<string> input = input_reader();
    string word = "XMAS"; // Example word to search for

    int count = search_word(input, word);
    cout << "The word '" << word << "' was found " << count << " times in the grid." << endl;

    return 0;
}
