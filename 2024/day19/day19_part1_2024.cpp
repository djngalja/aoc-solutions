#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

bool is_possible(const std::set<std::string>&, const std::string&, std::map<std::string, bool>&);
std::set<std::string> get_patterns(const std::string&);
bool read_input(const std::string&, std::set<std::string>&, std::vector<std::string>&);


int main() {
    std::set<std::string> patterns;
    std::vector<std::string> designs;
    if (read_input("input.txt", patterns, designs)) {
        int cnt {};
        std::map<std::string, bool> memo;
        for (const auto& design : designs) {
            if (is_possible(patterns, design, memo)) {
                cnt++;
            }
        }
        std::cout << "Result: " << cnt << '\n';
    }
    return 0;
}


bool is_possible(const std::set<std::string>& patterns, const std::string& design, std::map<std::string, bool>& memo) {
    if (design.empty()) { return true; }
    if (memo.find(design) != memo.end()) { return memo[design]; }
    for (const auto& pat : patterns) {
        if (design.find(pat) != 0) { continue; }
        std::string new_design = design.substr(pat.size());
        if (is_possible(patterns, new_design, memo)) {
            memo[design] = true;
            return true;
        }
    }
    memo[design] = false;
    return false;
}

std::set<std::string> get_patterns(const std::string& str) {
    std::set<std::string> patterns;
    std::string temp;
    for (char c : str) {
        if (std::isalpha(c)) { temp += c; }
        else {
            if (temp.empty()) { continue; }
            patterns.insert(temp);
            temp.clear();
        }
    }
    if (!temp.empty()) {
        patterns.insert(temp);
    }
    return patterns;
}

bool read_input(const std::string& f_name, std::set<std::string>& patterns, std::vector<std::string>& designs) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    int cnt {};
    for (std::string str; getline(file, str);) {
        cnt++;
        if (cnt == 1) { patterns = get_patterns(str); }
        else if (str.empty()) { continue; }
        else { designs.push_back(str); }
    }
    return true;
}
