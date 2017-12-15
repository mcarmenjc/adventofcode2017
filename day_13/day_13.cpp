#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

std::unordered_map<int, int> ReadFirewall(std::string filename){
    std::ifstream file (filename);
    std::unordered_map<int, int> firewall;
    std::string line;
    while (std::getline(file, line)){
        int layer = stoi(line.substr(0, line.find(':')));
        int range = stoi(line.substr(line.find(':')+2));
        firewall.insert(std::make_pair(layer, range));
    }
    file.close();
    return firewall;
}

int GetMaxLayer(std::unordered_map<int, int> & firewall){
    int max = INT_MIN;
    for (const auto & pair : firewall){
        if (pair.first > max){
            max = pair.first;
        }
    }
    return max;
}

void UpdateState(std::unordered_map<int, std::pair<int, int> > & state, std::unordered_map<int, int> & firewall){
    for (auto & pair : state){
        if (firewall[pair.first] > 1){
            if (pair.second.first == 1){
                pair.second.second = 1;
            }
            else if (pair.second.first == firewall[pair.first]){
                pair.second.second = -1;
            }
            pair.second.first += pair.second.second;
        }
    }
}

int CalculateSeverity(std::unordered_map<int, int> & firewall){
    int firewall_length = GetMaxLayer(firewall);
    int severity = 0;
    std::unordered_map<int, std::pair<int, int> > state;
    for (const auto & pair : firewall){
        state.insert(std::make_pair(pair.first, std::make_pair(1, 1)));
    }
    for (int i = 0; i <= firewall_length; ++i){
        if (firewall.count(i) > 0 && state[i].first == 1){
            severity += i*firewall.at(i);
        }
        UpdateState(state, firewall);
    }
    return severity;
}

int CalculateMinWaitToCrossTheFirewall(std::unordered_map<int, int> & firewall){
    int firewall_length = GetMaxLayer(firewall);
    int wait = 0;
    int pos = 0;
    std::unordered_map<int, std::pair<int, int> > state;
    std::unordered_map<int, std::pair<int, int> > wait_state;
    for (const auto & pair : firewall){
        state.insert(std::make_pair(pair.first, std::make_pair(1, 1)));
        wait_state.insert(std::make_pair(pair.first, std::make_pair(1, 1)));
    }
    while (pos <= firewall_length){
        if (firewall.count(pos) > 0 && state[pos].first == 1){
            ++wait;
            pos = 0;
            UpdateState(wait_state, firewall);
            state = wait_state;
            //std::cout << "wait = " << wait << std::endl;
        }
        else{
            UpdateState(state, firewall);
            ++pos;
        }
    }
    return wait;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_13 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::unordered_map<int, int> firewall = ReadFirewall(filename);
    int severity = CalculateSeverity(firewall);
    std::cout << "severity = " << severity << std::endl;
    int min_wait = CalculateMinWaitToCrossTheFirewall(firewall);
    std::cout << "min wait = " << min_wait << std::endl;
}