#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include  <iomanip>

using namespace std;

void PrintArray(const std::vector<int> &array, int start, int end){
    int i = start;
    while(i != end){ 
        std::cout << array[i] << " - ";
        i = (i+1)%array.size();
    }
    std::cout << array[i] << std::endl;
}

void SwapElements(int &v1, int &v2){
    int temp = v1;
    v1 = v2;
    v2 = temp;
}

void ReverseSubarray(std::vector<int> & hash, int start, int size){
    int end = (start + size - 1)%hash.size();
    int it = 0;
    while (it < size/2){
        SwapElements(hash[start], hash[end]);
        start = (start + 1)%hash.size();
        end = end == 0 ? hash.size()-1 : end-1;
        ++it;
    }
}

std::vector<int> CreateHash(const std::vector<int> subarray_sizes, int hash_size, int repeat){
    std::vector<int> hash(hash_size, 0);
    for (int i = 0; i < hash_size; i++){
        hash[i] = i;
    }

    int skip_size = 0;
    int pos = 0;

    for (int i = 0; i < repeat; ++i){
        for (int length : subarray_sizes){
            if (length <= hash.size()){
                ReverseSubarray(hash, pos, length);
                pos = (pos + length + skip_size)%hash_size;
                ++ skip_size;
            }
        }    
    }

    return hash;
}

std::vector<int> ReadLengths(std::string filename){
    std::ifstream file (filename);
    int size;
    std::vector<int> subarray_sizes;
    while (file >> size){
        subarray_sizes.push_back(size);
        char s;
        file >> s;
    }
    file.close();
    return subarray_sizes;
}

std::vector<int> ReadLengthsFromString(std::string filename){
    std::ifstream file (filename);
    std::string line;
    std::vector<int> subarray_sizes;
    std::getline(file, line);
    file.close();
    for(char c : line){
        subarray_sizes.push_back((int)c);
    }
    subarray_sizes.push_back(17);
    subarray_sizes.push_back(31);
    subarray_sizes.push_back(73);
    subarray_sizes.push_back(47);
    subarray_sizes.push_back(23);
    return subarray_sizes;
}

std::vector<int> DenseHash(const std::vector<int> &sparse_hash){
    std::vector<int> dense_hash;
    for (int i = 0; i < 16; ++i){
        int dense = sparse_hash[i*16];
        for (int j = 1; j < 16; j++){
            dense = dense ^ sparse_hash[i*16 + j];
        }
        dense_hash.push_back(dense);
    }
    return dense_hash;
}

int main(int argc, char **argv){
    if (argc != 3){
        std::cout << "Use of the program is: \n\t day_10 <hash_size> <filename>\n" << std::endl;
        return 0;
    }
    int hash_size = stoi(argv[1]);
    std::string filename = argv[2];
    std::vector<int> subarray_sizes = ReadLengths(filename);
    std::vector<int> hash = CreateHash(subarray_sizes, hash_size, 1);
    std::vector<int> subarray_sizes2 = ReadLengthsFromString(filename);
    std::vector<int> hash2 = CreateHash(subarray_sizes2, hash_size, 64);
    std::vector<int> dense = DenseHash(hash2);
    std::cout << "First two elements product = " << hash[0]*hash[1] << std::endl;
    std::cout << "Hex hash = ";
    for (int elem : dense){
        std::cout << std::hex << setfill('0') << setw(2) << std::right << elem;
    }
    std::cout << std::endl;
}