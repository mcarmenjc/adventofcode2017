#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

std::vector<std::string> GetStringMatrixFromString(const std::string &pattern){
    int size = pattern.find('/');
    std::vector<std::string> pattern_matrix(size, "");
    int start = 0;
    int i = 0;
    while (i < size) {
        pattern_matrix[i] = pattern.substr(start, size);
        ++i;
        start = pattern.find('/', start) + 1;
    }
    return pattern_matrix;
}

std::string RotateStringMatrix90Degrees(std::vector<std::string> &matrix){
    for (int i = 0; i < matrix.size()/2; ++i){
        int start = i;
        int end = matrix.size() - i*2;
        for (int j = start; j < end - 1; ++j){
            char aux = matrix[i][j];
            matrix[i][j] = matrix[end-1-j][i];
            matrix[end-1-j][i] = matrix[end-1][end-1-j];
            matrix[end-1][end-1-j] = matrix[j][end-1];
            matrix[j][end-1] = aux;
        }
    }
    std::string rule = matrix[0];
    for (int i = 1; i < matrix.size(); ++i){
        rule += "/" + matrix[i];
    }
    return rule;
}

std::string FlipMatrix(std::vector<std::string> &matrix){
    for (int i = 0; i < matrix.size(); ++i){
        for (int j = 0, k = matrix.size()-1; j < matrix.size()/2; ++j, --k){
            int aux = matrix[i][j];
            matrix[i][j] = matrix[i][k];
            matrix[i][k] = aux;
        }
    }
    std::string rule = matrix[0];
    for (int i = 1; i < matrix.size(); ++i){
        rule += "/" + matrix[i];
    }
    return rule;
}

std::unordered_map<std::string, std::vector<std::string> > ReadRulesFromFile(std::string filename){
    std::ifstream file (filename);
    std::unordered_map<std::string, std::vector<std::string> > rules;
    std::string line;
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string rule;
        std::string arrow;
        std::string pattern;
        ss >> rule;
        ss >> arrow;
        ss >> pattern;
        std::vector<std::string> pattern_matrix = GetStringMatrixFromString(pattern);
        std::vector<std::string> rule_matrix = GetStringMatrixFromString(rule);
        for (int i = 0; i < 4; ++i){
            if (rules.count(rule) == 0){
                rules.insert(std::make_pair(rule, pattern_matrix));
            }
            rule = RotateStringMatrix90Degrees(rule_matrix);
        }
        rule = FlipMatrix(rule_matrix);
        for (int i = 0; i < 4; ++i){
            if (rules.count(rule) == 0){
                rules.insert(std::make_pair(rule, pattern_matrix));
            }
            rule = RotateStringMatrix90Degrees(rule_matrix);
        }
    }
    file.close();

    return rules;
}

void PrintRules(const std::unordered_map<std::string, std::vector<std::string> > &rules){
    for (const std::pair<std::string, std::vector<std::string> > &p : rules){
        std::cout << "Rule = " << p.first << std::endl;
        for (const std::string &s : p.second){
            std::cout << s << std::endl;
        }
    }
}

std::string GetStringPatternFromStateBlock(const std::vector<std::string> &state, int row, int col, int size){
    std::string pattern_str = "";
    for (int i = row; i < row+size; ++i){
        for (int j = col; j < col+size; ++j){
            pattern_str += state[i][j];
        }
        if (i < row + size - 1){
            pattern_str += '/';
        }
    }
    return pattern_str;
}

void InsertNewPattern(std::vector<std::string> &state, int row, const std::vector<std::string> &pattern){
    for (int i = 0, j = row; i < pattern.size(); ++i, ++j){
        state[j] += pattern[i];
    }
}

void PrintState(const std::vector<std::string> &state){
    for (const std::string &s : state){
        std::cout << s << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------" << std::endl;
}

std::vector<std::string> GetNextState(const std::vector<std::string> &state, const std::unordered_map<std::string, std::vector<std::string> > &rules){
    int size = 3;
    int num_blocks = state.size()/3;
    if (state.size()%2 == 0){
        size = 2;
        num_blocks = state.size()/2;
    }
    std::vector<std::string> next_state((size+1)*num_blocks, "");

    for (int i = 0; i < num_blocks; ++i){
        for (int j = 0; j < num_blocks; ++j){
            std::string state_pattern = GetStringPatternFromStateBlock(state, i*size, j*size, size);
            InsertNewPattern(next_state, i*(size+1), rules.at(state_pattern));
        }
    }

    return next_state;
}

std::vector<std::string> CreateFractal(const std::vector<std::string> &initial_state, const std::unordered_map<std::string, std::vector<std::string> > &rules, int num_iterations){
    std::vector<std::string> state = initial_state;
    for (int i = 0; i < num_iterations; ++i){
        state = GetNextState(state, rules);
    }
    return state;
}

int CountNumHashes (const std::vector<std::string> &state){
    int num_hashes = 0;
    for (const std::string &s : state){
        for (char c : s){
            if (c == '#'){
                ++num_hashes;
            }
        }
    }
    return num_hashes;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_21 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::unordered_map<std::string, std::vector<std::string> > rules = ReadRulesFromFile(filename);
    //PrintRules(rules);
    std::vector<std::string> state = {".#.", "..#", "###"};
    state = CreateFractal(state, rules, 5);
    //PrintState(state);
    std::cout << "Number of hashes in state after 5 iterations = " << CountNumHashes(state) << std::endl;

    state = {".#.", "..#", "###"};
    state = CreateFractal(state, rules, 18);
    //PrintState(state);
    std::cout << "Number of hashes in state after 18 iterations = " << CountNumHashes(state) << std::endl;
}