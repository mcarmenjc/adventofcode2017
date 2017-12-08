#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <climits>

using namespace std;

struct RegisterOperation {
    std::string reg_name;
    std::string op;
    int value;
};

struct ProgramLine {
    RegisterOperation inc_dec_operation;
    RegisterOperation condition;
};

bool EvaluateCondition(int num1, int num2, std::string op){
    if (op == ">"){
        return num1 > num2;
    }
    else if (op == "<"){
        return num1 < num2;
    }
    else if (op == ">="){
        return num1 >= num2;
    }
    else if (op == "<="){
        return num1 <= num2;
    }
    else if (op == "=="){
        return num1 == num2;
    }
    else if (op == "!="){
        return num1 != num2;
    }
    return false;
}

int ApplyOperation(int num1, int num2, std::string op){
    if (op == "inc"){
        return num1 + num2;
    }
    else if (op == "dec"){
        return num1 - num2;
    }
    return 0;
}

std::vector<ProgramLine> ReadProgramFile(std::string filename){
    std::vector<ProgramLine> program;
    std::ifstream file (filename);
    std::string line;

    while (std::getline(file, line)){
        RegisterOperation inc_dec_op;
        RegisterOperation cond_op;
        std::stringstream ss(line);
        std::string value;

        ss >> inc_dec_op.reg_name;
        ss >> inc_dec_op.op;
        ss >> value;
        inc_dec_op.value = std::stoi(value);
        ss >> value;
        ss >> cond_op.reg_name;
        ss >> cond_op.op;
        ss >> value;
        cond_op.value = std::stoi(value);

        ProgramLine pline;
        pline.inc_dec_operation = inc_dec_op;
        pline.condition = cond_op;
        program.push_back(pline);
    }
    file.close();

    return program;
}

int GetMaxFromHash(const std::unordered_map<string, int> &registers){
    int max = INT_MIN;

    for (const auto & reg : registers){
        if (reg.second > max){
            max = reg.second;
        }
    }

    return max;
}

int GetMaxRegisterValue(const std::vector<ProgramLine> &program){
    std::unordered_map<std::string, int> registers;

    for (const ProgramLine & line : program){
        if (registers.count(line.condition.reg_name) == 0){
            registers.insert(std::make_pair(line.condition.reg_name, 0));
        }
        int register_condition_value = registers[line.condition.reg_name];
        bool condition_output = EvaluateCondition(register_condition_value, line.condition.value, line.condition.op);
        if (condition_output){
            if (registers.count(line.inc_dec_operation.reg_name) == 0){
                registers.insert(std::make_pair(line.inc_dec_operation.reg_name, 0));
            }

            int current_value = registers[line.inc_dec_operation.reg_name];
            registers[line.inc_dec_operation.reg_name] = ApplyOperation(current_value, line.inc_dec_operation.value, line.inc_dec_operation.op);
        }
    }

    return GetMaxFromHash(registers);
}

int GetMaxEverRegisterValue(const std::vector<ProgramLine> &program){
    std::unordered_map<std::string, int> registers;
    int max_ever = INT_MIN;

    for (const ProgramLine & line : program){
        if (registers.count(line.condition.reg_name) == 0){
            registers.insert(std::make_pair(line.condition.reg_name, 0));
        }
        int register_condition_value = registers[line.condition.reg_name];
        bool condition_output = EvaluateCondition(register_condition_value, line.condition.value, line.condition.op);
        if (condition_output){
            if (registers.count(line.inc_dec_operation.reg_name) == 0){
                registers.insert(std::make_pair(line.inc_dec_operation.reg_name, 0));
            }

            int current_value = registers[line.inc_dec_operation.reg_name];
            registers[line.inc_dec_operation.reg_name] = ApplyOperation(current_value, line.inc_dec_operation.value, line.inc_dec_operation.op);
        }
        if (registers[line.inc_dec_operation.reg_name] > max_ever){
            max_ever = registers[line.inc_dec_operation.reg_name];
        }
    }

    return max_ever;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_8 <filename>\n" << std::endl;
        return;
    }
    std::string filename = argv[1];
    std::vector<ProgramLine> program = ReadProgramFile(filename);

    int max_register_value = GetMaxRegisterValue(program);
    std::cout << "max = " << max_register_value << std::endl;
    int max_ever = GetMaxEverRegisterValue(program);
    std::cout << "max_ever = " << max_ever << std::endl;
}