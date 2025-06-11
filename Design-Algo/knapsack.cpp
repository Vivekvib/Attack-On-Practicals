#include <iostream>
#include <vector>
using namespace std;

int knapsackMem(vector<int> &weight, vector<int> &value, int W, int idx, vector<vector<int>> &dp)
{
    // Base case
    if (idx == 0)
    {
        if (weight[idx] <= W)
        {
            return value[idx];
        }
        else
        {
            return 0;
        }
    }

    // Performing Memoization
    if (dp[idx][W] != -1)
        return dp[idx][W];

    int include = 0;
    if (weight[idx] <= W)
        include = value[idx] + knapsackMem(weight, value, W - weight[idx], idx - 1, dp);

    int exclude = 0 + knapsackMem(weight, value, W, idx - 1, dp);

    return dp[idx][W] = max(include, exclude);
}

int main()
{
    int n;
    cout << "Enter the number of items: ";
    cin >> n;
    int capacity;
    cout << "Enter the maximum weight of the bag: ";
    cin >> capacity;

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter the weight of the items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i];
    }

    cout << "Enter the values of each item: ";
    for (int i = 0; i < n; i++)
    {
        cin >> value[i];
    }

    vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));

    int ans = knapsackMem(weight, value, capacity, n - 1, dp);
    cout << "Maximum value in knapsack: " << ans << endl;

    return 0;
}
