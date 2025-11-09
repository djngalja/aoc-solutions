#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>

constexpr int c_width{5};
constexpr int c_height{7};

bool read_file(const std::string&, std::vector<std::array<int, c_width>>&,
                std::vector<std::array<int, c_width>>&);
bool no_overlap(const std::array<int, c_width>&, const std::array<int, c_width>&);




int main() {
    std::vector<std::array<int, c_width>> locks;
    std::vector<std::array<int, c_width>> keys;
    if (read_file("input.txt", locks, keys)) {
        int cnt{};
        for (const auto& lock : locks) {
            for (const auto& key : keys) {
                if (no_overlap(lock, key)) { cnt++; }
            }
        }
        std::cout << "Result " << cnt << '\n';
    }
    return 0;
}




bool read_file(const std::string& f_name, std::vector<std::array<int, c_width>>& locks,
                std::vector<std::array<int, c_width>>& keys) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
        return false;
    }

    enum class Type {Lock, Key};
    Type current_t;
    std::array<int, c_width> current_arr{};
    int cnt{};

    for (std::string str; file >> str; ) {
        if (cnt++ == 0) {
            current_t = str == "#####" ? Type::Lock : Type::Key;
        }
        for (int i = 0; i < c_width; ++i) {
            if (str[i] == '#') {
                current_arr[i]++;
            }
        }
        if (cnt == c_height) {
            if (current_t == Type::Lock) {
                locks.push_back(current_arr);
            } else {
                keys.push_back(current_arr);
            }
            current_arr.fill(0);
            cnt = 0;
        }
    }
    return true;
}


bool no_overlap(const std::array<int, c_width>& lock, const std::array<int, c_width>& key) {
    for (int i = 0; i < c_width; ++i) {
        if (lock[i] + key[i] > c_height) {
            return false;
        }
    }
    return true;
}
