#include "split.cpp"
#include <iostream>
#include <regex>
#include <utility>

using namespace std;

pair<int, int> mul(const string &mul_operation) {
    pair<int, int> res;

    // guarantees the following structure:
    // mul([num],[num])

    auto begin = mul_operation.find("(");
    string paren = mul_operation.substr(begin);
    string args = paren.substr(1, paren.size() - 2);

    vector<int> nums = split_input(args, ",");

    res.first = nums[0];
    res.second = nums[1];

    return res;
}

int main() {
    regex matching_mul(
        "do\\(\\)|don't\\(\\)|mul\\(\\d+,\\d+\\)", // go to regexr.com and
                                                   // remove one forward slash
                                                   // on each special char to
                                                   // see how it works :)
        regex_constants::ECMAScript | regex_constants::icase);

    freopen("input.txt", "r", stdin);
    string whole_thing, curr;
    while (cin >> curr) {
        whole_thing += curr;
    }

    auto begin =
        sregex_iterator(whole_thing.begin(), whole_thing.end(), matching_mul);
    auto end = sregex_iterator();

    int ans = 0;
    bool do_mul = true;

    for (auto i = begin; i != end; i++) {
        // get each mul operator

        smatch match = *i;
        string smatch = match.str();

        if (smatch == "do()") {
            do_mul = true;
            continue;
        } else if (smatch == "don't()") {
            do_mul = false;
            continue;
        }

        if (!do_mul) {
            continue;
        }

        auto operation = mul(smatch);
        ans += operation.first * operation.second;
    }

    cout << ans;
}
