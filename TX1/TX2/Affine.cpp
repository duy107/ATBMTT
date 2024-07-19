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
    int r2 = -1;
    vector<int> q(1000, 0), s(1000, 0), t(1000, 0);
    int i = 0;
    while (r2 != 0)
    {
        r2 = r0 % r1;
        q[i + 1] = r0 / r1;
        if (i == 0)
        {
            s[i] = 1;
            t[0] = 0;
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
        i++;
        r0 = r1;
        r1 = r2;
    }
    s[i] = s[i - 2] - s[i - 1] * q[i - 1];
    t[i] = t[i - 2] - t[i - 1] * q[i - 1];
    if(t[i] < 0) t[i] += 26;
    return t[i];
}
void khoa(int &a, int &b)
{
    do
    {
        cout << "Nhap a: ";
        cin >> a;
        cout << "Nhap b: ";
        cin >> b;
        if(gcd(a, 26) != 1){
            cout << "Nhap lai.\n";
        }
    } while (gcd(a, 26) != 1);
}
void khoaGiaiMa(int a, int b){
    cout << "Khoa gia ma: (" << oCoLit(26, a) << ", " << b << ")" << endl;
}
string encrypt(string text1, string text2, int a, int b){
    string res = "";
    for(char c : text1){
        if(islower(c)){
            res += ((a*(c - 'a') + b) % 26 + 'a');
        }else{
            res += ((a*(c - 'A') + b) % 26 + 'A');
        }
    }
    return res;
    // if(res.compare(text2) == 0){
    //     cout << "Ban nhap dung.\n";
    // }else{
    //     cout << "Ban nhap sai.\n";
    //}
}
string decrypt(string banMa, int a, int b){
    int x = oCoLit(26, a);
    string res = "";
    for(int i = 0; i < banMa.size(); i++){
        int value = 0;
        if(banMa[i] == ' '){
            banMa += ' ';
        }else if(islower(banMa[i])){
            value = (x * ((banMa[i] % 97 ) - b));
            if(value < 0){
                value += 26;
            }
            res += value % 26 + 97; 
        }else{
            value = (x * ((banMa[i] % 65) - b));
            if(value < 0){
                value += 26;
            }
            res += value % 26 + 65;
        }
    }
    return res;
}
int main()
{
    int a, b;
    khoa(a, b);
    cin.ignore();
    string text1, text2;
    cout << "Nhap text1: ";
    getline(cin, text1);
    cout << "Nhap text2: ";
    getline(cin, text2);
    khoaGiaiMa(a, b);
    string banMa = encrypt(text1, text2, a, b);
    cout << banMa << endl;
    cout << decrypt(banMa, a, b) << endl;
    system("pause");
}