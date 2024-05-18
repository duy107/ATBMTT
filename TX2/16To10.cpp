#include <bits/stdc++.h>
using namespace std;
char c[] = "0123456789ABCDEF";
void convertNatural(string natural, int a, int &resNa)
{
    int n = natural.length();
    for (int i = 0; i < n; i++)
    {
        auto it = find(begin(c), end(c), natural[i]);
        if (it != end(c))
        {
            resNa = resNa + (it - begin(c)) * pow(a, n - i - 1);
        }
        else
        {
            return;
        }
    }
}
void converMod(string mod, int a, float &resMod)
{
    int n = mod.length();
    for (int i = 0; i < n; i++)
    {
        auto it = find(begin(c), end(c), mod[i]);
        if (it != end(c))
        {
            resMod += (it - begin(c)) * pow(a, -i-1);
        }
    }
}
int main()
{
    string s;
    int a;
    cin >> s >> a;
    int resNa = 0;
    float resMod = 0.0;
    string natural = s.substr(0, s.find("."));
    string mod = s.substr(s.find(".") + 1);
    convertNatural(natural, a, resNa);
    converMod(mod, a, resMod);
    cout << fixed << setprecision(7) << (float) resNa + resMod << endl;
    system("pause");
}