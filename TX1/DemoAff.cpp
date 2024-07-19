#include <bits/stdc++.h>
using namespace std;
// chuyen chuoi ban da cho ve dang ma tran
void getMatrix(string s, int keyMatrix[][2])
{
    int k = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (islower(s[i]))
            {
                keyMatrix[i][j] = s[k++] % 92;
            }
            else
            {
                keyMatrix[i][j] = s[k++] % 65;
            }
        }
    }
}
// tao ma tran text
void getMessMatrix(string text, int messMatrix[][2])
{
    for (int i = 0; i < 2; i++)
    {
        if (islower(text[i]))
        {
            messMatrix[0][i] = text[i] % 92;
        }
        else
        {
            messMatrix[0][i] = text[i] % 65;
        }
    }
}
// ma hoa
void encrypt(int cipherMatrix[][2], int messMatrix[][2], int keyMatrix[][2])
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cipherMatrix[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                cipherMatrix[i][j] += messMatrix[i][k] * keyMatrix[k][j];
            }
            cipherMatrix[i][j] %= 26;
        }
    }
}
string hillCipher(string key, string text)
{
    int len = text.length() / 2;
    int index = 0;
    string res = "";
    while (len--)
    {
        string tmp = "";
        for (int i = 0; i < text.length() / 2; i++)
        {
            tmp += text[index++];
        }
        int keyMatrix[2][2];
        int messMatrix[1][2];
        int cipherMatrix[1][2];
        getMatrix(key, keyMatrix);
        getMessMatrix(tmp, messMatrix);
        encrypt(cipherMatrix, messMatrix, keyMatrix);
        for (int i = 0; i < 2; i++)
        {
            res += cipherMatrix[0][i] + 65;
        }
    }
    return res;
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
void khoaGiaMa(string s, int keyMaTrix[][2], int a[][2])
{
    getMatrix(s, keyMaTrix);
    // key: ma tran khoa
    int det = (keyMaTrix[0][0] * keyMaTrix[1][1] - keyMaTrix[0][1] * keyMaTrix[1][0]) % 26;
    int det_oColit = oCoLit(26, det);
    a[0][0] = keyMaTrix[1][1];
    a[1][1] = keyMaTrix[0][0];
    a[0][1] = -keyMaTrix[0][1] + 26;
    a[1][0] = -keyMaTrix[1][0] + 26;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            a[i][j] = (a[i][j] * det_oColit) % 26;
        }
    }
}
// nhan ma tran
void nhanMaTran(int banMa[][2], int khoaGiaMa[][2], int ketQua[][2])
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ketQua[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                ketQua[i][j] += banMa[i][k] * khoaGiaMa[k][j];
            }
            ketQua[i][j] %= 26;
        }
    }
}
// giai ma
string giaMa(string s, string banMa, int keyMatrix[][2])
{
    int a[2][2];
    khoaGiaMa(s, keyMatrix, a);
    int len = banMa.size() / 2;
    int index = 0;
    string res = "";
    while (len--)
    {
        string tmp = "";
        for(int i = 0; i < 2; i++){
            tmp += banMa[index++];
        }
        // dua ban ma ve ma tran
        int getMatrix[1][2];
        for (int i = 0; i < 2; i++)
        {
            getMatrix[0][i] = tmp[i] % 65;
        }
        int nhan[1][2];
        nhanMaTran(getMatrix, a, nhan);
        for (int i = 0; i < 2; i++)
        {
            res += nhan[0][i] + 'A';
        }
    }
    return res;
}
int main()
{
    int keyMatrix[2][2];
    string s = "DDCF";
    string text = "HELP";
    string banMa = hillCipher(s, text);
    cout << banMa << endl;
    cout << giaMa(s, banMa, keyMatrix) << endl;
    // int keyMatrix[2][2];
    // int a[2][2];
    // khoaGiaMa(s, keyMatrix, a);
    system("pause");
}