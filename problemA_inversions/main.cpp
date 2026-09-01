// Problem A - Inversion Counter for Quality Control
//
// Technique: Divide & Conquer (modified merge sort).
//
// Idea:
//   An inversion is a pair (i, j) with i < j and A[i] > A[j].
//   Brute force checks all pairs -> O(n^2), too slow for n up to 2*10^5.
//   Instead, we count inversions while merge-sorting the array.
//   When merging two already-sorted halves L (left) and R (right):
//     - If L[i] <= R[j], no inversion involving L[i] and R[j] (or any
//       remaining element of R, since R is sorted, but that case is
//       handled on the R[j] side already accounted below).
//     - If L[i] > R[j], then L[i] and EVERY remaining element in L
//       (L[i], L[i+1], ..., L[end]) form an inversion with R[j], because
//       L is sorted ascending. That contributes (size of L - i) inversions
//       in one step, instead of counting them one by one.
//   Summing these contributions across all merge steps gives the total
//   inversion count in O(n log n).
//
// Correctness argument:
//   Every inversion (i, j) with i < j and A[i] > A[j] falls into exactly
//   one of three categories relative to the recursion: both indices in
//   the left half, both in the right half, or split across halves.
//   Same-half inversions are counted recursively (by induction on the
//   recursive calls). Split inversions are exactly the ones the merge
//   step counts, since at merge time the left half retains its original
//   relative order (still sorted ascending) and represents original
//   left-side positions, and likewise for the right half. Hence each
//   split inversion is counted exactly once, at the merge step where the
//   two elements first belong to sibling subarrays.
//
// Complexity:
//   Time:  T(n) = 2T(n/2) + O(n)  =>  O(n log n)   (standard merge sort
//          recurrence, Master theorem case 2)
//   Space: O(n) auxiliary array for merging + O(log n) recursion stack.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Merge step: merges a[l..m] and a[m+1..r] (inclusive), both sorted,
// and returns the number of split inversions found during the merge.
static ll mergeCount(vector<ll>& a, vector<ll>& buf, int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    ll inv = 0;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            buf[k++] = a[i++];
        } else {
            // a[i] > a[j]: all elements from i to m are > a[j]
            inv += (m - i + 1);
            buf[k++] = a[j++];
        }
    }
    while (i <= m) buf[k++] = a[i++];
    while (j <= r) buf[k++] = a[j++];
    for (int x = l; x <= r; x++) a[x] = buf[x];
    return inv;
}

static ll sortCount(vector<ll>& a, vector<ll>& buf, int l, int r) {
    if (l >= r) return 0;
    int m = l + (r - l) / 2;
    ll inv = 0;
    inv += sortCount(a, buf, l, m);
    inv += sortCount(a, buf, m + 1, r);
    inv += mergeCount(a, buf, l, m, r);
    return inv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> buf(n);
    ll inv = (n > 0) ? sortCount(a, buf, 0, n - 1) : 0;

    cout << inv << "\n";
    return 0;
}
