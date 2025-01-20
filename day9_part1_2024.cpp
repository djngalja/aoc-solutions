#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void day9_part1();
bool read_disk_map(const std::string&, std::vector<std::string>&);
bool is_number(const std::string&);
void compact_file(std::vector<std::string>&);
long long int calc_checksum(const std::vector<std::string>&);


int main() {
    day9_part1();
    return 0;
}


void day9_part1() {
    std::vector<std::string> disk_map;
    if (read_disk_map("input.txt", disk_map)) {
        compact_file(disk_map);
        std::cout << "The resulting filesystem checksum: " << calc_checksum(disk_map);
    }
}

bool read_disk_map(const std::string& f_name, std::vector<std::string>& disk_map) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string temp_str;
    getline(file, temp_str);
    int cnt {};
    for (std::size_t i=0; i!=temp_str.size(); ++i) {
        if (i%2 == 0) {
            for (int j=0; j<temp_str[i]-'0'; j++) {
                std::string block = std::to_string(cnt);
                disk_map.push_back(block);
            }
            cnt++;
        } else {
            for (int j=0; j<temp_str[i]-'0'; j++) {
                disk_map.push_back(".");
            }
        }
    }
    return true;
}

bool is_number(const std::string& str) {
    if (str != ".") { return true; }
    return false;
}

void compact_file(std::vector<std::string>& disk_map) {
    auto it_1st_free = std::find(disk_map.begin(), disk_map.end(), ".");
    auto it_last_num = std::find_if(disk_map.rbegin(), disk_map.rend(), is_number);
    while (it_1st_free < it_last_num.base()){
        std::iter_swap(it_1st_free, it_last_num);
        it_1st_free = std::find(it_1st_free, disk_map.end(), ".");
        it_last_num = std::find_if(it_last_num, disk_map.rend(), is_number);
    }
}

long long int calc_checksum(const std::vector<std::string>& disk_map) {
    long long int result {};
    for (std::size_t i=0; i!=disk_map.size(); ++i) {
        if (disk_map[i] == ".") { break; }
        result += i * std::stol(disk_map[i]);
    }
    return result;
}
