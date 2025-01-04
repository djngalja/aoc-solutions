#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> //isdigit()

struct Equation {
    long long int test_value;
    std::vector<long long int> nums;
};

auto sum(long long int, long long int);
auto prod(long long int, long long int);
auto conc(long long int, long long int);
void read_equations(std::vector<Equation>&);
bool eval_equation(Equation);
bool eval_equation2(Equation&);
void day7_part2();


int main() {
    day7_part2();
    return 0;
}


void day7_part2() {
    std::vector<Equation> vec;
    read_equations(vec);
    long long int result {0};
    int counter {0};
    for (auto& eq : vec) {
        if (++counter%10 == 0) {
            std::cout << "Progress: " << counter << " out of " << vec.size() << '\n';
        }
        if (eval_equation(eq)) {
            result += eq.test_value;
        }
        else {
            if (eval_equation2(eq)) {
                result += eq.test_value;
            }
        }
    }
    std::cout << "\nTotal calibration result: " << result;
}

auto sum(long long int a, long long int b) {
    return a + b;
}

auto prod(long long int a, long long int b) {
    return a * b;
}

auto conc(long long int a, long long int b) {
    std::string a_str = std::to_string(a);
    std::string b_str = std::to_string(b);
    return stoll(a_str + b_str);
}

bool eval_equation2(Equation& eq) {
    while (eq.nums.size() > 1) {
        auto s = sum(eq.nums[0], eq.nums[1]);
        auto p = prod(eq.nums[0], eq.nums[1]);
        auto c = conc(eq.nums[0], eq.nums[1]);
        eq.nums.erase(eq.nums.begin(), eq.nums.begin()+2);
        Equation eq2 {eq};
        eq2.nums.insert(eq2.nums.begin(), p);
        if (eval_equation2(eq2)) {
            return true;
        }
        Equation eq3 {eq};
        eq3.nums.insert(eq3.nums.begin(), c);
        if (eval_equation2(eq3)) {
            return true;
        }
        eq.nums.insert(eq.nums.begin(), s);
    }
    if (eq.test_value == eq.nums[0]) {
        return true;
    }
    return false;
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
        std::vector<long long int> temp_v;
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
