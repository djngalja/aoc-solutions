#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::unordered_set<size_t> beams;
        int res{};
        for (std::string temp; file >> temp;) {
            for (size_t i = 0; i < temp.size(); ++i) {
                if (temp[i] == 'S') {
                    beams.insert(i);
                } else if (temp[i] == '^') {
                    if (beams.find(i) != beams.end()) {
                        ++res;
                        beams.erase(i);
                        if (i > 0) { beams.insert(i - 1); }
                        if (i < temp.size() - 1) { beams.insert(i + 1); }
                    }
                }
            }
        }
        std::cout << res;
    }
    return 0;
}