#include <iostream>
#include <string>
#include <fstream>
#include <deque>

using namespace std;

std::pair<int, int> AnalyseStreamCharacters(const std::string &stream){
    std::deque<char> groups;
    bool escape_next_character = false;
    bool is_garbage_group = false;
    int score = 0;
    int level = 0;
    int num_garbage_characters = 0;

    for (char c : stream){
        if (!escape_next_character){
            if (is_garbage_group){
                if (c == '>'){
                    is_garbage_group = false;
                }
                else if (c == '!'){
                    escape_next_character = true;
                }
                else {
                    ++ num_garbage_characters;
                }
            }
            else{
                if (c == '{'){
                    groups.push_back(c);
                    ++ level;
                    score += level;
                }
                else if (c == '}'){
                    groups.pop_back();
                    -- level;
                }
                else if (c == '<'){
                    is_garbage_group = true;
                }
            }
        }
        else {
            escape_next_character = false;
        }
    }

    return std::make_pair(score, num_garbage_characters);
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_9 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::ifstream file (filename);
    std::string stream;
    while (std::getline(file, stream)){
        std::cout << "Stream = " << stream << std::endl;
        std::pair<int, int> stream_info = AnalyseStreamCharacters(stream);
        std::cout << "Score = " << stream_info.first << std::endl;
        std::cout << "Number of characters in garbage = " << stream_info.second << std::endl;
    }
    file.close();
}