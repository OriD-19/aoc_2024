#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int paths = 0;

bool validMove(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

pair<int, int> walk(int x, int y, vector<string> grid,
                    pair<int, int> start_position, int curr_position,
                    vector<vector<bool>> visited,
                    map<pair<int, int>, set<pair<int, int>>> &records) {

    if (!validMove(x, y, grid.size(), grid[0].size())) {
        return {-1, -1};
    }

    if (visited[x][y]) {
        return {-1, -1};
    }

    visited[x][y] = true;

    if (grid[x][y] - '0' != curr_position) {
        return {-1, -1}; // go back, wrong height
    }

    if (grid[x][y] == '9') {
        paths++;
        return {x, y};
    }

    for (auto dir : directions) {
        pair<int, int> res =
            walk(x + dir.first, y + dir.second, grid, start_position,
                 curr_position + 1, visited, records);

        if (res.first == -1 && res.second == -1) {
            continue;
        }

        records[start_position].insert(res);
    }

    return {-1, -1};
}

int main() {

    freopen("input.txt", "r", stdin);
    string row;
    vector<string> grid;
    map<pair<int, int>, set<pair<int, int>>> records;

    while (getline(cin, row)) {
        grid.push_back(row);
    }

    vector<vector<bool>> visited(grid.size(),
                                 vector<bool>(grid[0].size(), false));

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '0') {
                walk(i, j, grid, {i, j}, 0, visited, records);
            }
        }
    }

    cout << paths;
}
