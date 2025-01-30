#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

struct Two_stones { long long st1; long long st2; };

void day11_part2();
bool read_puzzle_input(const std::string&, std::map<long long, long long>&);
int digit_num(long long);
Two_stones split_stone(long long, long long);
void insert_stone(std::map<long long, long long>&, long long, long long);
void blink(std::map<long long, long long>&);
long long count_all_stones(const std::map<long long, long long>&);


int main() {
    day11_part2();
    return 0;
}


void day11_part2() {
    // After 25 blinks, only 0.2% of all the stones had unique values!
    std::map<long long, long long> stones; // map of stones and their count
    if (read_puzzle_input("input.txt", stones)) {
        for (int i=0; i<75; ++i) { blink(stones); }
        std::cout << "Result: " << count_all_stones(stones) << " stones\n";
    }
}

bool read_puzzle_input(const std::string& f_name, std::map<long long, long long>& stones) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    for (int i=0; file>>i;) {
        stones[i] = 1;
    }
    return true;
}

int digit_num(long long num) {
    int cnt {};
    while (num) {
        num/= 10;
        cnt++;
    }
    return cnt;
}

Two_stones split_stone(long long old_stone, int digit_num) {
    long long div = std::pow(10, digit_num/2);
    long long st1 = old_stone / div ;
    long long st2 = old_stone % div ;
    return {st1, st2};
}

void insert_stone(std::map<long long, long long>& stones, long long new_stone_num, long long old_stone_cnt) {
    if (stones.find(new_stone_num) != stones.end()) {
            stones[new_stone_num] += old_stone_cnt;
        } else {
            stones[new_stone_num] = old_stone_cnt;
        }
}

void blink(std::map<long long, long long>& stones) {
    std::map<long long, long long> new_stones;
    for (auto& old_stone : stones) {
        if (old_stone.first == 0) {
            insert_stone(new_stones, 1, old_stone.second);
        }
        else if (digit_num(old_stone.first)%2 == 0) {
            Two_stones new_st = split_stone(old_stone.first, digit_num(old_stone.first));
            insert_stone(new_stones, new_st.st1, old_stone.second);
            insert_stone(new_stones, new_st.st2, old_stone.second);
        } else {
            insert_stone(new_stones, old_stone.first*2024, old_stone.second);
        }
    }
    stones = std::move(new_stones);
}

long long count_all_stones(const std::map<long long, long long>& stones) {
    long long res {};
    for (const auto& stone: stones) {
        res += stone.second;
    }
    return res;
}
