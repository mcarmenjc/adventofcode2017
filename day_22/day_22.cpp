#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

std::vector<std::vector<char> > ReadMatrix(std::string filename){
    std::ifstream file (filename);
    std::vector<std::vector<char> > matrix(10001, std::vector<char>(10001, '.'));
    std::string line;
    int row = -1;
    int col = -1;
    while (std::getline(file, line)){
        if (row == -1){
            col = matrix.size()/2+1 - line.size()/2;
            row = matrix.size()/2+1 - line.size()/2;
        }
        for (int i = col, j = 0; j < line.size(); ++i, ++j){
            matrix[row][i] = line[j];
        }
        ++row;
    }
    file.close();

    return matrix;
}

void PrintMatrix(const std::vector< std::vector<char> > &matrix, int row, int col, int size, const std::pair<int, int> &pos){
    for (int i = row; i < row+size; ++i){
        for (int j = col; j < col+size; ++j){
            if (pos.first == i && pos.second == j){
                std::cout << "[" << matrix[i][j] << "]";
            }
            else {
                std::cout << " " << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

std::unordered_map<std::string, std::string> GoRightMap(){
    std::unordered_map<std::string, std::string> go_right;
    go_right.insert(std::make_pair("up", "right"));
    go_right.insert(std::make_pair("right", "down"));
    go_right.insert(std::make_pair("down", "left"));
    go_right.insert(std::make_pair("left", "up"));
    return go_right;
}

std::unordered_map<std::string, std::string> GoLeftMap(){
    std::unordered_map<std::string, std::string> go_left;
    go_left.insert(std::make_pair("up", "left"));
    go_left.insert(std::make_pair("left", "down"));
    go_left.insert(std::make_pair("down", "right"));
    go_left.insert(std::make_pair("right", "up"));
    return go_left;
}

std::unordered_map<std::string, std::string> ReverseMap(){
    std::unordered_map<std::string, std::string> reverse;
    reverse.insert(std::make_pair("up", "down"));
    reverse.insert(std::make_pair("left", "right"));
    reverse.insert(std::make_pair("down", "up"));
    reverse.insert(std::make_pair("right", "left"));
    return reverse;
}

std::unordered_map<std::string, std::pair<int, int> > DirectionsMap(){
    std::unordered_map<std::string, std::pair<int, int> > directions;
    directions.insert(std::make_pair("up", std::make_pair(-1, 0)));
    directions.insert(std::make_pair("down", std::make_pair(1, 0)));
    directions.insert(std::make_pair("right", std::make_pair(0, 1)));
    directions.insert(std::make_pair("left", std::make_pair(0, -1)));
    return directions;
}

std::pair<int, int> MoveResistentVirus(std::vector< std::vector<char> > &matrix, const std::pair<int, int> &pos, std::string &dir, int &infects){
    std::unordered_map<std::string, std::string> go_right = GoRightMap();
    std::unordered_map<std::string, std::string> go_left = GoLeftMap();
    std::unordered_map<std::string, std::string> reverse = ReverseMap();
    std::unordered_map<std::string, std::pair<int, int> > directions = DirectionsMap();
    std::pair<int, int> next_pos = pos;
    if (matrix[pos.first][pos.second] == '.'){
        dir = go_left[dir];
        matrix[pos.first][pos.second] = 'w';
    }
    else if (matrix[pos.first][pos.second] == 'w'){
        matrix[pos.first][pos.second] = '#';
        ++ infects;
    }
    else if (matrix[pos.first][pos.second] == '#'){
        dir = go_right[dir];
        matrix[pos.first][pos.second] = 'f';
    }
    else {
        dir = reverse[dir];
        matrix[pos.first][pos.second] = '.';
    }

    next_pos.first = pos.first + directions[dir].first;
    next_pos.second = pos.second + directions[dir].second;

    return next_pos;
}

int MoveResistentVirusXSteps(std::vector< std::vector<char> > &matrix, int num_iterations){
    int num_infected = 0;
    std::pair<int, int> curr_position = std::make_pair(matrix.size()/2+1, matrix.size()/2+1);
    std::string direction = "up";
    for (int i = 0; i < num_iterations; ++i){
        curr_position = MoveResistentVirus(matrix, curr_position, direction, num_infected);
    }
    PrintMatrix(matrix, 4971, 4971, 60, curr_position);
    return num_infected;
}

std::pair<int, int> MoveVirus(std::vector< std::vector<char> > &matrix, const std::pair<int, int> &pos, std::string &dir, int &infects){
    std::unordered_map<std::string, std::string> go_right = GoRightMap();
    std::unordered_map<std::string, std::string> go_left = GoLeftMap();
    std::unordered_map<std::string, std::pair<int, int> > directions = DirectionsMap();
    std::pair<int, int> next_pos = pos;
    if (matrix[pos.first][pos.second] == '.'){
        dir = go_left[dir];
        matrix[pos.first][pos.second] = '#';
        ++infects;
    }
    else {
        dir = go_right[dir];
        matrix[pos.first][pos.second] = '.';
    }

    next_pos.first = pos.first + directions[dir].first;
    next_pos.second = pos.second + directions[dir].second;

    return next_pos;
}

int MoveVirusXSteps(std::vector< std::vector<char> > &matrix, int num_iterations){
    int num_infected = 0;
    std::pair<int, int> curr_position = std::make_pair(matrix.size()/2+1, matrix.size()/2+1);
    std::string direction = "up";
    for (int i = 0; i < num_iterations; ++i){
        curr_position = MoveVirus(matrix, curr_position, direction, num_infected);
    }
    PrintMatrix(matrix, 4971, 4971, 60, curr_position);
    return num_infected;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_22 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<std::vector<char> > matrix = ReadMatrix(filename);
    int num_infected = MoveVirusXSteps(matrix, 10000);
    std::cout << "Num infections = " << num_infected << std::endl;
    matrix = ReadMatrix(filename);
    int num_infected_with_improved_virus = MoveResistentVirusXSteps(matrix, 10000000);
    std::cout << "Num infections = " << num_infected_with_improved_virus << std::endl;
}