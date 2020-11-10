//
// Created by shawn on 11/2/20.
//

#include "BigInt.h"
#include <cmath>

BigInt::BigInt(int b) {
    data = vector<char>();
    if(b == 0) {
        data.push_back(0);
    }
    else {
        for (int i = b; i > 0; i = i / 10) {
            data.push_back(i % 10);
        }
    }
}

void BigInt::print() const {
    cout << *this;
}

BigInt::BigInt(const string& s) {
    for(int i = s.size() - 1; i >= 0; i--) {
        data.push_back(s[i] - '0');
    }
}

BigInt &BigInt::operator=(int b) {
    return *this = BigInt(b);
}

bool BigInt::operator<(const BigInt &b) {
    if(b.data.size() < data.size()) {
        return false;
    }
    else if(b.data.size() > data.size()) {
        return true;
    }
    else {
        for(int i = data.size() - 1; i >= 0; i--) {
            if(data.at(i) < b.data.at(i)) {
                return true;
            }
            else if(data.at(i) > b.data.at(i)) {
                return false;
            }
        }
        return false;
    }
}

bool BigInt::operator<=(const BigInt &b) {
    if(b.data.size() < data.size()) {
        return false;
    }
    else if(b.data.size() > data.size()) {
        return true;
    }
    else if(b.data.size() == data.size()){
        for(int i = data.size() - 1; i >= 0; i--) {
            if(data.at(i) < b.data.at(i)) {
                return true;
            }
            else if(data.at(i) > b.data.at(i)) {
                return false;
            }
        }
        return true;
    }
    else {
        cout << "uh..." << endl;
        return false;
    }
}

bool BigInt::operator>(const BigInt &b) {
    if(b.data.size() > data.size()) {
        return false;
    }
    else if(b.data.size() < data.size()) {
        return true;
    }
    else {
        for(int i = data.size(); i > 0; i--) {
            if(data.at(i) > b.data.at(i)) {
                return true;
            }
            else if(data.at(i) < b.data.at(i)) {
                return false;
            }
        }
        return false;
    }
}

bool BigInt::operator>=(const BigInt &b) {
    if(b.data.size() > data.size()) {
        return false;
    }
    else if(b.data.size() < data.size()) {
        return true;
    }
    else {
        for(int i = data.size(); i > 0; i--) {
            if(data.at(i) > b.data.at(i)) {
                return true;
            }
            else if(data.at(i) < b.data.at(i)) {
                return false;
            }
        }
        return true;
    }
}

BigInt BigInt::operator++(int){
    return *this = *this + 1;
}

bool BigInt::operator==(const BigInt& b) {
    return data == b.data;
}

BigInt BigInt::operator-(int b) {
    BigInt ret(*this);
    ret.data.at(0) -= b;
    ret.fixData();
    return ret;
}

BigInt BigInt::operator+(int b) {
    BigInt ret(*this);
    ret.data.at(0) += b;
    ret.fixData();
    return ret;
}

BigInt BigInt::operator+(BigInt b) {
    BigInt ret(*this);
    for(int i = 0; i < b.data.size(); i++) {
        ret.data.at(i) += b.data.at(i);
    }
    ret.fixData();
    return ret;
}

void BigInt::fixData() {
    bool fixed = false, first = true;
    while(fixed || first) {
        fixed = false;
        first = false;
        short j = data.size();
        for(int i = 0; i < data.size(); i++) {
            char *k = &data.at(i);
            if(data.at(i) < 0) {
                int diff = 0;
                while(data.at(i)< 0) {
                    data.at(i) += 10;
                    diff++;
                }
                while(data.size() <= i + 1) {
                    data.push_back(0);
                }
                data.at(i + 1) -= diff;
            }
            else if(data.at(i) > 9) {
                while(data.size() <= i + 1) {
                    data.push_back(0);
                }
                data.at(i + 1) += data.at(i) / 10;
                data.at(i) = data.at(i) % 10;
                fixed = true;
            }
        }
    }
}

bool operator<(const BigInt a, const BigInt b) {
    if(b.data.size() < a.data.size()) {
        return false;
    }
    else if(b.data.size() > a.data.size()) {
        return true;
    }
    else {
        for(int i = a.data.size(); i > 0; i--) {
            if(a.data.at(i) < b.data.at(i)) {
                return true;
            }
            else if(a.data.at(i) > b.data.at(i)) {
                return false;
            }
        }
        return false;
    }
}

BigInt::BigInt(const BigInt &b) {
    data = vector<char>(b.data);
}

BigInt::operator long() {
    long ret = 0;
    for(int i = 0; i < data.size(); i++) {
        ret += data.at(i) * pow(10, i);
    }
    return ret;
}

BigInt::operator string() {
    string ret;
    for(auto i = data.rbegin(); i < data.rend(); i++) {
        ret += to_string((short(*i)));
    }
    return ret;
}

ostream &operator<<(ostream &os, BigInt &b) {
    os << string(BigInt(b));
    return os;
}

ostream &operator<<(ostream &os, const BigInt &dt) {
    os << string(BigInt(dt));
    return os;
}

BigInt::BigInt() {
    data = vector<char>();
    data.push_back(0);
}
