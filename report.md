# Report — Algorithms Mini-Lab

Language: C++17. All programs read from stdin and write to stdout, no
interactive input, 64-bit integers used wherever counts/values can
exceed 32-bit range.

---

## Problem A — Inversion Counter for Quality Control

### Problem summary
Given an array `A` of `n` integers, count the number of pairs `(i, j)`
with `i < j` and `A[i] > A[j]` (inversions). With `n` up to `2·10^5`,
the naive `O(n^2)` pairwise check is too slow, so an `O(n log n)`
algorithm is required.

### Algorithm idea
**Technique: Divide & Conquer** (modified merge sort).

Split the array in half, recursively count inversions fully contained
in the left half and fully contained in the right half, then count
"split" inversions — pairs where the larger element is in the left half
and the smaller is in the right half — during the merge step. Because
each half is already sorted when merging, whenever a right-half element
`R[j]` is smaller than the current left-half element `L[i]`, *every*
remaining element of `L` (from `i` to the end of the left half) is also
greater than `R[j]` (left half is sorted ascending). So all of those
inversions are counted in a single `O(1)` addition instead of one at a
time.

### Pseudocode
```
function sortCount(a, l, r):
    if l >= r: return 0
    m = (l + r) / 2
    inv = sortCount(a, l, m)
    inv += sortCount(a, m+1, r)
    inv += mergeCount(a, l, m, r)
    return inv

function mergeCount(a, l, m, r):
    i = l, j = m+1, k = l, inv = 0
    while i <= m and j <= r:
        if a[i] <= a[j]:
            buf[k++] = a[i++]
        else:
            inv += (m - i + 1)   # a[i..m] all > a[j]
            buf[k++] = a[j++]
    copy remaining a[i..m] into buf
    copy remaining a[j..r] into buf
    copy buf[l..r] back into a
    return inv
```

### Correctness (sketch)
Every inversion is either fully inside the left half, fully inside the
right half, or "split" across the two halves. Same-half inversions are
counted by induction on the recursive calls. Split inversions are
exactly what `mergeCount` counts: at merge time, `L` still holds
(in sorted order) the original left-half elements and `R` the original
right-half elements, so `a[i] > a[j]` with `i` in `L` and `j` in `R`
corresponds one-to-one to an original split inversion, and the bulk
addition `(m - i + 1)` counts all of them for that `j` without
double-counting (each `j` is advanced exactly once).

### Example run
Input: `A = [2, 4, 1, 3, 5]`

- Split into `[2, 4]` and `[1, 3, 5]`.
- `[2, 4]` → 0 inversions (already sorted), stays `[2, 4]`.
- `[1, 3, 5]` → split into `[1]` and `[3, 5]`, both sorted, 0
  inversions, merge → `[1, 3, 5]`, 0 inversions.
- Merge `[2, 4]` and `[1, 3, 5]`:
  - compare 2 vs 1: `2 > 1` → add `(2 - 0)= 2` inversions (2 and 4 both
    beat 1), take 1.
  - compare 2 vs 3: `2 <= 3` → take 2.
  - compare 4 vs 3: `4 > 3` → add `1` inversion (4 beats 3), take 3.
  - remaining: take 5.
  - merge inversions = 2 + 1 = 3.
- Total = 0 + 0 + 3 = **3**, matching the expected output.

### Complexity
- **Time:** `T(n) = 2T(n/2) + O(n)` ⇒ `O(n log n)` by the Master
  theorem (case 2). Each of the `O(log n)` levels of recursion does
  `O(n)` total work merging.
- **Space:** `O(n)` for the auxiliary merge buffer, plus `O(log n)`
  recursion stack depth.

---

## Problem B — Minimum Meeting Rooms (Scheduling)

### Problem summary
Given `m` meetings `(s_i, e_i)`, find the minimum number of rooms
needed so that no room hosts two overlapping meetings. A meeting ending
at time `t` and another starting at time `t` do not conflict.

### Algorithm idea
**Technique: Greedy** (event sweep-line).

The minimum number of rooms equals the maximum number of meetings that
are simultaneously "in progress" at any point in time. Separate all
start times and all end times into two arrays, sort each independently,
then sweep chronologically with two pointers: whenever the next event
is a start that occurs before the earliest pending end, allocate a room
(increment a counter); otherwise, an end event happens first (or at the
same time), freeing a room (decrement the counter). Track the maximum
value the counter ever reaches.

### Pseudocode
```
function minRooms(meetings[1..m]):
    starts = sort([s_i for each meeting])
    ends   = sort([e_i for each meeting])
    i = 0, j = 0, rooms = 0, maxRooms = 0
    while i < m:
        if starts[i] < ends[j]:
            rooms += 1
            maxRooms = max(maxRooms, rooms)
            i += 1
        else:
            rooms -= 1
            j += 1
    return maxRooms
```

### Correctness (greedy-choice property)
At any instant, the number of rooms in use equals the number of
meetings whose interval currently covers that instant (using the
half-open convention `[s, e)`, which is exactly why `starts[i] < ends[j]`
— not `<=` — is the condition to open a new room). The peak value of
this count over the whole timeline is:
- a **lower bound**: at that peak instant, that many meetings pairwise
  overlap, so that many distinct rooms are unavoidably required;
- an **upper bound**: allocating a room to each meeting as it starts,
  reusing any room that has just been vacated, never requires more
  rooms than the peak, because the counter never exceeds it by
  construction.

Hence the peak — exactly what the sweep computes — is optimal.

### Example run
Input: meetings `(0,30), (5,10), (15,20)`

- `starts = [0, 5, 15]`, `ends = [10, 20, 30]`.
- `i=0,j=0`: `starts[0]=0 < ends[0]=10` → rooms=1, maxRooms=1, i=1.
- `i=1,j=0`: `starts[1]=5 < ends[0]=10` → rooms=2, maxRooms=2, i=2.
- `i=2,j=0`: `starts[2]=15 < ends[0]=10`? No (15 ≥ 10) → rooms=1, j=1.
- `i=2,j=1`: `starts[2]=15 < ends[1]=20` → rooms=2, maxRooms stays 2, i=3.
- `i=3=m` → loop ends.
- Output: **2**, matching the expected output.

### Complexity
- **Time:** `O(m log m)` for sorting the two arrays of size `m`; the
  sweep itself is `O(m)`.
- **Space:** `O(m)` for the two sorted start/end arrays.

---

## Problem C — Budgeted Study Plan (0/1 Knapsack Variant)

### Problem summary
Given `n` modules, each with `time[i]` and `value[i]`, and a total time
budget `T`, choose a subset of modules (each usable at most once) whose
total time does not exceed `T`, maximizing total value. Brute-force
subset enumeration is `O(2^n)`, infeasible for `n` up to 2000.

### Algorithm idea
**Technique: Dynamic Programming** (0/1 knapsack, bottom-up with a
rolling 1-D array).

Let `dp[c]` be the best value achievable with total time at most `c`,
using the modules processed so far. For each module `i`, update `dp`
for capacities `c` from `T` down to `time[i]`:
`dp[c] = max(dp[c], dp[c - time[i]] + value[i])`. Iterating `c`
**downward** ensures `dp[c - time[i]]` still reflects the state
*before* module `i` was considered, so module `i` cannot be counted
twice — this is what makes it "0/1" rather than an unbounded knapsack.

### Pseudocode
```
function knapsack(n, T, time[1..n], value[1..n]):
    dp = array of size T+1, all zero
    for i = 1 to n:
        if time[i] > T: continue
        for c = T downto time[i]:
            dp[c] = max(dp[c], dp[c - time[i]] + value[i])
    return dp[T]
```

### Correctness (DP invariant)
Claim: after processing modules `1..i`, `dp[c]` holds the optimal value
achievable from a subset of modules `1..i` with total time `<= c`, for
every `c` in `[0, T]`.

- **Base case** (`i = 0`): no modules chosen, `dp[c] = 0` for all `c`.
- **Inductive step**: consider module `i+1`. Either it is excluded from
  the optimal subset (value stays `dp[c]`, unchanged from step `i`), or
  it is included, which requires `c >= time[i+1]` and contributes
  `dp_before[c - time[i+1]] + value[i+1]`, where `dp_before` is the
  table *before* processing module `i+1` — by the induction hypothesis
  this is the optimal value for modules `1..i` within the reduced
  budget. Taking the max of the two options gives the optimal value
  for modules `1..i+1`. Processing `c` in descending order guarantees
  `dp[c - time[i+1]]` read during this pass is still `dp_before`, so
  the invariant is preserved exactly, and each module contributes at
  most once to any given subset.

By induction, `dp[T]` after all `n` modules is the optimal answer.

### Example run
Input: modules `(3,4), (4,5), (7,10)`, `T = 10`.

- After module 1 (t=3,v=4): `dp[3..10]` all become 4 (each capacity
  ≥ 3 can afford it), `dp[0..2] = 0`.
- After module 2 (t=4,v=5): for `c=10..4`, try `dp[c-4]+5`. E.g.
  `dp[7] = max(dp[7]=4, dp[3]+5=4+5=9) = 9`. `dp[10] = max(4, dp[6]+5)`;
  `dp[6]` after module 1 was 4, so `dp[10] = max(4, 9) = 9`.
- After module 3 (t=7,v=10): for `c=10..7`, try `dp[c-7]+10`.
  `dp[10] = max(9, dp[3]+10) = max(9, 4+10) = 14`.
- `dp[10] = 14`, matching the expected output (modules 1 and 3: time
  `3+7=10`, value `4+10=14`).

### Complexity
- **Time:** `O(n · T)` — `n` modules, each doing an `O(T)` inner loop
  over capacities.
- **Space:** `O(T)` for the 1-D rolling `dp` array (a full 2-D
  `n × T` table is not needed since only item reconstruction, which is
  not required by this task, would need it).

---

## Summary table

| Problem | Technique          | Time complexity | Space complexity |
|---------|---------------------|------------------|-------------------|
| A       | Divide & Conquer    | O(n log n)       | O(n)              |
| B       | Greedy              | O(m log m)       | O(m)              |
| C       | Dynamic Programming | O(n·T)           | O(T)              |

## Testing notes
Each problem's `tests/` folder includes at least 3 input/output pairs
covering the statement's sample plus edge cases:
- **A:** already sorted, reverse sorted, all-duplicates, and a
  single-element array.
- **B:** back-to-back (non-overlapping) meetings, fully overlapping
  meetings, nested intervals, and many identical start times.
- **C:** nothing fits (all times exceed T), multiple competing choices,
  and a tight budget where items fit exactly.

All three solutions were additionally stress-tested at the stated
upper constraint sizes (`n = 2·10^5` for A, `m = 2·10^5` for B,
`n = 2000, T = 5000` for C) and complete in well under a second each,
confirming the complexity analysis above holds in practice.
