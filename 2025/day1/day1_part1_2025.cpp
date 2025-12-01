#include <fstream>
#include <iostream>
#include <string>

int main() {
    int res{};
    std::string f_name = "input.txt";
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        int val{50};
        for (std::string temp; file >> temp; ) {
            int num = stoi(temp.substr(1));
            if (temp[0] == 'L') {
                val = (val - num) % 100;
                if (val < 0) {
                    val += 100;
                }
            } else {
                val = (val + num) % 100;
            }
            if (val == 0) { ++res; }
        }
    }
    std::cout << res << '\n';
    return 0;
}