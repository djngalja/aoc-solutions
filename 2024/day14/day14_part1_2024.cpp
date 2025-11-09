#include <iostream>
#include <fstream>
#include <cmath> // std::abs
#include <cctype> // std::isdigit
#include <string>
#include <vector>

int calc_safety_f(const std::vector<std::vector<int>>&, int, int, int);
int predict_coord(int, int, int, int);
std::vector<int> split_str(const std::string&);
bool read_input(const std::string&, std::vector<std::vector<int>>&);
void day14_part1();


int main() {
    day14_part1();
    return 0;
}


void day14_part1() {
    std::vector<std::vector<int>> input;
    if (read_input("input.txt", input)) {
        std::cout << "The safety factor is " << calc_safety_f(input, 101, 103, 100) << ".\n";
    }
}

bool read_input(const std::string& f_name, std::vector<std::vector<int>>& input) {
    std::ifstream file(f_name);
    if(!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string temp_str;
    while(getline(file, temp_str)) {
        input.push_back(split_str(temp_str));
    }
    return true;
}

std::vector<int> split_str(const std::string& str) {
    std::vector<int> vec;
    std::string temp_str;
    for (auto c : str) {
        if (std::isdigit(c) || c == '-') {
            temp_str += c;
        }
        else {
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

int predict_coord(int init_p, int v, int ttl_len, int t) {
    int res = (init_p + v * t) % ttl_len;
    if (res < 0) {
        res = ttl_len - std::abs(res);
    }
    return res;
}

int calc_safety_f(const std::vector<std::vector<int>>& input, int width, int height, int t) {
    int mid_x = width / 2;
    int mid_y = height / 2;
    int q1 {}, q2 {}, q3 {}, q4 {};
    for (const auto& vec : input) {
        int pred_x = predict_coord(vec[0], vec[2], width, t);
        int pred_y = predict_coord(vec[1], vec[3], height, t);
        if (pred_x < mid_x) {
            if (pred_y < mid_y) { q1++; }
            if (pred_y > mid_y) { q2++; }
        }
        if (pred_x > mid_x) {
            if (pred_y < mid_y) { q3++; }
            if (pred_y > mid_y) { q4++; }
        }
    }
    return q1 * q2 * q3 * q4;
}
