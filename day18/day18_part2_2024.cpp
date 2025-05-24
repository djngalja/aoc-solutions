#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm> // std::find

struct Pos { int x; int y; }; // Coordinates
Pos operator+(const Pos&, const Pos&);
bool operator==(const Pos&, const Pos&);
bool operator<(const Pos&, const Pos&);

std::vector<Pos> get_input(const std::string&);
int find_pos_no_exit(const std::vector<Pos>&, int = 6, int = 12);
bool find_exit(const std::vector<Pos>&, int, int);
void bfs(const std::vector<Pos>&, int, int, const Pos&, std::set<Pos>&, bool&);
bool outside_bounds(int, const Pos&);


int main()  {
    std::vector<Pos> corrupted = get_input("input.txt");
    if (!corrupted.empty()) {
        std::size_t pos = find_pos_no_exit(corrupted, 70, 1024);
        std::cout << "Result: " << corrupted[pos].x << ',' << corrupted[pos].y << '\n';
    }
    return 0;
}


std::vector<Pos> get_input(const std::string& f_name) {
    std::vector<Pos> input;
    std::ifstream file(f_name);
    if (file) {
        for (std::string str; getline(file, str);) {
            auto pos = str.find(',');
            Pos temp {};
            temp.x = std::stoi(str.substr(0, pos));
            temp.y = std::stoi(str.substr(pos + 1));
            input.push_back(temp);
        }
    } else {
        std::cout << "File <" << f_name << "> not found\n";
    }
    return input;
}

// Find the position using binary search algorithm
int find_pos_no_exit(const std::vector<Pos>& corrupted, int memory_size, int n_bytes) {
    int min_val = n_bytes;
    int max_val = corrupted.size()-1;
    int mid_val {};
    while (min_val <= max_val) {
        mid_val = (min_val + max_val) / 2;
        bool res = find_exit(corrupted, memory_size, mid_val);
        if (res == 1) {
            min_val = mid_val + 1;
        } else {
            max_val = mid_val - 1;
        }
    }
    if (find_exit(corrupted, memory_size, mid_val)) {
        mid_val++;
    }
    return mid_val - 1; // subtract 1 to get a pos (indexing starts at 0)
}

bool find_exit(const std::vector<Pos>& corrupted, int memory_size, int n_bytes) {
    Pos init_pos {};
    std::set<Pos> visited;
    visited.insert(init_pos);
    bool found {};
    bfs(corrupted, memory_size, n_bytes, init_pos, visited, found);
    return found;
}

void bfs(const std::vector<Pos>& corrupted, int memory_size, int n_bytes, 
        const Pos& cur_pos, std::set<Pos>& visited, bool& found) {
    if (cur_pos == Pos{memory_size, memory_size}) {
        found = true;
        return;
    }
    for (const Pos& dir : { Pos{1, 0}, Pos{-1, 0}, Pos{0, 1}, Pos{0, -1} }) {
        Pos new_pos = cur_pos + dir;
        if (outside_bounds(memory_size, new_pos)) { continue; }
        if (std::find(corrupted.begin(), corrupted.begin() + n_bytes, new_pos) != corrupted.begin() + n_bytes) {
            continue; // if corrupted
        }
        auto res = visited.insert(new_pos);
        // Call bfs() only if the insertion took place (= not visited)
        if (res.second) {
            bfs(corrupted, memory_size, n_bytes, new_pos, visited, found);
        }
    }
}

bool outside_bounds(int memory_size, const Pos& new_pos) {
    if (new_pos.x > memory_size || new_pos.x < 0 || new_pos.y > memory_size || new_pos.y < 0) {
        return true;
    }
    return false;
}

Pos operator+(const Pos& lhs, const Pos& rhs) {
    Pos res {};
    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    return res;
}

bool operator==(const Pos& lhs, const Pos& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Pos& lhs, const Pos& rhs) {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}
