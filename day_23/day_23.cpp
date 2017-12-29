#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>

using namespace std;

struct Instruction {
    std::string command;
    std::string op1;
    std::string op2;
};

std::vector<Instruction> ReadInstructionFile(std::string filename){
    std::vector<Instruction> instructions;
    std::ifstream file (filename);
    std::string line;
    while (std::getline(file, line)){
        std::stringstream ss(line);
        Instruction what_to_do;
        ss >> what_to_do.command;
        ss >> what_to_do.op1;
        ss >> what_to_do.op2;
        instructions.push_back(what_to_do);
    }
    file.close();
    return instructions;
}

long GetOperandValue(const std::unordered_map<char, long> register_sounds, const std::string &soperand){
    long operand = 0;
    if (soperand[0] >= 'a' && soperand[0] <= 'z'){
        if (register_sounds.count(soperand[0]) == 0){
            return 0;
        }
        operand = register_sounds.at(soperand[0]); 
    }
    else {
        operand = stoi(soperand);
    }

    return operand;
}

int GetNumOfExecutedMultiplications(const std::vector<Instruction> &instructions){
    std::unordered_map<char, long> registers_values;
    int i = 0;
    int num_multiplications = 0;
    while (i < instructions.size()){
        long operand = GetOperandValue(registers_values, instructions[i].op2);
        if (instructions[i].command == "set"){
            if (registers_values.count(instructions[i].op1[0]) == 0){
                registers_values.insert(std::make_pair(instructions[i].op1[0], 0));
            }
            registers_values[instructions[i].op1[0]] = operand;
            ++i ;
        }
        else if (instructions[i].command == "sub") {
            registers_values[instructions[i].op1[0]] -= operand;
            ++i ;
        }
        else if (instructions[i].command == "mul") {
            registers_values[instructions[i].op1[0]] *= operand;
            ++num_multiplications;
            ++i ;
        }
        else if (instructions[i].command == "jnz") {
            int first_op = GetOperandValue(registers_values, instructions[i].op1);
            if (first_op != 0){
                i += operand;
            }
            else {
                ++i;
            }
        }
    }

    return num_multiplications;
}

std::unordered_map<char, long> GetRegValues(const std::vector<Instruction> &instructions){
    std::unordered_map<char, long> registers_values;
    int i = 0;
    while (i < instructions.size()){
        long operand = GetOperandValue(registers_values, instructions[i].op2);
        if (instructions[i].command == "set"){
            if (registers_values.count(instructions[i].op1[0]) == 0){
                registers_values.insert(std::make_pair(instructions[i].op1[0], 0));
            }
            registers_values[instructions[i].op1[0]] = operand;
            ++i ;
        }
        else if (instructions[i].command == "sub") {
            registers_values[instructions[i].op1[0]] -= operand;
            ++i ;
        }
        else if (instructions[i].command == "mul") {
            registers_values[instructions[i].op1[0]] *= operand;
            ++i ;
        }
        else if (instructions[i].command == "jnz") {
            int first_op = GetOperandValue(registers_values, instructions[i].op1);
            if (first_op != 0){
                i += operand;
            }
            else {
                ++i;
            }
        }
    }

    return registers_values;
}

bool IsPrime(int value){
    if (value%2 == 0){
        return false;
    }
    for (int i = 3; i < sqrt(value) + 1; ++i){
        if (value%i == 0){
            return false;
        }
    }

    return true;
}

long GetHRegValue(){
    long b = 81*100 + 100000;
    int it = 0;
    long h = 0;
    while (it <= 1000){
        if (!IsPrime(b)){
            ++h;
        }
        b+=17;
        ++it;
    }
    return h;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_23 <filename no optimised>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<Instruction> instructions = ReadInstructionFile(filename);
    int multiplications = GetNumOfExecutedMultiplications(instructions);
    std::cout << "Num executed multiplications = " << multiplications << std::endl;
    
    int h_value = GetHRegValue();
    std::cout << "Reg H value = " << h_value << std::endl;
}