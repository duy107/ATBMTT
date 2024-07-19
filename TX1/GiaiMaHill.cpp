#include <bits/stdc++.h>
using namespace std;
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
void dulMatrix(int textMatrix[][2], int ansMatrix[][2], int resMatrix[][2])
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            textMatrix[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                textMatrix[i][j] += ansMatrix[i][k] * resMatrix[k][j];
            }
            textMatrix[i][j] %= 26;
        }
    }
}
void decryptMatrix(int resMatrix[][2], int keyMatrix[][2])
{
    int det = abs(keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;
    int det_1 = oCoLit2(det, 26);
    // tinh ma tran nghich dao
    resMatrix[0][0] = keyMatrix[1][1] % 26;
    resMatrix[1][1] = keyMatrix[0][0] % 26;
    resMatrix[0][1] = (-keyMatrix[0][1] + 26) % 26;
    resMatrix[1][0] = (-keyMatrix[1][0] + 26) % 26;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            resMatrix[i][j] = (det_1 * resMatrix[i][j]) % 26;
        }
    }
}
string hill(string text, int keyMatrix[][2])
{
    string res = "";
    int p = text.length() / 2;
    int temp = 0;
    // ma tran giai ma
    int resMatrix[2][2];
    decryptMatrix(resMatrix, keyMatrix);
    while(p--){
        string ans = "";
        for(int i = 0; i < 2; i++){
            ans += text[temp];
            temp++;
        }
        int ansMatrix[1][2];
        for(int i = 0; i < 2; i++){
            if(isupper(ans[i])){
                ansMatrix[0][i] = int(ans[i]) - 65;
            }else{
                ansMatrix[0][i] = int(ans[i]) - 97;
            }
        }
        int textMatrix[1][2];
        dulMatrix(textMatrix, ansMatrix, resMatrix);
        // for(int i = 0; i < 2; i++){
        //     cout << textMatrix[0][i] << ' ';
        // }
        for(int i = 0; i < 2; i++){
            if(isupper(ans[i])){
                res += textMatrix[0][i] + 65;
            }else{
                res += textMatrix[0][i] + 97;
            }
        }
        // break;
    }
    return res;
}
int main()
{
    int keyMatrix[2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> keyMatrix[i][j];
        }
    }
    string banMa;
    cin.ignore();
    cout << "Nhap ban ma: ";
    getline(cin, banMa);
    cout << hill(banMa, keyMatrix) << endl;
    system("pause");
}