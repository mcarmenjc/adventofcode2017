#include <iostream>
#include <string>

using namespace std;

int CharToInt(char char_num){
    char start = '0';
    int num = char_num - start;
    return num;
}

int GetSumOfEqualConsecutiveDigits(std::string captcha){
    int sum = 0;
    for (int i = 0; i < captcha.length(); i++){
        int next_i = (i+1)%captcha.length();
        if (captcha[i] == captcha[next_i]){
            sum += CharToInt(captcha[next_i]);
        }
    }
    return sum;
}

int GetSumOfEqualHalfwayRoundDigits(std::string captcha){
    int sum = 0;
    int half_length = captcha.length()/2;
    int length = captcha.length();
    for (int i = 0; i < length; i++){
        int next_i = (i+half_length)%length;
        if (captcha[i] == captcha[next_i]){
            sum += CharToInt(captcha[next_i]);
        }
    }
    return sum;
}

int main(int argc, char** argv){
    if (argc < 3){
        std::cout << "Use of the program is: \n\t day_1 <option 1 or 2> <captcha>\n" << std::endl;
        return;
    }
    int option = CharToInt(argv[1][0]);
    string captcha = argv[2];
    int captcha_sum = 0;
    if (option == 1){
        captcha_sum = GetSumOfEqualConsecutiveDigits(captcha);
    }
    else {
        captcha_sum = GetSumOfEqualHalfwayRoundDigits(captcha);
    }
    std::cout << captcha_sum << std::endl;
}