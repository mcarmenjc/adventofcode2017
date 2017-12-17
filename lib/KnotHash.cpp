#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "KnotHash.h"

using namespace std;

std::vector<int> KnotHash::ReadLengths(const std::string &filename){
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

std::vector<int> KnotHash::ReadLengthsFromString(const std::string &filename){
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

std::vector<int> KnotHash::GetLengthsFromWord(const std::string &word){
    std::vector<int> subarray_sizes;
    for(char c : word){
        subarray_sizes.push_back((int)c);
    }
    subarray_sizes.push_back(17);
    subarray_sizes.push_back(31);
    subarray_sizes.push_back(73);
    subarray_sizes.push_back(47);
    subarray_sizes.push_back(23);
    return subarray_sizes;
}

void KnotHash::SwapElements(int &v1, int &v2){
    int temp = v1;
    v1 = v2;
    v2 = temp;
}

void KnotHash::ReverseSubarray(std::vector<int> & hash, int start, int size){
    int end = (start + size - 1)%hash.size();
    int it = 0;
    while (it < size/2){
        SwapElements(hash[start], hash[end]);
        start = (start + 1)%hash.size();
        end = end == 0 ? hash.size()-1 : end-1;
        ++it;
    }
}

std::vector<int> KnotHash::SparseKnotHashFromFile(const std::string &filename, int repeat){
    std::vector<int> subarray_lengths = ReadLengths(filename);
    return SparseKnotHash(subarray_lengths, repeat);
}

std::vector<int> KnotHash::SparseKnotHash(const std::vector<int> & subarray_lengths, int repeat){
    int hash_size = 256;
    std::vector<int> hash(hash_size, 0);
    for (int i = 0; i < hash_size; i++){
        hash[i] = i;
    }

    int skip_size = 0;
    int pos = 0;

    for (int i = 0; i < repeat; ++i){
        for (int length : subarray_lengths){
            if (length <= hash.size()){
                ReverseSubarray(hash, pos, length);
                pos = (pos + length + skip_size)%hash_size;
                ++ skip_size;
            }
        }    
    }

    return hash;
}

std::vector<int> KnotHash::DenseHash(const std::vector<int> &sparse_hash){
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

std::vector<int> KnotHash::DenseKnotHashFromFile(const std::string &filename){
    int repeat = 64;
    std::vector<int> subarray_lengths = ReadLengthsFromString(filename);
    std::vector<int> sparse_hash = SparseKnotHash(subarray_lengths, repeat);
    std::vector<int> dense_hash = DenseHash(sparse_hash);
    return dense_hash;
}

std::string KnotHash::DenseKnotHash(const std::string &word){
    int repeat = 64;
    std::vector<int> subarray_lengths = GetLengthsFromWord(word);
    std::vector<int> sparse_hash = SparseKnotHash(subarray_lengths, repeat);
    std::vector<int> dense_hash = DenseHash(sparse_hash);
    std::stringstream stream;
    for (int elem : dense_hash){
        stream << std::hex << setfill('0') << setw(2) << std::right << elem;
    }
    std::string hex_hash( stream.str() );
    return hex_hash;
}

void KnotHash::PrintHexHash(const std::vector<int> & hash){
    std::cout << "Hex hash = ";
    for (int elem : hash){
        std::cout << std::hex << setfill('0') << setw(2) << std::right << elem;
    }
    std::cout << std::endl;
}