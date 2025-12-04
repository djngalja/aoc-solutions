#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct XY { int x; int y; };

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::vector<std::string> input;
        for (std::string temp; file >> temp;) {
            input.push_back(temp);
        }

        int res{};
        int add{1};
        std::vector<XY> directions{{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};
        while (add) {
            add = 0;
            for (size_t i = 0; i < input.size(); ++i) {
                for (size_t j = 0; j < input[i].size(); ++j) {
                    if (input[i][j] == '@') {
                        int sum{};
                        for (const auto& dir : directions) {
                            int new_x = i + dir.x;
                            int new_y = j + dir.y;
                            if (new_x < 0 || new_x >= input.size() || new_y < 0 || new_y >= input[i].size()) {
                                continue;
                            } else {
                                if (input[new_x][new_y] == '@') {
                                    ++sum;
                                }
                            }
                        }
                        if (sum < 4) { 
                            ++add;
                            input[i][j] = '.'; 
                        }
                    }
                }
            }
            res += add;
        }
        std::cout << res << '\n';
    }
    return 0;
}