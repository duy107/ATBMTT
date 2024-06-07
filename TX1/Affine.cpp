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
int oCoLit2(int b, int n)
{
    int ri = n;
    int rin = b;
    int tmpR, tmpT;
    int ti_1 = 0, ti = 1;
    int tin;
    while (rin > 1)
    {
        tin = ti_1 - ti * (ri / rin);
        tmpR = rin;
        rin = ri - rin * (ri / rin);
        ri = tmpR;
        tmpT = ti;
        ti = tin;
        ti_1 = tmpT;
    }

    if (tin < 0)
    {
        tin = tin + n;
    }
    return tin;
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
string decrypt(string banMa, int a, int b) {
    string banRo;
    int x = oCoLit2(a, 26);
    for (int i = 0; i < banMa.length(); i++) {
        int value = 0;
        if (banMa[i] == ' ') {
            banRo += banMa[i];
        } else if (islower(banMa[i])) {
            value = x * ((banMa[i] - 'a') - b);
            if (value < 0) {
                value = 26 + (value % 26);
            }
            banRo += (char)(value % 26 + 'a');
        } else {
            value = x * ((banMa[i] - 'A') - b);
            if (value < 0) {
                value = 26 + (value % 26);
            }
            banRo += (char)(value % 26 + 'A');
        }
    }
    return banRo;
}
int main()
{
    int a, b;
    string text;
    do
    {
        cout << "Nhap a: ";
        cin >> a;
    } while (gcd(a, 26) != 1);
    cout << "Nhap b: ";
    cin >> b;
    cin.ignore();
    cout << "Nhap doan van ban can ma hoa: ";
    getline(cin, text);
    string banMa = encrypt(text, a, b);
    cout << "Ban ma: " + banMa << endl;
    cout << "Ban ro: " + decrypt(banMa, a, b) << endl;
    system("pause");
}