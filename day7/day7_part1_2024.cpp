#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> // std::isdigit

bool eval_equation(std::vector<long long>);
std::vector<long long> split_str(const std::string&);
bool read_equations(const std::string&, std::vector<std::vector<long long>>&);
void day7_part1();


int main() {
    day7_part1();
    return 0;
}


void day7_part1() {
    std::vector<std::vector<long long>> equations;
    if (read_equations("input.txt", equations)) {
        long long result {};
        for (const auto& eq : equations) {
            if (eval_equation(eq)) {
                result += eq[0]; // the 1st element is test value
            }
        }
        std::cout << "Total calibration result: " << result << '\n';
    }
}

bool read_equations(const std::string& f_name, std::vector<std::vector<long long>>& equations) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string temp_str;
    while (getline(file, temp_str)) {
        equations.push_back(split_str(temp_str));
    }
    return true;
}

std::vector<long long> split_str(const std::string& str) {
    std::vector<long long> temp_vec;
    std::string temp_str;
    for (char c : str) {
        if (isdigit(c)) {
            temp_str += c;
        } else {
            if (!temp_str.empty()) {
                temp_vec.push_back(stoll(temp_str));
                temp_str.clear();
            }
        }
    }
    temp_vec.push_back(stoll(temp_str));
    return temp_vec;
}

bool eval_equation(std::vector<long long> eq) {
    while (eq.size() > 2) {
        if (eq[0] % eq.back() == 0) { // division is possible
            std::vector<long long> new_eq {eq};
            new_eq[0] /= new_eq.back();
            new_eq.pop_back();
            if (eval_equation(new_eq)) {
                return true;
            }
        }
        eq[0] -= eq.back();
        eq.pop_back();
    }
    return eq[0] == eq[1];
}
