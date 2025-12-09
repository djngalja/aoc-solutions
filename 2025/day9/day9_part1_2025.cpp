#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct XY { long x; long y; };

int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::vector<XY> points;
        for (std::string temp; file >> temp;) {
            auto comma = temp.find(',');
            long x = stol(temp.substr(0, comma));
            long y = stol(temp.substr(comma + 1));
            points.push_back({x, y});
        }
        
        long res{};
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) {
                long area = labs(points[i].x - points[j].x + 1) * labs(points[i].y - points[j].y + 1);
                if (res < area) { res = area; }
            }
        }
        std::cout << res << '\n';     
    }
    return 0;
}