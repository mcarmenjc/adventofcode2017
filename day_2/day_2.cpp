#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int GetDiffBetweenDivisors(std::vector<int> & row){
    int res = 0;
    std::sort(row.begin(), row.end(), std::greater<int>());

    for (int i = 0; i < row.size()-1; ++i){
        int num = row[i];
        for (int j = i + 1; j < row.size(); ++j){
            int div = row[j];
            if (num%div == 0){
                if (num/div > res){
                    res = num/div;
                }
            }
        }
    }
    return res;
}

int GetDiffBetweenLargestAndSmallest(const std::vector<int> & row){
    int min = INT_MAX;
    int max = INT_MIN;

    for (int num : row){
        if (num < min){
            min = num;
        }
        if (num > max){
            max = num;
        }
    }

    return max - min;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_2 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    std::ifstream file (filename);
    std::string line;
    int sum_diff_largest_smallest = 0;
    int sum_for_divisors = 0;
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::vector<int> row;
        std::string number;
        while (ss >> number){
            row.push_back(std::stoi(number));
        }

        sum_diff_largest_smallest += GetDiffBetweenLargestAndSmallest(row);
        sum_for_divisors += GetDiffBetweenDivisors(row);
    }
    file.close();
    std::cout << "Sum of the difference between the largest and smallest = " << sum_diff_largest_smallest << std::endl;
    std::cout << "Sum of the difference between the divisors = " << sum_for_divisors << std::endl;
}