#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

    vector<int> a;
    unordered_map<int, int> b;

    int aa, bb;

    freopen("input.txt", "r", stdin);

    while (cin >> aa >> bb) {
        a.push_back(aa);
        b[bb] += 1;
    }

    int sum_score = 0;

    for (int score : a) {
        sum_score += score * b[score];
    }

    cout << sum_score;
}
