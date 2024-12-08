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

int find_xmas(vector<string>& grid, const string& word) {
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

int find_x_mas(vector<string>& grid, const string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;
    int word_len = word.size();

    int directions[4][2] = {
        {1, 1}, {-1, 1}, // down-right, up-right
        {-1, -1}, {1, -1} // up-left, down-left
    };

    // Start on 1 to not go out of bounds
    for (int x = 1; x < rows-1; ++x) {
        for (int y = 1; y < cols-1; ++y) {
            if (grid[x][y] == word[1]) {
                if ((grid[x+1][y+1] == word[0] && grid[x-1][y-1] == word[2]) || (grid[x+1][y+1] == word[2] && grid[x-1][y-1] == word[0])) {
                    if ((grid[x+1][y-1] == word[0] && grid[x-1][y+1] == word[2]) || (grid[x+1][y-1] == word[2] && grid[x-1][y+1] == word[0])) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    vector<string> input = input_reader();
    string word = "XMAS";

    int count = find_xmas(input, word);
    cout << "The word '" << word << "' was found " << count << " times in the grid." << endl;

    word = "MAS";
    count = find_x_mas(input, word);
    cout << "The word '" << word << "' was found " << count << " times in the grid." << endl;

    return 0;
}
