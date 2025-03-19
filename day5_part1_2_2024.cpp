#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

std::pair<int, int> sum_mid_nums(std::vector<std::vector<int>>&, const std::multimap<int, int>&);
bool read_input(const std::string&, std::multimap<int, int>&, std::vector<std::vector<int>>&);

class Compare {
public:
    std::multimap<int, int> rules;
    Compare(const std::multimap<int, int>& r) : rules {r} {}
    bool operator()(int, int);
};


int main() {
    std::multimap<int, int> rules;
    std::vector<std::vector<int>> updates;
    if (read_input("input.txt", rules, updates)) {
        auto result = sum_mid_nums(updates, rules);
        std::cout << "Part 1: " << result.first << "\nPart 2: " << result.second << '\n';
    }
    return 0;
}


bool read_input(const std::string& f_name, std::multimap<int, int>& rules, std::vector<std::vector<int>>& updates) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    for(std::string str; getline(file, str);) { // Read rules first
        if (str.empty()) { break; } // An empty line separates rules and updates
        std::vector<int> rule;
        std::istringstream line(str);
        for (std::string str2; getline(line, str2, '|');) {
            rule.push_back(stoi(str2));
        }
        rules.insert({rule[0], rule[1]});
    }
    for(std::string str; getline(file, str);) { // Read updates
        std::vector<int> pages;
        std::istringstream line(str);
        for (std::string str2; getline(line, str2, ',');) {
            pages.push_back(stoi(str2));
        }
        updates.push_back(pages);
    }
    return true;
}

std::pair<int, int> sum_mid_nums(std::vector<std::vector<int>>& updates, const std::multimap<int, int>& rules) {
    int sum1 {};
    int sum2 {};
    for (auto& pages : updates) {
        if (std::is_sorted(pages.begin(), pages.end(), Compare(rules))) {
            sum1 += pages[pages.size()/2];
        } else {
            // Sort incorrectly-ordered updates only
            std::sort(pages.begin(), pages.end(), Compare(rules));
            sum2 += pages[pages.size()/2];
        }
    }
    return {sum1, sum2};
}

bool Compare::operator()(int a, int b) {
    auto range = rules.equal_range(a);
    for (auto i = range.first; i != range.second; ++i) {
        if (i->second == b) {
            return true;
        }
    }
    return false;
}
