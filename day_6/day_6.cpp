#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int FindMaxBankPosition(const std::vector<int> &cycle){
    int max_pos = 0;

    for (int i = 1; i < cycle.size(); ++i){
        if (cycle[i] > cycle[max_pos]){
            max_pos = i;
        }
    }

    return max_pos;
}

void GetNextCycle(std::vector<int> &cycle){
    int num_banks = cycle.size();
    int full_bank = FindMaxBankPosition(cycle);
    int num_blocks = cycle[full_bank];
    cycle[full_bank] = 0;
    int it = (full_bank + 1)%num_banks;
    while (num_blocks > 0){
        ++cycle[it];
        --num_blocks;
        it = (it + 1)%num_banks;
    }
}

std::string TranslateCycleToString(const std::vector<int> &cycle){
    std::string translation = "";
    for (int block : cycle){
        translation += std::to_string(block) + "|";
    }
    return translation;
}

int GetNumStepsUntilFirstRepeatedCycle(std::vector<int> &cycle){
    std::unordered_set<std::string> seen_cyles;
    std::string translated_cyle = TranslateCycleToString(cycle);
    int steps = 0;
    
    while (seen_cyles.count(translated_cyle) == 0){
        seen_cyles.insert(translated_cyle);
        GetNextCycle(cycle);
        translated_cyle = TranslateCycleToString(cycle);
        ++steps;
    }

    return steps;
}

int GetNumStepsFromRepeatedCycle(std::vector<int> &cycle){
    std::unordered_map<std::string, int> seen_cyles;
    std::string translated_cyle = TranslateCycleToString(cycle);
    int steps = 0;
    
    while (seen_cyles.count(translated_cyle) == 0){
        seen_cyles.insert(std::make_pair(translated_cyle, steps));
        GetNextCycle(cycle);
        translated_cyle = TranslateCycleToString(cycle);
        ++steps;
    }

    int steps_from_repeated = steps - seen_cyles[translated_cyle];

    return steps_from_repeated;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_6 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    std::ifstream file (filename);
    std::vector<int> initial_state;
    int block;
    while (file >> block){
        initial_state.push_back(block);
    }
    file.close();

    int steps_to_cycle = GetNumStepsUntilFirstRepeatedCycle(initial_state);
    int num_steps_in_cycle = GetNumStepsFromRepeatedCycle(initial_state);
    
    std::cout << "Num steps to first cycle = " << steps_to_cycle << std::endl;
    std::cout << "Num steps inside cycle = " << num_steps_in_cycle << std::endl;
}