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
    long long int result {0};
    for (auto eq: vec) {
        if (eval_equation(eq)) {
            result += eq.test_value;
        }
    }
    std::cout << "Total calibration result: " << result;
}

bool eval_equation (Equation eq) {
    while (eq.nums.size() > 1) {
        if (eq.test_value%eq.nums.back() == 0) { //division possible
            Equation new_eq {eq};
            new_eq.test_value /= new_eq.nums.back();
            new_eq.nums.pop_back();
            if (eval_equation(new_eq)) {
                return true;
            }
        }
        eq.test_value -= eq.nums.back();
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
        std::size_t i {0};
        std::string temp;
        while (str[i] != ':') {
            temp += str[i];
            i++;
        }
        Equation e;
        e.test_value = stoll(temp);
        temp.clear();
        std::vector<int> temp_v;
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
