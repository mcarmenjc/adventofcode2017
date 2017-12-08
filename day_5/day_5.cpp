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
    if (argc != 3){
        std::cout << "Use of the program is: \n\t day_5 <option 1 or 2> <filename>\n" << std::endl;
        return;
    }
    int option = std::stoi(argv[1]);
    std::string filename = argv[2];

    std::ifstream file (filename);
    std::vector<int> jumps;
    int jump;
    while (file >> jump){
        jumps.push_back(jump);
    }
    file.close();

    int steps_to_exit = 0;
    if (option == 1){
        steps_to_exit = GetStepsToExit(jumps);
    }
    else{
        steps_to_exit = GetStepsToExitIncAndDecAfterJump(jumps);
    }
    std::cout << steps_to_exit << std::endl;
}