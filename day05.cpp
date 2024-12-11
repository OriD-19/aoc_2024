#include "split.cpp"
#include <iostream>
#include <vector>

using namespace std;
int main() {

    vector<pair<int, int>> page_nums;
    freopen("input.txt", "r", stdin);

    int a, b;
    string line;

    while (getline(cin, line)) {
        if (line == "") {
            break;
        }

        auto res = split_input(line, "|");
        a = res[0];
        b = res[1];

        page_nums.push_back({a, b});
    }

    int sum = 0;

    while (getline(cin, line)) {
        auto order = split_input(line, ",");

        bool valid = true;

        for (int i = 0; i < order.size(); i++) {

            int curr = order[i];

            for (int j = i + 1; j < order.size(); j++) {

                for (int k = 0; k < page_nums.size(); k++) {
                    if (page_nums[k].first == order[j]) {
                        if (page_nums[k].second == order[i]) {
                            // swap until in the correct position...
                            // how?
                            swap(order[j], order[i]);
                            valid = false;
                            break;
                        }
                    }
                }
            }
        }

        // incorrect ordering
        if (!valid)
            sum += order[order.size() / 2];
    }

    cout << sum;
}
