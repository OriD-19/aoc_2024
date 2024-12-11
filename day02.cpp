#include "split.cpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);

    vector<int> reports;
    string report;
    int total = 0;

    while (getline(cin, report)) {
        vector<int> curr_report = split_input(report, " ");

        bool valid = false;

        // allow for one exclusion of a single level
        for (int k = -1; k < static_cast<int>(curr_report.size()); k++) {
            // remove one element from each report
            vector<int> removed_report = curr_report;
            bool decreasing = false, increasing = false;

            if (k >= 0) {
                removed_report.erase(removed_report.begin() + k);
            }

            bool valid_comb = true;

            for (int i = 0; i < removed_report.size() - 1; i++) {
                int diff = removed_report[i] - removed_report[i + 1];
                bool decrease_curr = removed_report[i] > removed_report[i + 1];

                if (abs(diff) < 1 || abs(diff) > 3) {
                    valid_comb = false;
                    break;
                }

                if (decrease_curr) {
                    if (increasing) {
                        valid_comb = false;
                        break;
                    }
                    decreasing = true;
                }

                if (!decrease_curr) {
                    if (decreasing) {
                        valid_comb = false;
                        break;
                    }
                    increasing = true;
                }
            }

            if (valid_comb) {
                valid = true;
                break;
            }
        }

        total += valid;
    }

    cout << total;
}
