#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int64_t mix(int64_t, int64_t);
void prune(int64_t&);
void transform(int64_t&);
int64_t transform2000(int64_t);
bool read_input(const std::string& f_name, std::vector<int>&);


int main() {
    std::vector<int> input;
    if (read_input("input.txt", input)) {
        int64_t res{};
        for (int i : input) {
            res += transform2000(i);
        }
        std::cout << res << '\n';
    }
    return 0;
}


bool read_input(const std::string& f_name, std::vector<int>& input) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
        return false;
    }
    for (int num; file >> num; ) {
        input.push_back(num);
    }
    return true;
}

int64_t transform2000(int64_t num) {
    int64_t res{num};
    for (size_t i = 0; i < 2000; ++i) {
        transform(res);
    }
    return res;
}

void transform(int64_t& secret_num) {
    secret_num = mix(secret_num * 64, secret_num);
    prune(secret_num);
    secret_num = mix(secret_num / 32, secret_num);
    prune(secret_num);
    secret_num = mix(secret_num * 2048, secret_num);
    prune(secret_num);
}

void prune(int64_t& secret_num) {
    secret_num %= 16777216;
}

int64_t mix(int64_t num, int64_t secret_num) {
    return num ^ secret_num;
}
