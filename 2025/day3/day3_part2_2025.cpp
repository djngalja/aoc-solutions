#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::vector<std::vector<int>> input;
        for (std::string temp; file >> temp;) {
            std::vector<int> vec(temp.size());
            for (size_t i = 0; i < temp.size(); ++i) {
                vec[i] = temp[i] - '0';
            }
            input.push_back(vec);
        }

        long res{};
        const int len{12};
        for (const auto& vec : input) {
            int max_id{-1};
            for (int i = 0; i < len; ++i) {
                int max_digit{};
                for (size_t j = 1 + max_id; j <= vec.size() - (len - i); ++j) {
                    if (vec[j] > max_digit) {
                        max_digit = vec[j];
                        max_id = j;
                    }
                }
                res += max_digit * std::pow(10, len - 1 - i);
            }
        }
        std::cout << res << '\n';
    }
    return 0;
}