#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

bool IsAValidPassphrase(std::string passphrase){
    std::stringstream ss(passphrase);
    std::unordered_set<std::string> words;
    std::string word;
    while (ss >> word){
        if (words.count(word) == 0){
            words.insert(word);
        }
        else{
            return false;
        }
    }
    return true;
}

bool IsAValidPassphraseWithNoAnagrams(std::string passphrase){
    std::stringstream ss(passphrase);
    std::unordered_set<std::string> words;
    std::string word;
    while (ss >> word){
        std::sort(word.begin(), word.end());
        if (words.count(word) == 0){
            words.insert(word);
        }
        else{
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv){
    if (argc != 3){
        std::cout << "Use of the program is: \n\t day_4 <option 1 or 2> <filename>\n" << std::endl;
        return;
    }
    int option = std::stoi(argv[1]);
    std::string filename = argv[2];

    std::ifstream file (filename);
    std::string line;
    int num_valid_passphrases = 0;
    while (std::getline(file, line)){
        if (option == 1){
            if (IsAValidPassphrase(line)){
                ++num_valid_passphrases;
            }
        }
        else{
            if (IsAValidPassphraseWithNoAnagrams(line)){
                ++num_valid_passphrases;
            }
        }
    }
    file.close();
    std::cout << num_valid_passphrases << std::endl;
}