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
        std::vector<std::vector<long>> matrix;
        std::vector<char> operators;
        for (std::string temp; getline(file, temp);) {
            std::istringstream is(temp);
            if (temp[0] == '*' || temp[0] == '+') {
                for (char ch; is >> ch;) {
                    operators.push_back(ch);
                }
            } else {
                std::vector<long> vec;
                for (long i = 0; is >> i;) {
                    vec.push_back(i);
                }
                matrix.push_back(vec);
            }
        }

        std::vector<std::vector<long>> transpose(matrix[0].size(), std::vector<long>(matrix.size()));
        for (size_t i = 0; i < transpose.size(); ++i) {
            for (size_t j = 0; j < transpose[i].size(); ++j) {
                transpose[i][j] = matrix[j][i];
            }
        }

        long res{};
        for (size_t i = 0; i < operators.size(); ++i) {
            if (operators[i] == '+') {
                res += std::accumulate(transpose[i].begin(), transpose[i].end(), 0);
            } else {
                res += std::accumulate(transpose[i].begin(), transpose[i].end(), 1L, std::multiplies<long>());
            }
        }

        std::cout << res << '\n';
    }
    return 0;
}