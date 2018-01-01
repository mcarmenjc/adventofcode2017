#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

std::unordered_map<int, std::unordered_set<int> > ReadComponentsPorts(std::string filename){
    std::ifstream file (filename);
    std::unordered_map<int, std::unordered_set<int> > components;
    std::string line;
    while (std::getline(file, line)){
        int port1 = std::stoi(line.substr(0, line.find('/')));
        int port2 = std::stoi(line.substr(line.find('/')+1));
        if (components.count(port1) == 0){
            components.insert(std::make_pair(port1, std::unordered_set<int>()));
        }
        if (components.count(port2) == 0){
            components.insert(std::make_pair(port2, std::unordered_set<int>()));
        }
        components[port1].insert(port2);
        components[port2].insert(port1);
    }
    file.close();

    return components;
}

int GetStrongestBridgeFrom(int port, const std::unordered_map<int, std::unordered_set<int> > &ports, std::unordered_map<std::string, bool> &visited){
    int max_strength = INT_MIN;
    if (ports.count(port) == 0){
        return 0;
    }

    for (int port2 : ports.at(port)){
        int bridge_strength = 0;
        std::string component = port < port2 ? std::to_string(port) + "/" + std::to_string(port2) : std::to_string(port2) + "/" + std::to_string(port);
        if (!visited[component]){
            visited[component] = true;
            bridge_strength = port + port2 + GetStrongestBridgeFrom(port2, ports, visited);
            visited[component] = false;
        }
        if (bridge_strength > max_strength){
            max_strength = bridge_strength;
        }
    }
    return max_strength;
}

int GetStrongestBridge(const std::unordered_map<int, std::unordered_set<int> > &ports){
    int max = INT_MIN;
    std::unordered_map<std::string, bool> visited;
    for (const pair<int, std::unordered_set<int> > &c : ports){
        for (int p : c.second){
            std::string port = c.first < p ? std::to_string(c.first) + "/" + std::to_string(p) : std::to_string(p) + "/" + std::to_string(c.first);
            if (visited.count(port) == 0){
                visited.insert(std::make_pair(port, false));
            }
        }
    }
    
    for (int port : ports.at(0)){
        visited["0/"+std::to_string(port)] = true;
        int bridge_strength = port + GetStrongestBridgeFrom(port, ports, visited);
        if (bridge_strength > max){
            max = bridge_strength;
        }
    }

    return max;
}

void GetStrongestForLengthBridgeFrom(int port, int length, int strength, const std::unordered_map<int, std::unordered_set<int> > &ports, std::unordered_map<std::string, bool> &visited, std::unordered_map<int, int> &strength_for_length){
    if (ports.count(port) == 0){
        return;
    }

    for (int port2 : ports.at(port)){
        std::string component = port < port2 ? std::to_string(port) + "/" + std::to_string(port2) : std::to_string(port2) + "/" + std::to_string(port);
        if (!visited[component]){
            visited[component] = true;
            int new_strength = strength + port + port2;
            int new_length = length + 1;
            if (strength_for_length.count(new_length) == 0){
                strength_for_length.insert(std::make_pair(new_length, new_strength));
            }
            if (strength_for_length[new_length] < new_strength){
                strength_for_length[new_length] = new_strength;
            }
            GetStrongestForLengthBridgeFrom(port2, new_length, new_strength, ports, visited, strength_for_length);
            visited[component] = false;
        }
    }
}

int GetLongestStrongestBridge(const std::unordered_map<int, std::unordered_set<int> > &ports){
    std::unordered_map<std::string, bool> visited;
    std::unordered_map<int, int> strongest_for_length;
    for (const pair<int, std::unordered_set<int> > &c : ports){
        for (int p : c.second){
            std::string port = c.first < p ? std::to_string(c.first) + "/" + std::to_string(p) : std::to_string(p) + "/" + std::to_string(c.first);
            if (visited.count(port) == 0){
                visited.insert(std::make_pair(port, false));
            }
        }
    }
    
    for (int port : ports.at(0)){
        visited["0/"+std::to_string(port)] = true;
        if (strongest_for_length.count(1) == 0){
            strongest_for_length.insert(std::make_pair(1, port));
        }
        if (strongest_for_length[1] < port){
            strongest_for_length[1] = port;
        }
        GetStrongestForLengthBridgeFrom(port, 1, port, ports, visited, strongest_for_length);
        visited["0/"+std::to_string(port)] = false;
    }

    int max = INT_MIN;
    int length = INT_MIN;
    for (const pair<int, int> &p : strongest_for_length){
        if (length < p.first){
            length = p.first;
            max = p.second;
        }
    }

    return max;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_24 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::unordered_map<int, std::unordered_set<int> > ports = ReadComponentsPorts(filename);
    int strongest_bridge = GetStrongestBridge(ports);
    std::cout << "Strongest bridge = " << strongest_bridge << std::endl;
    int strongest_longest_bridge = GetLongestStrongestBridge(ports);
    std::cout << "Strongest longest bridge = " << strongest_longest_bridge << std::endl;
}