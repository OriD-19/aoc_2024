#include "split.cpp"
#include <cstdlib>
#include <inttypes.h>
#include <iostream>
#include <string>

using namespace std;

bool checkNextOperand(uint64_t res, uint64_t loc_result, int op,
                      vector<int> &operands, int curr_index) {

    if (curr_index == operands.size()) {
        return loc_result == res;
    }

    if (op == 0) {
        loc_result += operands[curr_index];
    } else if (op == 1) {
        loc_result *= operands[curr_index];
    } else if (op == 2) {
        string str_loc = to_string(loc_result);
        string str_op = to_string(operands[curr_index]);

        string res = str_loc + str_op;
        loc_result = strtoll(res.c_str(), NULL, 10);
    }

    return checkNextOperand(res, loc_result, 0, operands, curr_index + 1) ||
           checkNextOperand(res, loc_result, 1, operands, curr_index + 1) ||
           checkNextOperand(res, loc_result, 2, operands, curr_index + 1);
}

int main() {

    string eq;
    uint64_t res = 0;

    freopen("input.txt", "r", stdin);

    while (getline(cin, eq)) {
        string result_string = eq.substr(0, eq.find(':'));
        uint64_t result = strtoll(result_string.c_str(), NULL, 10);

        cout << "Result: " << result << endl;

        string other_nums = eq.substr(eq.find(' ') + 1);
        vector<int> operands = split_input(other_nums, " ");

        bool valid = false;

        valid = checkNextOperand(result, operands[0], 0, operands, 1) ||
                checkNextOperand(result, operands[0], 1, operands, 1) ||
                checkNextOperand(result, operands[0], 2, operands, 1);

        if (valid) {
            res += result;
        }
    }

    cout << res;
}
