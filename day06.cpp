#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

bool valid_move(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {

    freopen("input.txt", "r", stdin);

    string s;
    int row = 0;
    pair<int, int> position;
    pair<int, int> start_position;
    vector<string> grid;

    set<pair<int, int>> diff_positions;

    while (cin >> s) {
        auto caret = s.find('^');

        if (caret != string::npos) {
            position.first = row;
            position.second = static_cast<int>(caret);
        }

        grid.push_back(s);
        row++;
    }

    start_position = position;

    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int curr_direction = 0;

    while (valid_move(position.first, position.second, grid.size(),
                      grid[0].size())) {

        diff_positions.insert(position);
        int dir = curr_direction % 4;

        pair<int, int> next_move = {
            position.first + directions[curr_direction % 4].first,
            position.second + directions[curr_direction % 4].second};

        if (valid_move(next_move.first, next_move.second, grid.size(),
                       grid[0].size())) {
            if (grid[next_move.first][next_move.second] == '#') {
                curr_direction++;
                continue;
            }
        }

        // cout << "x, y: " << position.first << " " << position.second << endl;

        position.first += directions[curr_direction % 4].first;
        position.second += directions[curr_direction % 4].second;
    }

    cout << diff_positions.size() << endl;
    int ans = 0;

    for (auto it = diff_positions.begin(); it != diff_positions.end(); it++) {
        // put a new obstacle somewhere inside the grid,
        // and also inside the normal path of the guard!

        position = start_position;
        curr_direction = 0;

        auto obstacle = *it;
        set<pair<pair<int, int>, int>> new_path;

        if (grid[obstacle.first][obstacle.second] == '^') {
            continue;
        }

        // place new obstacle
        grid[obstacle.first][obstacle.second] = '#';

        // iterate
        // how to check if the guard is stuck inside a loop?
        // match both position and direction. if both are equal, the same
        // outcome is going to happen!

        bool loop = false;

        while (valid_move(position.first, position.second, grid.size(),
                          grid[0].size())) {

            if (new_path.find({position, curr_direction % 4}) !=
                new_path.end()) {
                // loop!
                loop = true;
                break;
            }

            int dir = curr_direction % 4;

            new_path.insert({position, curr_direction % 4});

            pair<int, int> next_move = {position.first + directions[dir].first,
                                        position.second +
                                            directions[dir].second};

            if (valid_move(next_move.first, next_move.second, grid.size(),
                           grid[0].size())) {
                if (grid[next_move.first][next_move.second] == '#') {
                    curr_direction++;
                    continue;
                }
            }

            // cout << "x, y: " << position.first << " " << position.second
            //<< endl;

            position.first += directions[dir].first;
            position.second += directions[dir].second;
        }

        if (loop) {
            ans++;
        }

        // revert changes and try again in a new position
        grid[obstacle.first][obstacle.second] = '.';
    }

    cout << ans;
}
