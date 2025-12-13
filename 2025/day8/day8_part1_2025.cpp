#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

struct Position { int x; int y; int z; };

struct Distance {
    size_t pos1_id;
    size_t pos2_id;
    double dist;

    bool operator<(const Distance& other) {
        return dist < other.dist;
    }
};

int find_rep(int i, std::vector<int>& parent) {
    int root = parent[i];
    if (parent[root] != root) {
        return parent[i] = find_rep(root, parent);
    }
    return root;
}


int main() {
    std::string f_name{"input.txt"};
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
    } else {
        std::vector<Position> input;
        for (std::string temp; file >> temp;) {
            Position pos;
            auto comma1 = temp.find(',');
            auto comma2 = temp.find(',', comma1 + 1);
            pos.x = stoi(temp.substr(0, comma1));
            pos.y = stoi(temp.substr(comma1 + 1, comma2 - comma1));
            pos.z = stoi(temp.substr(comma2 + 1));
            input.push_back(pos);
        }

        std::vector<Distance> distances;
        for (size_t i = 0; i < input.size(); ++i) {
            for (size_t j = i + 1; j < input.size(); ++j) {
                double dist = sqrt(pow(input[i].x - input[j].x, 2) + pow(input[i].y - input[j].y, 2) + pow(input[i].z - input[j].z, 2));
                distances.push_back({i, j, dist});
            }
        }

        std::sort(distances.begin(), distances.end());

        std::vector<int> size(input.size(), 1);
        std::vector<int> parent(input.size());
        for (size_t i = 0; i < input.size(); ++i) {
            parent[i] = i;
        }

        for (int i = 0; i < 1000; ++i) {
            int rep1 = find_rep(distances[i].pos1_id, parent);
            int rep2 = find_rep(distances[i].pos2_id, parent);
            if (rep1 != rep2) {
                if (size[rep1] < size[rep2]) {
                    parent[rep1] = rep2;
                    size[rep2] += size[rep1];
                } else {
                    parent[rep2] = rep1;
                    size[rep1] += size[rep2];
                }
            }
        }

        std::sort(size.begin(), size.end(), [](int a, int b){ return a > b; });
        std::cout << size[0] * size[1] * size[2] << '\n';
    }
    return 0;
}