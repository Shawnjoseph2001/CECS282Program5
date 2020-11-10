//
// Created by shawn on 11/2/20.
//

#ifndef CECS282PROGRAM5_BIGINT_H
#define CECS282PROGRAM5_BIGINT_H
#include <iostream>
#include <vector>
using namespace std;
class BigInt {
public:
    BigInt(int b);
    BigInt();
    BigInt(const BigInt& b);
    explicit BigInt(const string& s);
    void print() const;
    BigInt& operator=(int b);
    bool operator==(const BigInt& b);
    friend ostream& operator<<(ostream &os, const BigInt &b);
    bool operator<(const BigInt& b);
    bool operator<=(const BigInt& b);
    bool operator>(const BigInt& b);
    bool operator>=(const BigInt& b);
    BigInt operator++(int);
    BigInt operator-(int b);
    BigInt operator+(int b);
    BigInt operator+(BigInt b);
    explicit operator long();
    explicit operator string();
private:
    vector<char> data;
    friend bool operator<(const BigInt a, const BigInt b);
    void fixData();
};


#endif //CECS282PROGRAM5_BIGINT_H
