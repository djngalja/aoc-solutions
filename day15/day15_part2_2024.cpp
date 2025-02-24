#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <tuple> // std::tie

struct XY { int x; int y; };
bool operator<(const XY& l, const XY& r);

int calc_gps(const std::vector<std::vector<char>>&);
void move_up_down(const XY&, std::vector<std::vector<char>>&, const std::set<XY>&);
bool movable_up_down(const XY&, const XY&, const std::vector<std::vector<char>>&, std::set<XY>&);
void move_left_right(const XY&, const XY&, std::vector<std::vector<char>>&);
bool movable_left_right(const XY&, const XY&, const std::vector<std::vector<char>>&);
void update_map(const std::vector<XY>&, XY&, std::vector<std::vector<char>>&);
bool get_init_pos(std::vector<std::vector<char>>&, XY&);
std::vector<XY> get_directions(std::ifstream&);
std::vector<std::vector<char>> get_wh_map(std::ifstream&);
bool read_input(const std::string&, std::vector<std::vector<char>>&, std::vector<XY>&);
void day15_part2();


int main() {
    day15_part2();
    return 0;
}


void day15_part2() {
    std::vector<std::vector<char>> wh_map;
    std::vector<XY> directions;
    if (read_input("input.txt", wh_map, directions)) {
        XY init_pos {};
        if (get_init_pos(wh_map, init_pos)) {
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
        if (temp_str.empty()) { return wh_map; }
        std::vector<char> temp_vec;
        for (char c : temp_str) {
            if (c == '#' || c == '.') {
                temp_vec.push_back(c);
                temp_vec.push_back(c);
            }
            else if (c == 'O') {
                temp_vec.push_back('[');
                temp_vec.push_back(']');
            }
            else { // If the tile is '@'
                temp_vec.push_back(c);
                temp_vec.push_back('.');
            }
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

bool get_init_pos(std::vector<std::vector<char>>& wh_map, XY& init_pos) {
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
        if (wh_map[x][y] == '[' || wh_map[x][y] == ']') {
            if (dir.x == 0) { // Moving left or right
                if (movable_left_right(dir, XY{x, y}, wh_map)) {
                    move_left_right(dir, XY{x, y}, wh_map);
                    init_pos.y += dir.y;
                }
            } else { // Moving up or down
                std::set<XY> visited;
                if (movable_up_down(dir, XY{x, y}, wh_map, visited)) {
                    move_up_down(dir, wh_map, visited);
                    init_pos.x += dir.x;
                }
            }
        }
    }
}

bool movable_left_right(const XY& dir, const XY& pos, const std::vector<std::vector<char>>& wh_map) {
    int x = pos.x; //Remains unchanged
    int y = pos.y + dir.y;
    while (wh_map[x][y] == '[' || wh_map[x][y] == ']') {
        y += dir.y;
    }
    return wh_map[x][y] == '.';
}

void move_left_right(const XY& dir, const XY& pos, std::vector<std::vector<char>>& wh_map) {
    int x = pos.x; //Remains unchanged
    wh_map[x][pos.y] = '.';
    int y = pos.y + dir.y;
    while (wh_map[x][y] == '[' || wh_map[x][y] == ']') {
        wh_map[x][y] = (wh_map[x][y] == ']') ? '[' : ']';
        y += dir.y;
    }
    wh_map[x][y] = (wh_map[x][y - dir.y] == ']') ? '[' : ']';
}

bool movable_up_down(const XY& dir, const XY& pos, const std::vector<std::vector<char>>& wh_map, std::set<XY>& visited) {
    int y = pos.y; //Remains unchanged
    int y2 = (wh_map[pos.x][y] == ']') ? y-1 : y+1;
    visited.insert(pos);
    visited.insert(XY{pos.x, y2});
    int x = pos.x + dir.x;
    if (wh_map[x][y] == '#' || wh_map[x][y2] == '#') {
        return false;
    }
    if ((wh_map[x][y] == ']' || wh_map[x][y] == '[')
        && (wh_map[x][y2] == ']' || wh_map[x][y2] == '[')) {
            return movable_up_down(dir, XY{x, y}, wh_map, visited)
                && movable_up_down(dir, XY{x, y2}, wh_map, visited);
        }
    if (wh_map[x][y] == ']' || wh_map[x][y] == '[') {
            return movable_up_down(dir, XY{x, y}, wh_map, visited);
    }
    if (wh_map[x][y2] == ']' || wh_map[x][y2] == '[') {
            return movable_up_down(dir, XY{x, y2}, wh_map, visited);
    }
    return true;
}

void move_up_down(const XY& dir, std::vector<std::vector<char>>& wh_map, const std::set<XY>& visited) {
    std::vector<std::pair<XY, char>> boxes;
    for (const auto& v : visited) {
        boxes.push_back({v, wh_map[v.x][v.y]});
        wh_map[v.x][v.y] = '.'; // Erase old boxes
    }
    for (const auto& b : boxes) { // Place new boxes
        wh_map[b.first.x + dir.x][b.first.y] = (b.second == '[') ? '[' : ']';
    }
}

int calc_gps(const std::vector<std::vector<char>>& wh_map) {
    int sum {};
    for (std::size_t i=0; i<wh_map.size(); ++i) {
        for (std::size_t j=0; j<wh_map[i].size(); ++j) {
            if (wh_map[i][j] == '[') {
                sum += 100 * i + j;
            }
        }
    }
    return sum;
}

bool operator<(const XY& l, const XY& r) {
    return std::tie(l.x, l.y) < std::tie(r.x, r.y);
}
