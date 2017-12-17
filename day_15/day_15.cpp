#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int GetNumDrawsFromGenerator(int seed_A, int seed_B, int num_iterations) {
    int num_draws = 0;
    int factor_A = 16807;
    int factor_B = 48271;
    int div = 2147483647;
    long gen_A = seed_A;
    long gen_B = seed_B;
    unsigned int mask = 0xFFFF;
    for (int i = 0; i < num_iterations; ++i){
        gen_A = (factor_A * gen_A)%div;
        gen_B = (factor_B * gen_B)%div;

        if ((gen_A & mask) == (gen_B & mask)){
            ++num_draws;
        }
    }

    return num_draws;
}

int GetNextPossibleNumber(long seed, int factor, int div, int divisible_by){
    long gen = (factor * seed)%div;
    while (gen%divisible_by != 0){
        gen = (factor * gen)%div;
    }
    return gen;
}

int GetNumDrawsFromPickyGenerator(int seed_A, int seed_B, int num_pairs) {
    int num_draws = 0;
    int factor_A = 16807;
    int factor_B = 48271;
    int div = 2147483647;
    long gen_A = seed_A;
    long gen_B = seed_B;
    unsigned int mask = 0xFFFF;
    for (int i = 0; i < num_pairs; ++i){
        gen_A = GetNextPossibleNumber(gen_A, factor_A, div, 4);
        gen_B = GetNextPossibleNumber(gen_B, factor_B, div, 8);
        
        if ((gen_A & mask) == (gen_B & mask)){
            ++num_draws;
        }
    }

    return num_draws;
}

int main(int argc, char **argv){
    if (argc != 5){
        std::cout << "Use of the program is: \n\t day_15 <generator A> <generator B> <num iterations> <num picky iterations>\n" << std::endl;
        return 0;
    }
    int seed_A = stoi(argv[1]);
    int seed_B = stoi(argv[2]);
    int num_iterations = stoi(argv[3]);
    int num_picky_iterations = stoi(argv[4]);
    
    int num_draws = GetNumDrawsFromGenerator(seed_A, seed_B, num_iterations);
    std::cout << "Num draws = " << num_draws << std::endl;
    int num_picky_draws = GetNumDrawsFromPickyGenerator(seed_A, seed_B, num_picky_iterations);
    std::cout << "Num draws from picky generators = " << num_picky_draws << std::endl;
}