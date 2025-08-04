#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

typedef std::unordered_set<std::string> USetStr;
typedef std::set<std::string> SetStr;

bool read_file(const std::string&, std::unordered_map<std::string, USetStr>&);
void find_all_cliques_rec(const SetStr&, USetStr&, USetStr&,
    const std::unordered_map<std::string, USetStr>&, std::vector<SetStr>&);
void find_all_cliques(const std::unordered_map<std::string, USetStr>&,
    std::vector<SetStr>&);
SetStr find_max_clique(const std::vector<SetStr>&);
void print_result(const SetStr&);


int main() {
    std::unordered_map<std::string, USetStr> input;
    if (read_file("input.txt", input)) {
        std::vector<SetStr> all_cliques;
        find_all_cliques(input, all_cliques);
        print_result(find_max_clique(all_cliques));
    }
    return 0;
}


bool read_file(const std::string& f_name, 
std::unordered_map<std::string, USetStr>& input) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
        return false;
    }
    // Adjacency list representation 
    for (std::string str; file >> str; ) {
        std::string first = str.substr(0, 2);
        std::string second = str.substr(3);
        input[first].insert(second);
        input[second].insert(first);
    }
    return true;
}

// Using Bron-Kerbosch algorithm
void find_all_cliques_rec(const SetStr& current_clique, USetStr& not_visited, 
USetStr& visited, const std::unordered_map<std::string, USetStr>& input,
std::vector<SetStr>& all_cliques) {
    if (not_visited.empty() && visited.empty()) {
        all_cliques.push_back(current_clique);
        return;
    }
    while (!not_visited.empty()) {
        std::string str{*not_visited.begin()};
        SetStr new_current_clique{current_clique};
        new_current_clique.insert(str);
        USetStr new_not_visited;
        for (const auto& s : not_visited) {
            if (input.at(str).find(s) != input.at(str).end()) {
                new_not_visited.insert(s);
            }
        }
        USetStr new_visited;
        for (const auto& s : visited) {
            if (input.at(str).find(s) != input.at(str).end()) {
                new_visited.insert(s);
            }
        }
        find_all_cliques_rec(new_current_clique, new_not_visited, new_visited, input, all_cliques);
        not_visited.erase(str);
        visited.insert(str);
    }
}

void find_all_cliques(const std::unordered_map<std::string, USetStr>& input,
std::vector<SetStr>& all_cliques) {
    SetStr current_clique; // Needs to be sorted (to print out the result)
    USetStr not_visited;
        for (const auto& pair : input) {
            not_visited.insert(pair.first);
        }
    USetStr visited;
    find_all_cliques_rec(current_clique, not_visited, visited, input, all_cliques);
}

SetStr find_max_clique(const std::vector<SetStr>& all_cliques) {
    std::size_t max_sz = all_cliques[0].size();
    auto max_it = all_cliques.begin();
    for (auto it = all_cliques.begin() + 1; it != all_cliques.end(); it++) {
        if ((*it).size() > max_sz) {
            max_sz = (*it).size();
            max_it = it;
        }
    }
    return *max_it;
}

void print_result(const SetStr& max_clique) {
    std::string res;
    for (const auto& str : max_clique) {
        res += str + ',';
    }
    if (!res.empty()) {
        res.pop_back();
    }
    std::cout << res << '\n';
}
