#include <bits/stdc++.h>
using namespace std;
// tao ma tran khoa
void getKeyMatrix(string s, int keyMatrix[][3])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = s[k++] % 65;
        }
    }
}
void getMessMatrix(string text, int messMatrix[][1])
{
    for (int i = 0; i < 3; i++)
    {
        messMatrix[i][0] = text[i] % 65;
    }
}
void encrypt(int cipherMatrix[][1], int keyMatrix[][3], int messMatrix[][1])
{
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 1; k++)
        {
            cipherMatrix[i][k] = 0;
            for (int j = 0; j < 3; j++)
            {
                cipherMatrix[i][k] += keyMatrix[i][j] * messMatrix[j][k];
            }
            cipherMatrix[i][k] = cipherMatrix[i][k] % 26;
        }
    }
}
void HillCipher(string key, string text)
{
    int keyMatrix[3][3];
    int messMatrix[3][1];
    int cipherMatrix[3][1];
    getKeyMatrix(key, keyMatrix);
    getMessMatrix(text, messMatrix);
    encrypt(cipherMatrix, keyMatrix, messMatrix);
    string res = "";
    for(int i = 0; i < 3; i++){
        res += cipherMatrix[i][0] + 'A';
    }
    cout << res << endl;
}
int main()
{
    string key = "HILLMAGIC";
    string text = "GFG";
    HillCipher(key, text);
    system("pause");
}