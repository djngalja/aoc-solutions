#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

long long cnt_options(const std::set<std::string>&, const std::string&, std::map<std::string, long long>&);
std::set<std::string> get_patterns(const std::string&);
bool read_input(const std::string&, std::set<std::string>&, std::vector<std::string>&);


int main() {
    std::set<std::string> patterns;
    std::vector<std::string> designs;
    if (read_input("input.txt", patterns, designs)) {
        long long res {};
        std::map<std::string, long long> memo;
        for (const auto& design : designs) {
            res += cnt_options(patterns, design, memo);
        }
        std::cout << "Result: " << res << '\n';
    }
    return 0;
}


// Solve using recursion + memoization
long long cnt_options(const std::set<std::string>& patterns, const std::string& design, std::map<std::string, long long>& memo) {
    if (design.empty()) { return 1; }
    if (memo.find(design) != memo.end()) { return memo[design]; }
    long long cnt {};
    for (const auto& pat : patterns) {
        if (design.find(pat) != 0) { continue; } // if not prefix
        std::string new_design = design.substr(pat.size()); // remove prefix
        cnt += cnt_options(patterns, new_design, memo);
    }
    memo[design] = cnt;
    return cnt;
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
