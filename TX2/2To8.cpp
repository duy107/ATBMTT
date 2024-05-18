#include<bits/stdc++.h>
using namespace std;
char c[] = "0123456789ABCDEF";
string convertToB(int a, int b){
    string s = "";
    while(a > 0){
        s = c[a % b] + s;
        a /= b;
    }
    return s;
}
void convertTo10(string s, int a, int &res)
{
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        auto it = find(begin(c), end(c), s[i]);
        if (it != end(c))
        {
            res = res + (it - begin(c)) * pow(a, n - i - 1);
        }
        else
        {
            return;
        }
    }
}
int main(){
    // string s;
    // int a, b;
    // cin >> s >> a >> b;
    // int res = 0;
    // convertTo10(s, a, res);
    cout << convertToB(3, 2) << endl;
    system("pause");
}