#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> // std::modf
#include <cctype> // std::isdigit

struct Solution { bool int_sol; int x; int y; };

Solution solve_system(const std::vector<int>&);
std::vector<int> split_str(const std::string&);
bool read_input(const std::string&, std::vector<std::vector<int>>&);
void day13_part1();


int main() {
    day13_part1();
    return 0;
}


void day13_part1() {
    std::vector<std::vector<int>> input;
    if (read_input("input.txt", input)) {
        int tokens {};
        for (const auto& sys : input) {
            Solution sol = solve_system(sys);
            if (sol.int_sol) {
                tokens += sol.x * 3 + sol.y;
            }
        }
        std::cout << "Result: " << tokens << '\n';
    }
}

bool read_input(const std::string& f_name, std::vector<std::vector<int>>& input) {
    std::ifstream file(f_name);
    if(!file) {
        std::cout << "File <" << f_name << " not found\n";
        return false;
    }
    std::string temp_str;
    int cnt {};
    std::vector<int> temp_vec;
    while(getline(file, temp_str)) {
        if (temp_str.empty()) { continue; }
        cnt++;
        std::vector<int> temp_vec2 = split_str(temp_str);
        temp_vec.insert(temp_vec.end(), temp_vec2.begin(), temp_vec2.end());
        if (cnt % 3 == 0) {
            input.push_back(temp_vec);
            temp_vec.clear();
        }
    }
    return true;
}

std::vector<int> split_str(const std::string& str) {
    std::vector<int> vec;
    std::string temp_str;
    for (auto c : str) {
        if (isdigit(c)) {
            temp_str += c;
        } else {
            if (!temp_str.empty()) {
                vec.push_back(stoi(temp_str));
                temp_str.clear();
            }
        }
    }
    if (!temp_str.empty()) {
        vec.push_back(stoi(temp_str));
    }
    return vec;
}

/* Solving a system of 2 linear equations using Cramer's rule
a1*x + b1*y = c1
a2*x + b2*y = c1
*/
Solution solve_system(const std::vector<int>& system) { // Each vector contains 6 values: a1, a2, b1, b2, c1, c2
    double det = system[0] * system[3] - system[2] * system[1]; // det = a1*b2 - b1*a2
    double integral;
    double x = (system[4] * system[3] - system[2] * system[5]) / det; // x = (c1*b2 - b1*c2) / det
    double float_p = std::modf(x, &integral);
    Solution sol {};
    if (float_p) {
        sol.int_sol = false;
        return sol;
    }
    sol.x = x;
    sol.y = (system[0] * system[5] - system[4] * system[1]) / det; // y = (a1*c2 - c1*a2) / det
    sol.int_sol = true;
    return sol;
}
