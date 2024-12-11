#include "split.h"
#include <string>
#include <vector>

std::vector<int> split_input(std::string &s, const std::string &delimiter) {
    // split the input into various tokens
    std::vector<int> res;
    size_t pos = 0;
    int token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = std::stoi(s.substr(0, pos));
        res.push_back(token);
        // delete the recently processed part
        s.erase(0, pos + delimiter.length());
    }

    res.push_back(std::stoi(s));

    return res;
}
