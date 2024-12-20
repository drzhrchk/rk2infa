#include <iostream>
#include <bitset>
#include <string>
#include <algorithm> 

std::string binarySum(const std::string &a, const std::string &b) {
    std::string result;
    int carry = 0;
    

    int length = std::max(a.size(), b.size());
    std::string aPadded = std::string(length - a.size(), '0') + a;
    std::string bPadded = std::string(length - b.size(), '0') + b;


    for (int i = length - 1; i >= 0; --i) {
        int sum = (aPadded[i] - '0') + (bPadded[i] - '0') + carry;
        result.push_back((sum % 2) + '0'); 
        carry = sum / 2; 
    }
    

    if (carry) {
        result.push_back(carry + '0');
    }


    std::reverse(result.begin(), result.end());
    
    return result;
}

int main() {
    std::string A = "101101";
    std::string B = "110011";


    std::bitset<6> aBitset(A);
    std::bitset<6> bBitset(B);
    std::bitset<6> andResult = aBitset & bBitset;


    std::cout << "Побитовая операция AND: " << andResult << std::endl;


    std::string sumResult = binarySum(A, B);


    std::cout << "Сумма чисел A и B: " << sumResult << std::endl;

    return 0;
}
