#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>

struct Antenna { char frequency; int x; int y; };
struct XY { int x; int y; };

bool operator<(const XY&, const XY&);
bool operator<(const Antenna&, const Antenna&);

void day8_part1();
bool read_data(const std::string&, std::vector<Antenna>&, XY&);
std::map<char, int> get_uniq_freq(const std::vector<Antenna>&);
void add_antinode(int, int, const XY&, std::set<XY>&);
std::set<XY> find_antinodes(const std::vector<Antenna>&, const XY&, const std::map<char, int>&);


int main() {
    day8_part1();
    return 0;
}


void day8_part1() {
    std::vector<Antenna> input_data;
    XY map_size;
    if (read_data("advent_day8.txt", input_data, map_size)) {
        std::sort(input_data.begin(), input_data.end()); // sort by frequency
        std::map<char, int> freq_index {get_uniq_freq(input_data)};
        std::set<XY> antinodes {find_antinodes(input_data, map_size, freq_index)};
        std::cout<< "Result: " << antinodes.size();
    }
}

bool operator<(const XY& p1, const XY& p2) {
    return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y);
}

bool operator<(const Antenna& p1, const Antenna& p2) {
    return p1.frequency < p2.frequency;
}

bool read_data(const std::string& f_name, std::vector<Antenna>& input_data, XY& map_size) {
    std::ifstream file(f_name);
    if(!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string temp_str;
    int x {0};
    while (getline(file, temp_str)) {
        for (std::size_t i=0; i!=temp_str.size(); ++i) {
            if (temp_str[i] != '.') {
                const int y = i;
                input_data.push_back({temp_str[y], x, y});
            }
        }
        ++x; // count lines
    }
    map_size.x = {x};
    map_size.y = temp_str.size();
    return true;
}

/*
For every unique frequency, get the position of the 1st antenna inside of the input_data vector.
Since the vector is sorted by frequency, while searching antinodes, go through the vector only once.
*/
std::map<char, int> get_uniq_freq(const std::vector<Antenna>& input_data) {
    std::map<char, int> freq_index;
    for (std::size_t i=0; i!=input_data.size(); ++i) {
        freq_index.insert({input_data[i].frequency, i});
    }
    return freq_index;
}

void add_antinode(int x, int y, const XY& map_size, std::set<XY>& antinodes) {
    if (x >= 0 && x < map_size.x && y >= 0 && y < map_size.y) {
        antinodes.insert({x, y});
    }
}

std::set<XY> find_antinodes(const std::vector<Antenna>& input_data, const XY& map_size, const std::map<char, int>& freq_index) {
    std::set<XY> antinodes;
    for (const auto& f_id : freq_index) { // for every unique frequency
        std::size_t i = f_id.second;
        while (input_data[i].frequency == f_id.first) {
            std::size_t j {1};
            while (input_data[i+j].frequency == f_id.first) {
                const int dx = input_data[i].x - input_data[i+j].x; // change in x
                const int dy = input_data[i].y - input_data[i+j].y; // change in y
                const int x1 = input_data[i].x + dx;
                const int x2 = input_data[i+j].x - dx;
                const int y1 = input_data[i].y + dy;
                const int y2 = input_data[i+j].y - dy;
                add_antinode(x1, y1, map_size, antinodes); // add if within the bounds of the map
                add_antinode(x2, y2, map_size, antinodes);
                ++j;
            }
            ++i;
        }
    }
    return antinodes;
}
