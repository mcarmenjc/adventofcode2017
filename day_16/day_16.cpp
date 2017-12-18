#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Move {
    char move_type;
    int num_spins;
    int swap_pos1;
    int swap_pos2;
    char swap_char1;
    char swap_char2;
};

void SpinCharacters(std::vector<char> &characters, std::unordered_map<char, int> &char_to_pos, int num_spins){
    for (auto & p : char_to_pos){
        p.second = (num_spins + p.second)%characters.size();
        characters[p.second] = p.first;
    }
}

void SwapCharactersAtPositions(std::vector<char> &characters, std::unordered_map<char, int> &char_to_pos, int pos1, int pos2){
    char aux = characters[pos1];
    characters[pos1] = characters[pos2];
    characters[pos2] = aux;
    char_to_pos[characters[pos1]] = pos1;
    char_to_pos[characters[pos2]] = pos2;
}

void SwapCharacters(std::vector<char> &characters, std::unordered_map<char, int> &char_to_pos, char c1, char c2){
    int pos1 = char_to_pos[c1];
    int pos2 = char_to_pos[c2];
    SwapCharactersAtPositions(characters, char_to_pos, pos1, pos2);
}

void Dance(std::vector<char> &characters, const std::vector<Move> & movements){
    std::unordered_map<char, int> char_to_pos;
    for(int i = 0; i < characters.size(); ++i){
        char_to_pos.insert(std::make_pair(characters[i], i));
    }
    for (const Move &m : movements){
        if (m.move_type == 's'){
            SpinCharacters(characters, char_to_pos, m.num_spins);
        }
        else if (m.move_type == 'x'){
            SwapCharactersAtPositions(characters, char_to_pos, m.swap_pos1, m.swap_pos2);
        }
        else if (m.move_type == 'p'){
            SwapCharacters(characters, char_to_pos, m.swap_char1, m.swap_char2);
        }
    }
}

std::vector<Move> ReadMoves(std::string filename){
    std::vector<Move> moves;
    std::ifstream file (filename);
    std::string movement;
    while(std::getline(file, movement, ',')){
        Move m;
        m.move_type = movement[0];
        if (movement[0] == 's'){
            m.num_spins = stoi(movement.substr(1));
        }
        else if (movement[0] == 'x'){
            m.swap_pos1 = stoi(movement.substr(1, movement.find('/')-1));
            m.swap_pos2 = stoi(movement.substr(movement.find('/')+1));
        }
        else if (movement[0] == 'p'){
            m.swap_char1 = movement[1];
            m.swap_char2 = movement[3];
        }
        moves.push_back(m);
    }
    file.close();
    return moves;
}

std::string DanceTheWholeNight(std::vector<char> &characters, const std::vector<Move> moves, long num_iterations){
    std::unordered_map<std::string, int> dance_cycle;
    std::vector<std::string> sequence;
    std::string result(characters.begin(), characters.end());
    int it = 0;
    while(dance_cycle.count(result) == 0){
        dance_cycle.insert(std::make_pair(result, it));
        sequence.push_back(result);
        Dance(characters, moves);
        std::string aux(characters.begin(), characters.end());
        result = aux;
        ++it;
    }

    int pos = num_iterations%sequence.size();
    return sequence[pos];
}

int main(int argc, char **argv){
    if (argc != 3){
        std::cout << "Use of the program is: \n\t day_16 <initial word> <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[2];
    std::string word = argv[1];
    std::vector<char> characters(word.begin(), word.end());
    std::ifstream file (filename);
    std::vector<Move> moves = ReadMoves(filename);
    Dance(characters, moves);
    std::string after_dancing(characters.begin(), characters.end());
    std::cout << "Party is over and that's the result -> " << after_dancing << std::endl;
    std::vector<char> super_dancer_characters(word.begin(), word.end());
    std::string non_stop_dancers = DanceTheWholeNight(super_dancer_characters, moves, 1000000000);
    std::cout << "Non stop dancing during the night result in -> " << non_stop_dancers << std::endl;
}