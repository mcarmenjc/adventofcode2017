#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
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

int GetStart(const std::string start_row){
    int i = 0;
    while (i < start_row.length() && start_row[i] != '|'){
        ++i;
    }
    return i;
}

std::pair<int, int> GetNewDirection(const std::vector<std::string> &diagram, const std::vector< std::vector<bool> > &visited, std::pair<int, int> pos, std::pair<int, int> direction){
    std::pair<int, int> next_direction = std::make_pair(0, 0);
    if (direction.first == 1 || direction.first == -1){
        if (pos.second-1 >= 0 && diagram[pos.first][pos.second-1] != ' ' && 
            diagram[pos.first][pos.second-1] != '+' && 
            !visited[pos.first][pos.second-1]){
            next_direction.second = -1;
        }
        else{
            next_direction.second = 1;
        }
    }
    else if (direction.second == 1 || direction.second == -1){
        if (pos.first-1 >= 0 && diagram[pos.first-1][pos.second] != ' ' 
            && diagram[pos.first-1][pos.second] != '+' &&
            !visited[pos.first-1][pos.second]){
            next_direction.first = -1;
        }
        else{
            next_direction.first = 1;
        }
    }
    return next_direction;
}

std::pair<std::string, int> GetRobotPath(const std::vector<std::string> &diagram){
    std::vector< std::vector<bool> > visited (diagram.size(), std::vector<bool>(diagram[0].length(), false));
    std::string path;
    std::pair<int, int> curr_pos = std::make_pair(0, GetStart(diagram[0]));
    std::pair<int, int> direction = std::make_pair(1, 0);
    int num_steps = 0;

    while (curr_pos.first >= 0 && curr_pos.first < diagram.size() &&
            curr_pos.second >= 0 && curr_pos.second < diagram[0].size() &&
            diagram[curr_pos.first][curr_pos.second] != ' '){
        ++num_steps;
        visited[curr_pos.first][curr_pos.second] = true;
        if (diagram[curr_pos.first][curr_pos.second] == '+'){
            direction = GetNewDirection(diagram, visited, curr_pos, direction);
        }
        else if (diagram[curr_pos.first][curr_pos.second] >= 'A' && diagram[curr_pos.first][curr_pos.second] <= 'Z') {
            path += diagram[curr_pos.first][curr_pos.second];
        }
        curr_pos.first += direction.first;
        curr_pos.second += direction.second;
    }

    return std::make_pair(path, num_steps);
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_18 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<std::string> diagram = ReadDiagram(filename);
    std::pair<std::string, int> result = GetRobotPath(diagram);
    std::cout << "Robot path = " << result.first << std::endl;
    std::cout << "Num steps = " << result.second << std::endl;
}