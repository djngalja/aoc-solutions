#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Range { 
    long begin; 
    long end; 

    bool operator<(const Range& other) const {
        return std::tie(begin, end) < std::tie(other.begin, other.end);
    }
};

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::vector<Range> ranges;
        std::vector<long> ids;
        bool end_ranges{};
        for (std::string temp; file >> temp;) {
            if (!end_ranges) {
                auto pos = temp.find('-');
                if (pos == std::string::npos) {
                    end_ranges = true;
                } else {
                    long begin = stol(temp.substr(0, pos));
                    long end = stol(temp.substr(pos + 1));
                    ranges.push_back({begin, end});
                }
            } 
            if (end_ranges) {
                ids.push_back(stol(temp));
            }
        }

        std::sort(ranges.begin(), ranges.end());
        std::sort(ids.begin(), ids.end());

        int res{};
        int ptr{};
        for (long id : ids) {
            while (id > ranges[ptr].end) {
                ++ptr;
            } 
            if (ptr >= ranges.size()) { break; }
            if (id >= ranges[ptr].begin && id <= ranges[ptr].end) {
                ++res;
            }
        }
        std::cout << res << '\n';
    }
    return 0;
}