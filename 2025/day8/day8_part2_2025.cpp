#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

struct Position { long x; long y; long z; };

struct Distance {
    int pos1_id;
    int pos2_id;
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

        int input_sz = input.size();
        std::vector<Distance> distances;
        for (int i = 0; i < input_sz; ++i) {
            for (int j = i + 1; j < input_sz; ++j) {
                double dist = sqrt(pow(input[i].x - input[j].x, 2) + pow(input[i].y - input[j].y, 2) + pow(input[i].z - input[j].z, 2));
                distances.push_back({i, j, dist});
            }
        }

        std::sort(distances.begin(), distances.end());

        std::vector<int> size(input_sz, 1);
        std::vector<int> parent(input_sz);
        for (int i = 0; i < input_sz; ++i) {
            parent[i] = i;
        }

        for (size_t i = 0; i < distances.size(); ++i) {
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
                if (size[rep2] == input_sz || size[rep1] == input_sz) {
                    std::cout << input[distances[i].pos1_id].x * input[distances[i].pos2_id].x << '\n';
                    break;
                }
            }
        }
    }
    return 0;
}