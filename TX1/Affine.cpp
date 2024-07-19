#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int oCoLit(int r0, int r1)
{
    vector<int> q(1000, 0);
    vector<int> s(1000, 0);
    vector<int> t(1000, 0); 
    int r2 = -1;
    int mod = r0;
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
    if(t[i] < 0) t[i] += mod;
    return t[i]; 
}
// ma hoa : y = (ax + b) mod n
string encrypt(string text, int a, int b)
{
    string banMa = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            banMa += text[i];
        }
        else if (islower(text[i]))
        {
            banMa += (char)((((a * (text[i] - 'a')) + b) % 26) + 'a');
        }
        else
        {
            banMa += (char)((((a * (text[i] - 'A')) + b) % 26) + 'A');
        }
    }
    return banMa;
}
// x = a^-1(y - b)
string decrypt(string banMa, int a, int b)
{
    string banRo;
    int x = oCoLit(a, 26);
    for (int i = 0; i < banMa.length(); i++)
    {
        int value = 0;
        if (banMa[i] == ' ')
        {
            banRo += banMa[i];
        }
        else if (islower(banMa[i]))
        {
            value = x * ((banMa[i] - 'a') - b);
            if (value < 0)
            {
                value = 26 + (value % 26);
            }
            banRo += (char)(value % 26 + 'a');
        }
        else
        {
            value = x * ((banMa[i] - 'A') - b);
            if (value < 0)
            {
                value = 26 + (value % 26);
            }
            banRo += (char)(value % 26 + 'A');
        }
    }
    return banRo;
}
int main()
{
    // int a, b;
    // string text;
    // do
    // {
    //     cout << "Nhap a: ";
    //     cin >> a;
    // } while (gcd(a, 26) != 1);
    // cout << "Nhap b: ";
    // cin >> b;
    // cin.ignore();
    // cout << "Nhap doan van ban can ma hoa: ";
    // getline(cin, text);
    // string banMa = encrypt(text, a, b);
    // cout << "Ban ma: " + banMa << endl;
    // cout << "Ban ro: " + decrypt(banMa, a, b) << endl; 
    cout << oCoLit(29, 8) << endl;
    system("pause");
}