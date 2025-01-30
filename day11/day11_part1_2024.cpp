#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

struct Stones { long long int stone1; long long int stone2; };

void day11_part1();
bool read_puzzle_input(const std::string&, std::vector<long long int>&);
int digit_num(long long int);
Stones split_stone(long long int, int);
void blink(std::vector<long long int>&);


int main() {
    day11_part1();
    return 0;
}


void day11_part1() {
    std::vector<long long int> stones;
    if (read_puzzle_input("input.txt", stones)) {
        for (int i=0; i<25; ++i) { blink(stones); }
        std::cout << stones.size() << " stones\n";
    }
}

bool read_puzzle_input(const std::string& f_name, std::vector<long long int>& stones) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    for (int i=0; file>>i;) {
        stones.push_back(i);
    }
    return true;
}

int digit_num(long long int num) {
    int cnt {};
    while (num) {
        num/= 10;
        cnt++;
    }
    return cnt;
}

Stones split_stone(long long int stone, int digit_num) {
    long long int div = std::pow(10, digit_num/2);
    long long int stone1 = stone / div ;
    long long int stone2 = stone % div ;
    return {stone1, stone2};
}

void blink(std::vector<long long int>& stones) {
    std::vector<long long int> new_stones;
    for (const long long int& stone : stones) {
        if (stone == 0) { new_stones.push_back(1); }
        else if (digit_num(stone)%2 == 0) {
            Stones stones = split_stone(stone, digit_num(stone));
            new_stones.push_back(stones.stone1);
            new_stones.push_back(stones.stone2);
        } else {
            new_stones.push_back(stone*2024);
        }
    }
    stones = std::move(new_stones);
}
