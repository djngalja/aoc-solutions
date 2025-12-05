#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
        for (std::string temp; file >> temp;) {
            auto pos = temp.find('-');
            if (pos == std::string::npos) {
                break;
            } else {
                long begin = stol(temp.substr(0, pos));
                long end = stol(temp.substr(pos + 1));
                ranges.push_back({begin, end});
            }
        }

        std::sort(ranges.begin(), ranges.end());

        std::vector<Range> final_ranges;
        Range prev{ranges[0]};
        for (size_t i = 1; i < ranges.size(); ++i) {
            if (ranges[i].begin <= prev.end) {
                if (ranges[i].end > prev.end) {
                    prev.end = ranges[i].end;
                }
            } else {
                final_ranges.push_back(prev);
                prev = ranges[i];
            }
        }
        final_ranges.push_back(prev);

        long res{};
        for (const auto& range : final_ranges) {
            res += range.end - range.begin + 1;
        }
        std::cout << res << '\n';
    }
    return 0;
}