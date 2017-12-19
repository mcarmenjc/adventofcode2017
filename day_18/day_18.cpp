#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Instruction {
    std::string command;
    std::string reg;
    int value;
};

std::vector<Instruction> ReadInstructionFile(std::string filename){
    std::vector<Instruction> instructions;
    std::ifstream file (filename);
    std::string line;
    while (std::getline(file, line)){
        std::stringstream ss(line);
        Instruction what_to_do;
        ss >> what_to_do.command;
        ss >> what_to_do.reg;
        if (what_to_do.command == "set" || 
            what_to_do.command == "add" || 
            what_to_do.command == "mul" || 
            what_to_do.command == "mod" || 
            what_to_do.command == "jgz"){
            ss >> what_to_do.value;
        }
        instructions.push_back(what_to_do);
    }
    file.close();
    return instructions;
}

int GetFirstRecoveredValue(const std::vector<Instruction> &instructions){
    int previous_sound = 0;

    return previous_sound;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_18 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<Instruction> instructions = ReadInstructionFile(filename);
    for (auto & i : instructions){
        std::cout << i.command << "\t" << i.reg << "\t" << i.value << std::endl;
    }
}