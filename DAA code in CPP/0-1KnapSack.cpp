#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


// Function to solve 0/1 Knapsack problem using Dynamic Programming
int knapsackDP(int W, vector<int> &weights, vector<int> &values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}


// Structure for a node in the search tree
struct Node {
    int level;
    int profit;
    int weight;
    float bound;
};

// Comparator for sorting items by value/weight ratio
bool compare(int i, int j, const vector<int>& values, const vector<int>& weights) {
    double r1 = (double)values[i] / weights[i];
    double r2 = (double)values[j] / weights[j];
    return r1 > r2;
}

// Function to calculate bound of the node
float bound(Node u, int n, int W, const vector<int>& weights, const vector<int>& values, const vector<int>& index) {
    if (u.weight >= W) return 0;
    int profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while (j < n && totweight + weights[index[j]] <= W) {
        totweight += weights[index[j]];
        profit_bound += values[index[j]];
        j++;
    }

    if (j < n) profit_bound += (W - totweight) * (double)values[index[j]] / weights[index[j]];

    return profit_bound;
}

// Function to solve the 0/1 Knapsack problem using Branch and Bound
int knapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<int> index(n);
    for (int i = 0; i < n; i++) index[i] = i;

    sort(index.begin(), index.end(), [&](int i, int j) {
        return compare(i, j, values, weights);
    });

    queue<Node> Q;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    Q.push(u);
    int maxProfit = 0;

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

        // Taking the current item
        v.weight = u.weight + weights[index[v.level]];
        v.profit = u.profit + values[index[v.level]];

        if (v.weight <= W && v.profit > maxProfit) maxProfit = v.profit;

        v.bound = bound(v, n, W, weights, values, index);
        if (v.bound > maxProfit) Q.push(v);

        // Not taking the current item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, weights, values, index);
        if (v.bound > maxProfit) Q.push(v);
    }

    return maxProfit;
}


int main() {



    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    vector<int> weights(n), values(n);


    cout << "Enter the weights and values of the items:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> weights[i] >> values[i];     
    }

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;

    int maxProfit1 = knapsackDP(W, weights, values, n);

    cout << "Maximum profit using DP: " << maxProfit1 << endl;

    cout << "Maximum profit using Branch & Bound: " << knapsack(W, weights, values, n) << endl;


   




    return 0;
}
