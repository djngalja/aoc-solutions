#include <iostream>
#include <fstream>
#include <string>
#include <regex>

/* Returns a pair consisting of the puzzle answer
and a bool value set to false if the puzzle input couldn't be found */
std::pair<int, bool> read_file(const std::string&);


int main() {
    auto result = read_file("input.txt");
    if (result.second) {
        std::cout << "Result: " << result.first << '\n';
    }
    return 0;
}


std::pair<int, bool> read_file(const std::string& f_name) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return {0, false};
    }
    int result {};
    std::regex pat {R"(mul\((\d+),(\d+)\))"};
    for (std::string str; getline(file, str);) {
        for (std::sregex_iterator p(str.begin(), str.end(), pat); p!=std::sregex_iterator{}; ++p) {
            result += stoi((*p)[1]) * stoi((*p)[2]);
        }
    }
    return {result, true};
}
