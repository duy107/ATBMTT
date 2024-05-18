#include <bits/stdc++.h>
using namespace std;
char c[] = "0123456789ABCDEF";
string convert(int natural, int b)
{
    string s = "";
    while (natural > 0)
    {
        s = c[natural % b] + s;
        natural /= b;
    }
    return s;
}
void convertMod(string &mod, int b, string &resMod)
{
    float tmp = 0.0;
    while (mod.find(".") != string::npos)
    {
        tmp = stof(mod);
        tmp = tmp * b;
        mod = to_string(tmp);
        if (mod.find(".") == string::npos)
        {
            resMod = resMod + mod;
        }
        else
        {
            resMod = resMod + (mod.substr(0, mod.find(".")));
        }
        if (mod.find(".") != string::npos)
        {
            tmp = tmp - stof(mod.substr(0, mod.find(".")));
            mod = "0" + mod.substr(mod.find("."));
        }
    }
}
int main()
{
    string s;
    int b;
    cin >> s >> b;
    // int natural = stoi(s.substr(0, s.find(".")));
    string mod = "0" + s.substr(s.find("."));
    string resMod = "";
    float tmp = 0.0;
    while (mod.substr(mod.find(".") + 1) != "000000")
    {
        tmp = stof(mod);
        tmp = tmp * b;
        mod = to_string(tmp);
        if (mod.find(".") == string::npos)
        {
            resMod = resMod + mod;
        }
        else
        {
            resMod = resMod + (mod.substr(0, mod.find(".")));
        }
        if (mod.find(".") != string::npos)
        {
            tmp = tmp - stof(mod.substr(0, mod.find(".")));
            mod = "0" + mod.substr(mod.find("."));
        }
    }
    cout << resMod << endl;
    system("pause");
}