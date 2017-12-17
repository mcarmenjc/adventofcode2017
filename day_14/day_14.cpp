#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "../lib/KnotHash.h"

using namespace std;

std::string GetHashDotsCode(const std::string &dense_hash){
    std::string hash_dots = "";
    std::unordered_map<char, std::string> hex_to_bin;
    hex_to_bin.insert(std::make_pair('0', "...."));
    hex_to_bin.insert(std::make_pair('1', "...#"));
    hex_to_bin.insert(std::make_pair('2', "..#."));
    hex_to_bin.insert(std::make_pair('3', "..##"));
    hex_to_bin.insert(std::make_pair('4', ".#.."));
    hex_to_bin.insert(std::make_pair('5', ".#.#"));
    hex_to_bin.insert(std::make_pair('6', ".##."));
    hex_to_bin.insert(std::make_pair('7', ".###"));
    hex_to_bin.insert(std::make_pair('8', "#..."));
    hex_to_bin.insert(std::make_pair('9', "#..#"));
    hex_to_bin.insert(std::make_pair('a', "#.#."));
    hex_to_bin.insert(std::make_pair('b', "#.##"));
    hex_to_bin.insert(std::make_pair('c', "##.."));
    hex_to_bin.insert(std::make_pair('d', "##.#"));
    hex_to_bin.insert(std::make_pair('e', "###."));
    hex_to_bin.insert(std::make_pair('f', "####"));

    for (char c : dense_hash){
        hash_dots += hex_to_bin[c];
    }
    
    return hash_dots;
}

std::vector<std::string> CalculateKnotHashMatrix(const std::string &magic_word){
    std::vector<std::string> hash_dots_matrix(128, "");
    KnotHash hash_creator;
    for (int i = 0; i < 128; ++i){
        std::string word = magic_word + "-" + std::to_string(i);
        std::string dense_hash = hash_creator.DenseKnotHash(word);
        hash_dots_matrix[i] = GetHashDotsCode(dense_hash);
    }

    return hash_dots_matrix;
}

int CountHashesInMatrix(const std::vector<std::string> &knot_matrix){
    int num_hashes = 0;
    for (const std::string & hash : knot_matrix){
        for (char c : hash){
            if (c == '#'){
                ++num_hashes;
            }
        }
    }
    return num_hashes;
}

void ColourRegion(const std::vector<std::string> &knot_matrix, std::vector<std::vector<int> > &coloured_matrix, int x, int y, int colour){
    std::vector<std::pair<int, int> > neighbours(4);
    neighbours[0] = std::make_pair(1, 0);
    neighbours[1] = std::make_pair(-1, 0);
    neighbours[2] = std::make_pair(0, 1);
    neighbours[3] = std::make_pair(0, -1);

    for (std::pair<int, int> neighbour : neighbours){
        int new_x = x + neighbour.first;
        int new_y = y + neighbour.second;
        if (new_x >= 0 && new_x < coloured_matrix.size() &&
            new_y >= 0 && new_y < coloured_matrix[0].size() &&
            knot_matrix[new_x][new_y] == '#' &&
            coloured_matrix[new_x][new_y] == 0){
                coloured_matrix[new_x][new_y] = colour;
                ColourRegion(knot_matrix, coloured_matrix, new_x, new_y, colour);
            }
    }
}

int GetNumberOfRegions(const std::vector<std::string> &knot_matrix){
    int num_regions = 0;
    std::vector<std::vector<int> > coloured_matrix(knot_matrix.size(), std::vector<int>(knot_matrix[0].length(), 0));
    
    for (int i = 0; i < coloured_matrix.size(); ++i){
        for (int j = 0; j < coloured_matrix[j].size(); ++j){
            if (coloured_matrix[i][j] == 0 && knot_matrix[i][j] == '#'){
                ++num_regions;
                ColourRegion(knot_matrix, coloured_matrix, i, j, num_regions);
            }
        }
    }

    return num_regions;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_14 <magic_word>\n" << std::endl;
        return 0;
    }
    std::string magic_word = argv[1];
    
    std::vector<std::string> knot_matrix = CalculateKnotHashMatrix(magic_word);
    int num_hashes = CountHashesInMatrix(knot_matrix);
    std::cout << "Num hashes in matrix = " << num_hashes << std::endl;
    int num_regions = GetNumberOfRegions(knot_matrix);
    std::cout << "Num regions in matrix = " << num_regions << std::endl;
}