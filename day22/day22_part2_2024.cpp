#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map> 

int find_max(const std::unordered_map<std::string, int>&);
void get_sequences(const std::vector<int>&, std::unordered_map<std::string, int>&);
int64_t mix(int64_t, int64_t);
void prune(int64_t&);
void transform(int64_t&);
std::vector<int> get_prices(int64_t);
void aggregate_prices(int64_t, std::unordered_map<std::string, int>&);
bool read_input(const std::string& f_name, std::vector<int>&);



int main() {
    std::vector<int> input;
    if (read_input("input.txt", input)) {
        std::unordered_map<std::string, int> aggregated_prices;
        for (int secret_num : input) {
            aggregate_prices(secret_num, aggregated_prices);
        }
        std::cout << find_max(aggregated_prices);
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

void aggregate_prices(int64_t num, std::unordered_map<std::string, int>& aggregated_prices) {
    std::vector<int> prices{get_prices(num)};
    std::unordered_map<std::string, int> sequences; 
    get_sequences(prices, sequences);
    for (const auto& p : sequences) {
        aggregated_prices[p.first] += p.second;
    }
}

std::vector<int> get_prices(int64_t num) {
    std::vector<int> prices;
    prices.push_back(num % 10);
    for (size_t i = 0; i < 2000; ++i) {
        transform(num);
        prices.push_back(num % 10);
    }
    return prices;
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

// Using the sliding window technique
void get_sequences(const std::vector<int>& prices, std::unordered_map<std::string, int>& sequences) {
    // The first window
    std::string window;
    for (int i = 1; i <= 4; ++i) { 
        std::string new_num = std::to_string(prices[i] - prices[i - 1]);
        if (new_num.size() != 2) { window += '0'; }
        window += new_num;   
    }
    sequences[window] = prices[4]; 
    //The remaining windows
    for (size_t i = 5; i < prices.size(); ++i) {
        window = window.substr(2); // Remove the 1st number
        std::string new_num = std::to_string(prices[i] - prices[i - 1]);
        if (new_num.size() != 2) { window += '0'; } 
        window += new_num; 
        // Add unique sequences only
        if (sequences.find(window) == sequences.end()) {
            sequences[window] = prices[i];
        }
    }
}

int find_max(const std::unordered_map<std::string, int>& aggregated_prices) {
    int max{};
    for (const auto& p : aggregated_prices) {
        if (p.second > max) { max = p.second;}
    }
    return max;
}
