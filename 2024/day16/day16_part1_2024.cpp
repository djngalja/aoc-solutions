#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

typedef std::vector<std::vector<int>> VecVecInts;

struct XY { int x; int y; };
bool operator==(const XY&, const XY&);
XY operator+(const XY&, const XY&);

struct Tile { 
    int score; 
    XY pos; 
    XY dir; 
};
bool operator>(const Tile&, const Tile&);

bool read_input(const std::string& f_name, VecVecInts&, XY&, XY&);
int calc_lowest_score(VecVecInts&, const XY&, const XY&);
Tile get_new_tile(VecVecInts&, int, const XY&, const XY&);
XY rotate90(const XY&, bool);



int main() {
    VecVecInts maze_map;
    XY s_pos {};
    XY e_pos {};
    if (read_input("input.txt", maze_map, s_pos, e_pos)) {
        std::cout << "The lowest score is " << calc_lowest_score(maze_map, s_pos, e_pos) << '\n';
    }
    return 0;
}



bool read_input(const std::string& f_name, VecVecInts& maze_map, XY& s_pos, XY& e_pos) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found.\n";
        return false;
    }
    int x {}; 
    for (std::string temp_str; getline(file, temp_str);) {
        std::vector<int> temp_vec;
        for (size_t y = 0; y < temp_str.size(); ++y) {
            if (temp_str[y] == '#') {
                temp_vec.push_back(-1);
            } else if (temp_str[y] == '.') {
                temp_vec.push_back(INT_MAX);
            } else if (temp_str[y] == 'S') {
                temp_vec.push_back(0); // Start
                s_pos.x = x;
                s_pos.y = y;
            } else {
                temp_vec.push_back(INT_MAX); // End
                e_pos.x = x;
                e_pos.y = y;
            }
        }
        maze_map.push_back(temp_vec);
        ++x;
    }
    return true;
}

// Using Dijkstra's algorithm
int calc_lowest_score(VecVecInts& maze_map, const XY& s_pos, const XY& e_pos) {
    XY s_dir {0, 1}; // Start facing East
    int lowest_score {};
    std::priority_queue<Tile, std::vector<Tile>, std::greater<Tile>> pq;
    pq.push(Tile{lowest_score, s_pos, s_dir});
    while (!pq.empty()) {
        Tile tile = pq.top();
        if (tile.pos == e_pos) {
            lowest_score = tile.score;
            break;
        }
        pq.pop();
        Tile new_tile = get_new_tile(maze_map, tile.score, tile.pos, tile.dir);
        if (new_tile.score) {
            pq.push(new_tile);
        }
        for (bool cw : { true, false}) {
            Tile rotated_tile = get_new_tile(
                maze_map, tile.score + 1000, tile.pos, rotate90(tile.dir, cw));
            if (rotated_tile.score) {
                pq.push(rotated_tile);
            }
        }
        maze_map[tile.pos.x][tile.pos.y] = -1; // Visited
    }
    return lowest_score;
}

Tile get_new_tile(VecVecInts& maze_map, int score, const XY& pos, const XY& dir) {
    XY new_pos {pos + dir};
    if (maze_map[new_pos.x][new_pos.y] != -1 && 
        maze_map[new_pos.x][new_pos.y] > score + 1) { 
        maze_map[new_pos.x][new_pos.y] = score + 1;
        return Tile{maze_map[new_pos.x][new_pos.y], new_pos, dir};
    }
    return Tile{};
}

XY rotate90(const XY& dir, bool cw) {
    XY new_dir {};
    int k = cw ? 1 : -1; 
    if (dir.x == -1) {
        new_dir.y = k;
    } else if (dir.x == 1) {
        new_dir.y = -1 * k;
    } else if (dir.y == 1) {
        new_dir.x = k;
    } else { new_dir.x = -1 * k; }
    return new_dir;
}

//XY
bool operator==(const XY& lhs, const XY& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

XY operator+(const XY& lhs, const XY& rhs) {
    return XY{lhs.x + rhs.x, lhs.y + rhs.y};
}

//Tile
bool operator>(const Tile& lhs, const Tile& rhs) {
    return lhs.score > rhs.score;
}
