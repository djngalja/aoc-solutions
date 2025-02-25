#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct XY { int x; int y; };

int calc_gps(const std::vector<std::vector<char>>&);
bool move_boxes(const XY&, const XY&, std::vector<std::vector<char>>&);
void update_map(const std::vector<XY>&, XY&, std::vector<std::vector<char>>&);
bool find_init_pos(std::vector<std::vector<char>>&, XY&);
std::vector<XY> get_directions(std::ifstream&);
std::vector<std::vector<char>> get_wh_map(std::ifstream&);
bool read_input(const std::string&, std::vector<std::vector<char>>&, std::vector<XY>&);
void day15_part1();


int main() {
    day15_part1();
    return 0;
}


void day15_part1() {
    std::vector<std::vector<char>> wh_map;
    std::vector<XY> directions;
    if (read_input("input.txt", wh_map, directions)) {
        XY init_pos {};
        if (find_init_pos(wh_map, init_pos)) {
            update_map(directions, init_pos, wh_map);
            std::cout << "The sum of all GPS coordinates: " << calc_gps(wh_map) << ".\n";
        }
    }
}

bool read_input(const std::string& f_name, std::vector<std::vector<char>>& wh_map, std::vector<XY>& directions) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    wh_map = get_wh_map(file);
    directions = get_directions(file);
    return true;
}

std::vector<std::vector<char>> get_wh_map(std::ifstream& file) {
    std::vector<std::vector<char>> wh_map;
    std::string temp_str;
    while (getline(file, temp_str)) {
        if (temp_str.empty()) { break; }
        std::vector<char> temp_vec;
        for (char c : temp_str) {
            temp_vec.push_back(c);
        }
        wh_map.push_back(temp_vec);
    }
    return wh_map;
}

std::vector<XY> get_directions(std::ifstream& file) {
    std::vector<XY> directions;
    std::string temp_str;
    while (getline(file, temp_str)) {
        if (temp_str[0] == 'v' || temp_str[0] == '>' || temp_str[0] == '<' || temp_str[0] == '^') {
            for (char c : temp_str) {
                if (c == '>') {
                    directions.push_back(XY{0, 1});
                }
                else if (c == 'v') {
                    directions.push_back(XY{1, 0});
                }
                else if (c == '<') {
                    directions.push_back(XY{0, -1});
                }
                else {
                    directions.push_back(XY{-1, 0});
                }
            }
        }
    }
    return directions;
}

bool find_init_pos(std::vector<std::vector<char>>& wh_map, XY& init_pos) {
    for (std::size_t i=0; i<wh_map.size(); ++i) {
        for (std::size_t j=0; j<wh_map[i].size(); ++j) {
            if (wh_map[i][j] == '@') {
                wh_map[i][j] = '.'; // Don't need '@' anymore
                init_pos.x = i;
                init_pos.y = j;
                return true;
            }
        }
    }
    return false;
}

void update_map(const std::vector<XY>& directions, XY& init_pos, std::vector<std::vector<char>>& wh_map) {
    for (const auto& dir : directions) {
        int x = init_pos.x + dir.x;
        int y = init_pos.y + dir.y;
        if (wh_map[x][y] == '.') {
            init_pos.x += dir.x;
            init_pos.y += dir.y;
        }
        if (wh_map[x][y] == 'O') {
            if (move_boxes(dir, XY{x, y}, wh_map)) {
                init_pos.x += dir.x;
                init_pos.y += dir.y;
            }
        }
    }
}

bool move_boxes(const XY& dir, const XY& pos, std::vector<std::vector<char>>& wh_map) {
    int x = pos.x + dir.x;
    int y = pos.y + dir.y;
    while (wh_map[x][y] == 'O') {
        x += dir.x;
        y += dir.y;
    }
    if (wh_map[x][y] == '.') {
        wh_map[pos.x][pos.y] = '.'; // Remove the 1st box
        wh_map[x][y] = 'O'; // Place a new box after the last one
        return true;
    }
    return false;
}

int calc_gps(const std::vector<std::vector<char>>& wh_map) {
    int sum {};
    for (std::size_t i=0; i<wh_map.size(); ++i) {
        for (std::size_t j=0; j<wh_map[i].size(); ++j) {
            if (wh_map[i][j] == 'O') {
                sum += 100 * i + j;
            }
        }
    }
    return sum;
}
