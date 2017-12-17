#ifndef KNOTHASH_H
#define KNOTHASH_H

#include <string>
#include <vector>

class KnotHash{
    public:
        std::vector<int> SparseKnotHashFromFile(const std::string & filename, int repeat = 1);
        std::vector<int> DenseKnotHashFromFile(const std::string & filename);
        std::string DenseKnotHash(const std::string & word);
        void PrintHexHash(const std::vector<int> & hash);
    private:
        std::vector<int> ReadLengths(const std::string & filename);
        std::vector<int> ReadLengthsFromString(const std::string & filename);
        std::vector<int> GetLengthsFromWord(const std::string &word);
        void ReverseSubarray(std::vector<int> & hash, int start, int size);
        std::vector<int> SparseKnotHash(const std::vector<int> & subarray_lengths, int repeat);
        std::vector<int> DenseHash(const std::vector<int> &sparse_hash);
        void SwapElements(int &v1, int &v2);
};

#endif