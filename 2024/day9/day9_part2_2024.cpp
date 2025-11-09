#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct File {
    int id; // -1 for free space
    int len;
    std::vector<int> pos;
};

void day9_part2();
bool read_disk_map(const std::string&, std::vector<File>&);
void find_free_space(std::vector<File>&);
void update_file(int, int, std::vector<File>&);
long long int calc_checksum(const std::vector<File>&);


int main() {
    day9_part2();
    return 0;
}


void day9_part2() {
    std::vector<File> disk_map;
    if (read_disk_map("input.txt", disk_map)) {
        find_free_space(disk_map);
        std::cout << "The resulting filesystem checksum: " << calc_checksum(disk_map);
    }
}

bool read_disk_map(const std::string& f_name, std::vector<File>& disk_map) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string temp_str;
    getline(file, temp_str);
    int id {};
    int pos {};
    for (std::size_t i=0; i!=temp_str.size(); ++i) {
        int len = temp_str[i]-'0';
        std::vector<int> pos_vec;
        for (int j=0; j<len; j++) {
                pos_vec.push_back(pos++);
            }
        if (i%2 == 0) { // file
            disk_map.push_back({id++, len, pos_vec});
        } else { // free space
            disk_map.push_back({-1, len, pos_vec});
        }
    }
    return true;
}

void find_free_space(std::vector<File>& disk_map) {
    auto f = disk_map.back().id != -1 ? disk_map.size()-1 : disk_map.size()-2;
    for (; f>0; f-=2) { // files
        for (std::size_t fs=1; fs<f; fs+=2) { // free space
            if (disk_map[f].len <= disk_map[fs].len) {
                update_file(f, fs, disk_map);
                break;
            }
        }
    }
}

void update_file(int file, int space, std::vector<File>& disk_map) {
    disk_map[space].len -= disk_map[file].len; // update the length of free space
    // update positions of file blocks
    std::copy_n(disk_map[space].pos.begin(), disk_map[file].len, disk_map[file].pos.begin());
    disk_map[space].pos.erase(disk_map[space].pos.begin(),
                              disk_map[space].pos.begin() + disk_map[file].len);
}

long long int calc_checksum(const std::vector<File>& disk_map) {
    long long int result {};
    for (auto it=disk_map.begin(); it<disk_map.end(); it+=2) {
        for (int pos : (*it).pos) {
            result += pos * (*it).id;
        }
    }
    return result;
}
