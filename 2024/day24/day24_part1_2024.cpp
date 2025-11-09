#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <regex>
#include <cmath>

enum class Gate { AND, OR, XOR };

struct Connection {
    std::string wire_i1; 
    Gate gate;
    std::string wire_i2; 
    std::string wire_o; 
};

bool read_file(const std::string&, std::unordered_map<std::string, bool>&, std::vector<Connection>&);
bool add_wire(const Connection&, std::unordered_map<std::string, bool>&);
void connect_wires(const std::vector<Connection>&, std::unordered_map<std::string, bool>&);
long calc_result(const std::unordered_map<std::string, bool>&);



int main() {
    std::unordered_map<std::string, bool> wires;
    std::vector<Connection> connections;
    if (read_file("input.txt", wires, connections)) {
        connect_wires(connections, wires);
        std::cout << calc_result(wires) << '\n';
    }
    return 0;
}



bool read_file(const std::string& f_name, std::unordered_map<std::string, bool>& wires, 
                std::vector<Connection>& connections) {
    std::ifstream file(f_name);
    if (!file) {
        std::cerr << "File <" << f_name << "> not found\n";
        return false;
    }
    std::regex pat1{R"((\w{3}):\s(\d))"};
    std::regex pat2{R"((\w{3})\s(\w{2,3})\s(\w{3})\s->\s(\w{3}))"};
    for (std::string str; getline(file, str); ) {
        std::smatch match;
        if (std::regex_search(str, match, pat1)) {
            wires.insert(std::make_pair(match[1], stoi(match[2])));
        }
        if (std::regex_search(str, match, pat2)) {
            Gate cur_gate = match[2] == "AND" ? Gate::AND : (match[2] == "OR" ? Gate::OR : Gate::XOR);
            connections.push_back(Connection{match[1], cur_gate, match[3], match[4]});
        }
    }
    return true;
}

bool add_wire(const Connection& con, std::unordered_map<std::string, bool>& wires) {
    if (wires.find(con.wire_i1) != wires.end() 
            && wires.find(con.wire_i2) != wires.end()) {
        int res {};
        if (con.gate == Gate::AND) {
            res = wires[con.wire_i1] && wires[con.wire_i2];
        } else if (con.gate == Gate::OR) {
            res = wires[con.wire_i1] || wires[con.wire_i2];
        } else {
            res = wires[con.wire_i1] != wires[con.wire_i2];
        }
        wires[con.wire_o] = res;
        return true;
    }
    return false;
}

void connect_wires(const std::vector<Connection>& connections,
                    std::unordered_map<std::string, bool>& wires){
    std::queue<Connection> q;
    for (const auto& con : connections) {
        if (!add_wire(con, wires)) {
            q.push(con);
        }
    }
    while (!q.empty()) {
        auto con = q.front();
        q.pop();
        if (!add_wire(con, wires)) {
            q.push(con);
        }
    }   
}

long calc_result(const std::unordered_map<std::string, bool>& wires) {
    long res{};
    for (const auto& wire : wires) {
        if (wire.first[0] == 'z') {
            if (!wire.second) { continue; }
            int num = stoi(wire.first.substr(1));
            res += std::pow(2, num);
        }
    }
    return res;
}
