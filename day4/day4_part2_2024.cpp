#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // std::rotate

struct XY { int x; int y; };

int cnt_x_mas(const std::vector<std::vector<char>>&, const XY&);
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
    int x_max = matrix.size() - 1;
    int y_max = matrix[0].size() - 1;
    for (int i = 1; i != x_max; ++i) {
        for (int j = 1; j != y_max; ++j) {
            if (matrix[i][j] == 'A') {
                result += cnt_x_mas(matrix, XY{i, j});
            }
        }
    }
    return result;
}

int cnt_x_mas(const std::vector<std::vector<char>>& matrix, const XY& a_pos) {
    std::vector<XY> dir = { {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };
    int cnt {};
    for (int i = 0; i < 4; ++i) {
        std::rotate(dir.begin(), dir.begin() + 1, dir.end());
        if ((matrix[a_pos.x + dir[0].x][a_pos.y + dir[0].y] == 'M')
            && (matrix[a_pos.x + dir[1].x][a_pos.y + dir[1].y] == 'M')
            && (matrix[a_pos.x + dir[2].x][a_pos.y + dir[2].y] == 'S')
            && (matrix[a_pos.x + dir[3].x][a_pos.y + dir[3].y] == 'S')) {
                cnt++;
            }
    }
    return cnt;
}
