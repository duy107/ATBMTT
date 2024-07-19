#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(a, b);
}
int oCoLit(int r0, int r1)
{
    vector<int> q(1000, 0);
    vector<int> s(1000, 0);
    vector<int> t(1000, 0);
    int r2 = -1;
    int i = 0;
    while (r2 != 0)
    {
        r2 = r0 % r1;
        q[i + 1] = r0 / r1;
        if (i == 0)
        {
            s[i] = 1;
            t[i] = 0;
        }
        else if (i == 1)
        {
            s[i] = 0;
            t[i] = 1;
        }
        else
        {
            s[i] = s[i - 2] - s[i - 1] * q[i - 1];
            t[i] = t[i - 2] - t[i - 1] * q[i - 1];
        }
        r0 = r1;
        r1 = r2;
        i++;
    }
    s[i] = s[i - 2] - s[i - 1] * q[i - 1];
    t[i] = t[i - 2] - t[i - 1] * q[i - 1];
    if (t[i] < 0)
        t[i] += 26;
    return t[i];
}
void maHoa(string text, string s){
    string res = "";
    int a = 17, b = 5;
    for(char c : s){
        if(c == ' '){
            res += ' ';
        }else if (islower(c)){
            res += (char) ((a*(c - 'a') + b) % 26 + 'a');
        }else{
            res += (char) ((a*(c - 'A') + b) % 26 + 'A');
        }
    }
    if(res == text){
        cout << "La ban ma cua TAURUS sau khi ma hoa.\n";
    }else{
        cout << "Khong phai ban ma cua TAURUS sau khi ma hoa.\n";
    }
}
void khoaGiaMa(int a, int b){
    cout << "Khoa gia ma la: (" << oCoLit(26, a) << ", " << b << ")\n";
}
int main()
{
    string text;
    fflush(stdin);
    getline(cin, text);
    maHoa(text, "TAURUS");
    khoaGiaMa(17, 5);
    system("pause");
}