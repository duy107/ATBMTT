#include <bits/stdc++.h>
using namespace std;
int oCoLit(int r0, int r1)
{
    vector<int> q(1000, 0), s(1000, 0), t(1000, 0);
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
        return t[i] + 26;
    return t[i];
}
void nhap(int &a, int &b, int &c, int &d)
{
    cout << "Nhap a: ";
    cin >> a;
    cout << "Nhap b: ";
    cin >> b;
    cout << "Nhap c: ";
    cin >> c;
    cout << "Nhap d: ";
    cin >> d;
}
void khoaGiaiMa(int a, int b, int c, int d, int keyMatrix[][2])
{
    int det = abs((a * c - b * d)) % 26;
    int det_oCoLit = oCoLit(26, det);
    if (det_oCoLit != 1)
    {
        cout << "Khong ton tai khoa giai ma.\n";
    }
    else
    {
        keyMatrix[0][0] = d % 26;
        keyMatrix[1][1] = a % 26;
        keyMatrix[0][1] = (-b + 26) % 26;
        keyMatrix[1][0] = (-c + 26) % 26;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                keyMatrix[i][j] = (keyMatrix[i][j] * det_oCoLit) % 26;
            }
        }
    }
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         cout << keyMatrix[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
}
void getMessMatrix(string text1, int messMatrix[][2])
{
    for (int i = 0; i < 2; i++)
    {
        if (islower(text1[i]))
        {
            messMatrix[0][i] = text1[i] % 97;
        }
        else
        {
            messMatrix[0][i] = text1[i] % 65;
        }
    }
}
void nhanMaTran(int result[][2], int messMatrix[][2], int keyMatrix[][2])
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                result[i][j] += messMatrix[i][k] * keyMatrix[k][j];
            }
            result[i][j] %= 26;
        }
    }
}
string encrypt(string text1, string text2, int keyMatrix[][2])
{
    int len = text1.length() / 2;
    int index = 0;
    string res = "";
    while (len--)
    {
        string tmp = "";
        for (int i = 0; i < 2; i++)
        {
            tmp += text1[index++];
        }
        int messMatrix[1][2];
        int result[1][2];
        getMessMatrix(tmp, messMatrix);
        nhanMaTran(result, messMatrix, keyMatrix);
        for (int i = 0; i < 2; i++)
        {
            if (islower(tmp[i]))
            {
                res += result[0][i] + 'a';
            }
            else
            {
                res += result[0][i] + 'A';
            }
        }
    }
    return res;
}
string decrypt(int a, int b, int c, int d, string banMa, int keyMatrix[][2])
{
    khoaGiaiMa(a, b, c, d, keyMatrix);
    string res = "";
    int len = banMa.length() / 2;
    int index = 0;
    while (len--)
    {
        string tmp = "";
        for (int i = 0; i < 2; i++)
        {
            tmp += banMa[index++];
        }
        int resMatrix[1][2];
        int messMatrix[1][2];
        getMessMatrix(tmp, messMatrix);
        nhanMaTran(resMatrix, messMatrix, keyMatrix);
        for (int i = 0; i < 2; i++)
        {
            if (islower(tmp[i]))
            {
                res += resMatrix[0][i] + 'a';
            }
            else
            {
                res += resMatrix[0][i] + 'A';
            }
        }
    }
    return res;
}
int main()
{
    int a, b, c, d;
    nhap(a, b, c, d);
    // int keyMatrix[2][2];
    // int key[2][2] = {{a, b},
    //                  {c, d}};
    // khoaGiaiMa(a, b, c, d, keyMatrix);
    cin.ignore();
    string text1, text2;
    cout << "Nhap xau 1: "; fflush(stdin);
    getline(cin, text1);
    cout << "Nhap xau 2: "; fflush(stdin);
    getline(cin, text2);
    // string banMa = encrypt(text1, text2, key);
    // cout << banMa << endl;
    // cout << decrypt(a, b, c, d, banMa, key);
    // cout << endl;
    cout << text1 << endl << text2 << endl;
    system("pause");
}