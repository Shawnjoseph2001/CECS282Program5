#include <iostream>
#include "BigInt.h"
#include <bits/stdc++.h>
#include <map>  // you will need this for the goldRabbits function
using namespace std;

//int goldRabbits(int);
static map<int, BigInt> rabbitMap;
BigInt goldRabbits(BigInt);
void pause() {cout << "Press Enter to continue..."; getchar();}

int main()
{
    rabbitMap = map<int, BigInt>();
    BigInt B1("123456789123456789123456789123456789");
    BigInt B2(B1);
    BigInt MAX(INT_MAX);
    cout << "B1:"<<B1<<"\nB2:"<<B2<<"\nMAX:"<<MAX<<endl;
    //pause();
    cout << "\nB1:";
    B1.print();
    cout << endl;
    //pause();

	for(BigInt i=0; i<=3000; i++)	// uncomment this
//    for(int i=0; i<=3000; i++)		// comment this out
    {
	    int z = 0;
        cout << "\ngoldRabbits("<< i <<") = " << goldRabbits(i);
    }
    pause();
    cout<< "\nThis is the value of goldRabbits(3000)\n\n";
    BigInt gR3000 =  goldRabbits(int(3000));
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
        cout << goldRabbits(n);
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
