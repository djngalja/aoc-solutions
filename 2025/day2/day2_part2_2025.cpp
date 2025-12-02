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
            size_t pos = temp.find('-');
            long end = stol(temp.substr(pos + 1));
            for (long i = stol(temp.substr(0, pos)); i <= end; ++i) {
                std::string num = std::to_string(i);
                std::string num_num = num + num;
                num_num.pop_back();
                if (num_num.find(num, 1) != std::string::npos) { 
                    res += i;
                }
            }
        }
        std::cout << res;
    }
    return 0;
}
