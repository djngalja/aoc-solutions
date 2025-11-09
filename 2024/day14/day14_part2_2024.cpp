/*
I noticed that the total safety factor (at least for t >= 100) is a 9-digit number.
I assumed that in order to form a Christmas tree, the distribution of robots should change.
Most robots would move to some area, leaving some of the quadrants almost empty.
Thus, the resulting safety factor could be lower.
To test it, I calculated safety factors for t starting from 100 to 10000.
Then I checked the smallest value (it was an 8-digit number).
The corresponding t was the correct answer.
*/

#include <iostream>
#include <fstream>
#include <cmath> // std::abs
#include <cctype> // std::isdigit
#include <string>
#include <vector>
#include <algorithm> // std::sort

void draw_pic(const std::vector<std::vector<int>>&, int, int width = 101, int height = 103); // optional
int predict_coord(int, int, int, int);
int calc_safety_f(const std::vector<std::vector<int>>&, int, int, int);
int find_pic_t(const std::vector<std::vector<int>>&, int, int, int width = 101, int height = 103);
std::vector<int> split_str(const std::string&);
bool read_input(const std::string&, std::vector<std::vector<int>>&);
void day14_part2();


int main() {
    day14_part2();
    return 0;
}


void day14_part2() {
    std::vector<std::vector<int>> input;
    if (read_input("input.txt", input)) {
        int t = find_pic_t(input, 100, 10000);
        std::cout << "The fewest number of seconds is " << t << ".\n";
        //draw_pic(input, t);
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

int find_pic_t(const std::vector<std::vector<int>>& input, int min_t, int max_t, int width, int height) {
    std::vector<std::pair<int, int>> vec;
    for (int t = min_t; t <= max_t; ++t) {
        vec.push_back({calc_safety_f(input, width, height, t), t});
    }
    std::sort(vec.begin(), vec.end());
    return vec[0].second;
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

int predict_coord(int init_p, int v, int ttl_len, int t) {
    int res = (init_p + v * t) % ttl_len;
    if (res < 0) {
        res = ttl_len - std::abs(res);
    }
    return res;
}

void draw_pic(const std::vector<std::vector<int>>& input, int t, int width, int height) {
    //create an empty map
    std::vector<char> temp_vec (width, '.');
    std::vector<std::vector<char>> pic (height, temp_vec);
    //place robots
    for (const auto& vec : input) {
        int x = predict_coord(vec[0], vec[2], width, t);
        int y = predict_coord(vec[1], vec[3], height, t);
        pic[y][x] = '#';
    }
    //print out the whole picture
    for (const auto& i : pic) {
        for (char j : i) { std::cout << j; }
        std::cout << '\n';
    }
}
