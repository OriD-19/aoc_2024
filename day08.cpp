#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool validPosition(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {

    string row;
    vector<string> grid;

    freopen("input.txt", "r", stdin);

    while (getline(cin, row)) {
        grid.push_back(row);
    }

    vector<vector<bool>> antinodes(grid.size(), vector<bool>(grid[0].size()));
    unordered_map<char, vector<pair<int, int>>> antennas;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '.') {
                antennas[grid[i][j]].push_back({i, j}); // (row, col)
            }
        }
    }

    for (auto antenna : antennas) {
        for (int i = 0; i < antenna.second.size(); i++) {
            for (int j = 0; j < antenna.second.size(); j++) {
                if (i != j) { // do not compare with itself

                    int diff_row =
                        (antenna.second[j].first - antenna.second[i].first);
                    int diff_col =
                        (antenna.second[j].second - antenna.second[i].second);

                    cout << "Diffs between " << antenna.first << ": "
                         << diff_row << " " << diff_col << endl;

                    int pos_row = diff_row;
                    int pos_col = diff_col;

                    int new_pos_row = antenna.second[i].first + pos_row;
                    int new_pos_col = antenna.second[i].second + pos_col;

                    while (validPosition(new_pos_row, new_pos_col, grid.size(),
                                         grid[0].size())) {
                        antinodes[new_pos_row][new_pos_col] = true;

                        new_pos_row += pos_row;
                        new_pos_col += pos_col;
                    }
                }
            }
        }
    }

    int count = 0;

    for (int i = 0; i < antinodes.size(); i++) {
        for (int j = 0; j < antinodes[0].size(); j++) {

            if (grid[i][j] != '.') {
                cout << grid[i][j];
            } else if (antinodes[i][j]) {
                cout << '#';
            } else {
                cout << '.';
            }

            count += antinodes[i][j];
        }
        cout << endl;
    }

    cout << count;

    return 0;
}
