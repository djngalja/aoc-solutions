#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        long res{};
        for (std::string temp; getline(file, temp, ',');) {
            size_t delim = temp.find('-');
            long end = stol(temp.substr(delim + 1));
            for (long i = stol(temp.substr(0, delim)); i <= end; ++i) {
                std::string num = std::to_string(i);
                if (num.size() % 2 != 0) { continue; }
                size_t mid = num.size() / 2;
                if (num.substr(0, mid) == num.substr(mid)) { 
                    res += i;
                }
            }
        }
        std::cout << res;
    }
    return 0;
}
