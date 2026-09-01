// Problem B - Minimum Meeting Rooms (Scheduling)
//
// Technique: Greedy (event / sweep-line).
//
// Idea:
//   The minimum number of rooms needed equals the maximum number of
//   meetings that are simultaneously in progress at any instant.
//   We collect all start times and all end times separately, sort each,
//   then sweep through time using two pointers. Every start event
//   requires a room (rooms_in_use++); every end event that happens at
//   or before the current start frees a room (rooms_in_use--) BEFORE we
//   count the new start, respecting the rule that a meeting ending at
//   time t and another starting at time t do NOT overlap (same room OK).
//   We track the running maximum of rooms_in_use, which is the answer.
//
// Correctness (greedy-choice property):
//   Process events in time order. At any moment, rooms_in_use equals the
//   number of meetings whose interval currently contains that instant
//   (with the half-open convention [s, e) so back-to-back meetings don't
//   overlap). The peak of rooms_in_use over the whole timeline is a
//   lower bound on rooms needed (that many meetings are pairwise
//   overlapping at that instant, each needs its own room) AND an upper
//   bound (assigning rooms greedily as meetings start, reusing any room
//   freed by an ended meeting, never needs more than the peak). Hence
//   the peak is exactly the optimal answer.
//
// Complexity:
//   Time:  O(m log m) for sorting starts and ends, then O(m) sweep.
//   Space: O(m) for the two sorted arrays.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    vector<long long> starts(m), ends(m);
    for (int i = 0; i < m; i++) {
        cin >> starts[i] >> ends[i];
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;
    while (i < m) {
        if (starts[i] < ends[j]) {
            // a new meeting starts before the earliest ongoing one ends
            rooms++;
            maxRooms = max(maxRooms, rooms);
            i++;
        } else {
            // starts[i] >= ends[j]: a room is freed (end at t, start at t OK)
            rooms--;
            j++;
        }
    }

    cout << maxRooms << "\n";
    return 0;
}
