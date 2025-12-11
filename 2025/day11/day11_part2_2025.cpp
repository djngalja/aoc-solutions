#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Key { 
    std::string src;
    bool fft;
    bool dac;

    bool operator<(const Key& other) const {
        return std::tie(src, fft, dac) < std::tie(other.src, other.fft, other.dac);
    }
};

long dfs(const std::string& src, std::map<std::string, std::vector<std::string>>& input, 
    bool fft, bool dac, std::map<Key, long>& memo) {
    if (src == "fft") { fft = true; }
    if (src == "dac") { dac = true; }
    if (src == "out" && fft && dac) { return 1; } 
    Key key{src, fft, dac};
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    long res{};
    for (const auto& str : input[src]) {
        res += dfs(str, input, fft, dac, memo);
    }
    memo[key] = res;
    return res;
}

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::map<std::string, std::vector<std::string>> input;
        for (std::string temp; getline(file, temp);) {
            std::string key = temp.substr(0, 3);
            std::vector<std::string> values;
            int left{5};
            for (size_t right = 5; right < temp.size(); ++right) {
                if (temp[right] == ' ') {
                    values.push_back(temp.substr(left, right - left));
                    left = right + 1;
                }
            }
            values.push_back(temp.substr(left));
            input[key] = values;
        }

        std::map<Key, long> memo;
        long res = dfs("svr", input, false, false, memo);
        std::cout << res << '\n';
    }
    return 0;
}