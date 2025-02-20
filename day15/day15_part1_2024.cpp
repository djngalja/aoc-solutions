#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct XY { int x; int y; };

int calc_gps(const std::vector<std::vector<char>>&);
bool movable(const XY&, const XY&, std::vector<std::vector<char>>&);
void move_robot(const XY&, XY&, std::vector<std::vector<char>>&);
void update_map(const std::vector<char>&, XY&, std::vector<std::vector<char>>&);
bool get_init_pos(std::vector<std::vector<char>>&, XY&);
void get_movs(std::ifstream&, std::vector<char>&);
void get_wh_map(std::ifstream&, std::vector<std::vector<char>>&);
bool read_input(const std::string&, std::vector<std::vector<char>>&, std::vector<char>&);
void day15_part1();


int main() {
    day15_part1();
    return 0;
}


void day15_part1() {
    std::vector<std::vector<char>> wh_map;
    std::vector<char> mov;
    if (read_input("input.txt", wh_map, mov)) {
        XY init_pos {};
        if (get_init_pos(wh_map, init_pos)) {
            update_map(mov, init_pos, wh_map);
            std::cout << "The sum of all GPS coordinates: " << calc_gps(wh_map) << ".\n";
        }
    }
}

bool read_input(const std::string& f_name, std::vector<std::vector<char>>& wh_map, std::vector<char>& mov) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    get_wh_map(file, wh_map);
    get_movs(file, mov);
    return true;
}

void get_wh_map(std::ifstream& file, std::vector<std::vector<char>>& wh_map) {
    std::string temp_str;
    while (getline(file, temp_str)) {
        if (temp_str.empty()) { return; }
        std::vector<char> temp_vec;
        for (char c : temp_str) {
            temp_vec.push_back(c);
        }
        wh_map.push_back(temp_vec);
    }
}

void get_movs(std::ifstream& file, std::vector<char>& mov) {
    std::string temp_str;
    while (getline(file, temp_str)) {
        if (temp_str[0] == 'v' || temp_str[0] == '>' || temp_str[0] == '<' || temp_str[0] == '^') {
            for (char c : temp_str) {
                mov.push_back(c);
            }
        }
    }
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

void update_map(const std::vector<char>& mov, XY& init_pos, std::vector<std::vector<char>>& wh_map) {
    const std::vector<XY> dir = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // 4 directions
    for (char c : mov) {
        if (c == '>') {
            move_robot(dir[0], init_pos, wh_map);
        }
        else if (c == 'v') {
            move_robot(dir[1], init_pos, wh_map);
        }
        else if (c == '<') {
            move_robot(dir[2], init_pos, wh_map);
        }
        else {
            move_robot(dir[3], init_pos, wh_map);
        }
    }
}

void move_robot(const XY& dir, XY& init_pos, std::vector<std::vector<char>>& wh_map) {
    int x = init_pos.x + dir.x;
    int y = init_pos.y + dir.y;
    if (wh_map[x][y] == '#') { return; }
    if (wh_map[x][y] == '.') {
        init_pos.x += dir.x;
        init_pos.y += dir.y;
        return;
    }
    if (wh_map[x][y] == 'O') {
        if (movable(dir, {x, y}, wh_map)) {
            wh_map[x][y] = '.'; // Remove the 1st box only
            init_pos.x += dir.x;
            init_pos.y += dir.y;
            return;
        }
    }
}

bool movable(const XY& dir, const XY& pos, std::vector<std::vector<char>>& wh_map) {
    int x = pos.x + dir.x;
    int y = pos.y + dir.y;
    while (wh_map[x][y] == 'O') {
        x += dir.x;
        y += dir.y;
    }
    if (wh_map[x][y] == '.') {
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
