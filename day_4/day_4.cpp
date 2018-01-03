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
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_4 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    std::ifstream file (filename);
    std::string line;
    int num_valid_passphrases = 0;
    int num_valid_passphrases_no_anagrams = 0;
    while (std::getline(file, line)){
        if (IsAValidPassphrase(line)){
            ++num_valid_passphrases;
        }
        if (IsAValidPassphraseWithNoAnagrams(line)){
            ++num_valid_passphrases_no_anagrams;
        }
    }
    file.close();
    std::cout << "Num valid passphrases = " << num_valid_passphrases << std::endl;
    std::cout << "Num valid passphrases with no anagrams = " << num_valid_passphrases_no_anagrams << std::endl;
}