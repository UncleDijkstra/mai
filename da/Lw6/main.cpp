#include "bigint.hpp"
// #include <time.h> // for bench

int StingToInt(const std::string &str);

int main() {
    std::string strNum1;
    std::string strNum2;
    std::string strOperation;
    while(std::cin >> strNum1 
        >> strNum2 
        >> strOperation) {

        BigInt num1(strNum1);
        BigInt num2(strNum2);
        BigInt res;
        if(strOperation == "+") {
            res = num1 + num2;
        } else if(strOperation == "-") {
             if(num1 < num2) {
                std::cout << "Error" << std::endl;
             } else {
                res = num1 - num2;
             }
        } else if(strOperation == "*") {
            res = num1 * num2;
        } else if(strOperation == "/") {
            if(num2 == 0) {
                std::cout << "Error" << std::endl;
            } else {
                res = num1 / num2;
            }
        } else if(strOperation == "^") {
            if(num1 == 0) {
                if(num2 == 0) {
                    std::cout << "Error" << std::endl;
                } else {
                    res = 0;
                }
            } else if(num1 == 1) {
                res = 1;
            } else {
                res = num1.Power(StingToInt(strNum2));
            }
        } else if(strOperation == "<") {
            num1 < num2 ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
        } else if(strOperation == ">") {
            num1 > num2 ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
        } else if(strOperation == "=") {
            num1 == num2 ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
        }
        if(res.size() != 0) {
            std::cout << res << std::endl;
        }
    }
    return 0;
}

int StingToInt(const std::string &str) {
    int tmp = 0;
    for(int i = 0; i < str.size(); ++i) {
        tmp = tmp * 10 + (str[i] - '0');
    }
    return tmp;
}
