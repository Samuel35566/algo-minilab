// Problem C - Budgeted Study Plan (0/1 Knapsack Variant)
//
// Technique: Dynamic Programming.
//
// Idea:
//   Classic 0/1 knapsack: n items (modules), each with a time cost and a
//   value, capacity T. We want max total value without exceeding T,
//   each item used at most once. Brute force subsets are O(2^n),
//   infeasible for n up to 2000. Instead define:
//       dp[c] = maximum value achievable using time budget exactly <= c,
//               considering the items processed so far.
//   Transition per item i (time t_i, value v_i), iterating c from T down
//   to t_i (descending order is what enforces the "0/1" / at-most-once
//   property, since it prevents reusing item i within the same pass):
//       dp[c] = max(dp[c], dp[c - t_i] + v_i)
//   After processing all n items, dp[T] is the maximum achievable value
//   using at most T hours in total (dp is non-decreasing in c, so dp[T]
//   already accounts for using less than T if that is optimal).
//
// Correctness argument (DP invariant):
//   Invariant: after processing items 1..i, dp[c] holds the optimal
//   value achievable using a subset of items 1..i with total time <= c,
//   for every c in [0, T]. Base case (i = 0): dp[c] = 0 for all c (no
//   items chosen). Inductive step: for item i+1, either it is excluded
//   (value stays dp[c] from before) or included (only possible if
//   c >= t_{i+1}, contributing dp[c - t_{i+1}] + v_{i+1}, where
//   dp[c - t_{i+1}] is by induction hypothesis the optimal value for
//   items 1..i within the remaining budget). Taking the max of these two
//   options preserves the invariant. Iterating c downward when updating
//   in-place guarantees dp[c - t_{i+1}] still refers to the "before item
//   i+1" value, so item i+1 is not counted twice (0/1 property holds).
//
// Complexity:
//   Time:  O(n * T)   (n items, each doing an O(T) inner loop)
//   Space: O(T)       (1-D rolling DP array; O(n*T) would be needed only
//                       if we had to reconstruct the exact chosen items
//                       via a full 2-D table, which is not required here)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T;
    if (!(cin >> n >> T)) return 0;

    vector<int> t(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> v[i];

    vector<ll> dp(T + 1, 0);

    for (int i = 0; i < n; i++) {
        if (t[i] > T) continue; // item can never fit, skip
        for (int c = T; c >= t[i]; c--) {
            dp[c] = max(dp[c], dp[c - t[i]] + v[i]);
        }
    }

    ll best = dp[T];
    cout << best << "\n";
    return 0;
}
