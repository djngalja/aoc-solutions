#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <tuple> // std::tie

struct XY { int x; int y; };
bool operator<(const XY&, const XY&);

void turn_right(XY&);
int cnt_unique_pos(const XY&, const std::vector<std::vector<char>>&);
bool find_guard(const std::vector<std::vector<char>>&, XY&);
bool read_map(const std::string&, std::vector<std::vector<char>>&);
void day6_part1();


int main() {
    day6_part1();
    return 0;
}


void day6_part1() {
    std::vector<std::vector<char>> vec;
    if (read_map("input.txt", vec)) {
        XY init_pos {};
        if (find_guard(vec, init_pos)) {
            std::cout << "The guard will visit " << cnt_unique_pos(init_pos, vec) << " distinct positions.\n";
        }
    }
}

bool read_map(const std::string& f_name, std::vector<std::vector<char>>& vec) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    std::string temp_str;
    while (getline(file, temp_str)) {
        std::vector<char> temp_vec;
        for (auto c : temp_str) {
            temp_vec.push_back(c);
        }
        vec.push_back(temp_vec);
    }
    return true;
}

bool find_guard(const std::vector<std::vector<char>>& vec, XY& init_pos) {
    for (std::size_t i=0; i!=vec.size(); ++i) {
        for (std::size_t j=0; j!=vec[i].size(); ++j) {
            if (vec[i][j] == '^') {
                init_pos.x = i;
                init_pos.y = j;
                return true;
            }
        }
    }
    return false; // not found
}

int cnt_unique_pos(const XY& init_pos, const std::vector<std::vector<char>>& vec) {
    std::set<XY> visited;
    int x_max = vec.size();
    int y_max = vec[0].size();
    XY dir {-1, 0}; // North
    XY pos {init_pos};
    while ((pos.x + dir.x >= 0) && (pos.x + dir.x < x_max) &&
           (pos.y + dir.y >= 0) && (pos.y + dir.y < y_max)) {
        if (vec[pos.x + dir.x][pos.y + dir.y] == '#') {
            turn_right(dir);
        }
        if (vec[pos.x + dir.x][pos.y + dir.y] != '#') {
            pos.x += dir.x;
            pos.y += dir.y;
            visited.insert(pos);
        }
    }
    return visited.size();
}

void turn_right(XY& dir) {
    if (dir.x == -1) { dir = {0, 1}; } // E
    else if (dir.x == 1) { dir = {0, -1}; } // W
    else {
        if (dir.y == 1) { dir = {1, 0}; } // S
        else { dir = {-1, 0}; } // N
    }
}

bool operator<(const XY& l, const XY& r) {
    return std::tie(l.x, l.y) < std::tie(r.x, r.y);
}
