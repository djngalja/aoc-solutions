#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

typedef std::vector<std::vector<int>> VecVecInts;

struct XY { int x; int y; };
struct Tile { int score; XY pos; XY dir; };
bool operator==(const XY&, const XY&);
bool operator>(const Tile&, const Tile&);

XY rotate90(const XY&, bool = true);
int calc_lowest_score(VecVecInts&, const XY&, const XY&);
bool read_input(const std::string& f_name, VecVecInts&, XY&, XY&);


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
    int i {}; // Count lines
    for (std::string temp_str; getline(file, temp_str);) {
        std::vector<int> temp_vec;
        for (size_t j = 0; j < temp_str.size(); ++j) {
            if (temp_str[j] == '#') {
                temp_vec.push_back(-1);
            } else if (temp_str[j] == '.') {
                temp_vec.push_back(INT_MAX);
            } else if (temp_str[j] == 'S') {
                temp_vec.push_back(0); // Start
                s_pos.x = i;
                s_pos.y = j;
            } else {
                temp_vec.push_back(INT_MAX); // End
                e_pos.x = i;
                e_pos.y = j;
            }
        }
        maze_map.push_back(temp_vec);
        i++;
    }
    return true;
}

int calc_lowest_score(VecVecInts& maze_map, const XY& s_pos, const XY& e_pos) {
    XY init_dir {0, 1}; // Start facing East
    int lowest_score {};
    // Using Dijkstra's algorithm
    std::priority_queue<Tile, std::vector<Tile>, std::greater<Tile>> pq;
    pq.push(Tile{lowest_score, s_pos, init_dir});
    while (!pq.empty()) {
        Tile cur = pq.top();
        if (cur.pos == e_pos) {
            lowest_score = cur.score;
            break;
        }
        pq.pop();
        int x = cur.pos.x;
        int y = cur.pos.y;
        int dx = cur.dir.x;
        int dy = cur.dir.y;
        if (maze_map[x + dx][y + dy] != -1) { // Not a wall
            if (maze_map[x + dx][y + dy] > cur.score + 1) {
                maze_map[x + dx][y + dy] = cur.score + 1;
            }
            pq.push(Tile{maze_map[x + dx][y + dy], XY{x + dx, y + dy}, cur.dir});
        }
        for (const XY& new_dir : { rotate90(cur.dir), rotate90(cur.dir, false)}) {
            dx = new_dir.x;
            dy = new_dir.y;
            if (maze_map[x + dx][y + dy] != -1) {
                if (maze_map[x + dx][y + dy] > cur.score + 1001) {
                    maze_map[x + dx][y + dy] = cur.score + 1001;
                }
                pq.push(Tile{maze_map[x + dx][y + dy], XY{x + dx, y + dy}, new_dir});
            }
        }
        maze_map[x][y] = -1; // Visited
    }
    return lowest_score;
}

XY rotate90(const XY& dir, bool cw) {
    XY new_dir {};
    int k = cw ? 1 : -1; // Rotate clockwise by default
    if (dir.x == -1) {
        new_dir.y = k;
    } else if (dir.x == 1) {
        new_dir.y = -1 * k;
    } else if (dir.y == 1) {
        new_dir.x = k;
    } else { new_dir.x = -1 * k; }
    return new_dir;
}

bool operator>(const Tile& l, const Tile& r) {
    return l.score > r.score;
}

bool operator==(const XY& l, const XY& r) {
    return (l.x == r.x) && (l.y == r.y);
}
