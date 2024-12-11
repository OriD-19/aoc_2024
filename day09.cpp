#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    string record;
    getline(cin, record);
    int n = 0;

    for (auto c : record) {
        n += c - '0';
    }

    vector<int> nums(n, -1);
    stack<pair<int, int>> offset_right;
    vector<pair<int, int>> offset_free;

    cout << "Total size of the array: " << n << endl;

    int id = 0;
    int curr_idx = 0;
    bool free_mem = false;

    for (auto c : record) {
        if (free_mem) {

            pair<int, int> of;
            // offset of the free space
            of.first = curr_idx;
            curr_idx += (c - '0');
            // length of the free space
            of.second = curr_idx - of.first;

            offset_free.push_back(of);
        } else {
            pair<int, int> of;
            of.first = curr_idx; // offset of the file
            for (int i = 0; i < c - '0'; i++) {
                nums[curr_idx] = id;
                curr_idx++;
            }
            of.second = (curr_idx)-of.first; // length of the file

            offset_right.push(of);
            id++;
        }

        free_mem = !free_mem;
    }

    // swapping the free memory blocks with the ones that are filled
    int index_left = n - 1;
    uint64_t res = 0;

    while (!offset_right.empty()) {
        // while there are numbers to check...

        pair<int, int> curr_id = offset_right.top();

        for (int i = 0;
             i < offset_free.size() && offset_free[i].first < curr_id.first;
             i++) {
            if (offset_free[i].second >=
                curr_id.second) { // the file fits inside the free space

                for (int j = 0; j < min(offset_free[i].second, curr_id.second);
                     j++) {
                    swap(nums[offset_free[i].first + j],
                         nums[curr_id.first + j]);
                }

                offset_free[i].first += curr_id.second;
                offset_free[i].second -= curr_id.second;

                break;
            }
        }

        offset_right.pop();
    }

    for (auto num : nums) {
        if (num == -1) {
            cout << '.';
        } else {
            cout << num;
        }
    }
    cout << endl;

    // calculate the answer
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == -1) {
            continue;
        }

        res += nums[i] * i;
    }

    cout << res;
}
