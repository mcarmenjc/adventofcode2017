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
        if (what_to_do.command == "set" || 
            what_to_do.command == "add" || 
            what_to_do.command == "mul" || 
            what_to_do.command == "mod" || 
            what_to_do.command == "jgz"){
            ss >> what_to_do.op2;
        }
        else {
            what_to_do.op2 = "0";
        }
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

int GetFirstRecoveredValue(const std::vector<Instruction> &instructions){
    std::unordered_map<char, long> register_sounds;
    std::unordered_map<char, long> previous_sounds;
    int i = 0;
    while (i < instructions.size()){
        long operand = GetOperandValue(register_sounds, instructions[i].op2);
        if (instructions[i].command == "set"){
            if (register_sounds.count(instructions[i].op1[0]) == 0){
                register_sounds.insert(std::make_pair(instructions[i].op1[0], operand));
                previous_sounds.insert(std::make_pair(instructions[i].op1[0], 0));
            }
            register_sounds[instructions[i].op1[0]] = operand;
            ++i ;
        }
        else if (instructions[i].command == "add") {
            register_sounds[instructions[i].op1[0]] += operand;
            ++i ;
        }
        else if (instructions[i].command == "mul") {
            register_sounds[instructions[i].op1[0]] *= operand;
            ++i ;
        }
        else if (instructions[i].command == "mod") {
            register_sounds[instructions[i].op1[0]] %= operand;
            ++i ;
        }
        else if (instructions[i].command == "jgz") {
            int first_op = GetOperandValue(register_sounds, instructions[i].op1);
            if (first_op > 0){
                i += operand;
            }
            else {
                ++i;
            }
        }
        else if (instructions[i].command == "rcv") {
            if (register_sounds[instructions[i].op1[0]] > 0 && previous_sounds[instructions[i].op1[0]] > 0){
                register_sounds[instructions[i].op1[0]] = previous_sounds[instructions[i].op1[0]];
                return previous_sounds[instructions[i].op1[0]];
            }
            ++i;
        }
        else if (instructions[i].command == "snd") {
            previous_sounds[instructions[i].op1[0]] = register_sounds[instructions[i].op1[0]];
            ++i;
        }
    }

    return 0;
}

int ExecuteCommand(std::unordered_map<char, long> &reg_values, const Instruction &instruction, std::deque<int> &prod, std::deque<int> &cons, int &num_snd){
    long operand = GetOperandValue(reg_values, instruction.op2);
    long first_op = GetOperandValue(reg_values, instruction.op1);
    if (instruction.command == "set"){
        if (reg_values.count(instruction.op1[0]) == 0){
            reg_values.insert(std::make_pair(instruction.op1[0], operand));
        }
        reg_values[instruction.op1[0]] = operand;
    }
    else if (instruction.command == "add") {
        reg_values[instruction.op1[0]] += operand;
    }
    else if (instruction.command == "mul") {
        reg_values[instruction.op1[0]] *= operand;
    }
    else if (instruction.command == "mod") {
        reg_values[instruction.op1[0]] %= operand;
    }
    else if (instruction.command == "jgz") {
        if (first_op > 0){
            return operand;
        }
    }
    else if (instruction.command == "rcv") {
        if (cons.empty()){
            return 0;
        }
        else{
            reg_values[instruction.op1[0]] = cons.front();
            cons.pop_front();
        }
    }
    else if (instruction.command == "snd") {
        if (first_op > 0){
            prod.push_back(first_op);
            ++num_snd;
        }
    }
    return 1;
}

int GetNumberOfSentRegisterByProgOne(const std::vector<Instruction> &instructions){
    std::unordered_map<char, long> reg_values_prog0;
    reg_values_prog0.insert(std::make_pair('p', 0));
    std::unordered_map<char, long> reg_values_prog1;
    reg_values_prog1.insert(std::make_pair('p', 1));
    std::deque<int> queue_prog0;
    std::deque<int> queue_prog1;
    int prog0 = 0;
    int prog1 = 0;
    int step0 = 1;
    int step1 = 1;
    int prog1_sends = 0;
    int prog0_sends = 0;
    while (prog0 < instructions.size() && prog1 < instructions.size() && (step0 != 0 || step1 != 0)){
        step0 = 0;
        step1 = 0;
        if (prog0 < instructions.size()){
            step0 = ExecuteCommand(reg_values_prog0, instructions[prog0], queue_prog0, queue_prog1, prog0_sends);
        }
        if (prog1 < instructions.size()){
            step1 = ExecuteCommand(reg_values_prog1, instructions[prog1], queue_prog1, queue_prog0, prog1_sends);
        }
        prog0 += step0;
        prog1 += step1;
    }

    return prog1_sends;
} 

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_18 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<Instruction> instructions = ReadInstructionFile(filename);
    long first_recovered_value = GetFirstRecoveredValue(instructions);
    std::cout << "First recovered value = " << first_recovered_value << std::endl;
    int num_sends = GetNumberOfSentRegisterByProgOne(instructions);
    std::cout << "Num sends operations from program 1 = " << num_sends << std::endl;
}