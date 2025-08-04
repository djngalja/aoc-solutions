#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>

typedef std::set<std::string> SetStr;

bool read_file(const std::string&, std::unordered_map<std::string, SetStr>&);
void find_inter_connect(const std::unordered_map<std::string, SetStr>&, std::set<SetStr>&);
int cnt_t_inter_con(const std::set<SetStr>&);


int main() {
    std::unordered_map<std::string, SetStr> input;
    if (read_file("input.txt", input)) {
        std::set<SetStr> inter_con_computers;
        find_inter_connect(input, inter_con_computers);
        std::cout << cnt_t_inter_con(inter_con_computers) << '\n';
    }
    return 0;
}


bool read_file(const std::string& f_name, std::unordered_map<std::string, SetStr>& input) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
        return false;
    }
    for (std::string str; file >> str; ) {
        std::string first = str.substr(0, 2);
        std::string second = str.substr(3);
        input[first].insert(second);
        input[second].insert(first);
    }
    return true;
}

void find_inter_connect(const std::unordered_map<std::string, SetStr>& input, 
std::set<SetStr>& inter_con_computers) {
    for (const auto& connection : input) {
        for (const auto& computer : connection.second) {
            for (const auto& computer2 : input.at(computer)) {
                if (connection.second.find(computer2) != connection.second.end()) {
                    SetStr temp{connection.first, computer, computer2};
                    inter_con_computers.insert(temp);
                }
            }
        }
    }
}

int cnt_t_inter_con(const std::set<SetStr>& inter_con_computers) {
    int cnt{};
    for (const auto& connection: inter_con_computers) {
        for (const auto& computer : connection) {
            if (computer[0] == 't') {
                ++cnt;
                break;
            }
        }
    }
    return cnt;
}
