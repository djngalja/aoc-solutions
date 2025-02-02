#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <tuple>

struct XY { int x; int y; };
bool operator<(const XY&, const XY&);
struct PosDir { XY pos; XY dir; }; // position & direction
bool operator<(const PosDir&, const PosDir&);

void turn_right(XY&);
bool within_bounds(const std::vector<std::vector<char>>&, const XY&, const XY&);
std::set<XY> find_unique_pos(const XY&, const std::vector<std::vector<char>>&);
int cnt_loops(const XY&, std::vector<std::vector<char>>&);
XY find_guard(const std::vector<std::vector<char>>&);
bool read_map(const std::string&, std::vector<std::vector<char>>&);
void day6_part2();


int main() {
    day6_part2();
    return 0;
}


void day6_part2() {
    std::vector<std::vector<char>> vec;
    if (read_map("input.txt", vec)) {
        const XY init_pos = {find_guard(vec)};
        int loop_cnt = cnt_loops(init_pos, vec);
        std::cout << "\nThere are " << loop_cnt << " different positions.\n";
    }
}

bool read_map(const std::string& f_name, std::vector<std::vector<char>>& vec) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
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

XY find_guard(const std::vector<std::vector<char>>& vec) {
    XY init_pos {};
    for (std::size_t i=0; i!=vec.size(); ++i) {
        for (std::size_t j=0; j!=vec[i].size(); ++j) {
            if (vec[i][j] == '^') {
                init_pos.x = i;
                init_pos.y = j;
                break;
            }
        }
    }
    return init_pos;
}

int cnt_loops(const XY& init_pos, std::vector<std::vector<char>>& vec) {
    int cnt {};
    std::set<XY> unique_pos = {find_unique_pos(init_pos, vec)};
    for (const auto& u_pos : unique_pos) {
        XY pos {init_pos};
        XY dir {-1, 0}; // North
        if (vec[u_pos.x][u_pos.y] == '.') {
            vec[u_pos.x][u_pos.y] = '#';
            std::set<PosDir> new_path;
            while (within_bounds(vec, pos, dir)) {
                if (vec[pos.x + dir.x][pos.y + dir.y] == '#') {
                    turn_right(dir);
                }
                if (vec[pos.x + dir.x][pos.y + dir.y] != '#') {
                    pos.x += dir.x;
                    pos.y += dir.y;
                    auto result = new_path.insert({pos.x, pos.y, dir.x, dir.y});
                    if (result.second == false) { // couldn't insert -> it's a loop
                        if (++cnt%5==0) {
                            std:: cout << "Progress: " << cnt << " loops found\n";
                        }
                        break;
                    }
                }
            }
            vec[u_pos.x][u_pos.y] = '.'; //return to the original state
        }
    }
    return cnt;
}

std::set<XY> find_unique_pos(const XY& init_pos, const std::vector<std::vector<char>>& vec) {
    std::set<XY> unique_pos;
    XY dir {-1, 0}; // North
    XY pos {init_pos};
    while (within_bounds(vec, pos, dir)) {
        if (vec[pos.x + dir.x][pos.y + dir.y] == '#') {
            turn_right(dir);
        }
        if (vec[pos.x + dir.x][pos.y + dir.y] != '#') {
            pos.x += dir.x;
            pos.y += dir.y;
            unique_pos.insert(pos);
        }
    }
    return unique_pos;
}

bool within_bounds(const std::vector<std::vector<char>>& vec, const XY& pos, const XY& dir) {
    int x_max = vec.size();
    int y_max = vec[0].size();
    if ((pos.x + dir.x >= 0) && (pos.x + dir.x < x_max) &&
        (pos.y + dir.y >= 0) && (pos.y + dir.y < y_max)) {
            return true;
        }
    return false;
}

void turn_right(XY& dir) {
    if (dir.x == -1) { // East
        dir = {0, 1};
    } else if (dir.x == 1) { // West
        dir = {0, -1};
    } else {
        if (dir.y == 1) { // South
            dir = {1, 0};
        } else { // North
            dir = {-1, 0};
        }
    }
}

bool operator<(const PosDir& l, const PosDir& r) {
    return std::tie(l.pos, l.dir) < std::tie(r.pos, r.dir);
}

bool operator<(const XY& l, const XY& r) {
    return std::tie(l.x, l.y) < std::tie(r.x, r.y);
}
