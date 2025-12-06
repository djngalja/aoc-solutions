#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::vector<std::string> numbers;
        std::vector<char> operators;
        for (std::string temp; getline(file, temp);) {
            if (temp[0] == '*' || temp[0] == '+') {
                std::istringstream is(temp);
                for (char ch; is >> ch;) {
                    operators.push_back(ch);
                }
            } else {
                numbers.push_back(temp);
            }
        }

        int op_id = operators.size() - 1;
        std::vector<std::vector<long>> final_numbers(operators.size());
        for (int j = numbers[0].size() - 1; j >= 0; --j) {
            std::string num{};
            for (size_t i = 0; i < numbers.size(); ++i) {
                if (numbers[i][j] != ' ') {
                    num += numbers[i][j];
                }
            }
            if (num.empty()) { 
                --op_id; 
                continue;
            }
            final_numbers[op_id].push_back(stol(num));
        } 

        long res{};
        for (size_t i = 0; i < operators.size(); ++i) {
            if (operators[i] == '+') {
                res += std::accumulate(final_numbers[i].begin(), final_numbers[i].end(), 0);
            } else {
                res += std::accumulate(final_numbers[i].begin(), final_numbers[i].end(), 1L, std::multiplies<long>());
            }
        }
        std::cout << res << '\n'; 
    }
    return 0;
}