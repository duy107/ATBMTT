#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return (b, a % b);
}
string binary(int x){
    if(x == 0) return "000";
    string bin = "";
    int tmp = x;
    while(x > 0){
        bin = char('0' + x % 2) + bin;
        x/= 2;
    }
    if(tmp == 1) bin = "00" + bin;
    if(tmp == 2) bin = "0" + bin;
    return bin;
}
int main()
{
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    system("pause");
}