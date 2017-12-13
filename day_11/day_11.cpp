#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <climits>

using namespace std;

int GetDistanceBetweenStartAndChildProcess(const std::vector<string> &path){
    std::unordered_map<std::string, std::tuple<int, int, int> > movements;
    movements.insert(std::make_pair("n", std::make_tuple(0, 1, -1)));
    movements.insert(std::make_pair("ne", std::make_tuple(1, 0, -1)));
    movements.insert(std::make_pair("se", std::make_tuple(1, -1, 0)));
    movements.insert(std::make_pair("s", std::make_tuple(0, -1, 1)));
    movements.insert(std::make_pair("sw", std::make_tuple(-1, 0, 1)));
    movements.insert(std::make_pair("nw", std::make_tuple(-1, 1, 0)));
    std::tuple<int, int, int> curr_node(0, 0, 0);

    for (const auto & mov : path){
        std::get<0>(curr_node) += std::get<0>(movements[mov]);
        std::get<1>(curr_node) += std::get<1>(movements[mov]);
        std::get<2>(curr_node) += std::get<2>(movements[mov]);
    }

    return max(max(abs(std::get<0>(curr_node)), abs(std::get<1>(curr_node))), abs(std::get<2>(curr_node)));
}

int GetMaxDistanceAway(const std::vector<string> &path){
    std::unordered_map<std::string, std::tuple<int, int, int> > movements;
    movements.insert(std::make_pair("n", std::make_tuple(0, 1, -1)));
    movements.insert(std::make_pair("ne", std::make_tuple(1, 0, -1)));
    movements.insert(std::make_pair("se", std::make_tuple(1, -1, 0)));
    movements.insert(std::make_pair("s", std::make_tuple(0, -1, 1)));
    movements.insert(std::make_pair("sw", std::make_tuple(-1, 0, 1)));
    movements.insert(std::make_pair("nw", std::make_tuple(-1, 1, 0)));
    std::tuple<int, int, int> curr_node(0, 0, 0);
    int max_distance = INT_MIN;

    for (const auto & mov : path){
        std::get<0>(curr_node) += std::get<0>(movements[mov]);
        std::get<1>(curr_node) += std::get<1>(movements[mov]);
        std::get<2>(curr_node) += std::get<2>(movements[mov]);
        int current_distance = max(max(abs(std::get<0>(curr_node)), abs(std::get<1>(curr_node))), abs(std::get<2>(curr_node)));
        if (current_distance > max_distance){
            max_distance = current_distance;
        }
    }

    return max_distance;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_11 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::ifstream file (filename);
    std::string spath;
    while (std::getline(file, spath)){
        std::vector<std::string> path;
        std::stringstream ss(spath);
        std::string direction;
        while(std::getline(ss, direction, ',')){
            path.push_back(direction);
        }

        int steps = GetDistanceBetweenStartAndChildProcess(path);
        std::cout << "min steps = " << steps << std::endl;
        int max_distance = GetMaxDistanceAway(path);
        std::cout << "max distance = " << max_distance << std::endl;
    }
    file.close();
}