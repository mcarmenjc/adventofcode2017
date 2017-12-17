#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../lib/KnotHash.h"

using namespace std;

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_10 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    KnotHash hash_creator;
    std::vector<int> hash = hash_creator.SparseKnotHashFromFile(filename);
    std::vector<int> dense = hash_creator.DenseKnotHashFromFile(filename);
    std::cout << "First two elements product = " << hash[0]*hash[1] << std::endl;
    std::cout << "Hex hash = ";
    hash_creator.PrintHexHash(dense);
    std::cout << std::endl;
}