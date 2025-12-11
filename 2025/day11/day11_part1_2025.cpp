#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void dfs(const std::string& src, const std::string& dest, int& cnt, 
    std::unordered_map<std::string, std::vector<std::string>>& input) {
    if (src == dest) {
        ++cnt;
    } else {
        for (const auto& str : input[src]) {
            dfs(str, dest, cnt, input);
        }
    }
}

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::unordered_map<std::string, std::vector<std::string>> input;
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

        int res{};
        dfs("you", "out", res, input);
        std::cout << res << '\n';
    }
    return 0;
}