#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric> // std::inner_product
#include <algorithm> // std::sort

bool read_input(const std::string&, std::vector<int>&, std::vector<int>&);
std::vector<int> count_duplicates(const std::vector<int>&, const std::vector<int>&);


int main() {
    std::vector<int> v1;
    std::vector<int> v2;
    if (read_input("input.txt", v1, v2)) {
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());
        std::vector<int> v3 = count_duplicates(v1, v2); 
        int part1 = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0, std::plus<>(),
                                       [](int a,int b){return std::abs(a-b);});
        int part2 = std::inner_product(v1.begin(), v1.end(), v3.begin(), 0);
        std::cout << "Part 1: " << part1 << "\nPart 2: " << part2 << '\n';
    }
    return 0;
}


bool read_input(const std::string& f_name, std::vector<int>& v1, std::vector<int>& v2) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    int n1 {};
    int n2 {};
    while (file >> n1 >> n2) {
     v1.push_back(n1);
     v2.push_back(n2);
    }
    return true;
}

std::vector<int> count_duplicates(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> v3;
    for (int i : v1) {
        v3.push_back(std::count(v2.begin(), v2.end(), i));
    }
    return v3;
}
