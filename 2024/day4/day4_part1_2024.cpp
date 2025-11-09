#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct XY { int x; int y; };

int cnt_xmas(const std::vector<std::vector<char>>&, const XY&);
int calc_result(const std::vector<std::vector<char>>&);
bool read_file(const std::string&, std::vector<std::vector<char>>&);


int main() {
    std::vector<std::vector<char>> matrix;
    if (read_file("input.txt", matrix)) {
        std::cout << "Result: " << calc_result(matrix) << '\n';
    }
    return 0;
}


bool read_file(const std::string& f_name, std::vector<std::vector<char>>& matrix) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    for (std::string str; getline(file, str);) {
        std::vector<char> temp_vec;
        for (char c : str) {
            temp_vec.push_back(c);
        }
        matrix.push_back(temp_vec);
    }
    return true;
}

int calc_result(const std::vector<std::vector<char>>& matrix) {
    int result {};
    int x_max = matrix.size();
    int y_max = matrix[0].size();
    for (int i = 0; i != x_max; ++i) {
        for (int j = 0; j != y_max; ++j) {
            if (matrix[i][j] == 'X') {
                result += cnt_xmas(matrix, XY{i, j});
            }
        }
    }
    return result;
}

int cnt_xmas(const std::vector<std::vector<char>>& matrix, const XY& x_pos) {
    std::vector<XY> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1} };
    int cnt {};
    int x_max = matrix.size();
    int y_max = matrix[0].size();
    for (const XY& dir: directions) {
        if ((x_pos.x + 3 * dir.x < 0) || (x_pos.y + 3 * dir.y < 0)
            || (x_pos.x + 3 * dir.x >= x_max)
            || (x_pos.y + 3 * dir.y >= y_max)) {
                continue;
            }
        if ((matrix[x_pos.x + dir.x][x_pos.y + dir.y] == 'M')
            && (matrix[x_pos.x + 2 * dir.x][x_pos.y + 2 * dir.y] == 'A')
            && (matrix[x_pos.x + 3 * dir.x][x_pos.y + 3 * dir.y] == 'S')) {
                cnt++;
            }
    }
    return cnt;
}
