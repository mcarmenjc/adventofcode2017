#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int GetStepsToExit(std::vector<int> &jumps){
    int steps = 0;
    int pos = 0;

    while (pos < jumps.size()){
        int jump = jumps[pos];
        ++jumps[pos];
        pos = pos + jump;
        ++steps;
    }

    return steps;
}

int GetStepsToExitIncAndDecAfterJump(std::vector<int> &jumps){
    int steps = 0;
    int pos = 0;

    while (pos < jumps.size()){
        int jump = jumps[pos];
        if (jump < 3){
            ++jumps[pos];
        }
        else{
            --jumps[pos];
        }
        pos = pos + jump;
        ++steps;
    }

    return steps;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_5 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    std::ifstream file (filename);
    std::vector<int> jumps;
    int jump;
    while (file >> jump){
        jumps.push_back(jump);
    }
    file.close();

    int steps_to_exit = GetStepsToExit(jumps);
    int steps_to_exit_with_dec = GetStepsToExitIncAndDecAfterJump(jumps);
    std::cout << "Steps to exit = " << steps_to_exit << std::endl;
    std::cout << "Steps to exit jumping forward and backwards = " << steps_to_exit_with_dec << std::endl;
}