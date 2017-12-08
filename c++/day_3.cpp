#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

int GetDistanceToCenter(int number){
    int rows_cols = ceil(sqrt(number));
    if (rows_cols%2 == 0){
        rows_cols++;
    }
    int max = rows_cols * rows_cols;
    int mid = rows_cols/2;
    int diff = max - number;
    int side = diff/rows_cols;
    int row = 0;
    int col = 0;
    if (side == 0){
        row = -mid;
        col = abs(mid - diff);
    }
    else if (side == 1){
        col = -mid;
        row = abs(mid - (diff - rows_cols));
    }
    else if (side == 2){
        row = mid;
        col = abs(mid - (diff - 2*rows_cols));
    }
    else if (side == 3){
        col = -mid;
        row = abs(mid - (diff - 3*rows_cols));
    }

    return abs(row) + abs(col);
}

int CalculateSumOfNeighbours(const std::vector< std::vector<int> > & magic_spiral, int i, int j){
    std::vector< std::pair<int, int> > moves(8);
    moves.push_back(make_pair(0, 1));
    moves.push_back(make_pair(1, 1));
    moves.push_back(make_pair(1, 0));
    moves.push_back(make_pair(1, -1));
    moves.push_back(make_pair(0, -1));
    moves.push_back(make_pair(-1, -1));
    moves.push_back(make_pair(-1, 0));
    moves.push_back(make_pair(-1, 1));

    int sum = 0;
    for (const std::pair<int, int> & p : moves){
        if (i+p.first >= 0 && i+p.first < magic_spiral.size() && j+p.second >= 0 && j+p.second < magic_spiral.size()){
            sum += magic_spiral[i+p.first][j+p.second];
        }
    }

    return sum;
}

int GetNextNumber(int number){
    int radius = 1;
    int dimm = 1000;
    int center = dimm/2;
    int i = center;
    int j = center;

    std::vector< std::vector<int> > magic_spiral(dimm, std::vector<int> (dimm, 0) );
    magic_spiral[center][center] = 1;
    ++j;
    
    while ((i < dimm) && (i >= 0) && (j < dimm) && (j >= 0)){
        int right_limit = center + radius;
        int left_limit = center - radius;
        int bottom_limit = center + radius;
        int top_limit = center - radius;

        for (int c = i; i > top_limit; --i){
            magic_spiral[i][j] = CalculateSumOfNeighbours(magic_spiral, i, j);
            if (magic_spiral[i][j] > number){
                return magic_spiral[i][j];
            }
        }
        for (int c = j; j > left_limit; j--){
            magic_spiral[i][j] = CalculateSumOfNeighbours(magic_spiral, i, j);
            if (magic_spiral[i][j] > number){
                return magic_spiral[i][j];
            }
        }
        for (int c = i; i < bottom_limit; i++){
            magic_spiral[i][j] = CalculateSumOfNeighbours(magic_spiral, i, j);
            if (magic_spiral[i][j] > number){
                return magic_spiral[i][j];
            }
        }
        for (int c = j; j <= right_limit; j++){
            magic_spiral[i][j] = CalculateSumOfNeighbours(magic_spiral, i, j);
            if (magic_spiral[i][j] > number){
                return magic_spiral[i][j];
            }
        }
        ++radius;
    }

    return 0;
}

int main(int argc, char** argv){
    if (argc < 3){
        std::cout << "Use of the program is: \n\t day_3 <option 1 or 2> <captcha>\n" << std::endl;
        return;
    }
    int option = stoi(argv[1]);
    int number = stoi(argv[2]);
    int distance = 0;
    if (option == 1){
        distance = GetDistanceToCenter(number);
    }
    else {
        distance = GetNextNumber(number);
    }
    std::cout << distance << std::endl;
}