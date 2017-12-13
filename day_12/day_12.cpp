#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>

using namespace std;

std::unordered_map<int, std::vector<int> > ReadGraphFromFile(std::string filename){
    std::ifstream file (filename);
    std::unordered_map<int, std::vector<int> > graph;
    std::string line;
    while (std::getline(file, line)){
        std::vector<int> children;
        int node = stoi(line.substr(0, line.find(" ")));
        std::string children_list = line.substr(line.find(">")+1);
        std::stringstream ss(children_list);
        std::string child;
        while(std::getline(ss, child, ',')){
            children.push_back(stoi(child));
        }
        graph.insert(std::make_pair(node, children));
    }
    file.close();

    return graph;
}

std::unordered_set<int> GetAllNodesReachableFrom(const std::unordered_map<int, std::vector<int> > & graph, int origin_node){
    std::unordered_set<int> visited_nodes;
    std::deque<int> nodes_to_visit;
    nodes_to_visit.push_back(origin_node);
    visited_nodes.insert(origin_node);
    while (!nodes_to_visit.empty()){
        int node = nodes_to_visit.back();
        nodes_to_visit.pop_back();
        for (int child : graph.at(node)){
            if (visited_nodes.count(child) == 0){
                visited_nodes.insert(child);
                nodes_to_visit.push_back(child);
            }
        }
    }
    return visited_nodes;
}

int GetNumberOfGroupsInGraph(const std::unordered_map<int, std::vector<int> > & graph){
    std::unordered_set<int> visited_nodes;
    int num_groups = 0;
    for (const auto & pair : graph){
        int node = pair.first;
        if (visited_nodes.count(node) == 0){
            ++num_groups;
            std::unordered_set<int> nodes_in_group = GetAllNodesReachableFrom(graph, node);
            for (int node : nodes_in_group){
                visited_nodes.insert(node);
            }
        }
    }

    return num_groups;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_12 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::unordered_map<int, std::vector<int> > graph = ReadGraphFromFile(filename);
    std::unordered_set<int> nodes_from_orig = GetAllNodesReachableFrom(graph, 0);
    std::cout << "Num nodes accessible from 0 => " << nodes_from_orig.size() << std::endl;
    int num_groups_in_graph = GetNumberOfGroupsInGraph(graph);
    std::cout << "Num groups in graph => " << num_groups_in_graph << std::endl;
}