#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <deque>

using namespace std;

std::vector<std::string> ReadDiagram(std::string filename){
    std::vector<std::string> diagram;
    std::ifstream file (filename);
    std::string line;
    while (std::getline(file, line)){
        diagram.push_back(line);
    }
    file.close();
    return diagram;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_18 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<std::string> diagram = ReadDiagram(filename);
}