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
    if (argc < 2){
        std::cout << "Use of the program is: \n\t day_1 <captcha>\n" << std::endl;
        return 0;
    }
    string captcha = argv[1];
    int consecutive_captcha = GetSumOfEqualConsecutiveDigits(captcha);
    int halfway_captcha = GetSumOfEqualHalfwayRoundDigits(captcha);
    std::cout << "Captcha for consecutive digits = " << consecutive_captcha << std::endl;
    std::cout << "Captcha doing halfway round = " << halfway_captcha << std::endl;
}