#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> //isdigit()

struct Equation {
    long long int test_value;
    std::vector<int> nums;
};

void read_equations(std::vector<Equation>&);
bool eval_equation (Equation);
void day7_part1();





int main() {
    day7_part1();
    return 0;
}




void day7_part1() {
    std::vector<Equation> vec;
    read_equations(vec);

    long long int result = 0;
    for (auto eq: vec) {
        if (eval_equation(eq)) {
            result += eq.test_value;
        }
    }
    std::cout << "total calibration result: " << result;
}



bool eval_equation (Equation eq) {
    bool result = false;
    while (eq.nums.size() > 1) {
        if (eq.test_value%eq.nums[eq.nums.size()-1] == 0) {
            Equation new_eq = eq;
            new_eq.test_value /= new_eq.nums[new_eq.nums.size()-1];
            new_eq.nums.pop_back();
            result = eval_equation(new_eq);
            if (result) {
                return true;
            }
        }
        eq.test_value -= eq.nums[eq.nums.size()-1];
        eq.nums.pop_back();
    }
    if (eq.test_value == eq.nums[0]) {
        return true;
    }
    return false;
}



void read_equations(std::vector<Equation>& vec) {
    std::ifstream file("advent_day7.txt");
    if (!file) {
        std::cout << "File not found\n";
    }
    std::string str;
    while (getline(file, str)) {
        std::size_t i = 0;
        std::string temp;
        std::vector<int> temp_v;
        Equation e;
        while (str[i] != ':') {
            temp += str[i];
            i++;
        }
        e.test_value = stoll(temp);
        temp.clear();
        while (i != str.size()) {
            if(isdigit(str[i])) {
                temp += str[i];
            } else {
                if (!temp.empty()) {
                    temp_v.push_back(stoi(temp));
                    temp.clear();
                }
            }
            i++;
        }
        temp_v.push_back(stoi(temp));
        e.nums = temp_v;
        vec.push_back(e);
    }
}
