#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <unordered_map>

using namespace std;

struct Instruction {
    char next_instruction;
    int new_value;
    char direction;
    Instruction() : next_instruction(' '), new_value(0), direction('l'){}
    Instruction(char inst, int v, char m) : next_instruction(inst), new_value(v), direction(m){}
};

std::unordered_map<char, std::unordered_map<int, Instruction> > LoadInstructions(){
    std::unordered_map<int, Instruction> A;
    A.insert(std::make_pair(0, Instruction('B', 1, 'r')));
    A.insert(std::make_pair(1, Instruction('B', 0, 'l')));
    std::unordered_map<int, Instruction> B;
    B.insert(std::make_pair(0, Instruction('C', 1, 'l')));
    B.insert(std::make_pair(1, Instruction('E', 0, 'r')));
    std::unordered_map<int, Instruction> C;
    C.insert(std::make_pair(0, Instruction('E', 1, 'r')));
    C.insert(std::make_pair(1, Instruction('D', 0, 'l')));
    std::unordered_map<int, Instruction> D;
    D.insert(std::make_pair(0, Instruction('A', 1, 'l')));
    D.insert(std::make_pair(1, Instruction('A', 1, 'l')));
    std::unordered_map<int, Instruction> E;
    E.insert(std::make_pair(0, Instruction('A', 0, 'r')));
    E.insert(std::make_pair(1, Instruction('F', 0, 'r')));
    std::unordered_map<int, Instruction> F;
    F.insert(std::make_pair(0, Instruction('E', 1, 'r')));
    F.insert(std::make_pair(1, Instruction('A', 1, 'r')));

    std::unordered_map<char, std::unordered_map<int, Instruction> > instructions;
    instructions.insert(std::make_pair('A', A));
    instructions.insert(std::make_pair('B', B));
    instructions.insert(std::make_pair('C', C));
    instructions.insert(std::make_pair('D', D));
    instructions.insert(std::make_pair('E', E));
    instructions.insert(std::make_pair('F', F));

    return instructions;
}

int CalculateCheckSum(const std::unordered_map<char, std::unordered_map<int, Instruction> > &instructions, int iterations){
    std::deque<int> checksum_list;
    checksum_list.push_back(0);
    int position = 0;
    int i = 0;
    char current_instruction = 'A';
    while (i < iterations){
        ++i;
        int value = checksum_list[position];
        checksum_list[position] = instructions.at(current_instruction).at(value).new_value;
        if (instructions.at(current_instruction).at(value).direction == 'r'){
            ++position;
            if (position == checksum_list.size()){
                checksum_list.push_back(0);
            }
        }
        if (instructions.at(current_instruction).at(value).direction == 'l'){
            if (position == 0){
                checksum_list.push_front(0);
            }
            else {
                --position;
            }
        }

        current_instruction = instructions.at(current_instruction).at(value).next_instruction;;
    }

    int num_ones = 0;
    for (int v : checksum_list){
        if (v == 1){
            ++num_ones;
        }
    }
    return num_ones;
}

void Print(const std::unordered_map<char, std::unordered_map<int, Instruction> > &instructions){
    for (const pair<char, std::unordered_map<int, Instruction> > p : instructions){
        std::cout << p.first << std::endl;
        std::cout << "\t next = " << p.second.at(0).next_instruction << "\t direction = " << p.second.at(0).direction << "\t value = " << p.second.at(0).new_value << std::endl;
        std::cout << "\t next = " << p.second.at(1).next_instruction << "\t direction = " << p.second.at(1).direction << "\t value = " << p.second.at(1).new_value << std::endl;
    }
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_25 <num iterations>\n" << std::endl;
        return 0;
    }
    int num_iterations = std::stoi(argv[1]);
    std::unordered_map<char, std::unordered_map<int, Instruction> > instructions = LoadInstructions();
    Print(instructions);
    int checksum = CalculateCheckSum(instructions, num_iterations);
    std::cout << "Checksum = " << checksum << std::endl;
}