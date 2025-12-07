#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::unordered_map<size_t, long> beams;
        for (std::string temp; file >> temp;) {
            for (size_t i = 0; i < temp.size(); ++i) {
                if (temp[i] == 'S') {
                    beams[i] = 1;
                } else if (temp[i] == '^') {
                    if (beams.find(i) != beams.end()) {
                        if (i > 0) { beams[i - 1] += beams[i]; }
                        if (i < temp.size() - 1) { beams[i + 1] += beams[i]; }
                        beams.erase(i);
                    }
                }
            }
        }

        long res{};
        for (const auto& beam : beams) {
            res += beam.second;
        }
        std::cout << res;
    }
    return 0;
}