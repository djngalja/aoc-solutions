#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool check_report2(const std::vector<int>&);
int part2(const std::vector<std::vector<int>>&);
bool check_report(const std::vector<int>&);
int part1(const std::vector<std::vector<int>>&);
bool read_input(const std::string&, std::vector<std::vector<int>>&);


int main() {
    std::vector<std::vector<int>> reports;
    if (read_input("input.txt", reports)) {
        std::cout << "Part 1: " << part1(reports) << "\nPart 2: " << part2(reports) << '\n';
    }
    return 0;
}


bool read_input(const std::string& f_name, std::vector<std::vector<int>>& reports) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found.\n";
        return false;
    }
    std::string tmp_str;
    while(getline(file, tmp_str)) {
        std::vector<int> temp_vec;
        std::istringstream line(tmp_str);
        int temp_num {};
        while (line >> temp_num) {
            temp_vec.push_back(temp_num);
        }
        reports.push_back(temp_vec);
    }
    return true;
}

int part1(const std::vector<std::vector<int>>& reports) {
    int cnt {};
    for (const auto& report : reports) {
        cnt += check_report(report);
    }
    return cnt;
}

bool check_report(const std::vector<int>& report) {
    bool is_safe {};
    if (report[0] != report[1]) {
        bool is_decreasing = report[0] > report[1] ? true : false;
        for (std::size_t i=0; i!=report.size()-1; i++) {
            if ((report[i] != report[i+1])
                && ((report[i] > report[i+1]) == is_decreasing)
                && (std::abs(report[i] - report[i+1]) <= 3)) {
                is_safe = true;
            } else {
                is_safe = false;
                break;
            }
        }
    }
    return is_safe;
}

int part2(const std::vector<std::vector<int>>& reports) {
    int cnt {};
    for (const auto& report : reports) {
        bool is_safe = check_report(report);
        if (!is_safe) {
            is_safe = check_report2(report);
        }
        cnt += is_safe;
    }
    return cnt;
}

bool check_report2(const std::vector<int>& report) {
    for (std::size_t i=0; i!=report.size(); i++) {
        std::vector<int> temp_vec;
        for (std::size_t j=0; j!=report.size(); j++) {
            if (j == i) { // Try removing this element
                continue;
            }
            temp_vec.push_back(report[j]);
        }
        if (check_report(temp_vec)) {
            return true;
        }
    }
    return false;
}
