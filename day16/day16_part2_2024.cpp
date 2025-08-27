#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

struct XY { int x; int y; };
bool operator==(const XY&, const XY&);
bool operator<(const XY&, const XY&);
XY operator+(const XY&, const XY&);

struct Tile {
    int score;
    XY dir;
    std::vector<XY> path;
};
bool operator>(const Tile&, const Tile&);

struct PosDir { XY pos; XY dir; };
bool operator<(const PosDir&, const PosDir&);

bool read_input(const std::string&, XY&, XY&, std::vector<std::string>&);
size_t cnt_tiles(const XY&, const XY&, const std::vector<std::string>&);
Tile get_new_tile(const std::vector<std::string>&, const Tile&, 
    std::map<PosDir, int>&, XY = {});
XY rotate90(const XY&, bool);



int main() {
    XY s_pos {};
    XY e_pos {};
    std::vector<std::string> input;
    if (read_input("input.txt", s_pos, e_pos, input)) {
        std::cout << cnt_tiles(s_pos, e_pos, input) << '\n';
    }
    return 0;
}



bool read_input(const std::string& f_name, XY& s_pos, XY& e_pos, 
std::vector<std::string>& input) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
        return false;
    }
    int x = 0;
    for (std::string str; file >> str;) {
        input.push_back(str);
        auto s = str.find('S');
        if (s != std::string::npos) {
            s_pos.x = x;
            s_pos.y = s;
        }
        auto e = str.find('E');
        if (e != std::string::npos) {
            e_pos.x = x;
            e_pos.y = e;
        }
        ++x;
    }
    return true;
}

size_t cnt_tiles(const XY& s_pos, const XY& e_pos, 
const std::vector<std::string>& input) {
    XY s_dir {0, 1};
    std::map<PosDir, int> visited {{PosDir{s_pos, s_dir}, 0}}; // int == score
    int lowest_score {};
    std::set<XY> best_spots;
    std::priority_queue<Tile, std::vector<Tile>, std::greater<Tile>> pq;
    pq.push(Tile{0, s_dir, std::vector<XY>{s_pos}});
    while (!pq.empty()) {
        Tile tile = pq.top();
        if (tile.path.back() == e_pos) {
            if (lowest_score != 0 && tile.score > lowest_score) { break; }
            if (lowest_score == 0) { lowest_score = tile.score; }
            for (const auto& pos : tile.path) { best_spots.insert(pos); }
            pq.pop();
            continue;
        }
        pq.pop();
        Tile new_tile = get_new_tile(input, tile, visited);
        if (new_tile.score) {
            pq.push(new_tile);
        }
        for (bool cw : {true, false}) {
            Tile rotated_tile = get_new_tile(input, tile, visited, rotate90(tile.dir, cw));
            if (rotated_tile.score) {
                pq.push(rotated_tile);
            }
        }
    }
    return best_spots.size();
}

Tile get_new_tile(const std::vector<std::string>& input, const Tile& tile, 
std::map<PosDir, int>& visited, XY rotated_dir) {
    bool rotate = rotated_dir.x == 0 && rotated_dir.y == 0 ? false : true;
    int new_score;
    XY new_dir;
    XY new_pos;
    if (rotate) {
        new_score = tile.score + 1001;
        new_dir = rotated_dir;
        new_pos = tile.path.back() + new_dir;
    } else {
        new_score = tile.score + 1;
        new_dir = tile.dir;
        new_pos = tile.path.back() + tile.dir;
    }
    if (input[new_pos.x][new_pos.y] != '#') {
        PosDir pos_dir {new_pos, new_dir};
        bool is_found = visited.find(pos_dir) != visited.end();
        if (!(is_found && visited[pos_dir] < new_score)) {
            visited[pos_dir] = new_score;
            std::vector<XY> new_path(tile.path);
            new_path.push_back(new_pos);
            return Tile{new_score, new_dir, new_path};
        }
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

bool operator<(const XY& lhs, const XY& rhs) {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

XY operator+(const XY& lhs, const XY& rhs) {
    return XY{lhs.x + rhs.x, lhs.y + rhs.y};
}

//Tile
bool operator>(const Tile& lhs, const Tile& rhs) {
    return lhs.score > rhs.score;
}

//PosDir
bool operator<(const PosDir& lhs, const PosDir& rhs) {
    return std::tie(lhs.pos, lhs.dir) < std::tie(rhs.pos, rhs.dir);
}
