#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
        for (const auto& vec : input) {
            int max_digit{vec[0]};
            size_t max_id{};
            for (size_t i = 1; i < vec.size() - 1; ++i) {
                if (vec[i] > max_digit) {
                    max_digit = vec[i];
                    max_id = i;
                }
            }
            res += max_digit * 10;
            
            max_digit = vec[max_id + 1];
            for (size_t i = max_id + 1; i < vec.size(); ++i) {
                if (max_digit < vec[i]) {
                    max_digit = vec[i];
                }
            }
            res += max_digit;
        }
        std::cout << res << '\n';
    }
    return 0;
}