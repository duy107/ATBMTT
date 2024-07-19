#include <bits/stdc++.h>
using namespace std;
void backtrack(vector<int> &nums, int currSum, int sum, int index, int &minSum, vector<bool> &v, vector<bool> &used)
{
    if (minSum > abs(sum - 2 * currSum))
    {
        minSum = abs(sum - 2 * currSum);
        for (int i = 0; i < nums.size(); i++)
        {
            v[i] = used[i];
        }
    }
    for (int i = index; i < nums.size(); i++)
    {

        used[i] = true;
        backtrack(nums, currSum + nums[i], sum, i + 1, minSum, v, used);
        used[i] = false;
    }
}
int main()
{
    vector<int> nums = {2, 2, 2, 2, 1, 1};
    vector<bool> used(nums.size(), false);
    int sum = accumulate(nums.begin(), nums.end(), 0);
    vector<bool> v(nums.size(), false);
    int minSum = INT_MAX;
    backtrack(nums, 0, sum, 0, minSum, v, used);
    for (int i = 0; i < nums.size(); i++)
    {
        if (v[i])
            cout << nums[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < nums.size(); i++)
    {
        if (!v[i])
            cout << nums[i] << ' ';
    }
    cout << endl;
    system("pause");
}