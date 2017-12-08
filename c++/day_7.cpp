#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

std::unordered_map<std::string, std::pair<int, std::vector<string> > > ReadGraphFromFile(std::string filename){
    std::unordered_map<std::string, std::pair<int, std::vector<string> > > programs;
    std::ifstream file (filename);
    std::string line;

    while (std::getline(file, line)){
        std::string name = line.substr(0, line.find(" ("));
        int weight = std::stoi(line.substr(line.find("(")+1, line.find(")") - line.find("(")));
        std::vector<std::string> children;
        std::size_t pos = line.find("->");
        if (pos != std::string::npos){
            pos = pos + 3;
            std::size_t found = line.find(", ");
            while(found != std::string::npos){
                children.push_back(line.substr(pos, found - pos));
                pos = found + 2;
                found = line.find(", ", pos);
            }
            children.push_back(line.substr(pos));
        }
        programs.insert(std::make_pair(name, std::make_pair(weight, children)));
    }
    file.close();

    return programs;
}

std::string FindProgramRoot(const std::unordered_map<std::string, std::pair<int, std::vector<string> > > &programs){
    std::unordered_set<std::string> not_root;
    std::unordered_set<std::string> possible_roots;
    for (const auto & program : programs){
        possible_roots.insert(program.first);
        if (program.second.second.size() > 0){
            for (const std::string & child : program.second.second){
                not_root.insert(child);
            }
        }
    }

    for (const std::string & program : possible_roots){
        if (not_root.count(program) == 0){
            return program;
        }
    }

    return "";
}

int CalculateWeights(const std::unordered_map<std::string, std::pair<int, std::vector<string> > > &programs, std::string root, int &correct_weight){
    if (programs.at(root).second.size() == 0){
        return programs.at(root).first;
    }

    int total_weight = programs.at(root).first;
    std::unordered_map< int, std::vector<std::string> > children_weights;
    for (const auto & child : programs.at(root).second){
        int weight = CalculateWeights(programs, child, correct_weight);
        total_weight += weight;
        if (children_weights.count(weight) == 0){
            std::vector<std::string> children;
            children_weights.insert(std::make_pair(weight, children));
        }
        children_weights[weight].push_back(child);
    }

    if (correct_weight == 0 && children_weights.size() > 1){
        std::string wrong_child;
        int wrong_weight = 0;
        int expected_weight = 0;
        for (const auto & weight_child : children_weights){
            if (weight_child.second.size() == 1){
                wrong_child = weight_child.second[0];
                wrong_weight = weight_child.first;
            }
            else{
                expected_weight = weight_child.first;
            }
        }

        correct_weight = programs.at(wrong_child).first;
        if (wrong_weight > expected_weight){
            correct_weight -= wrong_weight - expected_weight;
        }
        else {
            correct_weight += expected_weight - wrong_weight;
        }
    }

    return total_weight;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_7 <filename>\n" << std::endl;
        return;
    }
    std::string filename = argv[1];
    std::unordered_map<std::string, std::pair<int, std::vector<string> > > programs = ReadGraphFromFile(filename);
    std::string root = FindProgramRoot(programs);
    int correct_weight = 0;
    CalculateWeights(programs, root, correct_weight);
    std::cout << "root = " << root << std::endl;
    std::cout << "correct weight = " << correct_weight << std::endl;
}