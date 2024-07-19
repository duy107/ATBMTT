#include <bits/stdc++.h>
using namespace std;
int oCoLit(int r0, int r1)
{
    int q[1000], s[1000], t[1000];
    int r2 = -1, i = 0;
    while (r2 != 0)
    {
        r2 = r1 % r0;
        q[i + 1] = r1 / r0;
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
        r1 = r0;
        r0 = r2;
        i++;
    }
    s[i] = s[i - 2] - s[i - 1] * q[i - 1];
    t[i] = t[i - 2] - t[i - 1] * q[i - 1];
    if(t[i] < 0){
        t[i] = t[i] + 26;
    }
    return t[i];
}
int main()
{
    cout << oCoLit(8, 26) << endl;
    system("pause");
}