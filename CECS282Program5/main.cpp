#include <iostream>
#include <bits/stdc++.h>
#include <map>  // you will need this for the goldRabbits function
using namespace std;

//int goldRabbits(int);
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
    friend bool operator<(const BigInt a, const BigInt b);
    void fixData();
    vector<char> data;
};


#endif //CECS282PROGRAM5_BIGINT_H

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
    cout << string(BigInt(*this)) << endl;
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
        for(int i = 0; i < data.size(); i++) {
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
        ret += to_string(*i);
    }
    return ret;
}

ostream &operator<<(ostream &os, const BigInt &bp) {
    BigInt b(bp);
    if(string(b).length() > 12) {
        os << string(b).at(0) << "." << string(b).substr(1, 12) << "e" << string(b).length();
    }
    else {
        os << string(b);
    }
    return os;
}

BigInt::BigInt() {
    data = vector<char>();
    data.push_back(0);
}
static map<int, BigInt> rabbitMap;
BigInt goldRabbits(BigInt);
int goldRabbits(int);
void pause() {cout << "Press Enter to continue..."; getchar();}

int main()
{
    BigInt B1("123456789123456789123456789123456789");
    BigInt B2(B1);
    BigInt MAX(INT_MAX);
    cout << "B1:"<<B1<<"\nB2:"<<B2<<"\nMAX:"<<MAX<<endl;
    pause();
    cout << "\nB1:";
    B1.print();
    cout << endl;
    pause();
    set<int> v = set<int>({0, 1, 2, 3, 4, 5, 6, 7, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 2994, 2995, 2996, 2997, 2998, 2999, 3000});
	for(BigInt i=0; i<=3000; i++)	// uncomment this
//    for(int i=0; i<=3000; i++)		// comment this out
    {
	    if(v.contains((long)i)) {
            cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
        }}
    pause();

    cout<< "\nThis is the value of goldRabbits(3000)\n\n";
    BigInt gR3000 =  goldRabbits(BigInt(3000));
    gR3000.print();

    pause();

    int n = 500;
    try{

        cout << "The value of goldRabbits(n) is:"<<goldRabbits(n)<<endl;
    }
    catch(string error)
    {
        cout << error << endl;
        cout << "Transitioning to BigInt\n";
        cout << goldRabbits(BigInt(n));
    }

    pause();
}

// Modify this function so that it accepts BigInt as input parameter and returns a BigInt
// and uses a map for speed
BigInt goldRabbits(BigInt n)
{

    if (n==0) { // base case
        rabbitMap[0] = 1;
        return 1;
    }
    if(n == 1) {
        rabbitMap[1] = 1;
        return 1;
    }
    else {
        BigInt first, second;
        if (rabbitMap.contains((long(n) - 1))) {
            first = rabbitMap.find(long(n) - 1)->second;
        }
        else {
            first = goldRabbits(n - 1);
            rabbitMap[long(n) - 1] = first;
        }
        if (rabbitMap.contains(long(n) - 2)) {
            second = rabbitMap.find(long(n) - 2)->second;
        }
        else {
            second = goldRabbits(n - 2);
            rabbitMap[long(n - 2)] = second;
        }
        return first + second;
    }
}

int goldRabbits(int n)
{
    if (n==0 || n==1)						// base case
        return 1;
    else {
        int gr1 = goldRabbits(n - 1);
        int gr2 = goldRabbits(n - 2);// general case
        int gs = gr1 + gr2;
        if (gs < gr1 || gs < gr2) {
            throw "Overflow Error – goldRabbits overflowed using " + to_string(n);
        }
        return gs;
    }
}


