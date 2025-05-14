#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

struct Registers { int a; int b; int c; };

class Computer {
public:
    void run_program();
    void print_output();
    Computer(const Registers& r, const std::vector<int>& pr) : reg {r}, program {pr} {}
private:
    Registers reg;
    std::vector<int> program;

    std::size_t pos {};
    std::vector<int> output {};

    int get_combo_operand(int) const;
    void adv(int);
    void bxl(int operand) { reg.b = reg.b ^ operand; }
    void bst(int);
    void jnz(int);
    void bxc() { reg.b = reg.b ^ reg.c; }
    void out(int);
    void bdv(int);
    void cdv(int);
};

int get_register(const std::string&);
std::vector<int> get_program(const std::string&);
Computer get_input(const std::string&);


int main()  {
    std::cout << "Test result: ";
    Computer test({729, 0, 0}, {0, 1, 5, 4, 3, 0}); // Expected: 4,6,3,5,6,3,5,2,1,0
    test.run_program();
    test.print_output();

    std::cout << "Result: ";
    Computer c1 = get_input("input.txt");
    c1.run_program();
    c1.print_output();

    return 0;
}


int Computer::get_combo_operand(int operand) const {
    switch (operand) {
        case 4:
            return reg.a;
        case 5:
            return reg.b;
        case 6:
            return reg.c;
        default:
            return operand;
    }
}

void Computer::adv(int operand) {
    int operand_val = get_combo_operand(operand);
    reg.a = reg.a / pow(2, operand_val);
}

void Computer::bst(int operand) {
    int operand_val = get_combo_operand(operand);
    reg.b = operand_val % 8;
}

void Computer::jnz(int operand) {
    if (reg.a) {
        // subtract 2 to compensate for its modification after loop iteration in Computer::run_program
        pos = operand - 2;
    }
}

void Computer::out(int operand) {
    int operand_val = get_combo_operand(operand);
    output.push_back(operand_val % 8);
}

void Computer::bdv(int operand) {
    int operand_val = get_combo_operand(operand);
    reg.b = reg.a / pow(2, operand_val);
}

void Computer::cdv(int operand) {
    int operand_val = get_combo_operand(operand);
    reg.c = reg.a / pow(2, operand_val);
}

void Computer::run_program() {
    for (; pos < program.size(); pos += 2) {
        switch(program[pos]) {
            case 0:
                adv(program[pos+1]);
                break;
            case 1:
                bxl(program[pos+1]);
                break;
            case 2:
                bst(program[pos+1]);
                break;
            case 3:
                jnz(program[pos+1]);
                break;
            case 4:
                bxc();
                break;
            case 5:
                out(program[pos+1]);
                break;
            case 6:
                bdv(program[pos+1]);
                break;
            case 7:
                cdv(program[pos+1]);
                break;
        }
    }
}

void Computer::print_output() {
    if (output.empty()) { return; }
    std::string str;
    for (int num : output) {
        str += std::to_string(num) + ',';
    }
    str.pop_back();
    std::cout << str << '\n';
}

int get_register(const std::string& str) {
    auto pos = str.find(':');
    return stoi(str.substr(pos + 2));
}

std::vector<int> get_program(const std::string& str) {
    std::vector<int> program;
    for (char c : str) {
        if (std::isdigit(c)) {
            std::string str;
            str += c;
            program.push_back(stoi(str));
        }
    }
    return program;
}

Computer get_input(const std::string& f_name) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return Computer({}, {});
    }
    std::vector<std::string> lines;
    for (std::string str; getline(file, str);) {
        if (!str.empty()) {
            lines.push_back(str);
        }
    }
    Registers reg {};
    reg.a = get_register(lines[0]);
    reg.b = get_register(lines[1]);
    reg.c = get_register(lines[2]);
    std::vector<int> program = get_program(lines[3]);
    return Computer(reg, program);
}
