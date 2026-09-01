# Algorithms Mini-Lab — Divide & Conquer / Greedy / Dynamic Programming

Three problems, each solved with a different algorithm design
technique (chosen based on problem structure, not stated up front):

| Folder                  | Problem                          | Technique used       |
|--------------------------|-----------------------------------|-----------------------|
| `problemA_inversions/`   | Inversion Counter                | Divide & Conquer      |
| `problemB_rooms/`        | Minimum Meeting Rooms             | Greedy                |
| `problemC_knapsack/`     | Budgeted Study Plan (0/1 Knapsack)| Dynamic Programming   |

Full write-up (pseudocode, worked examples, correctness arguments,
complexity analysis) is in [`report.md`](./report.md).

## Requirements
- C++17 compiler (`g++` recommended).

## Build & run — all problems

```bash
# Problem A
g++ -std=c++17 -O2 -Wall -Wextra -pedantic problemA_inversions/main.cpp -o problemA_inversions/main
./problemA_inversions/main < problemA_inversions/tests/test1_in.txt

# Problem B
g++ -std=c++17 -O2 -Wall -Wextra -pedantic problemB_rooms/main.cpp -o problemB_rooms/main
./problemB_rooms/main < problemB_rooms/tests/test1_in.txt

# Problem C
g++ -std=c++17 -O2 -Wall -Wextra -pedantic problemC_knapsack/main.cpp -o problemC_knapsack/main
./problemC_knapsack/main < problemC_knapsack/tests/test1_in.txt
```

Each subfolder also has its own `README.md` with problem-specific I/O
format, examples, and the list of tests in its `tests/` directory.

## Assumptions
- Input is always well-formed and respects the constraints given in the
  assignment (no input validation / error handling beyond what's
  needed for correctness).
- All arithmetic that could exceed 32 bits (inversion counts, knapsack
  values) uses `long long`.
- Problem B uses the half-open interval convention `[s, e)`: a meeting
  ending at `t` and one starting at `t` can share a room.

## Repository layout
```
problemA_inversions/
  main.cpp
  README.md
  tests/
problemB_rooms/
  main.cpp
  README.md
  tests/
problemC_knapsack/
  main.cpp
  README.md
  tests/
report.md
README.md
```
