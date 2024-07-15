#include "rle.h"

#define ull unsigned long long int

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int pow(int n, int k) {
    int sum = 1;
    for (int i = 0; i < k; i++) {
        sum *= n;
    }
    return sum;
}

string DecimalToBinary(int num) {
    string str;
    while (num) {
        if (num & 1) // 1
            str += '1';
        else // 0
            str += '0';
        num >>= 1; // Right Shift by 1 
    } 
    string rev = string(str.rbegin(), str.rend());
    return rev;
}

int binaryToDecimal(const string &input) {
    int sum = 0;
    int len = input.length();
    for (int i = 0; i < len; i++) {
        if (input[i] == '1') {
            sum += pow(2, len - i - 1);
        }
    }
    return sum;
}

int percentTen(int i) {
    int k = 1;
    while (i / k != 0) {
        k *= 10;
    }
    return k / 10;
}

// Constructor
rle::rle(int gamma) : gamma(gamma) {}

// Convert integer to gamma-bit binary string
string rle::f(int i) {
    string final;
    int maxValue = pow(2, gamma) - 1;
    int quotient = i / maxValue;
    int remainder = i % maxValue;
    string zeroes(gamma, '0');
    string ones(gamma, '1');
    string binaryRemainder = DecimalToBinary(remainder);

    for (int j = 0; j < quotient; j++) {
        final.append(ones);
        final.append(zeroes);
    }

    int paddingLength = gamma - binaryRemainder.length();
    final.append(string(paddingLength, '0'));
    final.append(binaryRemainder);

    return final;
}

// Convert gamma-bit binary string to integer
int rle::g(const string &binaryString) {
    int sum = 0;
    int len = binaryString.length();
    for (int j = 0; j < len; j += gamma) {
        string subStr = binaryString.substr(j, gamma);
        int value = binaryToDecimal(subStr);
        sum += value;
    }
    return sum;
}

// Compress the input string
string rle::compress(const string &inputString) {
    string result;
    result += inputString[0];
    int iter = 1;
    int charsMatched = 1;

    while (iter < inputString.length()) {
        if (inputString[iter] == inputString[iter - 1]) {
            charsMatched++;
        } else {
            result.append(f(charsMatched));
            charsMatched = 1;
        }
        iter++;
    }
    result.append(f(charsMatched));

    return result;
}

// Decompress the input string
string rle::decompress(const string &inputString) { 
    string result;
    bool isOne = (inputString[0] == '1');

    for (int iter = 1; iter < inputString.length(); iter += gamma) {
        string subStr = inputString.substr(iter, gamma);
        int count = binaryToDecimal(subStr);

        result.append(count, isOne ? '1' : '0');
        isOne = !isOne;
    }

    return result;
}
