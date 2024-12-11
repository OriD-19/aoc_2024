#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

unordered_set<char> letters = {'X', 'M', 'A', 'S'};

int is_xmas(int row, int col, vector<string> &grid,
            vector<vector<bool>> &visited) {
    // find both diagonals
    // compare them to either MAS or SAM
    // visit all of the cells; check that at least one of the cells is not
    // visited for validating a new X

    if (row - 1 < 0 || row + 1 >= grid.size()) {
        return 0;
    }

    if (col - 1 < 0 || col + 1 >= grid[0].size()) {
        return 0;
    }

    string first_diag;
    string second_diag;

    int valid_diags = 0;

    first_diag += grid[row - 1][col - 1];
    first_diag += 'A';
    first_diag += grid[row + 1][col + 1];

    second_diag += grid[row - 1][col + 1];
    second_diag += 'A';
    second_diag += grid[row + 1][col - 1];

    if (first_diag == "SAM" || first_diag == "MAS") {
        if (!(visited[row - 1][col - 1] && visited[row][col] &&
              visited[row + 1][col + 1])) {
            // if at least one of them is not visited
            valid_diags++;
        }
    }

    if (second_diag == "SAM" || second_diag == "MAS") {
        if (!(visited[row - 1][col + 1] && visited[row][col] &&
              visited[row + 1][col - 1])) {
            // if at least one of them is not visited
            valid_diags++;
        }
    }

    if (valid_diags == 2) {
        // mark all of these stuff as visited;
        visited[row - 1][col + 1] = true;
        visited[row + 1][col + 1] = true;
        visited[row][col] = true;
        visited[row - 1][col + 1] = true;
        visited[row - 1][col - 1] = true;
    }

    return valid_diags == 2;
}

int main() {
    vector<string> grid;
    string row;

    freopen("input.txt", "r", stdin);

    while (getline(cin, row)) {
        grid.push_back(row);
    }

    vector<vector<bool>> checked(grid.size(), vector<bool>(grid[0].size()));
    int ans = 0;

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            if (grid[row][col] == 'A') {
                // search for an A, which must be the center of the X (MAS,
                // lmao)
                ans += is_xmas(row, col, grid, checked);
            }
        }
    }

    cout << ans;
}
