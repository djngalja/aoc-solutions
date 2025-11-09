#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct Pos { int x; int y; }; // Coordinates
Pos operator+(const Pos&, const Pos&);
bool operator==(const Pos&, const Pos&);
bool operator!=(const Pos&, const Pos&);
bool operator<(const Pos&, const Pos&);

std::vector<Pos> get_input(const std::string&);
bool outside_bounds(int, const Pos&);
int cnt_min_n_steps(const std::vector<Pos>&, int = 6, int = 12);


int main()  {
    std::vector<Pos> corrupted = get_input("input.txt");
    std::cout << "Result: " << cnt_min_n_steps(corrupted, 70, 1024) << '\n';
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

// Count the minimum number of steps needed to reach end_pos using BFS algorithm
int cnt_min_n_steps(const std::vector<Pos>& corrupted, int memory_size, int n_bytes) {
    Pos init_pos {};
    Pos end_pos {memory_size, memory_size};
    // To track visted and previous pos at the same time
    std::map<Pos, Pos> prev { {init_pos, {}} }; 
    std::queue<Pos> q; // To track which pos to visit next
    q.push(init_pos);
    while (!q.empty()) {
        Pos cur_pos = q.front();
        if (cur_pos == end_pos) { break; }
        q.pop();
        for (const Pos& dir : { Pos{1, 0}, Pos{-1, 0}, Pos{0, 1}, Pos{0, -1} }) {
            Pos new_pos = cur_pos + dir;
            if (outside_bounds(memory_size, new_pos)) { continue; }
            if (std::find(corrupted.begin(), corrupted.begin() + n_bytes, new_pos) != corrupted.begin() + n_bytes) {
                continue; // if corrupted
            }
            auto res = prev.insert({new_pos, cur_pos});
            // Push new_pos to the end of q only if the insertion took place (= not visited)
            if (res.second) { q.push(new_pos); }
        }
    }
    // Count the min number of steps by goind backwards from the end
    Pos prev_pos = prev[end_pos];
    int cnt {1};
    while(prev_pos != init_pos) {
        cnt++;
        prev_pos = prev[prev_pos];
    }
    return cnt;
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

bool operator!=(const Pos& lhs, const Pos& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Pos& lhs, const Pos& rhs) {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}
