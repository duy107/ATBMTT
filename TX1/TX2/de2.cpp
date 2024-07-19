#include <bits/stdc++.h>
using namespace std;
void getMessMatrix(string text, int messMatrix[][2])
{
    for (int i = 0; i < 2; i++)
    {
        messMatrix[0][i] = text[i] % 65;
    }
}
void encrypt(int res[][2], int messMatrix[][2], int k[][2])
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            res[i][j] = 0;
            for (int h = 0; h < 2; h++)
            {
                res[i][j] += messMatrix[i][h] * k[h][j];
            }
            res[i][j] %= 26;
        }
    }
}
void hillCipher(string text, string s, int k[][2])
{
    int len = s.length() / 2;
    int index = 0;
    string res = "";
    while (len--)
    {
        string tmp = "";
        for (int i = 0; i < 2; i++)
        {
            tmp += s[index++];
        }
        int messMatrix[1][2];
        getMessMatrix(tmp, messMatrix);
        int result[1][2];
        encrypt(result, messMatrix, k);
        for (int i = 0; i < 2; i++)
        {
            res += result[0][i] + 65;
        }
    }
    if (res == text)
    {
        cout << "Ban nhap dung.\n";
    }
    else
    {
        cout << "Ban nhap sai.\n";
    }
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
void khoaGiaMa(int k[][2])
{
    int res[2][2];
    int det = k[0][0] * k[1][1] - k[0][1] * k[1][0];
    det %= 26;
    int det_oCoLit = oCoLit(26, det);
    res[0][0] = k[1][1] % 26;
    res[1][1] = k[0][0] % 26;
    res[0][1] = (-k[0][1] + 26) % 26;
    res[1][0] = (-k[1][0] + 26) % 26;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            res[i][j] = (res[i][j] * det_oCoLit) % 26;
        }
    }
    cout << "Khoa giai ma: \n";
    for (auto &t : res)
    {
        for (int c : t)
        {
            cout << c << ' ';
        }
        cout << endl;
    }
}
int main()
{
    int k[2][2] = {{12, 5},
                   {3, 7}};
    string text;
    fflush(stdin);
    getline(cin, text);
    hillCipher("", "HARD", k);
    khoaGiaMa(k);
    system("pause");
}