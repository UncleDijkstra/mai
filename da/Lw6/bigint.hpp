#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

const int R = 4;
const int BASE = pow(10, R);

class BigInt {
public:
    BigInt() {};
    BigInt(const std::string &str);
    BigInt(const size_t &size);
    BigInt(int size);
    ~BigInt() {};
    inline size_t size() const { return mData.size(); }
    BigInt operator+(const BigInt &other);
    BigInt operator-(const BigInt &other);
    BigInt operator*(const BigInt &other);
    BigInt operator/(BigInt &other);
    BigInt Power(int r);
    bool operator<(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator==(const BigInt &other) const;
    int Get(size_t i) const { return mData[i]; };
    void Set(size_t i, int num) { mData[i] = num; } ;
    friend std::ostream& operator<< (std::ostream& stream, const BigInt & number);
protected:
    std::vector<int> mData;
private:
    void DeleteZeros();
};

#endif