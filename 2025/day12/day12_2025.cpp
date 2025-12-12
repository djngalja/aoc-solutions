#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        int res{};
        for (std::string temp; getline(file, temp);) {
            if (std::isdigit(temp[0]) && temp[1] != ':') {
                int region{1};
                int hash_cnt{};
                int left{};
                for (size_t right = 0; right < temp.size(); ++right) {
                    if (temp[right] == 'x') {
                        region *= stoi(temp.substr(left, right - left));
                        left = right + 1;
                    } else if (temp[right] == ':') {
                        region *= stoi(temp.substr(left, right - left));
                        left = right + 2;
                        ++right;
                    } else if (temp[right] == ' ') {
                        hash_cnt += stoi(temp.substr(left, right - left));
                        left = right + 1;
                    }
                }
                hash_cnt += stoi(temp.substr(left));
                hash_cnt *= 7;
                if (region > hash_cnt) {
                    //std::cout << "diff = " << 100 * (region - hash_cnt) / region << "%\n";
                    ++res;
                }
            }
        }
        std::cout << res << '\n';
    }
    return 0;
}